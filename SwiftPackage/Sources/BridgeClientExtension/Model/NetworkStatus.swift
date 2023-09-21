// Created 2/22/23
// swift-tools-version:5.0

import Foundation
import Network

/// Option set for the current network status.
public struct NetworkStatus : OptionSet, CaseIterable, Hashable {
    public let rawValue: Int
    public init(rawValue: Int) {
        self.rawValue = rawValue
    }
    
    /// Network connectivity is unknown
    public static let unknown: NetworkStatus = .init(rawValue: 0)
    /// The network is connected
    public static let connected: NetworkStatus = .init(rawValue: 1 << 1)
    /// The network is not connected
    public static let notConnected: NetworkStatus = .init(rawValue: 1 << 2)
    /// The user has disabled cellular
    public static let cellularDenied: NetworkStatus = [.notConnected, .init(rawValue: 1 << 3)]
    
    public static var allCases: [NetworkStatus] {
        [.unknown, .connected, .notConnected, .cellularDenied]
    }
    
    public var stringValue: String {
        switch self {
        case .connected:
            return "connected"
        case .notConnected:
            return "notConnected"
        case .cellularDenied:
            return "cellularDenied"
        case .unknown:
            return "unknown"
        default:
            return String(rawValue, radix: 2)
        }
    }
}

/// A mockable wrapper for network monitoring.
public class NetworkMonitor : ObservableObject {
    
    /// Current network status.
    @Published public fileprivate(set) var networkStatus: NetworkStatus = .unknown {
        didSet {
            self.didChangeHandler?(networkStatus)
        }
    }
    
    /// Set a block to be called when the network status changes.
    public var didChangeHandler: ((NetworkStatus) -> Void)?
    
    public init(didChangeHandler: ((NetworkStatus) -> Void)? = nil) {
        self.didChangeHandler = didChangeHandler
    }

    fileprivate let networkMonitoringQueue = DispatchQueue(label: "org.sagebase.NetworkConnectivityMonitor.\(UUID())")
    fileprivate var networkMonitor: NWPathMonitor?
    
    deinit {
        networkMonitor?.cancel()
    }
    
    /// Cancel network monitoring, after which point no more path updates will be delivered.
    public func cancel() {
        networkMonitor?.cancel()
        networkMonitor = nil
        networkStatus = .unknown
    }

    /// Start monitoring network status. If status is already being monitored then multiple
    /// calls to start will be ignored.
    public func startIfNeeded() {
        guard networkMonitor == nil else { return }
        let networkMonitor = NWPathMonitor()
        self.networkMonitor = networkMonitor
        networkMonitor.pathUpdateHandler = { [weak self] path in
            guard let strongSelf = self else { return }
            DispatchQueue.main.async {
                switch path.status {
                case .unsatisfied:
                    if #available(iOS 14.2, *), path.unsatisfiedReason == .cellularDenied {
                        strongSelf.networkStatus = .cellularDenied
                    } else {
                        strongSelf.networkStatus = .notConnected
                    }
                case .satisfied:
                    strongSelf.networkStatus = .connected
                default:
                    strongSelf.networkStatus = .unknown
                }
            }
        }
        networkMonitor.start(queue: networkMonitoringQueue)
    }
}

/// A mock network monitor that can be used to set the network status. This can be used in SwiftUI Preview
/// or in unit tests.
public class MockNetworkMonitor : NetworkMonitor {
    
    override public func startIfNeeded() {
        // Do not start network monitoring - this is a mock.
    }
    
    public func setNetworkStatus(_ newStatus: NetworkStatus, withDelay delay: DispatchTimeInterval? = nil) {
        guard let delay = delay else {
            if Thread.isMainThread {
                self.networkStatus = newStatus
            } else {
                DispatchQueue.main.sync {
                    self.networkStatus = newStatus
                }
            }
            return
        }
        self.networkMonitoringQueue.asyncAfter(deadline: .now().advanced(by: delay)) {
            DispatchQueue.main.async {
                self.networkStatus = newStatus
            }
        }
    }
}

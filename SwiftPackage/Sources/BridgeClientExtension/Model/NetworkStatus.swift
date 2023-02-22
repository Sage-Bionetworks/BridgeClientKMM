// Created 2/22/23
// swift-tools-version:5.0

import Foundation

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

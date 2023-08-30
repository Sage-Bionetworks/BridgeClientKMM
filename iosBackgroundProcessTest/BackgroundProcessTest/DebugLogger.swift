// Created 8/29/23
// swift-tools-version:5.0

import Foundation

/// Fake logger that is used to test background processing
final class Logger {
    
    static func log(severity: LogSeverity, tag: LoggingTag = .bridgeClientUI, message: String, metadata: [String : Any]? = nil) {
        logToConsole(severity: severity, tag: tag, message: message, error: nil)
    }
    
    static func log(tag: LoggingTag = .bridgeClientUI, error: Error, message: String? = nil, metadata: [String : Any]? = nil) {
        logToConsole(severity: .error, tag: tag, message: message, error: error)
    }
    
    private static func logToConsole(severity: LogSeverity, tag: LoggingTag, message: String?, error: Error?) {
        print("[\(tag.rawValue):\(Date())] \(severity.name.uppercased()): \(message ?? "")")
        if let error = error {
            debugPrint(error)
        }
    }
}

struct LoggingTag : RawRepresentable, Hashable, ExpressibleByStringLiteral {
    
    public let rawValue: String
    
    public init(rawValue: String) {
        self.rawValue = rawValue
    }
    
    public init(stringLiteral value: StringLiteralType) {
        self.rawValue = value
    }
    
    public static let upload: LoggingTag = "Upload"
    public static let bridgeClientUI: LoggingTag = "BridgeClientUI"
}

enum LogSeverity : String, CaseIterable {
    case debug, info, warn, error
    
    var name: String {
        self.rawValue.uppercased()
    }
    
    var ordinal : Int {
        Self.allCases.firstIndex(of: self)!
    }
}

extension LogSeverity : Comparable {
    public static func < (lhs: LogSeverity, rhs: LogSeverity) -> Bool {
        lhs.ordinal < rhs.ordinal
    }
}

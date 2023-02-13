// Created 2/9/23
// swift-tools-version:5.0

import Foundation
import BridgeClient

public protocol IOSLogWriter : NativeLogWriter {
    var identifier: String { get }
    func setUserId(_ userId: String?)
}

public struct LoggingTag : RawRepresentable, Hashable, ExpressibleByStringLiteral {
    
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

public final class Logger {
    
    /// The level of logging to submit to the log writer.
    public static var logLevel: LogSeverity = .info
    
    /// The default logging level for printing to the debug console.
    public static var defaultDebugLevel: LogSeverity = .debug
    
    /// Allows raising or lowering the debug level for a given logging tag.
    public static var debugLevel: [LoggingTag : LogSeverity] = [:]
    
    static var logWriter: IOSLogWriter?
    
    /// The setter for the log writer. This is used to wire up both native logging and the logging in the Kotlin XCFramework.
    /// This method should be called only once during app launch. Subsequent calls will be ignored.
    ///
    /// - Parameter newValue: The log writer to use for this app.
    public static func setLogWriter(_ newValue: IOSLogWriter) {
        // Only allow setting the log writer once
        guard logWriter == nil else { return }
        self.logWriter = newValue
        BridgeClient.IOSLogger().addLogWriter(logWriter: newValue)
    }
    
    /// Use this method to log informational messages that might be useful if an error is later broadcast.
    ///
    /// - Parameters:
    ///   - severity: The logging level of the message.
    ///   - tag: A tag that can be used to parse where the message is coming from.
    ///   - message: The message to send.
    public static func log(severity: LogSeverity, tag: LoggingTag = .bridgeClientUI, message: String) {
        logToConsole(severity: severity, tag: tag, message: message, error: nil)
        guard severity >= logLevel else { return }
        logWriter?.log(severity: severity, message: message, tag: tag.rawValue, error: nil)
    }
    
    /// Log an error. This is not performant and the Crashlytics implementation for this is quite chatty. Only log errors if this is
    /// a non-fatal exception that is unexpected. This method requires an error and automatically sets the severity to `.error`.
    ///
    /// - Parameters:
    ///   - tag: A tag that can be used to parse where the error is coming from.
    ///   - error: The error to send to logging services.
    ///   - message: An optional message to send with the error.
    public static func log(tag: LoggingTag = .bridgeClientUI, error: Error, message: String? = nil) {
        logToConsole(severity: .error, tag: tag, message: message, error: error)
        logWriter?.log(severity: .error, message: message, tag: tag.rawValue, error: error)
    }
    
    private static func logToConsole(severity: LogSeverity, tag: LoggingTag, message: String?, error: Error?) {
        #if DEBUG
        // If debugging, then print to the console based on the default log level.
        let logLevel = self.debugLevel[tag] ?? self.defaultDebugLevel
        #else
        // If production, then check if there is a log writer wired up and if so, only print errors to the console.
        let logLevel = (self.logWriter == nil) ? self.logLevel : .error
        #endif
        guard severity >= logLevel else { return }
        print("[\(tag.rawValue)] \(severity.name.uppercased()): \(message ?? "")")
        if let error = error {
            debugPrint(error)
        }
    }
}

extension LogSeverity : Comparable {
    public static func < (lhs: LogSeverity, rhs: LogSeverity) -> Bool {
        lhs.ordinal < rhs.ordinal
    }
}


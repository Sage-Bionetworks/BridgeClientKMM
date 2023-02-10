//
//  ValidationError.swift
//  
//

import Foundation

/// Errors that can be thrown while building documentation.
public enum ValidationError : Error, CustomNSError {
    
    /// A `NULL` value was returned when expectation was that the result will be non-nil.
    case unexpectedNull(String)
    
    case unknown
    
    /// The domain of the error.
    public static var errorDomain: String {
        return "BridgeClient.ValidationErrorDomain"
    }
    
    /// The error code within the given domain.
    public var errorCode: Int {
        switch(self) {
        case .unexpectedNull(_):
            return -1
        case .unknown:
            return -2
        }
    }
    
    /// The user-info dictionary.
    public var errorUserInfo: [String : Any] {
        let description: String
        switch(self) {
        case .unexpectedNull(let str): description = str
        case .unknown: description = "Unknown error"
        }
        return [NSLocalizedFailureReasonErrorKey: description]
    }
}

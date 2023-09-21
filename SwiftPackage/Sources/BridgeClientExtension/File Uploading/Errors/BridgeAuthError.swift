// Created 7/26/23
// swift-tools-version:5.0

import Foundation

struct BridgeAuthError : Error, CustomNSError {
    static var errorDomain: String { "BridgeClientUI.AuthError" }
    
    let errorCode: Int
    let message: String
    
    init(errorCode: Int = -1, message: String = "Not logged in to an account.") {
        self.errorCode = errorCode
        self.message = message
    }
    
    var errorUserInfo: [String : Any] {
        [NSLocalizedFailureReasonErrorKey: message]
    }
}

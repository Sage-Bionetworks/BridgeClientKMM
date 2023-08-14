// Created 7/26/23
// swift-tools-version:5.0

import Foundation

struct BridgeHttpError : Error, CustomNSError {
    static var errorDomain: String { "BridgeClientUI.HttpError" }
    
    let errorCode: Int
    let message: String
    
    var errorUserInfo: [String : Any] {
        [NSLocalizedFailureReasonErrorKey: message]
    }
}

// Created 7/26/23
// swift-tools-version:5.0

import Foundation

struct BridgeUploadFailedError : Error, CustomNSError {
    static var errorDomain: String { "BridgeClient.UploadFailedError" }
    
    let errorCode: Int
    let message: String
    
    static let backgroundTaskTimeout = BridgeUploadFailedError(errorCode: -57, message: "Failed to finish background task before timeout")
    
    init(errorCode: Int = -1, message: String = "Bridge upload failed") {
        self.errorCode = errorCode
        self.message = message
    }
    
    var errorUserInfo: [String : Any] {
        [NSLocalizedFailureReasonErrorKey: message]
    }
}

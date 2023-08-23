// Created 7/26/23
// swift-tools-version:5.0

import Foundation

struct BridgeUploadFailedError : Error, CustomNSError {
    static var errorDomain: String { "BridgeClient.UploadFailedError" }
    
    let category: Category
    let message: String
    
    var errorCode: Int {
        category.rawValue
    }
    
    enum Category : Int {
        case unknown = -1
        case backgroundTaskTimeout = -51
        case wrongHandler = -52
        case fileFailure = -53
    }
    
    var errorUserInfo: [String : Any] {
        [NSLocalizedFailureReasonErrorKey: message]
    }
}

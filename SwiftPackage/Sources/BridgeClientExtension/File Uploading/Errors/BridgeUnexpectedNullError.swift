// Created 7/26/23
// swift-tools-version:5.0

import Foundation

struct BridgeUnexpectedNullError : Error, CustomNSError {
    static var errorDomain: String { "BridgeClientUI.UnexpectedNullError" }
    
    let category: Category
    let message: String
    
    var errorCode: Int {
        category.rawValue
    }
    
    var errorUserInfo: [String : Any] {
        [NSLocalizedFailureReasonErrorKey: message]
    }
    
    enum Category : Int {
        case missingFile = -100
        case wrongType = -101
        case missingAttributes = -102
        case missingIdentifier = -103
        case empty = -104
        case invalidURL = -105
        case corruptData = -106
        case missingMetadata = -107
        case missingMapping = -108
        case notFound = -109
        case duplicateCall = -110
    }
}

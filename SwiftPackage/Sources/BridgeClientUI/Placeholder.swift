//
//  Placeholder.swift
//  
//

import Foundation


struct BridgeUploaderInfoV2 : Codable {
    var files: [FileInfoEntry] = []
     
    let item: String
    let dataFilename: String
    let appName: String
    let appVersion: String
    let phoneInfo: String
    let format: FormatVersion
    
    init(schemaIdentifier: String, dataFilename: String = "answers.json") {
        self.item = schemaIdentifier
        self.dataFilename = dataFilename
        self.format = .v2_generic
        let platformContext = PlatformContext()
        self.phoneInfo = platformContext.deviceInfo
        self.appName = platformContext.appName
        self.appVersion = platformContext.appVersion
    }
    
    enum FormatVersion : String, Codable {
        case v1_legacy, v2_generic
    }
    
    struct FileInfoEntry : Codable {
        let filename: String
        let timestamp: Date
        let contentType: String
    }
}

//
//  AbstractResultArchive.swift
//

import Foundation
import BridgeArchiver
import JsonModel

fileprivate let kBridgeV2InfoFilename             = "info.json"

@available(*, deprecated, message: "Use `AbstractDataArchive` or `StudyDataUploadArchive` instead.")
open class AbstractResultArchive : DataArchive {

    /// The schema info for this archive.
    public let schemaIdentifier: String?
    public let schemaRevision: Int?
    
    /// Is the archive a top-level archive?
    public let isPlaceholder: Bool
    
    /// A special-cased file where the values are pulling into the Synapse table without requiring the filename as part of the column name.
    public var dataFilename: String = "answers.json"
    
    let v2Format: BridgeUploaderInfoV2.FormatVersion
    
    /// The schedule identifier is the `NativeScheduledAssessment.instanceGuid`
    public var scheduleIdentifier: String? {
        return schedule?.instanceGuid
    }

    public init?(identifier: String,
                 schemaIdentifier: String? = nil,
                 schemaRevision: Int? = nil,
                 dataGroups: [String]? = nil,
                 schedule: AssessmentScheduleInfo? = nil,
                 isPlaceholder: Bool = false,
                 v2Format: BridgeUploaderInfoV2.FormatVersion = .v2_generic) {
        self.schemaIdentifier = schemaIdentifier
        self.schemaRevision = schemaRevision
        self.isPlaceholder = isPlaceholder
        self.v2Format = v2Format
        super.init(identifier: identifier, schedule: schedule, dataGroups: dataGroups)
    }
    
    /// Close the archive with optional metadata from a task result.
    public final func completeArchive(createdOn: Date, with metadata: [String : Any]? = nil) throws {
        
        // If the archive is empty and this is a placeholder archive, then exit early without
        // adding the metadata.
        if self.isEmpty() && isPlaceholder { return }
        
        try addMetadata(metadata ?? [:])
        try addBridgeV2Info()
        
        isCompleted = true
    }
    
    private func addBridgeV2Info() throws {
        let platformConfig = PlatformConfigImpl()
        let info = BridgeUploaderInfoV2(files: files,
                                        dataFilename: dataFilename,
                                        format: v2Format,
                                        item: schemaIdentifier ?? identifier,
                                        schemaRevision: schemaRevision,
                                        appName: platformConfig.appName,
                                        appVersion: platformConfig.appVersionName,
                                        phoneInfo: platformConfig.deviceInfo)
        let encoder = JSONEncoder()
        let data = try encoder.encode(info)
        try addFile(data: data, filepath: kBridgeV2InfoFilename)
    }
}

public struct BridgeUploaderInfoV2 : Encodable {
    
    let files: [FileEntry]
    let dataFilename: String
    let format: FormatVersion
    let item: String
    let schemaRevision: Int?
    let appName: String
    let appVersion: String
    let phoneInfo: String
    
    public enum FormatVersion : String, Codable {
        case v1_legacy, v2_generic
    }
}

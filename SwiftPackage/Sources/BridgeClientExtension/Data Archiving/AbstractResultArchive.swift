//
//  AbstractResultArchive.swift
//

import Foundation
import BridgeArchiver
import JsonModel

fileprivate let kBridgeV2InfoFilename             = "info.json"
fileprivate let kMetadataFilename                 = "metadata.json"
fileprivate let kScheduledActivityGuidKey         = "scheduledActivityGuid"
fileprivate let kScheduleIdentifierKey            = "scheduleIdentifier"
fileprivate let kScheduledOnKey                   = "scheduledOn"
fileprivate let kScheduledActivityLabelKey        = "activityLabel"
fileprivate let kDataGroups                       = "dataGroups"

public final class StudyDataUploadArchive : AbstractResultArchive {
}

/// An abstract class for archiving result data.
open class AbstractResultArchive : DataArchive {
    
    /// The schedule used to start this task (if any).
    public let schedule: AssessmentScheduleInfo?
    
    /// The schema info for this archive.
    public let schemaIdentifier: String?
    public let schemaRevision: Int?
    
    /// Is the archive a top-level archive?
    public let isPlaceholder: Bool
    
    /// A special-cased file where the values are pulling into the Synapse table without requiring the filename as part of the column name.
    public var dataFilename: String = "answers.json"
    
    /// The data groups that are set as metadata on this archive.
    public let dataGroups: [String]?
    
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
        self.dataGroups = dataGroups
        self.schedule = schedule
        self.isPlaceholder = isPlaceholder
        self.v2Format = v2Format
        super.init(identifier: identifier)
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
    
    private func addMetadata(_ metadata: [String : Any]) throws {
        // Set up the activity metadata.
        var metadataDictionary: [String : Any] = metadata
        
        // Add metadata values from the schedule.
        if let schedule = self.schedule {
            metadataDictionary[kScheduledActivityGuidKey] = schedule.instanceGuid
            metadataDictionary[kScheduleIdentifierKey] = schedule.session.instanceGuid
            metadataDictionary[kScheduledOnKey] = ISO8601TimestampFormatter.string(from: schedule.session.scheduledOn)
            metadataDictionary[kScheduledActivityLabelKey] = schedule.assessmentInfo.label
        }
        
        // Add the current data groups.
        if let dataGroups = dataGroups {
            metadataDictionary[kDataGroups] = dataGroups.joined(separator: ",")
        }
        
        let data = try JSONSerialization.data(withJSONObject: metadataDictionary, options: [.prettyPrinted, .withoutEscapingSlashes])
        try addFile(data: data, filepath: kMetadataFilename, createdOn: Date(), contentType: "json")
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

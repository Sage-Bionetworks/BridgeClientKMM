//
//  ArchiveBuilder.swift
//  
//

import Foundation
import JsonModel
import ResultModel

public protocol ArchiveBuilder : AnyObject {
    
    /// A unique identifier that can be used to retain this task until it is complete.
    var uuid: UUID { get }

    /// An identifier that can be logging reports.
    var identifier: String { get }

    /// Build an archive asyncronously and return the result.
    func buildArchive() async throws -> DataArchive
    
    /// Cleanup after.
    func cleanup() async throws
}

public protocol ResultArchiveBuilder : ArchiveBuilder {
    
    /// A timestamp for tracking the archive.
    var startedOn: Date { get }
    
    /// A timestamp for tracking the archive.
    var endedOn: Date { get }
    
    /// Any adherence data that should be added to the adherence record. Limit 64kb.
    var adherenceData: JsonSerializable? { get }
}

open class JsonResultArchiveBuilder : ResultArchiveBuilder {
    
    public let uuid: UUID = .init()
    public let json: Data
    public let fileInfo: FileInfo
    public let startedOn: Date
    
    public var endedOn: Date { fileInfo.timestamp }
    public var adherenceData: JsonSerializable? { nil }
    
    /// The archive that backs this builder.
    let archive: StudyDataUploadArchive
    
    public var identifier: String {
        archive.identifier
    }
    
    public init?(json: Data, filename: String, schema: URL, timestamp: Date = Date(), startedOn: Date? = nil, schedule: AssessmentScheduleInfo? = nil, schemaIdentifier: String? = nil) {
        self.json = json
        self.startedOn = startedOn ?? timestamp
        self.fileInfo = .init(filename: filename, timestamp: timestamp, contentType: "application/json", identifier: schedule?.assessmentInfo.identifier, jsonSchema: schema)
        guard let archive = StudyDataUploadArchive(identifier: schedule?.assessmentInfo.identifier ?? schemaIdentifier ?? filename,
                   schemaIdentifier: schemaIdentifier,
                   schedule: schedule)
        else {
            return nil
        }
        self.archive = archive
    }
        
    public func buildArchive() async throws -> DataArchive {

        // Add the JSON file
        try archive.addFile(data: json, filepath: fileInfo.filename, createdOn: fileInfo.timestamp, contentType: fileInfo.contentType)
        
        // Close the archive.
        let metadata = ArchiveMetadata(files: [fileInfo])
        let metadataDictionary = try metadata.jsonEncodedDictionary()
        try archive.completeArchive(createdOn: Date(), with: metadataDictionary)
        
        return archive
    }
    
    public func cleanup() async throws {
        // Do nothing - A single json file result does not support output directory cleanup.
    }
}

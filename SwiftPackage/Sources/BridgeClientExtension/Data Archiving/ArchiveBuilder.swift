//
//  ArchiveBuilder.swift
//  
//

import Foundation
import JsonModel
import ResultModel

/// A simple archive builder to use when uploading a single json file that may not
/// implement the `AssessmentResult` protocol.
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
    
    @available(*, deprecated, message: "Bridge Exporter V1 no longer supported - schema identifier and revision are ignored.")
    public convenience init?(json: Data, filename: String, schema: URL, timestamp: Date = Date(), startedOn: Date? = nil, schedule: AssessmentScheduleInfo? = nil, schemaIdentifier: String?) {
        self.init(json: json, filename: filename, schema: schema, timestamp: timestamp, startedOn: startedOn)
    }
    
    public init?(json: Data, filename: String, schema: URL, timestamp: Date = Date(), startedOn: Date? = nil, schedule: AssessmentScheduleInfo? = nil) {
        guard let archive = StudyDataUploadArchive(identifier: schedule?.assessmentInfo.identifier ?? filename, schedule: schedule)
        else {
            return nil
        }
        self.json = json
        self.startedOn = startedOn ?? timestamp
        self.fileInfo = .init(filename: filename, timestamp: timestamp, contentType: "application/json", identifier: schedule?.assessmentInfo.identifier, jsonSchema: schema)
        self.archive = archive
    }
    
    /// Override to add additional files to the archive.
    open func additionalFiles() throws -> [(data: Data, fileInfo: FileInfo)] {
        []
    }
        
    public final func buildArchive() async throws -> DataArchive {

        // Add the JSON file.
        try archive.addFile(data: json, fileInfo: fileInfo)
        
        /// Any additional files to add to the archive.
        let files = try additionalFiles()
        try files.forEach {
            try archive.addFile(data: $0.data, fileInfo: $0.fileInfo)
        }
        
        // Close the archive.
        try archive.completeArchive()
        
        return archive
    }
    
    public func cleanup() async throws {
        // Do nothing - A single json file result does not support output directory cleanup.
    }
}

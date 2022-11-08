//
//  ResultCollectionArchiveBuilder.swift
//  

import Foundation
import JsonModel
import ResultModel

public protocol ResultCollectionArchivable : FileArchivable {
    var identifier: String { get }
    var startedOn: Date { get }
    var endedOn: Date { get }
    var associatedFiles: [FileResultObject]? { get }
    
    func buildAdherenceData() throws -> JsonSerializable?
}

public class ResultCollectionArchiveBuilder : ResultArchiveBuilder {
    
    public let uuid: UUID
    public let adherenceData: JsonSerializable?
    public var startedOn: Date { collection.startedOn }
    public var endedOn: Date { collection.endedOn }
    
    private let collection: ResultCollectionArchivable
    private let outputDirectory: URL?
    private var manifest = Set<FileInfo>()
    
    /// The archive that backs this builder.
    let archive: StudyDataUploadArchive
    
    public var identifier: String {
        archive.identifier
    }

    public init?(_ collection: ResultCollectionArchivable, outputDirectory: URL?, schedule: AssessmentScheduleInfo? = nil, schemaIdentifier: String? = nil, schemaRevision: Int? = nil) throws {
        self.collection = collection
        self.uuid = .init()
        self.adherenceData = try collection.buildAdherenceData()
        self.outputDirectory = outputDirectory
        guard let archive = StudyDataUploadArchive(identifier: collection.identifier,
                                                   schemaIdentifier: schemaIdentifier ?? collection.identifier,
                                                   schemaRevision: schemaRevision,
                                                   schedule: schedule)
        else {
            return nil
        }
        self.archive = archive
    }

    public func cleanup() async throws {
        try outputDirectory.map {
            try FileManager.default.removeItem(at: $0)
        }
    }
    
    public func buildArchive() async throws -> DataArchive {

        // Add the files
        try addFile(collection)
        try collection.associatedFiles?.forEach {
            try addFile($0)
        }

        // Close the archive.
        let metadata = ArchiveMetadata(files: Array(manifest))
        let metadataDictionary = try metadata.jsonEncodedDictionary()
        try archive.completeArchive(createdOn: Date(), with: metadataDictionary)
        
        return archive
    }

    func addFile(_ fileArchivable: FileArchivable) throws {
        guard let (manifestInfo, data) = try fileArchivable.buildArchivableFileData(at: nil)
        else {
            return
        }
        try archive.addFile(data: data, filepath: manifestInfo.filename, createdOn: manifestInfo.timestamp, contentType: manifestInfo.contentType)
        manifest.insert(manifestInfo)
    }
}

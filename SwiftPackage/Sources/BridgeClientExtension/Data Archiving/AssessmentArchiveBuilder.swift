//
//  AssessmentArchiveBuilder.swift
//  
//

import Foundation
import JsonModel
import ResultModel

open class AssessmentArchiveBuilder : ResultArchiveBuilder {

    /// The result to be processed for archive and upload.
    public let assessmentResult: AssessmentResult
    
    /// File URL for the directory in which generated data files that are referenced using `FileResult`
    /// may be included. Asynchronous actions with recorders (and potentially steps) can save data to
    /// files during the progress of the task. This property specifies where such data was being written to
    /// allow the archive to delete the output directory once the results have been archived and encrypted
    /// for upload.
    let outputDirectory: URL?
    
    /// The archive that backs this builder.
    let archive: StudyDataUploadArchive
    
    public var identifier: String {
        archive.identifier
    }
    
    public init?(_ assessmentResult: AssessmentResult,
                 schedule: AssessmentScheduleInfo? = nil,
                 adherenceData: JsonSerializable? = nil,
                 outputDirectory: URL? = nil,
                 schemaIdentifier: String? = nil,
                 schemaRevision: Int? = nil,
                 dataGroups: [String]? = nil,
                 v2Format: BridgeUploaderInfoV2.FormatVersion = .v2_generic) {
        self.assessmentResult = assessmentResult
        self.adherenceData = adherenceData
        self.outputDirectory = outputDirectory
        guard let archive = StudyDataUploadArchive(identifier: assessmentResult.identifier,
                                                   schemaIdentifier: schemaIdentifier ?? assessmentResult.schemaIdentifier,
                                                   schemaRevision: schemaRevision,
                                                   dataGroups: dataGroups,
                                                   schedule: schedule,
                                                   v2Format: v2Format)
        else {
            return nil
        }
        self.archive = archive
    }
    
    public var uuid: UUID { assessmentResult.taskRunUUID }
    public var startedOn: Date { assessmentResult.startDate }
    public var endedOn: Date { assessmentResult.endDate }
    public private(set) var adherenceData: JsonSerializable?
    
    public func cleanup() async throws {
        try outputDirectory.map {
            try FileManager.default.removeItem(at: $0)
        }
    }
    
    public func buildArchive() async throws -> DataArchive {

        // Iterate through all the results within this collection and add if they are `FileArchivable`.
        try addBranchResults(assessmentResult)
        
        // For backwards compatibility and adherence, add an "answers.json" dictionary.
        if !answers.isEmpty {
            let data = try JSONSerialization.data(withJSONObject: answers, options: [.prettyPrinted, .withoutEscapingSlashes, .sortedKeys])
            let manifestInfo = FileInfo(filename: "answers.json", timestamp: assessmentResult.endDate, contentType: "application/json")
            try archive.addFile(data: data, filepath: manifestInfo.filename, createdOn: manifestInfo.timestamp, contentType: manifestInfo.contentType)
            manifest.insert(manifestInfo)
        }
        
        // Add the top-level assessment if desired.
        if let (data, manifestInfo) = try assessmentResultFile() {
            try archive.addFile(data: data, filepath: manifestInfo.filename, createdOn: manifestInfo.timestamp, contentType: manifestInfo.contentType)
            manifest.insert(manifestInfo)
        }
        
        // Close the archive.
        let metadata = ArchiveMetadata(files: Array(manifest))
        let metadataDictionary = try metadata.jsonEncodedDictionary()
        try archive.completeArchive(createdOn: Date(), with: metadataDictionary)
        
        return archive
    }
    
    private var manifest = Set<FileInfo>()
    private var answers: [String : JsonSerializable] = [:]
    
    private func addBranchResults(_ branchResult: BranchNodeResult, _ stepPath: String? = nil) throws {
        try recursiveAddFiles(branchResult.stepHistory, stepPath)
        if let asyncResults = branchResult.asyncResults {
            try recursiveAddFiles(asyncResults, stepPath)
        }
    }
    
    private func recursiveAddFiles(_ results: [ResultData], _ stepPath: String? = nil) throws {
        try results.forEach {
            try recursiveAdd($0, stepPath)
        }
    }
    
    private func recursiveAdd(_ result: ResultData, _ stepPath: String? = nil) throws {
        let pathSuffix = stepPath.map { "\($0)/" } ?? ""
        let path = "\(pathSuffix)\(result.identifier)"
        
        if let branchResult = result as? BranchNodeResult {
            try addBranchResults(branchResult, path)
        }
        else if let collectionResult = result as? CollectionResult {
            try recursiveAddFiles(collectionResult.children, path)
        }
        else if let fileArchivable = result as? FileArchivable,
                let (fileInfo, data) = try fileArchivable.buildArchivableFileData(at: stepPath),
                let manifestInfo = manifestFileInfo(for: fileArchivable, fileInfo: fileInfo) {
            try archive.addFile(data: data, filepath: manifestInfo.filename, createdOn: manifestInfo.timestamp, contentType: manifestInfo.contentType)
            manifest.insert(manifestInfo)
        }
        else if let answer = result as? AnswerResult,
                let value = answer.jsonValue {
            answers[answer.identifier] = value.jsonObject()
        }
    }
    
    /// Return the FileInfo to use when including a file in the archive. This method is included to allow applications
    /// to modify the structure of an archive for assessments that were developed for use with Bridge Exporter 2.0.
    ///
    /// - returns: The `FileInfo` to use to add this file to the archive. If `nil` then the file should be skipped.
    open func manifestFileInfo(for result: FileArchivable, fileInfo: FileInfo) -> FileInfo? {
        fileInfo
    }
    
    /// The top-level assessment result file to include in the archive (if any).
    open func assessmentResultFile() throws -> (Data, FileInfo)? {
        guard let result = assessmentResult as? AssessmentResultObject else {
            return nil
        }
        let data = try result.jsonEncodedData()
        let fileInfo = FileInfo(filename: "assessmentResult.json",
                                timestamp: result.endDate,
                                contentType: "application/json",
                                identifier: result.identifier,
                                jsonSchema: result.jsonSchema)
        return (data, fileInfo)
    }
}

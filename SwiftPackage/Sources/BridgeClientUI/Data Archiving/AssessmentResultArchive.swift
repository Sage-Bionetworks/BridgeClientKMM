//
//  AssessmentResultArchive.swift
//  
//
//  Copyright © 2022 Sage Bionetworks. All rights reserved.
//
// Redistribution and use in source and binary forms, with or without modification,
// are permitted provided that the following conditions are met:
//
// 1.  Redistributions of source code must retain the above copyright notice, this
// list of conditions and the following disclaimer.
//
// 2.  Redistributions in binary form must reproduce the above copyright notice,
// this list of conditions and the following disclaimer in the documentation and/or
// other materials provided with the distribution.
//
// 3.  Neither the name of the copyright holder(s) nor the names of any contributors
// may be used to endorse or promote products derived from this software without
// specific prior written permission. No license is granted to the trademarks of
// the copyright holders even if such marks are included in this software.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE
// FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
// DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
// SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
// CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
// OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//

import Foundation
import JsonModel

open class AssessmentResultArchive : AbstractResultArchive, ResultArchiveBuilder {

    /// The result to be processed for archive and upload.
    public let assessmentResult: AssessmentResult
    
    /// File URL for the directory in which generated data files that are referenced using `FileResult`
    /// may be included. Asynchronous actions with recorders (and potentially steps) can save data to
    /// files during the progress of the task. This property specifies where such data was being written to
    /// allow the archive to delete the output directory once the results have been archived and encrypted
    /// for upload.
    let outputDirectory: URL?
    
    public init?(_ assessmentResult: AssessmentResult, schedule: AssessmentScheduleInfo? = nil, adherenceData: JsonSerializable? = nil, outputDirectory: URL? = nil) {
        self.assessmentResult = assessmentResult
        self.adherenceData = adherenceData
        self.outputDirectory = outputDirectory
        super.init(identifier: assessmentResult.identifier,
                   schemaIdentifier: assessmentResult.schemaIdentifier,
                   schedule: schedule)
    }
    
    public var uuid: UUID { assessmentResult.taskRunUUID }
    public var startedOn: Date { assessmentResult.startDate }
    public var endedOn: Date { assessmentResult.endDate }
    public let adherenceData: JsonSerializable?
    
    public func cleanup() async throws {
        try outputDirectory.map {
            try FileManager.default.removeItem(at: $0)
        }
    }
    
    public func buildArchive() async throws -> DataArchive {

        // Iterate through all the results within this collection and add if they are `FileArchivable`.
        try addBranchResults(assessmentResult)
        
        // Add the top-level assessment if desired.
        if let (data, manifestInfo) = try assessmentResultFile() {
            try self.addFile(data: data, filepath: manifestInfo.filename, createdOn: manifestInfo.timestamp, contentType: manifestInfo.contentType)
            manifest.insert(manifestInfo)
        }
        
        // Close the archive.
        let metadata = ArchiveMetadata(files: Array(manifest))
        let metadataDictionary = try metadata.jsonEncodedDictionary()
        try completeArchive(createdOn: Date(), with: metadataDictionary)
        
        return self
    }
    
    private var manifest = Set<FileInfo>()
    
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
            try self.addFile(data: data, filepath: manifestInfo.filename, createdOn: manifestInfo.timestamp, contentType: manifestInfo.contentType)
            manifest.insert(manifestInfo)
        }
    }
    
    /// Return the FileInfo to use when including a file in the archive. This method is included to allow applications
    /// to modify the structure of an archive for assessments that were developed for use with Bridge Exporter 2.0.
    ///
    /// - returns: The `FileInfo` to use to add this file to the archive. If `nil` then the file should be skipped.
    open func manifestFileInfo(for result: FileArchivable, fileInfo: FileInfo) -> FileInfo? {
        fileInfo
    }
    
    /// The top-level assessment result file to include in the archive (if any). By default, this is only included for surveys.
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

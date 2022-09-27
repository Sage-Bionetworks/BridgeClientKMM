//
//  ResultCollectionArchiveBuilder.swift
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

//
//  ArchiveBuilder.swift
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

open class JsonResultArchive : AbstractResultArchive, ResultArchiveBuilder {
    
    public let uuid: UUID = .init()
    public let json: Data
    public let fileInfo: FileInfo
    public let startedOn: Date
    
    public var endedOn: Date { fileInfo.timestamp }
    public var adherenceData: JsonSerializable? { nil }
    
    public init?(json: Data, filename: String, schema: URL, timestamp: Date = Date(), startedOn: Date? = nil, schedule: AssessmentScheduleInfo? = nil, schemaIdentifier: String? = nil) {
        self.json = json
        self.startedOn = startedOn ?? timestamp
        self.fileInfo = .init(filename: filename, timestamp: timestamp, contentType: "application/json", identifier: schedule?.assessmentInfo.identifier, jsonSchema: schema)
        super.init(identifier: schedule?.assessmentInfo.identifier ?? schemaIdentifier ?? filename,
                   schemaIdentifier: schemaIdentifier,
                   schedule: schedule)
    }
        
    public func buildArchive() async throws -> DataArchive {

        // Add the JSON file
        try self.addFile(data: json, filepath: fileInfo.filename, createdOn: fileInfo.timestamp, contentType: fileInfo.contentType)
        
        // Close the archive.
        let metadata = ArchiveMetadata(files: [fileInfo])
        let metadataDictionary = try metadata.jsonEncodedDictionary()
        try completeArchive(createdOn: Date(), with: metadataDictionary)
        
        return self
    }
    
    public func cleanup() async throws {
        // Do nothing - A single json file result does not support output directory cleanup.
    }
}

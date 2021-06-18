//
//  SageResearchArchiveManager.swift
//
//  Copyright © 2018-2021 Sage Bionetworks. All rights reserved.
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
import Research
import JsonModel
import BridgeClient

open class SageResearchArchiveManager : NSObject, RSDDataArchiveManager {
    
    public var bridgeManager: BridgeClientAppManager!
    
    private var _defaultTaskToSchemaMapping: [String : String]?
    
    open func load(bridgeManager: BridgeClientAppManager, taskToSchemaMapping: [String : String]? = nil) {
        self.bridgeManager = bridgeManager
        self._defaultTaskToSchemaMapping = taskToSchemaMapping
    }
    
    open func schemaReference(for taskResult: RSDTaskResult) -> RSDSchemaInfo? {
        _schemaReference(taskResult)
    }
    
    private func _schemaReference(_ taskResult: RSDTaskResult) -> RSDSchemaInfo? {
        var ret: RSDSchemaInfo? = nil
        DispatchQueue.main.sync {
            let schemaIdentifier =
                (taskResult as? AssessmentResult)?.schemaIdentifier ??
                self.bridgeManager.appConfig?.taskToSchemaMapping()?[taskResult.identifier] ??
                self._defaultTaskToSchemaMapping?[taskResult.identifier] ??
                taskResult.identifier
            
            if let ref = bridgeManager.appConfig?.schemaReferences?.first(where: { $0.id == schemaIdentifier }) {
                ret = RSDSchemaInfoObject(identifier: ref.id, revision: ref.revision?.intValue ?? 0)
            }
            else if let assessmentResult = taskResult as? AssessmentResult,
                    let schemaIdentifier = assessmentResult.schemaIdentifier,
                    let versionString = assessmentResult.versionString,
                    let revision = Int(versionString) {
                ret = RSDSchemaInfoObject(identifier: schemaIdentifier, revision: revision)
            }
        }
        return ret
    }
    
    public final func dataGroups() -> [String]? {
        var ret: [String]? = nil
        DispatchQueue.main.sync {
            ret = bridgeManager.userSessionInfo?.dataGroups
        }
        return ret
    }
        
    open func schedule(for taskResult: RSDTaskResult) -> AssessmentScheduleInfo? {
        guard let taskRunUUID = (taskResult as? AssessmentResult)?.taskRunUUID else { return nil }
        var found: AssessmentScheduleInfo?
        _retainedPathsQueue.sync {
            found = _retainedPaths.first(where: {
                ($0.value.taskState.taskResult as? AssessmentResult)?.taskRunUUID == taskRunUUID
            })?.value.schedule
        }
        return found
    }
    
    /// A serial queue used to manage data crunching.
    public let offMainQueue = DispatchQueue(label: "org.sagebionetworks.BridgeClientUI.SageResearchUploader")
    
    /// Archive and upload the results from the task view model.
    public final func archiveAndUpload(_ taskState: RSDTaskState, schedule: AssessmentScheduleInfo?) {
        offMainQueue.async {
            self._archiveAndUpload(taskState, schedule)
        }
    }

    /// DO NOT MAKE OPEN. This method retains the task path until archiving is completed and because it
    /// nils out the pointer to the task path with a strong reference to `self`, it will also retain the
    /// archive manager until the completion block is called. syoung 05/31/2018
    private final func _archiveAndUpload(_ taskState: RSDTaskState, _ schedule: AssessmentScheduleInfo?) {
        let uuid = UUID()
        self._retainPath(uuid, taskState, schedule)
        taskState.archiveResults(with: self) { _ in
            self._releasePath(uuid)
        }
    }
 
    private var _retainedPaths: [UUID : (taskState: RSDTaskState, schedule: AssessmentScheduleInfo?)] = [:]
    private let _retainedPathsQueue = DispatchQueue(label: "org.sagebionetworks.BridgeClientUI.SageResearchUploader.RetainedPaths")
    
    private func _retainPath(_ uuid: UUID, _ taskState: RSDTaskState, _ schedule: AssessmentScheduleInfo?) {
        _retainedPathsQueue.sync {
            self._retainedPaths[uuid] = (taskState, schedule)
        }
    }
    
    private func _releasePath(_ uuid: UUID) {
        _retainedPathsQueue.sync {
            self._retainedPaths[uuid] = nil
        }
    }
    
    /// Should the task result archiving be continued if there was an error adding data to the current
    /// archive? Default behavior is to flush the archive and then return `false`.
    ///
    /// - parameters:
    ///     - archive: The current archive being built.
    ///     - error: The encoding error that was thrown.
    /// - returns: Whether or not archiving should continue. Default = `false`.
    public func shouldContinueOnFail(for archive: RSDDataArchive, error: Error) -> Bool {
        debugPrint("ERROR! Failed to archive results: \(error)")
        // Flush the archive.
        (archive as? AbstractResultArchive)?.remove()
        return false
    }
    
    /// When archiving a task result, it is possible that the results of a task need to be split into
    /// multiple archives -- for example, when combining two or more activities within the same task. If the
    /// task result components should be added to the current archive, then the manager should return
    /// `currentArchive` as the response. If the task result *for this section* should be ignored, then the
    /// manager should return `nil`. This allows the application to only upload data that is needed by the
    /// study, and not include information that is ignored by *this* study, but may be of interest to other
    /// researchers using the same task protocol.
    open func dataArchiver(for taskResult: RSDTaskResult, scheduleIdentifier: String?, currentArchive: RSDDataArchive?) -> RSDDataArchive? {
        
        // Look for a schema info associated with this portion of the task result.
        // If not found, then return the current archive.
        let schema = self.schemaReference(for: taskResult)
        guard (currentArchive == nil) || (schema != nil) else {
            return currentArchive
        }
        
        let isPlaceholder = (currentArchive == nil) && (schema == nil)
        let schedule = self.schedule(for: taskResult)
        let archiveIdentifier = schema?.schemaIdentifier ?? taskResult.identifier

        // If there is a top-level archive then return the exisiting if and only if the identifiers are the
        // same or the schema is nil.
        if let inputArchive = currentArchive,
            ((inputArchive.identifier == archiveIdentifier) || (schema == nil)) {
            return inputArchive
        }

        if isPlaceholder {
            // If this is a placeholder top-level archive without a schema table then consider it empty.
            return SageResearchResultArchive(identifier: archiveIdentifier,
                                             schemaIdentifier: schema?.schemaIdentifier,
                                             schemaRevision: schema?.schemaVersion,
                                             dataGroups: dataGroups(),
                                             schedule: schedule,
                                             isPlaceholder: true)
        }
        else {
            // Otherwise, instantiate a new archive.
            let archive = self.instantiateArchive(archiveIdentifier, for: schedule, with: schema)
            archive?.taskResult = taskResult
            return archive
        }
    }
    
    /// Finalize the upload of all the created archives.
    public final func encryptAndUpload(taskResult: RSDTaskResult, dataArchives: [RSDDataArchive], completion: @escaping (() -> Void)) {
        let archives: [AbstractResultArchive] = dataArchives.compactMap {
            guard let archive = $0 as? AbstractResultArchive, self.shouldUpload(archive: archive)
            else {
                return nil
            }
            return archive
        }
        #if DEBUG
        if dataGroups()?.contains("test_user") ?? false {
            archives.forEach {
                $0.copyTestArchive()
            }
        }
        #endif
        bridgeManager.encryptAndUpload(archives)
        completion()
    }
    
    /// By default, if an archive fails, the error is printed and that's all that is done.
    open func handleArchiveFailure(taskResult: RSDTaskResult, error: Error, completion: @escaping (() -> Void)) {
        debugPrint("WARNING! Failed to archive \(taskResult.identifier). \(error)")
        completion()
    }
    
    /// This method is called during `encryptAndUpload()` to allow subclasses to cancel uploading an archive.
    ///
    /// - returns: Whether or not to upload. Default is to return `true` if the archive is not empty.
    open func shouldUpload(archive: AbstractResultArchive) -> Bool {
        return !archive.isEmpty()
    }
    
    /// Instantiate the data archive to use for this schedule and schema info.
    open func instantiateArchive(_ archiveIdentifier: String, for schedule: AssessmentScheduleInfo?, with schema: RSDSchemaInfo?) -> SageResearchResultArchive? {
        SageResearchResultArchive(identifier: archiveIdentifier,
                                  schemaIdentifier: schema?.schemaIdentifier,
                                  schemaRevision: schema?.schemaVersion,
                                  dataGroups: dataGroups(),
                                  schedule: schedule,
                                  isPlaceholder: false)
    }
}

extension AppConfig {
    
    func taskToSchemaMapping() -> [String : String]? {
        guard let dictionary = clientDataDictionary() else { return nil }
        return dictionary["taskToSchemaIdentifierMap"] as? [String : String]
    }
}

open class SageResearchResultArchive : AbstractResultArchive, RSDDataArchive {
    
    /// Hold the task result (if any) used to create the archive.
    internal var taskResult: RSDTaskResult?
    
    open func shouldInsertData(for filename: RSDReservedFilename) -> Bool {
        true
    }
    
    open func archivableData(for result: RSDResult, sectionIdentifier: String?, stepPath: String?) -> RSDArchivable? {
        result as? RSDArchivable
    }
    
    open func insertDataIntoArchive(_ data: Data, manifest: RSDFileManifest) throws {
        let filename = manifest.filename
        let fileKey = (filename as NSString).deletingPathExtension
        if let reserved = RSDReservedFilename(rawValue: fileKey), reserved == .answers {
            self.dataFilename = filename
        }
        try addFile(data: data, filepath: filename, createdOn: manifest.timestamp, contentType: manifest.contentType)
    }
    
    /// Close the archive.
    public final func completeArchive(with metadata: RSDTaskMetadata) throws {
        let metadataDictionary = try metadata.rsd_jsonEncodedDictionary()
        try completeArchive(createdOn: metadata.startDate, with: metadataDictionary)
    }
}


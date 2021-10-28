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

/// Base-class implementation of archiving results from a ``Research.RSDTaskState`` run.
/// Typically, this is used for active assessments, but can be used for any data collected using the
/// SageResearch libraries.
open class SageResearchArchiveManager : NSObject, RSDDataArchiveManager {
    
    /// Pointer to the app manager singleton for this application.
    public var bridgeManager: BridgeClientAppManager!
    
    private var _defaultTaskToSchemaMapping: [String : String]?
    private var _appConfigTaskToSchemaMapping: [String : String]?
    
    /// Set up the archive manager by attaching the ``BridgeClientAppManager`` singleton to it.
    ///
    /// - Parameters:
    ///   - bridgeManager: The app manager singleton for this application
    ///   - taskToSchemaMapping: The mapping to use for mapping which results to include in a single archive.
    open func load(bridgeManager: BridgeClientAppManager, taskToSchemaMapping: [String : String]? = nil) {
        self.bridgeManager = bridgeManager
        self._defaultTaskToSchemaMapping = taskToSchemaMapping
        self._appConfigTaskToSchemaMapping = bridgeManager.appConfig?.taskToSchemaMapping()
    }
    
    /// Get the ```RSDSchemaInfo`` associated with this task result.
    open func schemaReference(for taskResult: RSDTaskResult) -> RSDSchemaInfo? {
        _schemaReference(taskResult)
    }
    
    private func _schemaReference(_ taskResult: RSDTaskResult) -> RSDSchemaInfo? {
        // Because this accesses the ``BridgeClient.AppConfig``, it must be processed
        // on the main thread. Kotlin classes are not threadsafe.
        return processResultOnMainThread() {
            let schemaIdentifier =
                self._appConfigTaskToSchemaMapping?[taskResult.identifier] ??
                self._defaultTaskToSchemaMapping?[taskResult.identifier] ??
                (taskResult as? AssessmentResult)?.schemaIdentifier ??
                taskResult.identifier
            
            if let ref = bridgeManager.appConfig?.schemaReferences?.first(where: { $0.id == schemaIdentifier }) {
                return RSDSchemaInfoObject(identifier: ref.id, revision: ref.revision?.intValue ?? 0)
            }
            else if let assessmentResult = taskResult as? AssessmentResult,
                    let schemaIdentifier = assessmentResult.schemaIdentifier,
                    let versionString = assessmentResult.versionString,
                    let revision = Int(versionString) {
                return RSDSchemaInfoObject(identifier: schemaIdentifier, revision: revision)
            }
            else {
                return nil
            }
        }
    }
    
    /// Get the data groups associated with this user.
    public final func dataGroups() -> [String]? {
        bridgeManager.userSessionInfo.dataGroups
    }
        
    /// Get the schedule info associated with the given task result.
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
        do {
            guard let dictionary = try self.clientDataDictionary()
            else {
                return nil
            }
            return dictionary["taskToSchemaIdentifierMap"] as? [String : String]
        } catch let err {
            print("WARNING! Failed to decode client data to a dictionary. \(err)")
            return nil
        }
    }
}

/// Depending upon the needs of the researchers using this application, a collection of assessments may be
/// presented to the participant as a single "task" that then needs to be split into different archives for
/// post-processing. This structure of having a manager for the state object and a separate class for holding
/// the archive data is intended to allow for that scenario.
open class SageResearchResultArchive : AbstractResultArchive, RSDDataArchive {
    
    /// Hold the task result (if any) used to create the archive.
    internal var taskResult: RSDTaskResult?
    
    /// Whether or not the archive should include "reserved" files that are collated separately from the
    /// default behavoir of iteratively looking through the result for objects that support the ``RSDArchivable``
    /// protocol.
    /// - Parameter filename: The enum for the reserved file name.
    /// - Returns: Whether or not the file should be added. (Default == true)
    open func shouldInsertData(for filename: RSDReservedFilename) -> Bool {
        true
    }
    
    /// The archivable object to use to process the given result.
    ///
    /// - Parameters:
    ///   - result: The result to process.
    ///   - sectionIdentifier: The section identifier for result within the assessment.
    ///   - stepPath: The step path for the result within the assessment
    /// - Returns: The archivable or `nil` if the result is ignored.
    open func archivableData(for result: ResultData, sectionIdentifier: String?, stepPath: String?) -> RSDArchivable? {
        result as? RSDArchivable
    }
    
    
    /// Insert the data into the archive.
    ///
    /// - Parameters:
    ///   - data: The data to be added to the archive.
    ///   - manifest: The file manifest for this data.
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

/// A convenience method for ensuring that a given result is processed on the main thread.
func processResultOnMainThread<T>(_ process: () -> T?) -> T? {
    var ret: T? = nil
    if Thread.isMainThread {
        ret = process()
    } else {
        DispatchQueue.main.sync {
            ret = process()
        }
    }
    return ret
}


// Created 7/26/23
// swift-tools-version:5.0

import Foundation
import BridgeClient
import JsonModel

#if canImport(UIKit)
import UIKit
#endif

fileprivate let UnprocessedUploadsKey = "unprocessedUploads"

/// This is a processor to use to handle archiving data and uploading in the background.
final class ArchiveUploadProcessor {
    
    let pemPath: String?
    let sharedUserDefaults: UserDefaults
    var isTestUser: Bool = false
    
    weak var uploadManager: BridgeUploader!
    
    init(pemPath: String?, sharedUserDefaults: UserDefaults) {
        self.pemPath = pemPath
        self.sharedUserDefaults = sharedUserDefaults
    }
    
    func encryptAndUpload(using builder: ArchiveBuilder) {
        Task.detached(priority: .userInitiated) {
            await self.asyncEncryptAndUpload(using: builder)
        }
    }
    
    @MainActor
    func asyncEncryptAndUpload(using builder: ArchiveBuilder) async {
        uploadManager.isArchiving = true

        #if canImport(UIKit)
        // This allows the app to request about 30 seconds after the app has been
        // backgrounded to prepare data for upload.
        let taskId = UIApplication.shared.beginBackgroundTask {
            Logger.log(tag: .upload,
                       error: BridgeUploadFailedError(category: .backgroundTaskTimeout, message: "Timed out when archiving and starting background upload.")
            )
            self.uploadManager.isArchiving = false
        }
        #endif
        
        do {
            let archive = try await builder.buildArchive()
            // Copy the startedOn date (if available) from the builder to the archive.
            // This is a work-around for older code so that the adherence record can be
            // marked for a requested archive.
            if let resultBuilder = builder as? ResultArchiveBuilder, archive.adherenceStartedOn == nil {
                archive.adherenceStartedOn = resultBuilder.startedOn
            }
            await _copyTest(archive: archive)
            try await _encrypt(archive: archive)
            try await _upload(archive: archive)
        } catch {
            Logger.log(error: error, message: "Failed to archive and upload \(builder.identifier)")
        }
        
        #if canImport(UIKit)
        // Let the OS know that the app is done with the processing that needs to happen
        // before ending.
        UIApplication.shared.endBackgroundTask(taskId)
        #endif
        
        uploadManager.isArchiving = false
    }
    
    private func _copyTest(archive: DataArchive) async {
        #if DEBUG
        if isTestUser {
            archive.copyTestArchive()
        }
        #endif
    }
    
    private func _encrypt(archive: DataArchive) async throws {
        guard let path = self.pemPath else {
            // Throw an assert to alert the developer that the pem file is missing.
            let message = "Cannot upload archive. Missing pemPath."
            assertionFailure(message)
            throw BridgeUnexpectedNullError(category: .missingFile, message: message)
        }
        try archive.encryptArchive(using: path)
    }
    
    @MainActor
    private func _upload(archive: DataArchive) async throws {
        guard let url = archive.encryptedURL else {
            let message = "Cannot upload archive. Missing encryption."
            assertionFailure(message)   // Throw an assert to alert the developer that the pem file is missing.
            throw BridgeUnexpectedNullError(category: .missingFile, message: message)
        }
        await _uploadEncrypted(id: archive.identifier, url: url, schedule: archive.schedule, startedOn: archive.adherenceStartedOn)
    }

    @MainActor
    private func _uploadEncrypted(id: String, url: URL, schedule: AssessmentScheduleInfo?, startedOn: Date?) async {
        let success = await uploadManager.uploadEncryptedArchive(fileUrl: url, schedule: schedule, startedOn: startedOn)
        if (success) {
            // Only if the file was successfully queued for upload should the original file be deleted.
            do {
                try FileManager.default.removeItem(at: url)
            } catch let err {
                Logger.log(error: err, message: "Failed to delete encrypted archive \(id) at \(url)")
            }
        }
        else {
            // Store the path to the failed upload to allow potentially recovering the file and log error.
            var failedUploads = (sharedUserDefaults.array(forKey: UnprocessedUploadsKey) as? [String]) ?? []
            failedUploads.append(url.path)
            sharedUserDefaults.set(failedUploads, forKey: UnprocessedUploadsKey)
            let err = BridgeUploadFailedError(category: .fileFailure, message: "Failed to queue encrypted file for upload. \(url)")
            Logger.log(tag: .upload, error: err)
        }
    }
    
}

/// Use a protocol to allow for unit tests to mock the Upload Manager.
protocol BridgeUploader : NSObjectProtocol {
    var isArchiving: Bool { get set }
    @MainActor func uploadEncryptedArchive(fileUrl: URL, schedule: AssessmentScheduleInfo?, startedOn: Date?) async -> Bool
    @MainActor func upload(fileUrl: URL, contentType: String, encrypted: Bool, metadata: UploadMetadata?, s3UploadType: S3UploadType) async -> Bool
}

extension UploadManager : BridgeUploader {
}

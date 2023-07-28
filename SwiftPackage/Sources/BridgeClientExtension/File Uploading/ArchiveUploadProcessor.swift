// Created 7/26/23
// swift-tools-version:5.0

import Foundation
import BridgeClient
import JsonModel

fileprivate let UnprocessedUploadsKey = "unprocessedUploads"

final class ArchiveUploadProcessor {
    
    let pemPath: String?
    let sharedUserDefaults: UserDefaults
    var isTestUser: Bool = false
    
    @MainActor
    lazy var uploader: BridgeUploader = UploadManager.shared
    
    init(pemPath: String?, sharedUserDefaults: UserDefaults) {
        self.pemPath = pemPath
        self.sharedUserDefaults = sharedUserDefaults
    }
    
    func encryptAndUpload(using builder: ArchiveBuilder) {
        Task.detached(priority: .medium) {
            await self._encryptAndUpload(using: builder)
        }
    }
    
    @MainActor
    private func _encryptAndUpload(using builder: ArchiveBuilder) async {
        do {
            let archive = try await builder.buildArchive()
            // Copy the startedOn date (if available) from the builder to the archive.
            if let resultBuilder = builder as? ResultArchiveBuilder, archive.adherenceStartedOn == nil {
                archive.adherenceStartedOn = resultBuilder.startedOn
            }
            await _copyTest(archive: archive)
            let encrypted = await _encrypt(archive: archive)
            await _upload(archive: archive, encrypted: encrypted)
        } catch {
            Logger.log(error: error, message: "Failed to archive and upload \(builder.identifier)")
        }
    }
    
    private func _copyTest(archive: DataArchive) async {
        #if DEBUG
        if isTestUser {
            archive.copyTestArchive()
        }
        #endif
    }
    
    private func _encrypt(archive: DataArchive) async -> Bool {
        guard let path = self.pemPath else { return false }
        do {
            try archive.encryptArchive(using: path)
            return true
        } catch {
            Logger.log(error: error, message: "Failed to encrypt \(archive.identifier)")
            return false
        }
    }
    
    @MainActor
    private func _upload(archive: DataArchive, encrypted: Bool) async {
        guard let url = archive.encryptedURL else {
            let message = "Cannot upload archive. Missing encryption."
            assertionFailure(message)   // Throw an assert to alert the developer that the pem file is missing.
            Logger.log(error: BridgeUnexpectedNullError(category: .missingFile, message: message))
            return
        }
        _uploadEncrypted(id: archive.identifier, url: url, schedule: archive.schedule, startedOn: archive.adherenceStartedOn)
    }

    @MainActor
    private func _uploadEncrypted(id: String, url: URL, schedule: AssessmentScheduleInfo?, startedOn: Date?) {
        let uploadMetadata = schedule.map {
            UploadMetadata(
                instanceGuid: $0.instanceGuid,
                eventTimestamp: $0.session.eventTimestamp,
                startedOn: startedOn?.jsonObject() as? String
            )
        }
        let dictionary = uploadMetadata?.toStringMap()
        let exporterV3Metadata: JsonElement? = dictionary.map { .object($0) }
        let extras = StudyDataUploadExtras(encrypted: true, metadata: exporterV3Metadata, zipped: true)
        Logger.log(severity: .info, message: "Uploading file: \(id)", metadata: dictionary)
        StudyDataUploadAPI.shared.upload(fileId: id, fileUrl: url, contentType: "application/zip", extras: extras)
        do {
            try FileManager.default.removeItem(at: url)
        } catch let err {
            Logger.log(error: err, message: "Failed to delete encrypted archive \(id) at \(url)")
        }
    }
    
    // TODO: syoung 07/27/2023 Replace upload with V2 uploader
//    @MainActor
//    private func _uploadEncrypted(id: String, url: URL, schedule: AssessmentScheduleInfo?, startedOn: Date?) {
//        let success = uploader.uploadEncryptedArchive(fileUrl: url, schedule: schedule, startedOn: startedOn)
//        if (success) {
//            // Only if the file was successfully queued for upload should the original file be deleted.
//            do {
//                try FileManager.default.removeItem(at: url)
//            } catch let err {
//                Logger.log(error: err, message: "Failed to delete encrypted archive \(id) at \(url)")
//            }
//        }
//        else {
//            // Store the path to the failed upload to allow potentially recovering the file and log error.
//            var failedUploads = (sharedUserDefaults.array(forKey: UnprocessedUploadsKey) as? [String]) ?? []
//            failedUploads.append(url.path)
//            sharedUserDefaults.set(failedUploads, forKey: UnprocessedUploadsKey)
//            let err = BridgeUploadFailedError(errorCode: -99, message: "Failed to queue encrypted file for upload. \(url)")
//            Logger.log(tag: .upload, error: err)
//        }
//    }
    
}

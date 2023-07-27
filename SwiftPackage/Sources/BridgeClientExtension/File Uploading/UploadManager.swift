// Created 7/26/23
// swift-tools-version:5.0

import Foundation
import BridgeClient

protocol BridgeUploader {
    
    /// Upload an encrypted archive.
    /// - Parameters:
    ///   - fileUrl: The file url of the original encrypted archive.
    ///   - schedule: The schedule (if any) associated with this archive.
    ///   - startedOn: The `startedOn` value for the associated adherence record that is used to uniquely identify it.
    /// - Returns: `true` if the file was successfully copied and queued for upload.
    @MainActor func uploadEncryptedArchive(fileUrl: URL, schedule: AssessmentScheduleInfo?, startedOn: Date?) -> Bool
    
    
    /// Upload a file to Bridge.
    /// - Parameters:
    ///   - fileUrl: The original file url for the file to upload.
    ///   - contentType: The content-type for the file.
    ///   - encrypted: Whether or not the file is encrypted.
    ///   - metadata: The metadata associated with this file.
    ///   - s3UploadType: The upload type.
    /// - Returns: `true` if the file was successfully copied and queued for upload.
    @MainActor func upload(fileUrl: URL, contentType: String, encrypted: Bool, metadata: UploadMetadata?, s3UploadType: S3UploadType) -> Bool
}

class UploadManager : NSObject, BridgeUploader {
    static let shared: UploadManager = .init()
    
    lazy var sandboxFileManager: SandboxFileManager = .init()
    lazy var nativeUploadManager: BridgeClientUploadManager = NativeUploadManager()
    
    lazy var uploadDirURL: URL? = {
        do {
            let baseURL = try FileManager.default.sharedAppSupportDirectory()
            let url: URL
            let subdir = "BridgeUploads"
            if #available(iOS 16.0, *) {
                url = baseURL.appending(component: subdir, directoryHint: .isDirectory)
            } else {
                url = baseURL.appendingPathComponent(subdir)
            }
            try FileManager.default.createDirectory(at: url, withIntermediateDirectories: true, attributes: nil)
            return url
        } catch {
            Logger.log(tag: .upload, error: error, message: "Error trying to create the uploads directory.")
            return nil
        }
    }()
    
    func uploadEncryptedArchive(fileUrl: URL, schedule: AssessmentScheduleInfo?, startedOn: Date?) -> Bool {
        let metadata: UploadMetadata? = schedule.map {
            UploadMetadata(
                instanceGuid: $0.instanceGuid,
                eventTimestamp: $0.session.eventTimestamp,
                startedOn: startedOn?.jsonObject() as? String
            )
        }
        return upload(fileUrl: fileUrl, contentType: "application/zip", encrypted: true, metadata: metadata, s3UploadType: .studyData)
    }
    
    func upload(fileUrl: URL, contentType: String, encrypted: Bool, metadata: UploadMetadata?, s3UploadType: S3UploadType) -> Bool {
        
        // Both study data and participant data should first be copied to a temp file.
        guard let uploadDirURL = self.uploadDirURL,
              let (_, tempUrl) = sandboxFileManager.tempFileFor(inFileURL: fileUrl, uploadDirURL: uploadDirURL),
              let contentLength = sandboxFileManager.fileContentLength(tempUrl)
        else {
            return false
        }
        
        // The MD5 is only required for study data.
        let contentMD5String: String?
        if s3UploadType == .studyData {
            guard let md5 = sandboxFileManager.fileMD5String(tempUrl)
            else {
                return false
            }
            contentMD5String = md5
        }
        else {
            contentMD5String = nil
        }
        
        // Both study data and participant data use the sandbox relative path for tracking the file.
        let invariantFilePath = sandboxFileManager.sandboxRelativePath(of: tempUrl)
        
        // Now that we have all the info, create the model object that is stored.
        let uploadFile = UploadFile(filePath: invariantFilePath,
                                    contentType: contentType,
                                    fileLength: Int64(contentLength),
                                    md5Hash: contentMD5String,
                                    encrypted: encrypted,
                                    metadata: metadata,
                                    s3UploadType: .studyData)
        
        // Finally, queue the upload using the native upload manager.
        nativeUploadManager.queueAndRequestUploadSession(uploadFile: uploadFile, callBack: startS3Upload)
        return true
    }
    
    private func startS3Upload(_ uploadSession: S3UploadSession?) {
        // TODO: Implement syoung 07/26/2023
    }
    
}

// Use a protocol to wrap the native upload manager - this is to allow using a mock for testing.
protocol BridgeClientUploadManager : AnyObject {
    func getUploadFiles() -> [String]
    func queueAndRequestUploadSession(uploadFile: UploadFile, callBack: @escaping (S3UploadSession?) -> Void)
    func requestUploadSession(filePath: String, callBack: @escaping (S3UploadSession?) -> Void)
    func markUploadFileFinished(filePath: String, callBack: @escaping (KotlinBoolean) -> Void)
    func processFinishedUploads(callBack: @escaping (KotlinBoolean) -> Void)
}

extension NativeUploadManager : BridgeClientUploadManager {
}

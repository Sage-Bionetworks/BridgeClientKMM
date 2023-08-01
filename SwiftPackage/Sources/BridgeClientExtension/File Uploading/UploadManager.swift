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

class UploadManager : NSObject, BridgeUploader, BridgeURLSessionHandler {

    weak private(set) var backgroundNetworkManager: BackgroundNetworkManager!
    let sandboxFileManager: SandboxFileManager
    let nativeUploadManager: BridgeClientUploadManager
    
    init(backgroundNetworkManager: BackgroundNetworkManager,
         sandboxFileManager: SandboxFileManager = .init(),
         nativeUploadManager: BridgeClientUploadManager = NativeUploadManager()
    ) {
        // Set up pointers
        self.sandboxFileManager = sandboxFileManager
        self.nativeUploadManager = nativeUploadManager
        super.init()
        
        // register self with the background network manager
        self.backgroundNetworkManager = backgroundNetworkManager
        backgroundNetworkManager.registerBackgroundTransferHandler(self)
    }
    
    private let subdir = "BridgeUploadsV2"
    lazy var uploadDirURL: URL? = {
        do {
            let baseURL = try FileManager.default.sharedAppSupportDirectory()
            let url: URL
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
    
    // MARK: BridgeURLSessionHandler
    
    func canHandle(task: BridgeURLSessionTask) -> Bool {
        // TODO: syoung 08/01/2023 Use the taskDescription to parse out whether or not the task should be handled by this handler.
        return false
    }

    func bridgeUrlSession(_ session: any BridgeURLSession, task: BridgeURLSessionTask, didCompleteWithError error: Error?) {
        // TODO: syoung 08/01/2023 Handle responding to an S3 upload success/failure.
    }

    func bridgeUrlSession(_ session: any BridgeURLSession, didBecomeInvalidWithError error: Error?) {
        // TODO: syoung 08/01/2023 Manage any cleanup needed to handle S3 session becoming invalid. Retry?
    }
}

// Use a protocol to wrap the background network manager - this is to allow using a mock for testing.
protocol SharedBackgroundUploadManager : AnyObject {
    @discardableResult
    func uploadFile(_ fileURL: URL, httpHeaders: [String : String]?, to urlString: String, taskDescription: String) -> BridgeURLSessionUploadTask?
}

extension BackgroundNetworkManager : SharedBackgroundUploadManager {
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

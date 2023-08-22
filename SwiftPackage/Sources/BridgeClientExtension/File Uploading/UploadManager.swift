// Created 7/26/23
// swift-tools-version:5.0

import Foundation
import BackgroundTasks
import BridgeClient

#if canImport(UIKit)
import UIKit
#endif

class UploadManager : NSObject, BridgeURLSessionHandler {

    weak private(set) var backgroundNetworkManager: SharedBackgroundUploadManager!
    let sandboxFileManager: SandboxFileManager
    let nativeUploadManager: BridgeClientUploadManager
    
    init(backgroundNetworkManager: SharedBackgroundUploadManager,
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
    
    let subdir = "BridgeUploadsV2"
    
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
    
    @MainActor
    func setup(backgroundProcessId: String?) {
        do {
            // Register the background process
            if let backgroundProcessId = backgroundProcessId {
                try registerBackgroundTasks(backgroundProcessId)
            }
            // setup checking and retrying uploads
            try setupCheckAndRetryUploads()
            
        } catch {
            Logger.log(tag: .upload, error: error)
        }
    }
    
    
    // MARK: Upload handling
    
    /// Upload an encrypted archive.
    /// - Parameters:
    ///   - fileUrl: The file url of the original encrypted archive.
    ///   - schedule: The schedule (if any) associated with this archive.
    ///   - startedOn: The `startedOn` value for the associated adherence record that is used to uniquely identify it.
    /// - Returns: `true` if the file was successfully copied and queued for upload.
    @MainActor
    func uploadEncryptedArchive(fileUrl: URL, schedule: AssessmentScheduleInfo?, startedOn: Date?) async -> Bool {
        let metadata: UploadMetadata? = schedule.map {
            UploadMetadata(
                instanceGuid: $0.instanceGuid,
                eventTimestamp: $0.session.eventTimestamp,
                startedOn: startedOn?.jsonObject() as? String
            )
        }
        return await upload(fileUrl: fileUrl, contentType: "application/zip", encrypted: true, metadata: metadata, s3UploadType: .studyData)
    }
    
    /// Upload a file to Bridge.
    /// - Parameters:
    ///   - fileUrl: The original file url for the file to upload.
    ///   - contentType: The content-type for the file.
    ///   - encrypted: Whether or not the file is encrypted.
    ///   - metadata: The metadata associated with this file.
    ///   - s3UploadType: The upload type.
    /// - Returns: `true` if the file was successfully copied and queued for upload.
    @MainActor
    func upload(fileUrl: URL, contentType: String, encrypted: Bool, metadata: UploadMetadata?, s3UploadType: S3UploadType) async -> Bool {
        
        // Both study data and participant data should first be copied to a temp file.
        guard let uploadDirURL = self.uploadDirURL?.appendingPathComponent(s3UploadType.name),
              let (_, tempUrl) = sandboxFileManager.tempFileFor(inFileURL: fileUrl,uploadDirURL: uploadDirURL),
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
                                    s3UploadType: s3UploadType)
        
        // Finally, queue the upload using the native upload manager.
        let success: Bool = await withCheckedContinuation { continuation in
            nativeUploadManager.queueAndRequestUploadSession(uploadFile: uploadFile) { [weak self] uploadSession in
                if let uploadSession = uploadSession {
                    // If there is an upload session then start the upload
                    self?.startS3Upload(uploadSession)
                } else {
                    // If the callback is nil then services are offline. Try again later.
                    // TODO: syoung 08/02/2023 Retry after delay? Check for network and then retry when connected?
                }
                // Always return true - encryption and copy was successful.
                continuation.resume(returning: true)
            }
        }

        return success
    }
    
    @MainActor
    private func startS3Upload(_ uploadSession: S3UploadSession) {
        let fileURL = sandboxFileManager.fileURL(of: uploadSession.filePath)
        let taskIdentifier = "\(uploadSession.uploadSessionId)|\(uploadSession.filePath)"
        backgroundNetworkManager.uploadFile(fileURL,
                                            httpHeaders: uploadSession.requestHeaders,
                                            to: uploadSession.url,
                                            taskDescription: taskIdentifier)
    }
    
    
    // MARK: BridgeURLSessionHandler
    
    func canHandle(task: BridgeURLSessionTask) -> Bool {
        return (task.taskType == .upload) && (task.taskDescription?.contains(subdir) ?? false)
    }

    func bridgeUrlSession(_ session: any BridgeURLSession, task: BridgeURLSessionTask, didCompleteWithError error: Error?) {
        // TODO: syoung 08/01/2023 Handle responding to an S3 upload success/failure.
    }

    func bridgeUrlSession(_ session: any BridgeURLSession, didBecomeInvalidWithError error: Error?) {
        // TODO: syoung 08/01/2023 Manage any cleanup needed to handle S3 session becoming invalid. Retry?
    }
    
    
    // MARK: Background process handling
    
    private var backgroundProcessId: String?
    private var appBackgroundObserver: Any?
    
    @MainActor
    func registerBackgroundTasks(_ backgroundProcessId: String) throws {
        guard self.backgroundProcessId == nil, self.backgroundProcessId != backgroundProcessId
        else {
            throw BridgeUnexpectedNullError(category: .duplicateCall, message: "Attempting to register for a background process multiple times.")
        }
        self.backgroundProcessId = backgroundProcessId
        BGTaskScheduler.shared.register(forTaskWithIdentifier: backgroundProcessId, using: .main) { task in
            Task {
                let success = await self.handleBackgroundProcessing()
                task.setTaskCompleted(success: success)
                self.scheduleBackgroundProcessingIfNeeded()
            }
        }
        #if canImport(UIKit)
        // Set up a listener to retry temporarily-failed uploads whenever the app becomes active
        self.appBackgroundObserver = NotificationCenter.default.addObserver(forName: UIApplication.didEnterBackgroundNotification, object: nil, queue: nil) { notification in
            Logger.log(severity: .info, message: "App did enter background. Scheduling background processing if needed.")
            self.scheduleBackgroundProcessingIfNeeded()
        }
        #endif
    }
    
    func handleBackgroundProcessing() async -> Bool {
        // TODO: Implement syoung 08/18/2023 Check for any archives or adherence records that are not uploaded.
        return true
    }
    
    func scheduleBackgroundProcessingIfNeeded() {
        // Only schedule background processing if there are pending uploads.
        guard nativeUploadManager.hasPendingUploads(),
              let taskId = self.backgroundProcessId
        else {
            return
        }
        Logger.log(severity: .info, tag: .upload, message: "Pending uploads detected. Scheduling background process: \(taskId)")
        
        let request = BGProcessingTaskRequest(identifier: taskId)
        request.requiresNetworkConnectivity = true                     // Do not attempt processing without network connectivity
        request.earliestBeginDate = Date(timeIntervalSinceNow: 15*60)  // Wait 15 minutes to allow S3 uploads in progress to complete
        
        do {
            try BGTaskScheduler.shared.submit(request)
        } catch {
            Logger.log(tag: .upload, error: error)
        }
    }
    
    
    // MARK: Check and retry handling
    
    private var appActiveObserver: Any?
    
    func setupCheckAndRetryUploads() throws {
        guard self.appActiveObserver == nil else {
            throw BridgeUnexpectedNullError(category: .duplicateCall, message: "Attempting to setup listening to app active multiple times")
        }
        
        #if canImport(UIKit)
        // Set up a listener to retry temporarily-failed uploads whenever the app becomes active
        self.appActiveObserver = NotificationCenter.default.addObserver(forName: UIApplication.didBecomeActiveNotification, object: nil, queue: nil) { notification in
            Logger.log(severity: .info, message: "App did enter foreground. Checking for uploads.")
            self.checkAndRetryUploads()
        }
        #endif

        // Check for uploads that need to be retried
        checkAndRetryUploads()
    }
    
    /// Check and retry uploads.
    func checkAndRetryUploads() {
        // TODO: syoung 08/22/2023 Implement
    }
}

// Use a protocol to wrap the background network manager - this is to allow using a mock for testing.
protocol SharedBackgroundUploadManager : AnyObject {
    var sessionDelegateQueue: OperationQueue { get }
    func registerBackgroundTransferHandler(_ handler: BridgeURLSessionHandler)
    @discardableResult func uploadFile(_ fileURL: URL, httpHeaders: [String : String]?, to urlString: String, taskDescription: String) -> Bool
    func getAllTasks() async -> [BridgeURLSessionTask]
}

extension BackgroundNetworkManager : SharedBackgroundUploadManager {
}

// Use a protocol to wrap the native upload manager - this is to allow using a mock for testing.
protocol BridgeClientUploadManager : AnyObject {
    func hasPendingUploads() -> Bool
    func getUploadFiles() -> [String]
    func queueAndRequestUploadSession(uploadFile: UploadFile, callBack: @escaping (S3UploadSession?) -> Void)
    func requestUploadSession(filePath: String, callBack: @escaping (S3UploadSession?) -> Void)
    func markUploadFileFinished(filePath: String, callBack: @escaping (KotlinBoolean) -> Void)
    func processFinishedUploads(callBack: @escaping (KotlinBoolean) -> Void)
}

extension NativeUploadManager : BridgeClientUploadManager {
}

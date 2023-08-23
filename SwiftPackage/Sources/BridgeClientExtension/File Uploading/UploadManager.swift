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
    
    // MARK: Life-cycle handling
    
    @MainActor var isArchiving: Bool = false
    
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
                                    s3UploadType: s3UploadType)
        
        // Finally, queue the upload using the native upload manager.
        let uploadSession = await nativeUploadManager.queueAndRequestUploadSession(uploadFile: uploadFile)
        handleS3UploadRequest(filePath: invariantFilePath, uploadSession: uploadSession)

        return true
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
        Task {
            do {
                try await urlSession(task: task, didCompleteWithError: error)
            } catch {
                Logger.log(tag: .upload, error: error, message: "Failed to handle completed task \(task)")
            }
        }
    }
    
    func urlSession(task: BridgeURLSessionTask, didCompleteWithError error: Error?) async throws {
        // Ignore tasks that are not uploads
        guard task.taskType == .upload else {
            throw BridgeUploadFailedError(category: .wrongHandler, message: "Failed to handle upload task \(task) using the \(self)")
        }

        // get the sandbox-relative path to the temp copy of the participant file
        let (uploadSessionId, invariantFilePath) = try task.parseTaskDescription()
        
        // any error that makes it all the way through to here would be the result of something like a
        // malformed request, so clean up the temp file and throw the error
        if let error = error {
            handleUnrecoverableFailure(filePath: invariantFilePath)
            throw error
        }
        
        // get the http response
        guard let httpResponse = task.response as? HTTPURLResponse else {
            throw BridgeUnexpectedNullError(category: .wrongType,
                                            message: "Upload task response is not an HTTPURLResponse: \(type(of: task.response))")
        }
        
        // check the upload status
        switch httpResponse.httpUploadStatus() {
        case .unhandled:
            // The status code is unrecoverable
            handleUnrecoverableFailure(filePath: invariantFilePath)
            throw BridgeHttpError(errorCode: httpResponse.statusCode, message: "Participant file upload to S3 of file \(invariantFilePath) failed with HTTP response status code \(httpResponse.statusCode)--unhandled, will not retry")
            
        case .retry:
            // this call failed but we may be able to recover with a retry
            await enqueueForRetry(filePath: invariantFilePath)
            
        case .success:
            // If we get here, then we are done uploading to S3. Mark the file and clean up the temp file.
            async let success = nativeUploadManager.markUploadFileFinished(filePath: invariantFilePath, uploadSessionId: uploadSessionId)
            sandboxFileManager.removeTempFile(filePath: invariantFilePath)
            if await !success {
                // If we aren't successful in sending the completion then enqueue for retry
                await enqueueForRetry(filePath: invariantFilePath, uploaded: true)
            }
        }
    }
    
    private func handleUnrecoverableFailure(filePath: String) {
        nativeUploadManager.markUploadUnrecoverableFailure(filePath: filePath)
        // TODO: syoung 08/24/2023 If something "unrecoverable" happens, do we want to remove the file or just leave it?
        sandboxFileManager.removeTempFile(filePath: filePath)
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
                let retry = self.taskToRetryAllPendingUploads(isBackground: true)
                let _ = await retry.result
                task.setTaskCompleted(success: true)
                self.scheduleBackgroundProcessingIfNeeded()
            }
        }
        #if canImport(UIKit)
        // Set up a listener to retry temporarily-failed uploads whenever the app becomes active
        self.appBackgroundObserver = NotificationCenter.default.addObserver(forName: UIApplication.didEnterBackgroundNotification) {
            // when entering the background, we want to cancel waiting to retry uploads
            Logger.log(severity: .info, tag: .upload, message: "App did enter background. Scheduling background processing if needed.")
            self.waitRetryTask?.cancel()
            self.scheduleBackgroundProcessingIfNeeded()
        }
        #endif
    }
    
    @MainActor
    func scheduleBackgroundProcessingIfNeeded() {
        // Only schedule background processing if there are pending uploads.
        guard nativeUploadManager.hasPendingUploads() || isArchiving,
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

    /// The minimum delay before retrying a failed upload (in seconds). This is a variable so that unit
    /// tests can run without waiting.
    var delayForRetry: TimeInterval = 5 * 60
    
    private var appActiveObserver: Any?
    private var waitRetryTask: Task<Void, Never>?
    private var checkRetryTask: Task<Void, Never>?
    
    @MainActor
    func setupCheckAndRetryUploads() throws {
        guard self.appActiveObserver == nil else {
            throw BridgeUnexpectedNullError(category: .duplicateCall, message: "Attempting to setup listening to app active multiple times")
        }
        
        #if canImport(UIKit)
        // Set up a listener to retry temporarily-failed uploads whenever the app becomes active
        self.appActiveObserver = NotificationCenter.default.addObserver(forName: UIApplication.didBecomeActiveNotification) {
            Logger.log(severity: .info, message: "App did enter foreground. Check and retry uploads.")
            self.checkAndRetryUploads()
        }
        #endif
    }
    
    @MainActor
    func checkAndRetryUploads() {
        guard !backgroundNetworkManager.isAppBackground else {
            Logger.log(severity: .info, tag: .upload, message: "Attempting to check and retry uploads from the background")
            return
        }
        guard checkRetryTask?.isCancelled ?? true else {
            Logger.log(severity: .info, tag: .upload, message: "Check and retry already running. Ignoring.")
            return
        }
        
        #if canImport(UIKit)
        let taskId = UIApplication.shared.beginBackgroundTask {
            Logger.log(tag: .upload,
                       error: BridgeUploadFailedError(category: .backgroundTaskTimeout, message: "Timed out when checking and retrying uploads.")
            )
            self.checkRetryTask?.cancel()
        }
        #endif
        
        checkRetryTask = Task(priority: .background) {
            
            // retry all pending uploads
            let task = taskToRetryAllPendingUploads(isBackground: false)
            let _ = await task.result
            
            // check if we still have pending uploads and schedule a retry
            if nativeUploadManager.hasPendingUploads() {
                enqueueForRetry()
            }
            
            #if canImport(UIKit)
            // finally, send message that we are finished with our background tasks
            UIApplication.shared.endBackgroundTask(taskId)
            #endif
        }
    }
    
    @MainActor
    var retryTask: Task<Void, Never>?
       
    @MainActor
    func taskToRetryAllPendingUploads(isBackground: Bool) -> Task<Void, Never> {
        if retryTask == nil {
            retryTask = Task(priority: .background) {
                do {
                    // retry all uploads
                    try await retryUploadToS3()
                    try await processFinishedUploads()
                    try await cleanupLostFiles()
                    
                } catch is CancellationError {
                    Logger.log(severity: .info, tag: .upload, message: "Check and retry uploads cancelled")
                } catch {
                    Logger.log(tag: .upload, error: error, message: "Unexpected failure when checking and retrying uploads")
                }
            }
        }
        return retryTask!
    }
    
    @MainActor
    private func enqueueForRetry(filePath: String? = nil, uploaded: Bool = false) {
        guard !backgroundNetworkManager.isAppBackground else {
            Logger.log(severity: .info, tag: .upload, message: "Attempting to enqueue file for retry in the background. Ignoring.")
            return
        }
        // Start with the simpliest case of retrying everything
        // TODO: syoung 08/28/2023 Revisit whether or not we need to only retry the one file
        guard waitRetryTask?.isCancelled ?? true else { return }
        waitRetryTask = Task(priority: .background) {
            do {
                try await Task.sleep(nanoseconds: UInt64(delayForRetry * 1_000_000_000))
                checkAndRetryUploads()
            } catch is CancellationError {
                Logger.log(severity: .info, tag: .upload, message: "Wait for check and retry uploads cancelled")
            } catch {
                Logger.log(tag: .upload, error: error, message: "Unexpected failure waiting to retry upload")
            }
        }
    }
    
    func processFinishedUploads() async throws {
        // process the finished uploads - this is the last call and can take a while
        // TODO: syoung 08/23/2023 We need to revisit this for the case where there are *a lot*
        // of completion messages to send (since they are all set serially) so that this process
        // doesn't timeout and get killed by the OS.
        let _ = try await nativeUploadManager.processFinishedUploads()
        guard !Task.isCancelled else {
            throw CancellationError()
        }
    }
    
    func retryUploadToS3() async throws {
        
        // get all the currently running upload tasks that can be handled by this manager
        async let allUrlSessionTasks = backgroundNetworkManager.getAllTasks()
        // get all the files that are currently pending
        async let allPendingUploads = nativeUploadManager.getPendingUploadFiles()
        
        // check that the task is not cancelled
        guard !Task.isCancelled else {
            throw CancellationError()
        }
        
        // Look through all the currect url session tasks and figure out which should be restarted
        var uploadsToRetry = Set(await allPendingUploads)
        for urlSessionTask in await allUrlSessionTasks {
            guard self.canHandle(task: urlSessionTask),
                  let uploadId = urlSessionTask.parsePendingUpload()
            else {
                Logger.log(severity: .info, tag: .upload, message: "Skipping URLSessionTask \(urlSessionTask) - does not match pattern of tasks handled by the UploadManager.")
                continue
            }
            let requiresRestart = uploadsToRetry.contains(.init(filePath: uploadId.filePath, uploadSessionId: nil))
            switch urlSessionTask.state {
            case .running, .suspended:
                if requiresRestart {
                    // upload session id has expired - need to restart
                    Logger.log(severity: .info, tag: .upload, message: "Found expired URLSessionTask for \(uploadId) - cancelling task")
                    urlSessionTask.cancel()
                }
                else {
                    // If the session is still valid, then check if it needs to be resumed.
                    if urlSessionTask.state == .suspended {
                        Logger.log(severity: .warn, tag: .upload, message: "Found valid suspended URLSessionTask for \(uploadId) - resuming")
                        urlSessionTask.resume()
                    }
                    if let _ = uploadsToRetry.remove(uploadId) {
                        Logger.log(severity: .info, tag: .upload, message: "Found valid running URLSessionTask for \(uploadId) - not restarting")
                    }
                }
                
            default:
                // TODO: syoung 08/28/2023 Do we need to do more handling for cancelled or completed tasks?
                Logger.log(severity: .info, tag: .upload, message: "Found URLSessionTask for \(uploadId) - state=\(urlSessionTask.state)")
                break
            }
        }
        
        // fetch the uploads to retry
        for upload in uploadsToRetry {
            // check that the task is not cancelled
            guard !Task.isCancelled else {
                throw CancellationError()
            }
            let uploadSession = await nativeUploadManager.requestUploadSession(filePath: upload.filePath)
            await handleS3UploadRequest(filePath: upload.filePath, uploadSession: uploadSession)
        }
    }
    
    @MainActor
    private func handleS3UploadRequest(filePath: String, uploadSession: S3UploadSession?) {
        if let uploadSession = uploadSession {
            // If there is an upload session then start the upload.
            startS3Upload(uploadSession)
        }
        else {
            // If the callback is nil then services are offline. Try again later.
            enqueueForRetry(filePath: filePath)
        }
    }
    
    func cleanupLostFiles() async throws {
        // TODO: syoung 08/25/2023 Implement
    }
}

enum HTTPS3UploadStatus {
    case success, retry, unhandled
}

extension HTTPURLResponse {
    func httpUploadStatus() -> HTTPS3UploadStatus {
        if statusCode < 300 {
            return .success
        }
        else {
            switch statusCode {
            case 403, 409, 500, 503:
                // 403: for our purposes means the pre-signed url timed out before starting the actual upload to S3.
                // 409: in our case it could only mean a temporary conflict (resource locked by another process, etc.) that should be retried.
                // 500: means internal server error ("We encountered an internal error. Please try again.")
                // 503: means service not available or the requests are coming too fast, so try again later.
                // In any case, we'll retry after a minimum delay to avoid spamming retries.
                return .retry
                
            default:
                // iOS handles redirects automatically so only e.g. 304 resource not changed etc. from the 300 range should end up here
                // (along with all unhandled 4xx and 5xx of course).
                return .unhandled
            }
        }
    }
}

extension BridgeURLSessionTask {
    
    fileprivate func parseTaskDescription() throws -> (sessionId: String, invariantFilePath: String) {
        guard let identifier = taskDescription else {
            throw BridgeUnexpectedNullError(category: .empty, message: "The `taskDescription` should not be NULL for an S3 upload.")
        }
        let split = identifier.components(separatedBy: "|")
        guard split.count == 2 else {
            throw BridgeUnexpectedNullError(category: .missingIdentifier, message: "The `taskDescription` should include the '|' character to separate the components of the identifier: \(identifier)")
        }
        return (split[0], split[1])
    }
    
    fileprivate func parsePendingUpload() -> PendingUploadFile? {
        guard let (sessionId, filePath) = try? parseTaskDescription() else {
            return nil
        }
        return .init(filePath: filePath, uploadSessionId: sessionId)
    }
}

extension NotificationCenter {
    func addObserver(forName name: NSNotification.Name, callback: @escaping @MainActor () -> Void) -> NSObjectProtocol {
        addObserver(forName: name, object: nil, queue: .main) { _ in
            Task {
                await callback()
            }
        }
    }
}

// Use a protocol to wrap the background network manager - this is to allow using a mock for testing.
protocol SharedBackgroundUploadManager : AnyObject {
    @MainActor var isAppBackground: Bool { get }
    var sessionDelegateQueue: OperationQueue { get }
    func registerBackgroundTransferHandler(_ handler: BridgeURLSessionHandler)
    @discardableResult func uploadFile(_ fileURL: URL, httpHeaders: [String : String]?, to urlString: String, taskDescription: String) -> Bool
    func getAllTasks() async -> [BridgeURLSessionTask]
}

extension BackgroundNetworkManager : SharedBackgroundUploadManager {
    
    @MainActor
    var isAppBackground: Bool {
        #if canImport(UIKit)
        return UIApplication.shared.applicationState == .background
        #else
        return false
        #endif
    }
}

// Use a protocol to wrap the native upload manager - this is to allow using a mock for testing.
protocol BridgeClientUploadManager : AnyObject {
    func hasPendingUploads() -> Bool
    func getPendingUploadFiles() async -> [PendingUploadFile]
    func queueAndRequestUploadSession(uploadFile: UploadFile) async -> S3UploadSession?
    func requestUploadSession(filePath: String) async -> S3UploadSession?
    func markUploadFileFinished(filePath: String, uploadSessionId: String) async -> Bool
    func markUploadUnrecoverableFailure(filePath: String)
    func processFinishedUploads() async throws -> Bool
}

extension NativeUploadManager : BridgeClientUploadManager {
    
    func getPendingUploadFiles() async -> [PendingUploadFile] {
        return await withCheckedContinuation { continuation in
            self.getPendingUploadFiles() { ret in
                continuation.resume(returning: ret)
            }
        }
    }
    
    func queueAndRequestUploadSession(uploadFile: UploadFile) async -> S3UploadSession? {
        return await withCheckedContinuation { continuation in
            self.queueAndRequestUploadSession(uploadFile: uploadFile) { session in
                continuation.resume(returning: session)
            }
        }
    }
    
    func requestUploadSession(filePath: String) async -> S3UploadSession? {
        return await withCheckedContinuation { continuation in
            self.requestUploadSession(filePath: filePath) { session in
                continuation.resume(returning: session)
            }
        }
    }
    
    func markUploadFileFinished(filePath: String, uploadSessionId: String) async -> Bool {
        return await withCheckedContinuation { continuation in
            self.markUploadFileFinished(filePath: filePath, uploadSessionId: uploadSessionId) { result in
                continuation.resume(returning: result.boolValue)
            }
        }
    }
    
    func processFinishedUploads() async throws -> Bool {
        return await withCheckedContinuation { continuation in
            self.processFinishedUploads() { result in
                continuation.resume(returning: result.boolValue)
            }
        }
    }
}


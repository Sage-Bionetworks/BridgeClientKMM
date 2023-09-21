// Created 7/26/23
// swift-tools-version:5.0

import Foundation
import BackgroundTasks
import BridgeClient

#if canImport(UIKit)
import UIKit
#endif

class UploadManager : NSObject, BridgeURLSessionHandler, BackgroundProcessSyncDelegate {

    weak private(set) var backgroundNetworkManager: SharedBackgroundUploadManager!
    let sandboxFileManager: SandboxFileManager
    let nativeUploadManager: BridgeClientUploadManager
    lazy private(set) var syncManager: BackgroundProcessSyncManager = .init(delegate: self)
    
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
            return try sandboxFileManager.createSubdirectory(baseURL: baseURL, subdir: subdir)
        } catch {
            Logger.log(tag: .upload, error: error, message: "Error trying to create the shared app support directory.")
            return nil
        }
    }()
    
    var isArchiving: Bool = false
    
    /// **Required:** This method should be called on app launch to register the background
    /// process id and set up the listeners for app becoming active and entering the
    /// background.
    @MainActor
    func onLaunch(backgroundProcessId: String?) {
        syncManager.onLaunch(backgroundProcessId: backgroundProcessId)
    }
    
    /// Force check and retry uploads.
    func checkAndRetryUploads() {
        Task {
            await syncManager.retryBackgroundProcessAsync()
        }
    }
    
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
        guard let uploadDirURL = self.uploadDir(for: s3UploadType),
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
        if let uploadSession = await nativeUploadManager.queueAndRequestUploadSession(uploadFile: uploadFile) {
            // If there is an upload session then start the upload.
            startS3Upload(uploadSession)
        }
        else {
            // If the callback is nil then services are offline. Try again later.
            await enqueueForRetry(filePath: invariantFilePath, uploaded: false)
        }

        return true
    }
    
    fileprivate func uploadDir(for s3UploadType: S3UploadType) -> URL? {
        guard let baseURL = uploadDirURL else { return nil }
        do {
            return try sandboxFileManager.createSubdirectory(baseURL: baseURL, subdir: s3UploadType.name)
        } catch {
            Logger.log(tag: .upload, error: error, message: "Error trying to create the uploads directory for \(s3UploadType.name).")
            return nil
        }
    }
    
    // MARK: BackgroundProcessSyncDelegate

    var shouldScheduleBackgroundProcess: Bool {
        isArchiving || nativeUploadManager.hasPendingUploads()
    }
    
    func retryBackgroundProcess(isBackground: Bool) async throws {
        try await retryUploadToS3()
        try await processFinishedUploads()
        try await cleanupLostFiles()
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
            await enqueueForRetry(filePath: invariantFilePath, uploaded: false)
            
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

    func bridgeUrlSession(_ session: any BridgeURLSession, didBecomeInvalidWithError error: Error?) {
        // If a url session becomes invalid, just queue up a delayed retry
        Task {
            await syncManager.enqueueForRetry()
        }
    }
    
    // MARK: Private methods
    
    func urlUploadTaskIdentifier(filePath: String, uploadSessionId: String) -> String {
        "\(uploadSessionId)|\(filePath)"
    }
    
    private func startS3Upload(_ uploadSession: S3UploadSession) {
        let fileURL = sandboxFileManager.fileURL(of: uploadSession.filePath)
        let taskIdentifier = urlUploadTaskIdentifier(filePath: uploadSession.filePath, uploadSessionId: uploadSession.uploadSessionId)
        backgroundNetworkManager.uploadFile(fileURL,
                                            httpHeaders: uploadSession.requestHeaders,
                                            to: uploadSession.url,
                                            taskDescription: taskIdentifier)
    }
    
    private func handleUnrecoverableFailure(filePath: String) {
        nativeUploadManager.markUploadUnrecoverableFailure(filePath: filePath)
        // TODO: syoung 08/24/2023 If something "unrecoverable" happens, do we want to remove the file or just leave it?
        sandboxFileManager.removeTempFile(filePath: filePath)
    }
    
    func enqueueForRetry(filePath: String, uploaded: Bool) async {
        // TODO: syoung 08/29/2023 Consider if we need to *only* retry the one file?
        await syncManager.enqueueForRetry()
    }
    
    private func processFinishedUploads() async throws {
        // process the finished uploads - this is the last call and can take a while
        // TODO: syoung 08/23/2023 We need to revisit this for the case where there are *a lot*
        // of completion messages to send (since they are all set serially) so that this process
        // doesn't timeout and get killed by the OS.
        guard !Task.isCancelled else {
            throw CancellationError()
        }
        let _ = try await nativeUploadManager.processFinishedUploads()
    }
    
    private func retryUploadToS3() async throws {
        
        // get all the currently running upload tasks that can be handled by this manager
        async let allUrlSessionTasks = backgroundNetworkManager.getAllTasks()
        // get all the files that are currently pending
        async let allPendingUploads = nativeUploadManager.getPendingUploadFiles()
        
        // look through all the currect url session tasks and figure out which should be restarted
        var uploadsToRetry = Set(await allPendingUploads)
        for urlSessionTask in await allUrlSessionTasks {
            // check that the task is not cancelled
            guard !Task.isCancelled else {
                throw CancellationError()
            }
            // check that this is an upload task handled by this manager
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
            // request an upload session and if non-nil, then start it
            if let uploadSession = await nativeUploadManager.requestUploadSession(filePath: upload.filePath) {
                startS3Upload(uploadSession)
            }
        }
    }

    private func cleanupLostFiles() async throws {
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


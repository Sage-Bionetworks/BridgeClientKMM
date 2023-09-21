// Created 8/1/23
// swift-tools-version:5.0

import XCTest
import BridgeClient
import JsonModel
@testable import BridgeClientExtension

final class UploadManagerTests: XCTestCase {

    override func setUpWithError() throws {
        // Put setup code here. This method is called before the invocation of each test method in the class.
    }

    override func tearDownWithError() throws {
        // Put teardown code here. This method is called after the invocation of each test method in the class.
    }
    
    let expectedTempFileDir = "/App Support/BridgeUploadsV2/STUDY_DATA/"
    
    fileprivate func createUploadManager() -> (manager: TestUploadManager, mock: Mock) {
        let mock = Mock()
        let manager = TestUploadManager(
            backgroundNetworkManager: mock.networkManager,
            sandboxFileManager: mock.sandboxFileManager,
            nativeUploadManager: mock.nativeManager)
        let fakePath = "\(fakeBaseDirectory)/App Support/\(manager.subdir)"
        manager.uploadDirURL = URL(fileURLWithPath: fakePath, isDirectory: true)
        
        XCTAssertEqual(1, mock.networkManager.registeredHandlers.count)
        XCTAssertEqual(manager, mock.networkManager.registeredHandlers.first as? UploadManager)
        
        return (manager, mock)
    }
    
    // MARK: Upload study data archive

    func testUploadArchive_Offline() async {
        let (manager, mock) = createUploadManager()
        let (fileURL, schedule, startedOn) = mock.sandboxFileManager.setupFakeArchive()
        
        // -- Method under test
        let success = await manager.uploadEncryptedArchive(fileUrl: fileURL, schedule: schedule, startedOn: startedOn)
        XCTAssertTrue(success)
        
        // independent of network connectivity, the file should be copied and queued for upload
        XCTAssertEqual(mock.nativeManager.queuedUploadFiles.count, 1)
        guard let uploadFile = mock.nativeManager.queuedUploadFiles.first else {
            XCTFail("Unexpected NULL")
            return
        }
        XCTAssertEqual(fileURL, mock.sandboxFileManager.copyFileCalls[uploadFile.filePath])
        checkUploadFileExpectations(uploadFile)
        
        // and b/c the native upload manager failed to return an S3UploadSession, it should be
        // queued to retry upload
        XCTAssertEqual([uploadFile.filePath : false], manager.retryQueue)
    }
    
    func testUploadArchive_Online() async throws {
        let (manager, mock) = createUploadManager()
        let (fileURL, schedule, startedOn) = mock.sandboxFileManager.setupFakeArchive()
        let requestHeaders = ["foo" : "magoo"]
        mock.nativeManager.queuedS3UploadSession = .init(
            filePath: "ignored",
            contentType: "application/zip",
            uploadSessionId: "not-a-real-uploadSessionId-0",
            url: "https://not-a-real-org.org/not-a-real-url",
            requestHeaders: requestHeaders)
        
        // -- Method under test
        let success = await manager.uploadEncryptedArchive(fileUrl: fileURL, schedule: schedule, startedOn: startedOn)
        XCTAssertTrue(success)
        
        // Independent of network connectivity, the file should be copied and queued for upload
        XCTAssertEqual(mock.nativeManager.queuedUploadFiles.count, 1)
        guard let uploadFile = mock.nativeManager.queuedUploadFiles.first else {
            XCTFail("Unexpected NULL")
            return
        }
        XCTAssertEqual(fileURL, mock.sandboxFileManager.copyFileCalls[uploadFile.filePath])
        checkUploadFileExpectations(uploadFile)
        
        // If successful in requesting an S3UploadSession then the upload manager should
        // call the network manager with that request.
        XCTAssertEqual(mock.networkManager.uploadRequests.count, 1)
        XCTAssertEqual(1, mock.sandboxFileManager.copyTempFiles.count)
        guard let uploadTask = mock.networkManager.uploadRequests.first,
              let tempFile = mock.sandboxFileManager.copyTempFiles.first
        else {
            XCTFail("Unexpected NULL")
            return
        }
        
        let expectedIdentifier = "not-a-real-uploadSessionId-0|\(uploadFile.filePath)"
        XCTAssertEqual(expectedIdentifier, uploadTask.taskDescription)
        XCTAssertEqual(requestHeaders, uploadTask.httpHeaders)
        XCTAssertEqual(tempFile, uploadTask.fileURL)
        XCTAssertEqual("https://not-a-real-org.org/not-a-real-url", uploadTask.urlString)
        
        // Check if the manager can handle the upload response
        XCTAssertTrue(manager.canHandle(task: uploadTask))
    }
    
    func checkUploadFileExpectations(_ uploadFile: UploadFile ) {
        XCTAssertEqual("application/zip", uploadFile.contentType)
        XCTAssertEqual(1024, uploadFile.fileLength)
        XCTAssertEqual("not-a-real-md5Hash", uploadFile.md5Hash)
        XCTAssertTrue(uploadFile.encrypted)
        XCTAssertEqual(.studyData, uploadFile.s3UploadType)
        XCTAssertNotNil(uploadFile.metadata)
        XCTAssertEqual("not-a-real-instanceGuid", uploadFile.metadata?.instanceGuid)
        XCTAssertEqual("not-a-real-eventTimestamp", uploadFile.metadata?.eventTimestamp)
        XCTAssertNotNil(uploadFile.metadata?.startedOn)
        XCTAssertTrue(uploadFile.filePath.hasPrefix(expectedTempFileDir), "\(uploadFile.filePath) does not have expected prefix")
    }
    
    // MARK: Upload S3 responses
    
    fileprivate func createS3UploadTask(_ manager: TestUploadManager, _ mock: Mock) -> (filePath: String, uploadId: String, uploadTask: MockBackgroundNetworkManager.UploadRequest) {
        let filePath = "\(expectedTempFileDir)not-a-real-file"
        let uploadId = "not-a-real-uploadSessionId-0"
        let uploadTask = MockBackgroundNetworkManager.UploadRequest(
            fileURL: mock.sandboxFileManager.fileURL(of: filePath),
            httpHeaders: ["foo" : "magoo"],
            urlString: "https://not-a-real-org.org/\(uploadId)/not-a-real-url",
            taskDescription: manager.urlUploadTaskIdentifier(filePath: filePath, uploadSessionId: uploadId))
        
        // check test setup assumptions
        XCTAssertTrue(manager.canHandle(task: uploadTask))
        
        return (filePath, uploadId, uploadTask)
    }
    
    func testS3UploadResponse_HappyPath() async throws {
        let (manager, mock) = createUploadManager()
        let (filePath, _, uploadTask) = createS3UploadTask(manager, mock)
        
        // for the happy path, the S3 response code is 200
        uploadTask.setResponse(statusCode: 200)
        // and the native upload was successful
        mock.nativeManager.uploadFinishedResponse[filePath] = true

        // -- Method under test
        
        // Once the S3 upload is complete, the shared network manager will call back to the upload manager.
        // This should fire a call to the native upload manager (Kotlin) that will then attempt to mark the
        // file as done.
        try await manager.urlSession(task: uploadTask, didCompleteWithError: nil)

        // Check that the file was marked as uploaded
        XCTAssertEqual([filePath], mock.nativeManager.uploadFinished)
        // Check for file deleted
        XCTAssertEqual([filePath], mock.sandboxFileManager.removeTempFiles)
        // Check that the file was *not* queued for retry
        XCTAssertEqual([:], manager.retryQueue)
    }
    
    func checkRetryS3Failure(statusCode: Int) async throws {
        let (manager, mock) = createUploadManager()
        let (filePath, _, uploadTask) = createS3UploadTask(manager, mock)
        
        uploadTask.setResponse(statusCode: statusCode)

        // -- Methods under test
        
        // Once the S3 upload is complete, the shared network manager will call back to the upload manager.
        // This should fire a call to the native upload manager (Kotlin) that will then attempt to mark the
        // file as done.
        try await manager.urlSession(task: uploadTask, didCompleteWithError: nil)

        // check that the file was not marked for upload
        XCTAssertEqual([], mock.nativeManager.uploadFinished)
        // and that the file was not removed
        XCTAssertEqual([], mock.sandboxFileManager.removeTempFiles)
        // but it is marked for retry
        XCTAssertEqual([filePath:false], manager.retryQueue)
    }
    
    func testS3UploadResponse_403() async throws {
        try await checkRetryS3Failure(statusCode: 403)
    }
    
    func testS3UploadResponse_409() async throws {
        try await checkRetryS3Failure(statusCode: 409)
    }
    
    func testS3UploadResponse_500() async throws {
        try await checkRetryS3Failure(statusCode: 500)
    }
    
    func testS3UploadResponse_503() async throws {
        try await checkRetryS3Failure(statusCode: 503)
    }
    
    // MARK: Sanity checks of Kotlin framework
    
    func testKotlinDataClassEquality() {
        // Check to make sure that data classes are properly handling equality and hash value.
        let obj1 = PendingUploadFile(filePath: "/foo/goo/laroo", uploadSessionId: "1234567890")
        let obj2 = PendingUploadFile(filePath: "/foo/goo/laroo", uploadSessionId: "1234567890")
        XCTAssertEqual(obj1, obj2)
        XCTAssertEqual(obj1.hashValue, obj2.hashValue)
    }

}

fileprivate let fakeBaseDirectory = "/Foo/48B0BAEB-94C4-4158-953C-74AB0935E5FA"

class TestUploadManager : UploadManager {
    var retryQueue: [String : Bool] = [:]
    
    override func enqueueForRetry(filePath: String, uploaded: Bool) async {
        // Do not call through to the sync manager
        retryQueue[filePath] = uploaded
    }
}

/// Used to hold onto the mocks so they aren't prematurely released
fileprivate class Mock {
    let networkManager: MockBackgroundNetworkManager = .init()
    let sandboxFileManager: MockSandboxFileManager = .init()
    let nativeManager: MockNativeUploadManager = .init()
}

class MockSandboxFileManager : SandboxFileManager {
    
    var removeTempFiles: [String] = []
    var copyTempFiles: [URL] = []
    var copyFileCalls: [String : URL] = [:]
    var touchCalls: [URL : Date] = [:]
    var contentLengthMap: [URL : Int] = [:]
    var md5Map: [URL : String] = [:]

    override init() {
        super.init()
        self.baseDirectory = fakeBaseDirectory
    }
    
    override func copyFile(from fileURL: URL, to tempFileURL: URL) -> Bool {
        let invariantPath = self.sandboxRelativePath(of: tempFileURL)
        copyTempFiles.append(tempFileURL)
        copyFileCalls[invariantPath] = fileURL
        return true
    }
    
    override func removeTempFile(filePath: String) {
        removeTempFiles.append(filePath)
    }
    
    override func touch(fileUrl: URL) {
        touchCalls[fileUrl] = Date()
    }
    
    override func fileContentLength(_ fileUrl: URL) -> Int? {
        contentLengthMap[fileUrl] ?? copyFileCalls[sandboxRelativePath(of: fileUrl)].flatMap { contentLengthMap[$0] }
    }
    
    override func fileMD5String(_ fileUrl: URL) -> String? {
        md5Map[fileUrl] ?? copyFileCalls[sandboxRelativePath(of: fileUrl)].flatMap { md5Map[$0] }
    }
    
    override func createSubdirectory(baseURL: URL, subdir: String) throws -> URL {
        baseURL.appendingPathComponent(subdir, isDirectory: true)
    }
    
    func setupFakeArchive() -> (URL, AssessmentScheduleInfo, Date) {
        let now = Date()
        let schedule = AssessmentScheduleInfo(
            instanceGuid: "not-a-real-instanceGuid",
            session: .init(instanceGuid: UUID().uuidString,
                           eventTimestamp: "not-a-real-eventTimestamp",
                           scheduledOn: now.addingTimeInterval(-60*60),
                           assessments: ["not-a-real-guid"]),
            assessmentInfo: .init(identifier: "not-a-real-assessmentIdentifier",
                                  key: nil,
                                  guid: "not-a-real-guid",
                                  label: nil))
        let filename = UUID().uuidString
        let fileURL = URL(fileURLWithPath: "\(fakeBaseDirectory)/tmp/\(filename).zip.encypted")
        let startedOn = now.addingTimeInterval(-5*60)
        contentLengthMap[fileURL] = 1024
        md5Map[fileURL] = "not-a-real-md5Hash"
        return (fileURL, schedule, startedOn)
    }
    
}

class MockBackgroundNetworkManager : NSObject, SharedBackgroundUploadManager {

    let mockURLSession: MockURLSession = MockURLSession()
    
    let sessionDelegateQueue: OperationQueue = {
        let delegateQueue = OperationQueue()
        delegateQueue.maxConcurrentOperationCount = 1
        return delegateQueue
    }()

    var isAppBackground: Bool = false
    
    var registeredHandlers: [BridgeURLSessionHandler] = []
    var uploadRequests: [UploadRequest] = []
    var tasks: [BridgeURLSessionTask] = []
    
    func registerBackgroundTransferHandler(_ handler: BridgeURLSessionHandler) {
        registeredHandlers.append(handler)
    }
    
    @discardableResult
    func uploadFile(_ fileURL: URL, httpHeaders: [String : String]?, to urlString: String, taskDescription: String) -> Bool {
        let request: UploadRequest = .init(fileURL: fileURL, httpHeaders: httpHeaders, urlString: urlString, taskDescription: taskDescription)
        uploadRequests.append(request)
        return true
    }
    
    class UploadRequest : NSObject, BridgeURLSessionUploadTask {
        let fileURL: URL
        let httpHeaders: [String : String]?
        let urlString: String
        var taskDescription: String?
        var state: URLSessionTask.State = .running
        
        init(fileURL: URL, httpHeaders: [String : String]?, urlString: String, taskDescription: String) {
            self.fileURL = fileURL
            self.httpHeaders = httpHeaders
            self.urlString = urlString
            self.taskDescription = taskDescription
            self.originalRequest = URL(string: urlString).map {
                var request = URLRequest(url: $0)
                request.allHTTPHeaderFields = httpHeaders
                request.httpMethod = HTTPMethod.PUT.rawValue
                return request
            }
        }
        
        var taskType: BridgeClientExtension.BridgeURLSessionTaskType {
            .upload
        }
        
        var originalRequest: URLRequest?
        var response: URLResponse?
        
        var didCallResume: Bool = false
        var didCallCancel: Bool = false
        
        func setResponse(statusCode: Int) {
            self.response = HTTPURLResponse(url: URL(string: urlString)!, statusCode: statusCode, httpVersion: nil, headerFields: nil)
        }
        
        func resume() {
            didCallResume = true
        }
        
        func cancel() {
            didCallCancel = true
        }
    }
    
    func getAllTasks() async -> [BridgeURLSessionTask] {
        tasks
    }
}

class MockNativeUploadManager : NSObject, BridgeClientUploadManager {

    var queuedUploadFiles: [UploadFile] = []
    var queuedS3UploadSession: S3UploadSession?
    
    var uploadFiles: [String] = []
    var s3Uploads: [String : S3UploadSession] = [:]
    var uploadFinished: [String] = []
    var uploadFailedPermanently: [String] = []
    var uploadFinishedResponse: [String : Bool] = [:]
    var processFinishedUploadsResponse: Bool = false
    
    func getPendingUploadFiles() async -> [PendingUploadFile] {
        uploadFiles.map {
            .init(filePath: $0, uploadSessionId: s3Uploads[$0]?.uploadSessionId)
        }
    }

    func hasPendingUploads() -> Bool {
        uploadFiles.count > 0 || uploadFinishedResponse.count > 0
    }
    
    func queueAndRequestUploadSession(uploadFile: UploadFile) async -> S3UploadSession? {
        queuedUploadFiles.append(uploadFile)
        return queuedS3UploadSession.map {
            .init(filePath: uploadFile.filePath,
                  contentType: $0.contentType,
                  uploadSessionId: $0.uploadSessionId,
                  url: $0.url,
                  requestHeaders: $0.requestHeaders)
        }
    }
    
    func requestUploadSession(filePath: String) async -> S3UploadSession? {
        return s3Uploads[filePath]
    }
    
    func markUploadFileFinished(filePath: String, uploadSessionId: String) async -> Bool {
        uploadFinished.append(filePath)
        return uploadFinishedResponse[filePath] ?? false
    }
    
    func markUploadUnrecoverableFailure(filePath: String) {
        uploadFailedPermanently.append(filePath)
    }
    
    func processFinishedUploads() async -> Bool {
        return processFinishedUploadsResponse
    }
}

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

    @MainActor
    func createUploadManager() -> (UploadManager, MockBackgroundNetworkManager, MockSandboxFileManager, MockNativeUploadManager) {
        let bnm: MockBackgroundNetworkManager = .init()
        let sfm: MockSandboxFileManager = .init()
        let num: MockNativeUploadManager = .init()
        let manager = UploadManager(
            backgroundNetworkManager: bnm,
            sandboxFileManager: sfm,
            nativeUploadManager: num)
        let fakePath = "\(fakeBaseDirectory)/App Support/\(manager.subdir)"
        manager.uploadDirURL = URL(fileURLWithPath: fakePath, isDirectory: true)
        
        XCTAssertEqual(1, bnm.registeredHandlers.count)
        XCTAssertEqual(manager, bnm.registeredHandlers.first as? UploadManager)
        
        return (manager, bnm, sfm, num)
    }
    
    @MainActor
    func testUploadArchive_Offline() async {
        let (manager, mockNetworkManager, mockSandboxFileManager, mockNativeManager) = createUploadManager()
        let (fileURL, schedule, startedOn) = mockSandboxFileManager.setupFakeArchive()
        
        // Method under test
        let success = await manager.uploadEncryptedArchive(fileUrl: fileURL, schedule: schedule, startedOn: startedOn)
        XCTAssertTrue(success)
        
        // Independent of network connectivity, the file should be copied and queued for upload
        XCTAssertEqual(mockNativeManager.queuedUploadFiles.count, 1)
        guard let uploadFile = mockNativeManager.queuedUploadFiles.first else {
            XCTFail("Unexpected NULL")
            return
        }
        XCTAssertEqual(fileURL, mockSandboxFileManager.copyFileCalls[uploadFile.filePath])
        checkUploadFileExpectations(uploadFile)
        
        // TODO: syoung 08/03/2023 Decide what to require before retrying the upload and test it.
        
    }
    
    @MainActor
    func testUploadArchive_Online_HappyPath() async throws {
        let (manager, mockNetworkManager, mockSandboxFileManager, mockNativeManager) = createUploadManager()
        let (fileURL, schedule, startedOn) = mockSandboxFileManager.setupFakeArchive()
        let requestHeaders = ["foo" : "magoo"]
        mockNativeManager.queuedS3UploadSession = .init(
            filePath: "ignored",
            contentType: "application/zip",
            uploadSessionId: "not-a-real-uploadSessionId-0",
            url: "https://not-a-real-org.org/not-a-real-url",
            requestHeaders: requestHeaders)
        
        // Method under test
        let success = await manager.uploadEncryptedArchive(fileUrl: fileURL, schedule: schedule, startedOn: startedOn)
        XCTAssertTrue(success)
        
        // Independent of network connectivity, the file should be copied and queued for upload
        XCTAssertEqual(mockNativeManager.queuedUploadFiles.count, 1)
        guard let uploadFile = mockNativeManager.queuedUploadFiles.first else {
            XCTFail("Unexpected NULL")
            return
        }
        XCTAssertEqual(fileURL, mockSandboxFileManager.copyFileCalls[uploadFile.filePath])
        checkUploadFileExpectations(uploadFile)

        // If successful in requesting an S3UploadSession then the upload manager should
        // call the network manager with that request.
        XCTAssertEqual(mockNetworkManager.uploadRequests.count, 1)
        XCTAssertEqual(1, mockSandboxFileManager.copyTempFiles.count)
        guard let uploadTask = mockNetworkManager.uploadRequests.first,
              let tempFile = mockSandboxFileManager.copyTempFiles.first
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
        
        // Once the S3 upload is complete, the shared network manager will call back to the upload manager.
        // This should fire a call to the native upload manager (Kotlin) that will then attempt to mark the
        // file as done.
        uploadTask.setResponse(statusCode: 200)
        try await manager.urlSession(task: uploadTask, didCompleteWithError: nil)
        
        // Check that the file was marked as uploaded
        XCTAssertEqual([uploadFile.filePath], mockNativeManager.uploadFinished)
        // Check for file deleted
        XCTAssertEqual([uploadFile.filePath], mockSandboxFileManager.removeTempFiles)
        
        // TODO: syoung 08/23/2023 Check for processessing uploads requested
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
    }
    
    func testKotlinDataClassEquality() {
        // Check to make sure that data classes are properly handling equality and hash value.
        let obj1 = PendingUploadFile(filePath: "/foo/goo/laroo", uploadSessionId: "1234567890")
        let obj2 = PendingUploadFile(filePath: "/foo/goo/laroo", uploadSessionId: "1234567890")
        XCTAssertEqual(obj1, obj2)
        XCTAssertEqual(obj1.hashValue, obj2.hashValue)
    }

}

fileprivate let fakeBaseDirectory = "/Foo/48B0BAEB-94C4-4158-953C-74AB0935E5FA"

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

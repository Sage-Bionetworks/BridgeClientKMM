//
//  StudyDataUploadAPITests.swift
//  BridgeFileUploadsTests
//

import XCTest
@testable import BridgeClient
@testable import BridgeClientExtension

class StudyDataUploadAPITests : XCTestCase, BridgeFileUploadManagerTestCaseTyped {
    typealias T = StudyDataUploadObject
    
    var uploadRequestSuccessResponseFile: String = "sd-upload-request-success"
    var uploadRequestExpiredResponseFile: String = "sd-upload-request-expired"
    var mockURLSession: MockURLSession = MockURLSession()
    var mockAppManager: MockBridgeClientAppManager = MockBridgeClientAppManager(appId: "not-a-real-appid")
    var testFileId: String = "TestFileId"
    var savedSession: URLSession?
    var savedDelay: TimeInterval?
    var savedAppManager: UploadAppManager?
    var uploadApi: BridgeFileUploadAPI = StudyDataUploadAPI.shared
    var uploadExtras: Codable?
    
    lazy var requestEndpoint: String = {
        "/v3/uploads"
    }()
    
    var uploadSucceededNotification: Notification.Name = .SBBStudyFileUploaded
    var uploadRequestFailedNotification: Notification.Name = .SBBStudyFileUploadRequestFailed
    var uploadToS3FailedNotification: Notification.Name  = .SBBStudyFileUploadToS3Failed
    var bridgeNotificationFailedNotification: Notification.Name = .SBBStudyFileUploadBridgeNotificationFailed

    override func setUp() {
        // Put setup code here. This method is called before the invocation of each test method in the class.
        super.setUp()
        self.genericSetUp()
    }

    override func tearDown() {
        // Put teardown code here. This method is called after the invocation of each test method in the class.
        self.genericTearDown()
        super.tearDown()
    }
    
    func uploadRequestFailed412Tests(userInfo: [AnyHashable : Any]) {
        let sdua = StudyDataUploadAPI.shared
        let fileName = userInfo[sdua.fileNameKey] as? String
        XCTAssertNotNil(fileName, "SBBStudyFileUploadRequestFailed notification userInfo has no file name string at '\(sdua.fileNameKey)'")
    }
    
    func uploadSucceeded503RetriedTests(userInfo: [AnyHashable : Any]) {
        let sdua = StudyDataUploadAPI.shared
        let fileName = userInfo[sdua.fileNameKey] as? String
        XCTAssertNotNil(fileName, "SBBStudyFileUploaded notification userInfo has no file name string at '\(sdua.fileNameKey)'")
    }
    
    func testUploadRequestFails() {
        self.tryUploadRequestFails()
    }
    
    func testUploadFileToBridgeWhenS3RespondsWithVariousFailuresThatShouldRetryLater() {
        self.tryUploadFileToBridgeWhenS3RespondsWithVariousFailuresThatShouldRetryLater()
    }
    
    func testUploadFileToBridgeHappyPath() {
        self.tryUploadFileToBridgeHappyPath()
    }
    
}
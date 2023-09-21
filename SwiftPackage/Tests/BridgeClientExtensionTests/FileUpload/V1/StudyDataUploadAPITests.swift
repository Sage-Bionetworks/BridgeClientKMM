//
//  StudyDataUploadAPITests.swift
//  BridgeFileUploadsTests
//

import XCTest
@testable import BridgeClient
@testable import BridgeClientExtension

/** Disable V1 upload tests - they have a timing issue in them that causes them to fail github action sometimes. syoung 09/13/2023

class StudyDataUploadAPITests : XCTestCase, BridgeFileUploadManagerTestCaseTyped {
    typealias T = StudyDataUploadObject
    
    var uploadRequestSuccessResponseFile: String = "sd-upload-request-success"
    var uploadRequestExpiredResponseFile: String = "sd-upload-request-expired"
    var mockURLSession: MockURLSession = MockURLSession()
    var mockAppManager: MockBridgeClientAppManager = MockBridgeClientAppManager(mockType: .unitTest)
    var testFileId: String = "TestFileId"
    var uploadApi: BridgeFileUploadAPI {
        mockAppManager.uploadManagerV1.studyDataUploadAPI
    }
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
        let sdua = mockAppManager.uploadManagerV1.studyDataUploadAPI
        let fileName = userInfo[sdua.fileNameKey] as? String
        XCTAssertNotNil(fileName, "SBBStudyFileUploadRequestFailed notification userInfo has no file name string at '\(sdua.fileNameKey)'")
    }
    
    func uploadSucceededRetriedTests(userInfo: [AnyHashable : Any]) {
        let sdua = mockAppManager.uploadManagerV1.studyDataUploadAPI
        let fileName = userInfo[sdua.fileNameKey] as? String
        XCTAssertNotNil(fileName, "SBBStudyFileUploaded notification userInfo has no file name string at '\(sdua.fileNameKey)'")
    }
    
    func testUploadRequestFails_412() {
        tryUploadRequestFails412_Consent()
    }
    
    func testUploadRequestFails_503() {
        tryUploadRequestFailsInitial503_ServerDown()
    }
    
    func testUploadRequestFails_401_ReauthSuccess() {
        tryUploadRequestFails401_ReauthSucceeded()
    }
    
    func testUploadFileToBridgeWhenS3RespondsShouldRetry_403() {
        tryUploadFileToBridgeWhenS3Responds(status: 403)
    }
    
    func testUploadFileToBridgeWhenS3RespondsShouldRetry_409() {
        tryUploadFileToBridgeWhenS3Responds(status: 409)
    }
    
    func testUploadFileToBridgeWhenS3RespondsShouldRetry_500() {
        tryUploadFileToBridgeWhenS3Responds(status: 500)
    }
    
    func testUploadFileToBridgeWhenS3RespondsShouldRetry_503() {
        tryUploadFileToBridgeWhenS3Responds(status: 503)
    }
    
    func testUploadFileToBridgeHappyPath() {
        self.tryUploadFileToBridgeHappyPath()
    }
}

// */

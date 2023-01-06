//
//  ParticipantFileUploadAPITests.swift
//  BridgeFileUploadsTests
//

import XCTest
@testable import BridgeClient
@testable import BridgeClientExtension

class ParticipantFileUploadAPITests : XCTestCase, BridgeFileUploadManagerTestCaseTyped {
    typealias T = ParticipantFile
    
    var uploadRequestSuccessResponseFile: String = "pf-upload-request-success"
    var uploadRequestExpiredResponseFile: String = "pf-upload-request-expired"
    var mockURLSession: MockURLSession = MockURLSession()
    var mockAppManager: MockBridgeClientAppManager = MockBridgeClientAppManager(appId: "not-a-real-appid")
    var testFileId: String = "TestFileId"
    var savedSession: URLSession?
    var savedDelay: TimeInterval?
    var savedAppManager: UploadAppManager?
    var uploadApi: BridgeFileUploadAPI = ParticipantFileUploadAPI.shared
    var uploadExtras: Codable?
    
    lazy var requestEndpoint: String = {
        "/v3/participants/self/files/\(testFileId)"
    }()
    
    var uploadSucceededNotification: Notification.Name = .SBBParticipantFileUploaded
    var uploadRequestFailedNotification: Notification.Name = .SBBParticipantFileUploadRequestFailed
    var uploadToS3FailedNotification: Notification.Name  = .SBBParticipantFileUploadToS3Failed
    var bridgeNotificationFailedNotification: Notification.Name = .SBBFileUploadPlaceholder

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
        let pfua = ParticipantFileUploadAPI.shared
        let fileId = userInfo[pfua.fileIdKey] as? String
        XCTAssertNotNil(fileId, "SBBParticipantFileUploadRequestFailed notification userInfo has no file id string at '\(pfua.fileIdKey)'")
        let participantFile = userInfo[pfua.participantFileKey] as? ParticipantFile
        XCTAssertNotNil(participantFile, "SBBParticipantFileUploadRequestFailed notification userInfo has no ParticipantFile object at '\(pfua.participantFileKey)'")
    }
    
    func uploadSucceeded503RetriedTests(userInfo: [AnyHashable : Any]) {
        let pfua = ParticipantFileUploadAPI.shared
        let fileId = userInfo[pfua.fileIdKey] as? String
        XCTAssertNotNil(fileId, "SBBParticipantFileUploaded notification userInfo has no file id string at '\(pfua.fileIdKey)'")
        let participantFile = userInfo[pfua.participantFileKey] as? ParticipantFile
        XCTAssertNotNil(participantFile, "SBBParticipantFileUploaded notification userInfo has no ParticipantFile object at '\(pfua.participantFileKey)'")
        let requestUrl = userInfo[pfua.requestUrlKey] as? URL
        XCTAssertNotNil(requestUrl, "SBBParticipantFileUploaded notification userInfo has no request URL at '\(pfua.requestUrlKey)")
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
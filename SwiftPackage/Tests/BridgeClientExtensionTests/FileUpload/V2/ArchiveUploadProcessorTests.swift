// Created 9/5/23
// swift-tools-version:5.0

import XCTest
@testable import BridgeClientExtension
import ResultModel

final class ArchiveUploadProcessorTests: XCTestCase {

    override func setUpWithError() throws {
        // Put setup code here. This method is called before the invocation of each test method in the class.
    }

    override func tearDownWithError() throws {
        // Put teardown code here. This method is called after the invocation of each test method in the class.
        
        // Remove created files in app support directory
        let baseURL = try FileManager.default.sharedAppSupportDirectory()
        let url: URL = baseURL.appendingPathComponent("BridgeUploadsV2")
        try FileManager.default.removeItem(at: url)
        
        // Remove any unprocessed uploads
        UserDefaults.standard.removeObject(forKey: "unprocessedUploads")
    }
    
    fileprivate func createArchiveUploadProcessor() -> (ArchiveUploadProcessor, Mock) {
        let mock = Mock()
        let pemPath = Bundle.module.path(forResource: "sample-study", ofType: "pem")
        let processor = ArchiveUploadProcessor(pemPath: pemPath, sharedUserDefaults: .init())
        processor.uploadManager = mock.uploadManager
        processor.isTestUser = false
        return (processor, mock)
    }
    
    fileprivate func createAssessmentScheduleInfo() -> (Date, AssessmentScheduleInfo) {
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
        return (now, schedule)
    }
    
    func testEncryptAndUpload_AssessmentArchiveBuilder() async throws {
        let (uploadProcessor, mock) = createArchiveUploadProcessor()
        let (now, schedule) = createAssessmentScheduleInfo()
        let step = ResultObject(identifier: "step1", startDate: now.addingTimeInterval(-5*60), endDate: now)
        let result = AssessmentResultObject(identifier: schedule.assessmentIdentifier,
                                            startDate: step.startDate,
                                            endDate: step.endDate,
                                            taskRunUUID: UUID(),
                                            stepHistory: [step],
                                            path: [.init(identifier: "step1", direction: .forward)])
        let builder = AssessmentArchiveBuilder(result, schedule: schedule)!
        
        // -- Method under test
        await uploadProcessor.asyncEncryptAndUpload(using: builder)
        
        // This silences warnings about retaining the mock (which can zombie if you don't)
        XCTAssertEqual(mock.nativeManager.queuedUploadFiles.count, 1)
        XCTAssertEqual(mock.uploadManager.retryQueue.count, 1)
        
        // Should not be any markers for unprocessed uploads
        XCTAssertNil(uploadProcessor.sharedUserDefaults.object(forKey: "unprocessedUploads"))
        
        // Look for the original encrypted file to have been moved and deleted
        if let encryptedUrl = builder.archive.encryptedURL {
            let exists = FileManager.default.fileExists(atPath: encryptedUrl.absoluteString)
            XCTAssertFalse(exists, "Expecting file \(encryptedUrl) to have been deleted.")
        } else {
            XCTFail("The builder encrypted file is missing. Failed to encrypt.")
        }
        
        // Look for the file to upload to be staged
        if let uploadFile = mock.nativeManager.queuedUploadFiles.first {
            let fullPath = mock.uploadManager.sandboxFileManager.fullyQualifiedPath(of: uploadFile.filePath)
            let exists = FileManager.default.fileExists(atPath: fullPath)
            XCTAssertTrue(exists, "Expecting file \(fullPath) to exist.")
        } else {
            XCTFail("Failed to queue the encrypted file for upload.")
        }
    }

}

fileprivate class Mock {
    let networkManager: MockBackgroundNetworkManager = .init()
    let nativeManager: MockNativeUploadManager = .init()
    lazy var uploadManager: TestUploadManager = .init(backgroundNetworkManager: networkManager,
                                                      nativeUploadManager: nativeManager)
}

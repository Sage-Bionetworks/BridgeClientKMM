//
//  BridgeFileUploadManagerTestCase.swift
//  BridgeFileUploadsTests
//

import XCTest
import BridgeClient
@testable import BridgeClientExtension

extension NSNotification.Name {
    /// Placeholder notification name for initializing values intended to be overridden in subclasses.
    public static let SBBFileUploadPlaceholder = Notification.Name(rawValue: "SBBFileUploadPlaceholder")
}

protocol BridgeFileUploadManagerTestCase : XCTWaiterDelegate {
    var mockURLSession: MockURLSession { get }
    var mockAppManager: MockBridgeClientAppManager { get }
    var testFileId: String { get }
    
    var requestEndpoint: String { get }
    var uploadRequestSuccessResponseFile: String { get }
    var uploadRequestExpiredResponseFile: String { get }
    var uploadSucceededNotification: Notification.Name { get }
    var uploadRequestFailedNotification: Notification.Name { get }
    var uploadToS3FailedNotification: Notification.Name { get }
    var bridgeNotificationFailedNotification: Notification.Name { get }
    var uploadApi: BridgeFileUploadAPI { get }
    var uploadExtras: Codable? { get }
    
    func uploadRequestFailed412Tests(userInfo: [AnyHashable : Any])
    func uploadSucceededRetriedTests(userInfo: [AnyHashable : Any])
}

protocol BridgeFileUploadManagerTestCaseTyped: BridgeFileUploadManagerTestCase {
    associatedtype T : Codable
}

extension BridgeFileUploadManagerTestCaseTyped {
    func genericSetUp() {
        // Call this in the XCTestCase setUp() func after calling super.setUp()
        let bnm = mockAppManager.backgroundNetworkManager
        mockAppManager.mockAuthManager.reset()

        mockURLSession.mockDelegate = bnm
        mockURLSession.mockDelegateQueue = bnm.sessionDelegateQueue
        let setMockSession = BlockOperation {
            bnm.primaryBackgroundSession = self.mockURLSession
        }
        bnm.sessionDelegateQueue.addOperations([setMockSession], waitUntilFinished: true)
        mockAppManager.uploadManagerV1.delayForRetry = 0 // don't delay retries for tests
        
        // Clear user defaults - may have leftover cruft from previous failed test run
        let bfum = mockAppManager.uploadManagerV1
        let defaults = bfum.userDefaults
        defaults.set(nil, forKey: bfum.retryUploadsKey)
        defaults.set(nil, forKey: bfum.bridgeFileUploadsKey)
        defaults.set(nil, forKey: bfum.uploadURLsRequestedKey)
        defaults.set(nil, forKey: bfum.uploadingToS3Key)
        defaults.set(nil, forKey: bfum.notifyingBridgeUploadSucceededKey)
        
        // Remove all temp files - may have leftover cruft from previous failed test run
        if let items = try? FileManager.default.contentsOfDirectory(at: self.uploadApi.tempUploadDirURL, includingPropertiesForKeys: nil, options: []) {
            items.forEach {
                try? FileManager.default.removeItem(at: $0)
            }
        }
    }

    func genericTearDown() {
        // Call this in the XCTestCase tearDown() func before calling super.tearDown()
    }
    
    func check(file: URL, willRetry: Bool, message: String) {
        check(file: file, willRetry: willRetry, stillExists: willRetry, message: message, cleanUpAfter: true)
    }
    
    func removeMappings(for relativeFilePath: String) {
        let bfum = mockAppManager.uploadManagerV1
        bfum.removeMapping(String.self, from: relativeFilePath, defaultsKey: bfum.bridgeFileUploadsKey)
        let _ = uploadApi.fetchUploadRequested(for: relativeFilePath)
        let _ = uploadApi.fetchUploadingToS3(for: relativeFilePath)
        let _ = uploadApi.fetchNotifyingBridge(for: relativeFilePath)
        bfum.removeMapping(String.self, from: relativeFilePath, defaultsKey: bfum.downloadErrorResponseBodyKey)
    }
    
    func check(file: URL, willRetry: Bool, stillExists: Bool, message: String, cleanUpAfter: Bool) {
        self.mockURLSession.doSyncInDelegateQueue {
            var willRetryCheck = false
            let tempFilePath = file.path
            let fileExists = FileManager.default.fileExists(atPath: tempFilePath)
            let bfum = self.mockAppManager.uploadManagerV1
            let userDefaults = bfum.userDefaults
            var retryUploads = userDefaults.dictionary(forKey: bfum.retryUploadsKey)
            for relativeFilePath in retryUploads?.keys ?? [String: Any]().keys {
                let filePath = bfum.fullyQualifiedPath(of: relativeFilePath)
                if filePath == tempFilePath {
                    willRetryCheck = true
                    if cleanUpAfter {
                        bfum.cleanUpTempFile(filePath: relativeFilePath)
                        self.removeMappings(for: relativeFilePath)
                        retryUploads?.removeValue(forKey: relativeFilePath)
                        userDefaults.setValue(retryUploads, forKey: bfum.retryUploadsKey)
                   }
                }
            }
            XCTAssert(willRetry == willRetryCheck, message)
            XCTAssert(fileExists == stillExists, "\(message): File for retry doesn't still exist if it should, or does if it shouldn't")
        }
    }
    
    func tryUploadRequestFails412_Consent() {
        // test fails unrecoverably due to not consented (412)
        let responseJson = ["message": "try again later"]
        let endpoint = requestEndpoint
        let mimeType = "image/jpeg"
        guard let downloadFileUrl = Bundle.module.url(forResource: "failed-upload-request-response", withExtension: "json") else {
            XCTAssert(false, "Unable to find test response file 'failed-upload-request-response.json' for upload api \(self.uploadApi.apiString) upload failure tests")
            return
        }
        mockURLSession.set(json: responseJson, responseCode: 412, for: endpoint, httpMethod: "POST")
        mockURLSession.set(downloadFileUrl: downloadFileUrl, error: nil, for: endpoint, httpMethod: "POST")
        let expect412 = XCTestExpectation(description: "412: not consented, don't retry")
        var tempCopyUrl: URL?
        
        // NOTE: If I move this block any further up in the function, it causes a compiler crash. Not
        // a syntax error, an actual crash of the compiler. ¯\_(ツ)_/¯ ~emm 2021-07-08
        guard let uploadFileUrl = Bundle.module.url(forResource: "cat", withExtension: "jpg") else {
            XCTAssert(false, "Unable to find test image 'cat.jpg' for upload api \(self.uploadApi.apiString) upload failure tests")
            return
        }
        
        let observer412 = NotificationCenter.default.addObserver(forName: uploadRequestFailedNotification, object: nil, queue: nil) { notification in
            guard let userInfo = notification.userInfo else {
                XCTAssert(false, "\(self.uploadRequestFailedNotification.rawValue) notification has no userInfo")
                expect412.fulfill()
                return
            }
            
            self.uploadRequestFailed412Tests(userInfo: userInfo)
            
            let statusCode = userInfo[self.uploadApi.httpStatusKey] as? Int
            XCTAssertNotNil(statusCode, "\(self.uploadRequestFailedNotification.rawValue) notification userInfo has no HTTP status code at '\(self.uploadApi.httpStatusKey)'")
            XCTAssert(statusCode == 412, "Status code in userInfo of \(self.uploadRequestFailedNotification.rawValue) notification should be 412 but is \(String(describing: statusCode)) instead")
            
            XCTAssertNotNil(tempCopyUrl, "Temp file copy URL is nil")
            if let tempCopyUrl = tempCopyUrl {
                self.check(file: tempCopyUrl, willRetry: false, message: "Should not retry after 412 from \(String(describing: self.uploadApi.apiString)) api")
            }
            expect412.fulfill()
        }
        
        tempCopyUrl = uploadApi.uploadInternal(fileId: testFileId, fileUrl: uploadFileUrl, contentType: mimeType, extras: uploadExtras)
        XCTAssertNotNil(tempCopyUrl, "Temp file url is nil when testing \(uploadApi.apiString) upload request failure due to 412 not consented")
        
        XCTWaiter(delegate: self).wait(for: [expect412], timeout: 5.0)
        NotificationCenter.default.removeObserver(observer412)
    }
    
    func tryUploadRequestFailsInitial503_ServerDown() {
        let responseJson = ["message": "try again later"]
        let endpoint = requestEndpoint
        let mimeType = "image/jpeg"
        guard let downloadFileUrl = Bundle.module.url(forResource: "failed-upload-request-response", withExtension: "json") else {
            XCTAssert(false, "Unable to find test response file 'failed-upload-request-response.json' for upload api \(self.uploadApi.apiString) upload failure tests")
            return
        }
        let bfum = mockAppManager.uploadManagerV1
        var tempCopyUrl: URL?
        
        // NOTE: If I move this block any further up in the function, it causes a compiler crash. Not
        // a syntax error, an actual crash of the compiler. ¯\_(ツ)_/¯ ~emm 2021-07-08
        guard let uploadFileUrl = Bundle.module.url(forResource: "cat", withExtension: "jpg") else {
            XCTAssert(false, "Unable to find test image 'cat.jpg' for upload api \(self.uploadApi.apiString) upload failure tests")
            return
        }
        
        // test initially fails due to server down (503) but succeeds on retry
        // -- set up initial 503 response, and add observer for eventual success
        mockURLSession.set(json: responseJson, responseCode: 503, for: endpoint, httpMethod: "POST")
        mockURLSession.set(downloadFileUrl: downloadFileUrl, error: nil, for: endpoint, httpMethod: "POST")
        let expectRetried = XCTestExpectation(description: "503: retry later")
        let observer503Retried = NotificationCenter.default.addObserver(forName: uploadSucceededNotification, object: nil, queue: nil) { notification in
            if let userInfo = notification.userInfo {
                self.uploadSucceededRetriedTests(userInfo: userInfo)
            }
            else {
                XCTAssert(false, "\(self.uploadSucceededNotification) notification has no userInfo")
            }
                
            XCTAssertNotNil(tempCopyUrl, "Temp file copy URL is nil")
            if let tempCopyUrl = tempCopyUrl {
                let shouldStillExist = self.uploadApi.notifiesBridgeWhenUploaded
                self.check(file: tempCopyUrl, willRetry: false, stillExists: shouldStillExist, message: "Should no longer be in retry queue upon successful retry after initial 503 error", cleanUpAfter: true)
            }
            
            // make sure we didn't generate any spurious uploads or retries
            let defaults = self.mockAppManager.uploadManagerV1.userDefaults
            let retryUploads = defaults.dictionary(forKey: bfum.retryUploadsKey)
            let fileUploads = defaults.dictionary(forKey: bfum.bridgeFileUploadsKey)
            let uploadRequests = defaults.dictionary(forKey: bfum.uploadURLsRequestedKey)
            let uploadsToS3 = defaults.dictionary(forKey: bfum.uploadingToS3Key)
            let notifyingBridge = defaults.dictionary(forKey: bfum.notifyingBridgeUploadSucceededKey)
            XCTAssert(retryUploads?.count ?? 0 == 0, "Spurious files left in retryUploads map: \(retryUploads!)")
            XCTAssert(fileUploads?.count ?? 0 == 0, "Spurious files left in bridgeFileUploads map: \(fileUploads!)")
            XCTAssert(uploadRequests?.count ?? 0 == 0, "Spurious files left in uploadURLsRequested map: \(uploadRequests!)")
            XCTAssert(uploadsToS3?.count ?? 0 == 0, "Spurious files left in uploadingToS3 map: \(uploadsToS3!)")
            XCTAssert(notifyingBridge?.count ?? 0 == 0, "Spurious files left in notifyingBridge map: \(notifyingBridge!)")

            // make sure we didn't leave any unreferenced files lying around in the temp upload dir
            let items = try! FileManager.default.contentsOfDirectory(atPath: self.uploadApi.tempUploadDirURL.path)
            if self.uploadApi.notifiesBridgeWhenUploaded {
                XCTAssert(items.count == 1, "Expected exactly one file to be in temp upload dir:\n\(items)")
            }
            else {
                XCTAssert(items.count == 0, "Files left hanging around in temp upload dir:\n\(items)")
            }
            
            // make sure all the mock response stuff got "used up"
            for key in self.keysEmptyAfterUpload(for: self.mockURLSession.jsonForEndpoints) {
                let responses = self.mockURLSession.jsonForEndpoints[key] as? [Any]
                XCTAssert(responses?.count ?? 0 == 0, "Mock URLSession still has mock json response(s):\n\(self.mockURLSession.jsonForEndpoints)")
            }
            for key in self.keysEmptyAfterUpload(for: self.mockURLSession.codesforEndpoints) {
                let responses = self.mockURLSession.codesforEndpoints[key] as? [Any]
                XCTAssert(responses?.count ?? 0 == 0, "Mock URLSession still has mock response code(s):\n\(self.mockURLSession.codesforEndpoints)")
            }
            for key in self.keysEmptyAfterUpload(for: self.mockURLSession.URLsForEndpoints) {
                let responses = self.mockURLSession.URLsForEndpoints[key] as? [Any]
                XCTAssert(responses?.count ?? 0 == 0, "Mock URLSession still has (a) mock downloaded response file URL(s):\n\(self.mockURLSession.URLsForEndpoints)")
            }
            for key in self.keysEmptyAfterUpload(for: self.mockURLSession.errorsForEndpoints) {
                let responses = self.mockURLSession.errorsForEndpoints[key] as? [Any]
                XCTAssert(responses?.count ?? 0 == 0, "Mock URLSession still has (a) mock error code(s):\n\(self.mockURLSession.errorsForEndpoints)")
            }

            expectRetried.fulfill()
        }
        
        var retryRecoverable = true
        let observer503NotRetried = NotificationCenter.default.addObserver(forName: uploadRequestFailedNotification, object: nil, queue: nil) { notification in
            XCTAssert(false, "initial 503 treated as unrecoverable, not retried")
            retryRecoverable = false
            expectRetried.fulfill()
        }
        
        let observer503RetriedButS3Failed = NotificationCenter.default.addObserver(forName: uploadToS3FailedNotification, object: nil, queue: nil) { notification in
            XCTAssert(false, "initial 503 retried, but mock upload to S3 failed")
            expectRetried.fulfill()
        }
        
        // -- now set up the responses for the retry attempt so they're ready to go when it happens.
        let s3url = "/not-a-real-pre-signed-S3-url"
        guard let successResponseUrl = Bundle.module.url(forResource: self.uploadRequestSuccessResponseFile, withExtension: "json") else {
            XCTAssert(false, "Unable to find test response file '\(self.uploadRequestSuccessResponseFile).json' for upload api \(self.uploadApi.apiString) upload failure tests")
            return
        }

        self.mockURLSession.setJsonFromFile(named: self.uploadRequestSuccessResponseFile, responseCode: 201, for: endpoint, httpMethod: "POST")
        self.mockURLSession.set(downloadFileUrl: successResponseUrl, error: nil, for: endpoint, httpMethod: "POST")
        
        // -- set up the S3 upload success response
        self.mockURLSession.set(json: Dictionary<String, Any>(), responseCode: 200, for: s3url, httpMethod: "PUT")
        
        // -- set up the "upload completed" api call response
        if self.uploadApi.notifiesBridgeWhenUploaded {
            guard let uploadOnlyMetadata = self.uploadApi.uploadMetadata(for: self.testFileId, fileUrl: uploadFileUrl, mimeType: mimeType, extras: self.uploadExtras) else {
                XCTAssert(false, "Failed to create test upload metadata for \(self.uploadApi.apiString) upload failure test retry attempt in order to get the notifyBridgeUrlString")
                return
            }
            var jsonData: Data
            do {
                jsonData = try Data(contentsOf: successResponseUrl)
            } catch let err {
                XCTAssert(false, "Error getting contents of \(successResponseUrl) as Data: \(err)")
                return
            }
            guard let uploadMetadata = self.uploadApi.update(metadata: uploadOnlyMetadata, with: jsonData) else {
                XCTAssert(false, "Failed to update upload metadata with json from mock upload request response")
                return
            }
            guard let uploadCompleteResponseUrl = Bundle.module.url(forResource: "upload-complete-response", withExtension: "json") else {
                XCTAssert(false, "Unable to find upload complete response file 'upload-complete-response.json' for \(self.uploadApi.apiString) upload failure test retry attempt")
                return
            }
            guard let notifyBridgeUrlString = self.uploadApi.notifyBridgeUrlString(for: uploadMetadata) else {
                XCTAssert(false, "Unable to build notifyBridgeUrlString from uploadMetadata \(uploadMetadata)")
                return
            }
            let notifyBridgeEndpoint = "/\(notifyBridgeUrlString)"
            self.mockURLSession.set(json: Dictionary<String, Any>(), responseCode: 200, for: notifyBridgeEndpoint, httpMethod: "POST")
            self.mockURLSession.set(downloadFileUrl: uploadCompleteResponseUrl, error: nil, for: notifyBridgeEndpoint, httpMethod: "POST")
        }
        
        // -- start the upload attempt. This should get a 503 Server Busy response initially and
        //    queue up the file for 'later' retry. In the test environment, the delay is set to 0 so
        //    it should happen immediately.
        tempCopyUrl = uploadApi.uploadInternal(fileId: testFileId, fileUrl: uploadFileUrl, contentType: mimeType, extras: uploadExtras)
        XCTAssertNotNil(tempCopyUrl, "Temp file url is nil when testing upload request retrying after initial 503 from upload api \(self.uploadApi.apiString)")
        guard let tempCopyUrl = tempCopyUrl else { return }
        
        // -- Check that a retry will indeed be attempted.
        //    (queue up so this happens after the initial attempt has completed)
        OperationQueue.main.addOperation {
            self.mockURLSession.delegateQueue.addOperation {
                guard retryRecoverable else { return }
                // check that the file is indeed in the retry queue as expected
                self.check(file: tempCopyUrl, willRetry: true, stillExists: true, message: "Should retry after 503 from upload api \(self.uploadApi.apiString)", cleanUpAfter: false)
                
                // -- do the retry
                bfum.retryUploadsAfterDelay()
            }
        }
        
        // -- wait here until everything above has worked its way through.
        XCTWaiter(delegate: self).wait(for: [expectRetried], timeout: 5.0)
        NotificationCenter.default.removeObserver(observer503Retried)
        NotificationCenter.default.removeObserver(observer503NotRetried)
        NotificationCenter.default.removeObserver(observer503RetriedButS3Failed)

    }
    
    func tryUploadRequestFails401_ReauthSucceeded() {
        let responseJson = ["message": "session token expired"]
        let endpoint = requestEndpoint
        let mimeType = "image/jpeg"
        guard let downloadFileUrl = Bundle.module.url(forResource: "failed-upload-request-response", withExtension: "json") else {
            XCTAssert(false, "Unable to find test response file 'failed-upload-request-response.json' for upload api \(self.uploadApi.apiString) upload failure tests")
            return
        }
        let bfum = mockAppManager.uploadManagerV1
        var tempCopyUrl: URL?
        
        // NOTE: If I move this block any further up in the function, it causes a compiler crash. Not
        // a syntax error, an actual crash of the compiler. ¯\_(ツ)_/¯ ~emm 2021-07-08
        guard let uploadFileUrl = Bundle.module.url(forResource: "cat", withExtension: "jpg") else {
            XCTAssert(false, "Unable to find test image 'cat.jpg' for upload api \(self.uploadApi.apiString) upload failure tests")
            return
        }
        
        // test initially fails due to session token expired (401)
        // -- set up initial 401 response, and add observer for eventual success
        mockURLSession.set(json: responseJson, responseCode: 401, for: endpoint, httpMethod: "POST")
        mockURLSession.set(downloadFileUrl: downloadFileUrl, error: nil, for: endpoint, httpMethod: "POST")
       
        let expectRetried = XCTestExpectation(description: "401: reauth")
        let observerRetried = NotificationCenter.default.addObserver(forName: uploadSucceededNotification, object: nil, queue: nil) { notification in
            
            debugPrint("Received Notification: uploadSucceededNotification")
            
            if let userInfo = notification.userInfo {
                self.uploadSucceededRetriedTests(userInfo: userInfo)
            }
            else {
                XCTAssert(false, "\(self.uploadSucceededNotification) notification has no userInfo")
            }
                
            XCTAssertNotNil(tempCopyUrl, "Temp file copy URL is nil")
            if let tempCopyUrl = tempCopyUrl {
                let shouldStillExist = self.uploadApi.notifiesBridgeWhenUploaded
                self.check(file: tempCopyUrl, willRetry: false, stillExists: shouldStillExist, message: "Should no longer be in retry queue upon successful retry after initial 401 error", cleanUpAfter: true)
            }
            
            // make sure we didn't generate any spurious uploads or retries
            let defaults = self.mockAppManager.uploadManagerV1.userDefaults
            let retryUploads = defaults.dictionary(forKey: bfum.retryUploadsKey)
            let fileUploads = defaults.dictionary(forKey: bfum.bridgeFileUploadsKey)
            let uploadRequests = defaults.dictionary(forKey: bfum.uploadURLsRequestedKey)
            let uploadsToS3 = defaults.dictionary(forKey: bfum.uploadingToS3Key)
            let notifyingBridge = defaults.dictionary(forKey: bfum.notifyingBridgeUploadSucceededKey)
            XCTAssert(retryUploads?.count ?? 0 == 0, "Spurious files left in retryUploads map: \(retryUploads!)")
            XCTAssert(fileUploads?.count ?? 0 == 0, "Spurious files left in bridgeFileUploads map: \(fileUploads!)")
            XCTAssert(uploadRequests?.count ?? 0 == 0, "Spurious files left in uploadURLsRequested map: \(uploadRequests!)")
            XCTAssert(uploadsToS3?.count ?? 0 == 0, "Spurious files left in uploadingToS3 map: \(uploadsToS3!)")
            XCTAssert(notifyingBridge?.count ?? 0 == 0, "Spurious files left in notifyingBridge map: \(notifyingBridge!)")

            // make sure we didn't leave any unreferenced files lying around in the temp upload dir
            let items = try! FileManager.default.contentsOfDirectory(atPath: self.uploadApi.tempUploadDirURL.path)
            if self.uploadApi.notifiesBridgeWhenUploaded {
                XCTAssert(items.count == 1, "Expected exactly one file to be in temp upload dir:\n\(items)")
            }
            else {
                XCTAssert(items.count == 0, "Files left hanging around in temp upload dir:\n\(items)")
            }
            
            // make sure all the mock response stuff got "used up"
            for key in self.keysEmptyAfterUpload(for: self.mockURLSession.jsonForEndpoints) {
                let responses = self.mockURLSession.jsonForEndpoints[key] as? [Any]
                XCTAssert(responses?.count ?? 0 == 0, "Mock URLSession still has mock json response(s):\n\(self.mockURLSession.jsonForEndpoints)")
            }
            for key in self.keysEmptyAfterUpload(for: self.mockURLSession.codesforEndpoints) {
                let responses = self.mockURLSession.codesforEndpoints[key] as? [Any]
                XCTAssert(responses?.count ?? 0 == 0, "Mock URLSession still has mock response code(s):\n\(self.mockURLSession.codesforEndpoints)")
            }
            for key in self.keysEmptyAfterUpload(for: self.mockURLSession.URLsForEndpoints) {
                let responses = self.mockURLSession.URLsForEndpoints[key] as? [Any]
                XCTAssert(responses?.count ?? 0 == 0, "Mock URLSession still has (a) mock downloaded response file URL(s):\n\(self.mockURLSession.URLsForEndpoints)")
            }
            for key in self.keysEmptyAfterUpload(for: self.mockURLSession.errorsForEndpoints) {
                let responses = self.mockURLSession.errorsForEndpoints[key] as? [Any]
                XCTAssert(responses?.count ?? 0 == 0, "Mock URLSession still has (a) mock error code(s):\n\(self.mockURLSession.errorsForEndpoints)")
            }

            expectRetried.fulfill()
        }
        
        let observerNotRetried = NotificationCenter.default.addObserver(forName: uploadRequestFailedNotification, object: nil, queue: nil) { notification in
            XCTAssert(false, "initial 401 treated as unrecoverable, not retried")
            expectRetried.fulfill()
        }
        
        let observerRetriedButS3Failed = NotificationCenter.default.addObserver(forName: uploadToS3FailedNotification, object: nil, queue: nil) { notification in
            XCTAssert(false, "initial 401 retried, but mock upload to S3 failed")
            expectRetried.fulfill()
        }
        
        // -- now set up the responses for the retry attempt so they're ready to go when it happens.
        let s3url = "/not-a-real-pre-signed-S3-url"
        guard let successResponseUrl = Bundle.module.url(forResource: self.uploadRequestSuccessResponseFile, withExtension: "json") else {
            XCTAssert(false, "Unable to find test response file '\(self.uploadRequestSuccessResponseFile).json' for upload api \(self.uploadApi.apiString) upload failure tests")
            return
        }

        self.mockURLSession.setJsonFromFile(named: self.uploadRequestSuccessResponseFile, responseCode: 201, for: endpoint, httpMethod: "POST")
        self.mockURLSession.set(downloadFileUrl: successResponseUrl, error: nil, for: endpoint, httpMethod: "POST")
        
        // -- set up the S3 upload success response
        self.mockURLSession.set(json: Dictionary<String, Any>(), responseCode: 200, for: s3url, httpMethod: "PUT")
        
        // -- set up the "upload completed" api call response
        if self.uploadApi.notifiesBridgeWhenUploaded {
            guard let uploadOnlyMetadata = self.uploadApi.uploadMetadata(for: self.testFileId, fileUrl: uploadFileUrl, mimeType: mimeType, extras: self.uploadExtras) else {
                XCTAssert(false, "Failed to create test upload metadata for \(self.uploadApi.apiString) upload failure test retry attempt in order to get the notifyBridgeUrlString")
                return
            }
            var jsonData: Data
            do {
                jsonData = try Data(contentsOf: successResponseUrl)
            } catch let err {
                XCTAssert(false, "Error getting contents of \(successResponseUrl) as Data: \(err)")
                return
            }
            guard let uploadMetadata = self.uploadApi.update(metadata: uploadOnlyMetadata, with: jsonData) else {
                XCTAssert(false, "Failed to update upload metadata with json from mock upload request response")
                return
            }
            guard let uploadCompleteResponseUrl = Bundle.module.url(forResource: "upload-complete-response", withExtension: "json") else {
                XCTAssert(false, "Unable to find upload complete response file 'upload-complete-response.json' for \(self.uploadApi.apiString) upload failure test retry attempt")
                return
            }
            guard let notifyBridgeUrlString = self.uploadApi.notifyBridgeUrlString(for: uploadMetadata) else {
                XCTAssert(false, "Unable to build notifyBridgeUrlString from uploadMetadata \(uploadMetadata)")
                return
            }
            let notifyBridgeEndpoint = "/\(notifyBridgeUrlString)"
            self.mockURLSession.set(json: Dictionary<String, Any>(), responseCode: 200, for: notifyBridgeEndpoint, httpMethod: "POST")
            self.mockURLSession.set(downloadFileUrl: uploadCompleteResponseUrl, error: nil, for: notifyBridgeEndpoint, httpMethod: "POST")
        }
        
        // -- start the upload attempt. This should get a 401 Session token expired response initially.
        //    queue up the file for 'later' retry. In the test environment, the delay is set to 0 so
        //    it should happen immediately.
        tempCopyUrl = uploadApi.uploadInternal(fileId: testFileId, fileUrl: uploadFileUrl, contentType: mimeType, extras: uploadExtras)
        XCTAssertNotNil(tempCopyUrl, "Temp file url is nil when testing upload request retrying after initial 401 from upload api \(self.uploadApi.apiString)")
        
        // NOTE: for a successful reauth, retry should happen automatically.
        
        // -- wait here until everything above has worked its way through.
        XCTWaiter(delegate: self).wait(for: [expectRetried], timeout: 5.0)
        NotificationCenter.default.removeObserver(observerRetried)
        NotificationCenter.default.removeObserver(observerNotRetried)
        NotificationCenter.default.removeObserver(observerRetriedButS3Failed)
    }
    
    func tryUploadFileToBridgeWhenS3Responds(status: Int) {
        let s3url = "/not-a-real-pre-signed-S3-url"
        let mimeType = "image/jpeg"
        let endpoint = requestEndpoint
        guard let uploadFileUrl = Bundle.module.url(forResource: "cat", withExtension: "jpg") else {
            XCTAssert(false, "Unable to find test image 'cat.jpg' for upload api \(self.uploadApi.apiString) S3 error response tests")
            return
        }

        // -- set up the mock UploadRequest response
        let downloadFileName = (status == 403) ? self.uploadRequestExpiredResponseFile : self.uploadRequestSuccessResponseFile
        guard let downloadFileUrl = Bundle.module.url(forResource: downloadFileName, withExtension: "json") else {
            XCTAssert(false, "Unable to find test response file '\(downloadFileName).json' for upload api \(self.uploadApi.apiString) S3 error response tests")
            return
        }

        self.mockURLSession.setJsonFromFile(named: downloadFileName, responseCode: 201, for: endpoint, httpMethod: "POST")
        self.mockURLSession.set(downloadFileUrl: downloadFileUrl, error: nil, for: endpoint, httpMethod: "POST")

        // -- set up the mock S3 upload failed response
        let responseJson = ["Arbitrary S3 response" : "We should be ignoring this"]
        self.mockURLSession.set(json: responseJson, responseCode: status, for: s3url, httpMethod: "PUT")
        
        // -- try it
        let expectStatus = XCTestExpectation(description: "Should have been in retry queue after non-success status from S3")
        var tempCopyUrl: URL?
        let errorResponseButSucceeded = NotificationCenter.default.addObserver(forName: uploadSucceededNotification, object: nil, queue: nil) { notification in
            XCTAssert(false, "S3 upload succeeded, but should have been queued up for retry on response code \(status)")
            expectStatus.fulfill()
        }
        let retryableErrorButFailed = NotificationCenter.default.addObserver(forName: uploadToS3FailedNotification, object: nil, queue: nil) { notification in
            XCTAssert(false, "S3 upload failed permanently, but should have been queued up for retry on response code \(status)")
            expectStatus.fulfill()
        }
        let whatTheHow = NotificationCenter.default.addObserver(forName: uploadRequestFailedNotification, object: nil, queue: nil) { notification in
            XCTAssert(false, "S3 upload attempt somehow posted a file upload request failed notification (wth?), but should have been queued up for retry on response code \(status)")
            expectStatus.fulfill()
        }

        tempCopyUrl = uploadApi.uploadInternal(fileId: testFileId, fileUrl: uploadFileUrl, contentType: mimeType, extras: uploadExtras)
        XCTAssertNotNil(tempCopyUrl, "Temp file url is nil when testing upload api \(self.uploadApi.apiString) upload request with retryable S3 error response")
        guard let tempCopyUrl = tempCopyUrl else { return }

        // queue up a bunch of times to make sure the above stuff has actually completed before we check the retry queue
        self.mockURLSession.delegateQueue.addOperation {
            print("testUploadFileToBridgeWhenS3Responds \(status): once through delegate queue")
            OperationQueue.main.addOperation {
                self.mockURLSession.delegateQueue.addOperation {
                    print("testUploadFileToBridgeWhenS3Responds \(status): twice through delegate queue")
                    OperationQueue.main.addOperation {
                        self.mockURLSession.delegateQueue.addOperation {
                            print("testUploadFileToBridgeWhenS3Responds \(status): thrice through delegate queue")
                            OperationQueue.main.addOperation {
                                self.mockURLSession.delegateQueue.addOperation {
                                    print("testUploadFileToBridgeWhenS3Responds \(status): fourth time through delegate queue")
                                    expectStatus.fulfill()
                                }
                            }
                        }
                    }
                }
            }
        }
        XCTWaiter(delegate: self).wait(for: [expectStatus], timeout: 5.0)
        NotificationCenter.default.removeObserver(whatTheHow)
        NotificationCenter.default.removeObserver(retryableErrorButFailed)
        NotificationCenter.default.removeObserver(errorResponseButSucceeded)
        
        self.check(file: tempCopyUrl, willRetry: true, message: "Should have been in retry queue after non-success status \(status) from S3")
    }

    func tryUploadFileToBridgeHappyPath() {
        let s3url = "/not-a-real-pre-signed-S3-url"
        let mimeType = "image/jpeg"
        let endpoint = requestEndpoint
        guard let uploadFileUrl = Bundle.module.url(forResource: "cat", withExtension: "jpg") else {
            XCTAssert(false, "Unable to find test image 'cat.jpg' for upload api \(self.uploadApi.apiString) happy path test")
            return
        }

        // -- set up the mock UploadRequest response
        guard let downloadFileUrl = Bundle.module.url(forResource: self.uploadRequestSuccessResponseFile, withExtension: "json") else {
            XCTAssert(false, "Unable to find test response file '\(self.uploadRequestSuccessResponseFile).json' for \(uploadApi.apiString) happy path test")
            return
        }
        
        self.mockURLSession.setJsonFromFile(named: self.uploadRequestSuccessResponseFile, responseCode: 201, for: endpoint, httpMethod: "POST")
        self.mockURLSession.set(downloadFileUrl: downloadFileUrl, error: nil, for: endpoint, httpMethod: "POST")

        // -- set up the mock S3 upload succeeded response
        let responseJson = ["Arbitrary S3 response" : "We should be ignoring this"]
        self.mockURLSession.set(json: responseJson, responseCode: 200, for: s3url, httpMethod: "PUT")
        
        // -- set up the mock upload completed response
        if uploadApi.notifiesBridgeWhenUploaded {
            guard let uploadOnlyMetadata = self.uploadApi.uploadMetadata(for: testFileId, fileUrl: uploadFileUrl, mimeType: mimeType, extras: self.uploadExtras) else {
                XCTAssert(false, "Failed to create test upload metadata for \(uploadApi.apiString) happy path test in order to get the notifyBridgeUrlString")
                return
            }
            var jsonData: Data
            do {
                jsonData = try Data(contentsOf: downloadFileUrl)
            } catch let err {
                XCTAssert(false, "Error getting contents of \(downloadFileUrl) as Data: \(err)")
                return
            }
            guard let uploadMetadata = self.uploadApi.update(metadata: uploadOnlyMetadata, with: jsonData) else {
                XCTAssert(false, "Failed to update upload metadata with json from mock upload request response")
                return
            }
            guard let uploadCompleteResponseUrl = Bundle.module.url(forResource: "upload-complete-response", withExtension: "json") else {
                XCTAssert(false, "Unable to find upload complete response file 'upload-complete-response.json' for \(uploadApi.apiString) happy path test")
                return
            }
            guard let notifyBridgeUrlString = self.uploadApi.notifyBridgeUrlString(for: uploadMetadata) else {
                XCTAssert(false, "Unable to create notifyBridgeUrlString from uploadMetadata: \(uploadMetadata)")
                return
            }
            let notifyBridgeEndpoint = "/\(notifyBridgeUrlString)"
            self.mockURLSession.set(json: Dictionary<String, Any>(), responseCode: 200, for: notifyBridgeEndpoint, httpMethod: "POST")
            self.mockURLSession.set(downloadFileUrl: uploadCompleteResponseUrl, error: nil, for: notifyBridgeEndpoint, httpMethod: "POST")
        }

        // -- try it
        let bfum = mockAppManager.uploadManagerV1
        let expectUploaded = XCTestExpectation(description: "Should have successfully uploaded")
        var tempCopyUrl: URL?
        var succeeded = false
        let succeededObserver = NotificationCenter.default.addObserver(forName: self.uploadSucceededNotification, object: nil, queue: nil) { notification in
            succeeded = true
            XCTAssertNotNil(tempCopyUrl, "Temp copy URL is nil in upload succeeded notification observer")
            if let tempCopyUrl = tempCopyUrl {
                let shouldStillExist = self.uploadApi.notifiesBridgeWhenUploaded
                self.check(file: tempCopyUrl, willRetry: false, stillExists: shouldStillExist, message: "Should not be in retry queue after successful upload", cleanUpAfter: true)
            }
            
            // make sure we didn't generate any spurious uploads or retries
            let defaults = bfum.userDefaults
            let retryUploads = defaults.dictionary(forKey: bfum.retryUploadsKey)
            let fileUploads = defaults.dictionary(forKey: bfum.bridgeFileUploadsKey)
            let uploadRequests = defaults.dictionary(forKey: bfum.uploadURLsRequestedKey)
            let uploadsToS3 = defaults.dictionary(forKey: bfum.uploadingToS3Key)
            let notifyingBridge = defaults.dictionary(forKey: bfum.notifyingBridgeUploadSucceededKey)
            XCTAssert(retryUploads?.count ?? 0 == 0, "Spurious files left in retryUploads map: \(retryUploads!)")
            XCTAssert(fileUploads?.count ?? 0 == 0, "Spurious files left in bridgeFileUploads map: \(fileUploads!)")
            XCTAssert(uploadRequests?.count ?? 0 == 0, "Spurious files left in uploadURLsRequested map: \(uploadRequests!)")
            XCTAssert(uploadsToS3?.count ?? 0 == 0, "Spurious files left in uploadingToS3 map: \(uploadsToS3!)")
            XCTAssert(notifyingBridge?.count ?? 0 == 0, "Spurious files left in notifyingBridge map: \(notifyingBridge!)")

            // make sure we didn't leave any unreferenced files lying around in the temp upload dir
            let items = try! FileManager.default.contentsOfDirectory(atPath: self.uploadApi.tempUploadDirURL.path)
            if self.uploadApi.notifiesBridgeWhenUploaded {
                XCTAssert(items.count == 1, "Expected exactly one file to be in temp upload dir:\n\(items)")
            }
            else {
                XCTAssert(items.count == 0, "Files left hanging around in temp upload dir:\n\(items)")
            }

            // make sure all the mock response stuff got "used up"
            for key in self.keysEmptyAfterUpload(for: self.mockURLSession.jsonForEndpoints) {
                let responses = self.mockURLSession.jsonForEndpoints[key] as? [Any]
                XCTAssert(responses?.count ?? 0 == 0, "Mock URLSession still has mock json response(s):\n\(self.mockURLSession.jsonForEndpoints)")
            }
            for key in self.keysEmptyAfterUpload(for: self.mockURLSession.codesforEndpoints) {
                let responses = self.mockURLSession.codesforEndpoints[key] as? [Any]
                XCTAssert(responses?.count ?? 0 == 0, "Mock URLSession still has mock response code(s):\n\(self.mockURLSession.codesforEndpoints)")
            }
            for key in self.keysEmptyAfterUpload(for: self.mockURLSession.URLsForEndpoints) {
                let responses = self.mockURLSession.URLsForEndpoints[key] as? [Any]
                XCTAssert(responses?.count ?? 0 == 0, "Mock URLSession still has (a) mock downloaded response file URL(s):\n\(self.mockURLSession.URLsForEndpoints)")
            }
            for key in self.keysEmptyAfterUpload(for: self.mockURLSession.errorsForEndpoints) {
                let responses = self.mockURLSession.errorsForEndpoints[key] as? [Any]
                XCTAssert(responses?.count ?? 0 == 0, "Mock URLSession still has (a) mock error code(s):\n\(self.mockURLSession.errorsForEndpoints)")
            }

            expectUploaded.fulfill()
        }
        
        let s3FailedObserver = NotificationCenter.default.addObserver(forName: uploadToS3FailedNotification, object: nil, queue: nil) { notification in
            XCTAssert(false, "S3 upload failed when testing \(self.uploadApi.apiString) File Upload happy path")
            expectUploaded.fulfill()
        }
        let uploadRequestFailedObserver = NotificationCenter.default.addObserver(forName: uploadRequestFailedNotification, object: nil, queue: nil) { notification in
            XCTAssert(false, "Initial upload request to Bridge failed when testing \(self.uploadApi.apiString) File Upload happy path")
            expectUploaded.fulfill()
        }

        tempCopyUrl = uploadApi.uploadInternal(fileId: testFileId, fileUrl: uploadFileUrl, contentType: mimeType, extras: uploadExtras)
        XCTAssertNotNil(tempCopyUrl, "Temp file url is nil when testing \(uploadApi.apiString) File Upload happy path")

        XCTWaiter(delegate: self).wait(for: [expectUploaded], timeout: 5.0)
        NotificationCenter.default.removeObserver(uploadRequestFailedObserver)
        NotificationCenter.default.removeObserver(s3FailedObserver)
        NotificationCenter.default.removeObserver(succeededObserver)
        
        XCTAssert(succeeded, "\(uploadApi.apiString) File Upload happy path test did not post successful upload notification")
    }
    
    // Uploaded notification gets sent while notifying Bridge of success is
    // still in process, so we don't want to fail the test if there are still
    // mock responses etc. set for that step.
    func keysEmptyAfterUpload(for mockURLSessionList: NSMutableDictionary) -> [String] {
        let allKeys = mockURLSessionList.allKeys as! [String]
        return allKeys.filter { key in
            key == mockAppManager.uploadManagerV1.notifyingBridgeUploadSucceededKey
        }
    }
}

//
//  ParticipantFileUploadManagerTests.swift
//  BridgeFileUploadsTests
//
//  Copyright © 2021 Sage Bionetworks. All rights reserved.
//
// Redistribution and use in source and binary forms, with or without modification,
// are permitted provided that the following conditions are met:
//
// 1.  Redistributions of source code must retain the above copyright notice, this
// list of conditions and the following disclaimer.
//
// 2.  Redistributions in binary form must reproduce the above copyright notice,
// this list of conditions and the following disclaimer in the documentation and/or
// other materials provided with the distribution.
//
// 3.  Neither the name of the copyright holder(s) nor the names of any contributors
// may be used to endorse or promote products derived from this software without
// specific prior written permission. No license is granted to the trademarks of
// the copyright holders even if such marks are included in this software.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE
// FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
// DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
// SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
// CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
// OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//

import XCTest
@testable import BridgeClient

class ParticipantFileUploadManagerTests: XCTestCase {
    
    let mockURLSession = MockURLSession()
    let testFileId = "TestFileId"
    var savedSession: URLSession?
    var savedDelay: TimeInterval?

    override func setUp() {
        // Put setup code here. This method is called before the invocation of each test method in the class.
        super.setUp()
        savedSession = BackgroundNetworkManager.shared.backgroundSession()
        mockURLSession.mockDelegate = savedSession!.delegate
        mockURLSession.mockDelegateQueue = savedSession!.delegateQueue
        let setMockSession = BlockOperation {
            BackgroundNetworkManager._backgroundSession = self.mockURLSession
        }
        BackgroundNetworkManager.sessionDelegateQueue.addOperations([setMockSession], waitUntilFinished: true)
        savedDelay = ParticipantFileUploadManager.shared.delayForRetry
        ParticipantFileUploadManager.shared.delayForRetry = 0 // don't delay retries for tests
    }

    override func tearDown() {
        // Put teardown code here. This method is called after the invocation of each test method in the class.
        let restoreSession = BlockOperation {
            BackgroundNetworkManager._backgroundSession = self.savedSession
        }
        BackgroundNetworkManager.sessionDelegateQueue.addOperations([restoreSession], waitUntilFinished: true)
        ParticipantFileUploadManager.shared.delayForRetry = savedDelay!
        super.tearDown()
    }
    
    func check(file: URL, willRetry: Bool, message: String) {
        check(file: file, willRetry: willRetry, stillExists: willRetry, message: message, cleanUpAfter: true)
    }
    
    func check(file: URL, willRetry: Bool, stillExists: Bool, message: String, cleanUpAfter: Bool) {
        self.mockURLSession.doSyncInDelegateQueue {
            var willRetryCheck = false
            let tempFilePath = file.path
            let fileExists = FileManager.default.fileExists(atPath: tempFilePath)
            let userDefaults = BridgeSDK.sharedUserDefaults()
            let pfum = ParticipantFileUploadManager.shared
            var retryUploads = userDefaults.dictionary(forKey: pfum.retryUploadsKey)
            for relativeFilePath in retryUploads?.keys ?? [String: Any]().keys {
                let filePath = relativeFilePath.fullyQualifiedPath()
                if filePath == tempFilePath {
                    willRetryCheck = true
                    if cleanUpAfter {
                        pfum.cleanUpTempFile(filePath: relativeFilePath)
                        let _ = pfum.removeMapping(String.self, from: relativeFilePath, defaultsKey: pfum.participantFileUploadsKey)
                        let _ = pfum.removeMapping(ParticipantFileS3Metadata.self, from: relativeFilePath, defaultsKey: pfum.uploadURLsRequestedKey)
                        let _ = pfum.removeMapping(ParticipantFileS3Metadata.self, from: relativeFilePath, defaultsKey: pfum.uploadingToS3Key)
                        let _ = pfum.removeMapping(String.self, from: relativeFilePath, defaultsKey: pfum.downloadErrorResponseBodyKey)
                        retryUploads?.removeValue(forKey: relativeFilePath)
                        BridgeSDK.sharedUserDefaults().setValue(retryUploads, forKey: pfum.retryUploadsKey)
                   }
                }
            }
            XCTAssert(willRetry == willRetryCheck, message)
            XCTAssert(fileExists == stillExists, "\(message): File for retry doesn't still exist if it should, or does if it shouldn't")
        }
    }

    func testUploadRequestFails() {
        // test fails unrecoverably due to not consented (412)
        let responseJson = ["message": "try again later"]
        let endpoint = "/v3/participants/self/files/\(testFileId)"
        let mimeType = "image/jpeg"
        guard let downloadFileUrl = Bundle(for: type(of: self)).url(forResource: "failed-upload-request-response", withExtension: "json") else {
            XCTAssert(false, "Unable to find test response file 'failed-upload-request-response.json' for ParticipantFileUploadManager upload failure tests")
            return
        }
        mockURLSession.set(json: responseJson, responseCode: 412, for: endpoint, httpMethod: "POST")
        mockURLSession.set(downloadFileUrl: downloadFileUrl, error: nil, for: endpoint, httpMethod: "POST")
        let pfum = ParticipantFileUploadManager.shared
        let expect412 = self.expectation(description: "412: not consented, don't retry")
        var tempCopyUrl: URL?
        
        // NOTE: If I move this block any further up in the function, it causes a compiler crash. Not
        // a syntax error, an actual crash of the compiler. ¯\_(ツ)_/¯ ~emm 2021-07-08
        guard let uploadFileUrl = Bundle(for: type(of: self)).url(forResource: "cat", withExtension: "jpg") else {
            XCTAssert(false, "Unable to find test image 'cat.jpg' for ParticipantFileUploadManager upload failure tests")
            return
        }
        
        let observer412 = NotificationCenter.default.addObserver(forName: .SBBParticipantFileUploadRequestFailed, object: nil, queue: nil) { notification in
            let userInfo = notification.userInfo
            XCTAssertNotNil(userInfo, "SBBParticipantFileUploadRequestFailed notification has no userInfo")
            let originalFilePath = userInfo?[pfum.filePathKey] as? String
            XCTAssertNotNil(originalFilePath, "SBBParticipantFileUploadRequestFailed notification userInfo has no file path string at '\(pfum.filePathKey)'")
            XCTAssert(originalFilePath == uploadFileUrl.path, "Original file path in userInfo '\(String(describing: originalFilePath))' does not match upload file path '\(uploadFileUrl.path)'")
            let participantFile = userInfo?[pfum.participantFileKey] as? ParticipantFile
            XCTAssertNotNil(participantFile, "SBBParticipantFileUploadRequestFailed notification userInfo has no ParticipantFile object at '\(pfum.participantFileKey)'")
            let statusCode = userInfo?[pfum.httpStatusKey] as? Int
            XCTAssertNotNil(statusCode, "SBBParticipantFileUploadRequestFailed notification userInfo has no HTTP status code at '\(pfum.httpStatusKey)'")
            XCTAssert(statusCode == 412, "Status code in userInfo should be 412 but is \(String(describing: statusCode)) instead")
            
            XCTAssertNotNil(tempCopyUrl, "Temp file copy URL is nil")
            if let tempCopyUrl = tempCopyUrl {
                self.check(file: tempCopyUrl, willRetry: false, message: "Should not retry after 412 from participant file upload api")
            }
            expect412.fulfill()
        }
        
        tempCopyUrl = pfum.uploadInternal(fileId: testFileId, fileUrl: uploadFileUrl, contentType: mimeType)
        XCTAssertNotNil(tempCopyUrl, "Temp file url is nil when testing participant file upload request failure due to 412 not consented")
        
        self.wait(for: [expect412], timeout: 5.0)
        NotificationCenter.default.removeObserver(observer412)
        
        // test initially fails due to server down (503) but succeeds on retry
        // -- set up initial 503 response, and add observer for eventual success
        mockURLSession.set(json: responseJson, responseCode: 503, for: endpoint, httpMethod: "POST")
        mockURLSession.set(downloadFileUrl: downloadFileUrl, error: nil, for: endpoint, httpMethod: "POST")
        let expectRetried = self.expectation(description: "503: retry later")
        let observer503Retried = NotificationCenter.default.addObserver(forName: .SBBParticipantFileUploaded, object: nil, queue: nil) { notification in
            let userInfo = notification.userInfo
            XCTAssertNotNil(userInfo, "SBBParticipantFileUploaded notification has no userInfo")
            let originalFilePath = userInfo?[pfum.filePathKey] as? String
            XCTAssertNotNil(originalFilePath, "SBBParticipantFileUploaded notification userInfo has no file path string at '\(pfum.filePathKey)'")
            XCTAssert(originalFilePath == uploadFileUrl.path, "Original file path in userInfo '\(String(describing: originalFilePath))' does not match upload file path '\(uploadFileUrl.path)'")
            let participantFile = userInfo?[pfum.participantFileKey] as? ParticipantFile
            XCTAssertNotNil(participantFile, "SBBParticipantFileUploaded notification userInfo has no ParticipantFile object at '\(pfum.participantFileKey)'")
            let requestUrl = userInfo?[pfum.requestUrlKey] as? URL
            XCTAssertNotNil(requestUrl, "SBBParticipantFileUploaded notification userInfo has no request URL at '\(pfum.requestUrlKey)")
            XCTAssertNotNil(tempCopyUrl, "Temp file copy URL is nil")
            if let tempCopyUrl = tempCopyUrl {
                self.check(file: tempCopyUrl, willRetry: false, message: "Should no longer be in retry queue upon successful retry after initial 503 error")
            }
            
            // make sure we didn't generate any spurious uploads or retries
            let defaults = BridgeSDK.sharedUserDefaults()
            let retryUploads = defaults.dictionary(forKey: pfum.retryUploadsKey)
            let fileUploads = defaults.dictionary(forKey: pfum.participantFileUploadsKey)
            let uploadRequests = defaults.dictionary(forKey: pfum.uploadURLsRequestedKey)
            let uploadsToS3 = defaults.dictionary(forKey: pfum.uploadingToS3Key)
            XCTAssert(retryUploads?.count ?? 0 == 0, "Spurious files left in retryUploads map: \(retryUploads!)")
            XCTAssert(fileUploads?.count ?? 0 == 0, "Spurious files left in participantFileUploads map: \(fileUploads!)")
            XCTAssert(uploadRequests?.count ?? 0 == 0, "Spurious files left in uploadURLsRequested map: \(uploadRequests!)")
            XCTAssert(uploadsToS3?.count ?? 0 == 0, "Spurious files left in uploadingToS3 map: \(uploadsToS3!)")

            // make sure we didn't leave any unreferenced files lying around in the temp upload dir
            let items = try! FileManager.default.contentsOfDirectory(atPath: pfum.tempUploadDirURL.path)
            XCTAssert(items.count == 0, "Files left hanging around in temp upload dir:\n\(items)")

            // make sure all the mock response stuff got "used up"
            for key in self.mockURLSession.jsonForEndpoints.allKeys {
                let responses = self.mockURLSession.jsonForEndpoints[key] as? [Any]
                XCTAssert(responses?.count ?? 0 == 0, "Mock URLSession still has mock json response(s):\n\(self.mockURLSession.jsonForEndpoints)")
            }
            for key in self.mockURLSession.codesforEndpoints.allKeys {
                let responses = self.mockURLSession.codesforEndpoints[key] as? [Any]
                XCTAssert(responses?.count ?? 0 == 0, "Mock URLSession still has mock response code(s):\n\(self.mockURLSession.codesforEndpoints)")
            }
            for key in self.mockURLSession.URLsForEndpoints.allKeys {
                let responses = self.mockURLSession.URLsForEndpoints[key] as? [Any]
                XCTAssert(responses?.count ?? 0 == 0, "Mock URLSession still has (a) mock downloaded response file URL(s):\n\(self.mockURLSession.URLsForEndpoints)")
            }
            for key in self.mockURLSession.errorsForEndpoints.allKeys {
                let responses = self.mockURLSession.errorsForEndpoints[key] as? [Any]
                XCTAssert(responses?.count ?? 0 == 0, "Mock URLSession still has (a) mock error code(s):\n\(self.mockURLSession.errorsForEndpoints)")
            }

            expectRetried.fulfill()
        }
        
        var retryRecoverable = true
        let observer503NotRetried = NotificationCenter.default.addObserver(forName: .SBBParticipantFileUploadRequestFailed, object: nil, queue: nil) { notification in
            XCTAssert(false, "initial 503 treated as unrecoverable, not retried")
            retryRecoverable = false
            expectRetried.fulfill()
        }
        
        let observer503RetriedButS3Failed = NotificationCenter.default.addObserver(forName: .SBBParticipantFileUploadToS3Failed, object: nil, queue: nil) { notification in
            XCTAssert(false, "initial 503 retried, but mock upload to S3 failed")
            expectRetried.fulfill()
        }
        
        // -- start the upload attempt. This should get a 503 Server Busy response initially and
        //    queue up the file for 'later' retry.
        tempCopyUrl = pfum.uploadInternal(fileId: testFileId, fileUrl: uploadFileUrl, contentType: mimeType)
        XCTAssertNotNil(tempCopyUrl, "Temp file url is nil when testing participant file upload request retrying after initial 503 from upload api")
        guard let tempCopyUrl = tempCopyUrl else { return }

        // -- now set up the responses for the retry attempt and then initiate it.
        //    (queue up so this happens after the above has completed)
        self.mockURLSession.delegateQueue.addOperation {
            guard retryRecoverable else { return }
            // first, check that the file is indeed in the retry queue as expected
            self.check(file: tempCopyUrl, willRetry: true, stillExists: true, message: "Should retry after 503 from participant file upload API", cleanUpAfter: false)
            
            // set up the responses for the retry
            // -- set up the Participant File Upload Request response
            let s3url = "/not-a-real-pre-signed-S3-url"
            let participantFile = ParticipantFile(fileId: self.testFileId, mimeType: mimeType, createdOn: nil, downloadUrl: nil, uploadUrl: s3url)
            var responseJson: Any
            do {
                responseJson = try DictionaryEncoder().encode(participantFile)
            } catch let error {
                print("Error attempting to encode ParticipantFile object \(participantFile) to json dict: \(error)")
                return
            }
            guard let downloadFileUrl = Bundle(for: type(of: self)).url(forResource: "upload-request-success", withExtension: "json") else {
                XCTAssert(false, "Unable to find test response file 'upload-request-success.json' for ParticipantFileUploadManager upload failure tests")
                return
            }
            self.mockURLSession.set(json: responseJson, responseCode: 201, for: endpoint, httpMethod: "POST")
            self.mockURLSession.set(downloadFileUrl: downloadFileUrl, error: nil, for: endpoint, httpMethod: "POST")
            
            // -- set up the S3 upload success response
            self.mockURLSession.set(json: [:], responseCode: 200, for: s3url, httpMethod: "PUT")
            
            // TODO: When adapting this test for result file uploads, set up the "upload completed"
            // api call response here too ~emm 2021-07-08
            
            // -- do the retry
            pfum.retryUploadsAfterDelay()
        }
        
        // -- wait here until everything above has worked its way through.
        self.wait(for: [expectRetried], timeout: 5.0)
        NotificationCenter.default.removeObserver(observer503Retried)
        NotificationCenter.default.removeObserver(observer503NotRetried)
        NotificationCenter.default.removeObserver(observer503RetriedButS3Failed)

    }
    
    func testUploadFileToBridgeWhenS3RespondsWithVariousFailuresThatShouldRetryLater() {
        testUploadFileToBridgeWhenS3Responds(status: 403)
        testUploadFileToBridgeWhenS3Responds(status: 409)
        testUploadFileToBridgeWhenS3Responds(status: 500)
        testUploadFileToBridgeWhenS3Responds(status: 503)
    }
    
    func testUploadFileToBridgeWhenS3Responds(status: Int) {
        let s3url = "/not-a-real-pre-signed-S3-url"
        let mimeType = "image/jpeg"
        let endpoint = "/v3/participants/self/files/\(testFileId)"
        guard let uploadFileUrl = Bundle(for: type(of: self)).url(forResource: "cat", withExtension: "jpg") else {
            XCTAssert(false, "Unable to find test image 'cat.jpg' for ParticipantFileUploadManager S3 error response tests")
            return
        }

        // -- set up the mock UploadRequest response
        let createdOn = Date().addingTimeInterval(-172800)
        let expiresOn = Date().addingTimeInterval(-86400)
        let participantFile = ParticipantFile(fileId: self.testFileId, mimeType: mimeType, createdOn: createdOn, downloadUrl: nil, uploadUrl: s3url, expiresOn: expiresOn)
        var responseJson: Any
        do {
            responseJson = try DictionaryEncoder().encode(participantFile)
        } catch let error {
            XCTAssert(false, "Error attempting to encode ParticipantFile object \(participantFile) to json dict: \(error)")
            return
        }
        let downloadFileName = (status == 403) ? "upload-request-expired" : "upload-request-success"
        guard let downloadFileUrl = Bundle(for: type(of: self)).url(forResource: downloadFileName, withExtension: "json") else {
            XCTAssert(false, "Unable to find test response file '\(downloadFileName).json' for ParticipantFileUploadManager S3 error response tests")
            return
        }
        self.mockURLSession.set(json: responseJson, responseCode: 201, for: endpoint, httpMethod: "POST")
        self.mockURLSession.set(downloadFileUrl: downloadFileUrl, error: nil, for: endpoint, httpMethod: "POST")

        // -- set up the mock S3 upload failed response
        responseJson = ["Arbitrary S3 response" : "We should be ignoring this"]
        self.mockURLSession.set(json: responseJson, responseCode: status, for: s3url, httpMethod: "PUT")
        
        // -- try it
        let pfum = ParticipantFileUploadManager.shared
        let expectStatus = self.expectation(description: "Should have been in retry queue after non-success status from S3")
        var tempCopyUrl: URL?
        let errorResponseButSucceeded = NotificationCenter.default.addObserver(forName: .SBBParticipantFileUploaded, object: nil, queue: nil) { notification in
            XCTAssert(false, "S3 upload succeeded, but should have been queued up for retry on response code \(status)")
            expectStatus.fulfill()
        }
        let retryableErrorButFailed = NotificationCenter.default.addObserver(forName: .SBBParticipantFileUploadToS3Failed, object: nil, queue: nil) { notification in
            XCTAssert(false, "S3 upload failed permanently, but should have been queued up for retry on response code \(status)")
            expectStatus.fulfill()
        }
        let whatTheHow = NotificationCenter.default.addObserver(forName: .SBBParticipantFileUploadRequestFailed, object: nil, queue: nil) { notification in
            XCTAssert(false, "S3 upload attempt somehow posted a file upload request failed notification (wth?), but should have been queued up for retry on response code \(status)")
            expectStatus.fulfill()
        }

        tempCopyUrl = pfum.uploadInternal(fileId: testFileId, fileUrl: uploadFileUrl)
        XCTAssertNotNil(tempCopyUrl, "Temp file url is nil when testing participant file upload request with retryable S3 error response")
        guard let tempCopyUrl = tempCopyUrl else { return }

        // queue up a couple of times to make sure the above stuff has actually completed before we check the retry queue
        self.mockURLSession.delegateQueue.addOperation {
            print("testUploadFileToBridgeWhenS3Responds \(status): once through delegate queue")
            self.mockURLSession.delegateQueue.addOperation {
                print("testUploadFileToBridgeWhenS3Responds \(status): twice through delegate queue")
                self.mockURLSession.delegateQueue.addOperation {
                    print("testUploadFileToBridgeWhenS3Responds \(status): thrice through delegate queue")
                    expectStatus.fulfill()
                }
            }
        }
        self.wait(for: [expectStatus], timeout: 5.0)
        NotificationCenter.default.removeObserver(whatTheHow)
        NotificationCenter.default.removeObserver(retryableErrorButFailed)
        NotificationCenter.default.removeObserver(errorResponseButSucceeded)
        
        self.check(file: tempCopyUrl, willRetry: true, message: "Should have been in retry queue after non-success status \(status) from S3")
    }

    func testUploadFileToBridgeHappyPath() {
        let s3url = "/not-a-real-pre-signed-S3-url"
        let mimeType = "image/jpeg"
        let endpoint = "/v3/participants/self/files/\(testFileId)"
        guard let uploadFileUrl = Bundle(for: type(of: self)).url(forResource: "cat", withExtension: "jpg") else {
            XCTAssert(false, "Unable to find test image 'cat.jpg' for ParticipantFileUploadManager happy path test")
            return
        }

        // -- set up the mock UploadRequest response
        let createdOn = Date()
        let expiresOn = createdOn.addingTimeInterval(86400)
        let participantFile = ParticipantFile(fileId: self.testFileId, mimeType: mimeType, createdOn: createdOn, downloadUrl: nil, uploadUrl: s3url, expiresOn: expiresOn)
        var responseJson: Any
        do {
            responseJson = try DictionaryEncoder().encode(participantFile)
        } catch let error {
            XCTAssert(false, "Error attempting to encode ParticipantFile object \(participantFile) to json dict: \(error)")
            return
        }
        guard let downloadFileUrl = Bundle(for: type(of: self)).url(forResource: "upload-request-success", withExtension: "json") else {
            XCTAssert(false, "Unable to find test response file 'upload-request-success.json' for ParticipantFileUploadManager happy path test")
            return
        }
        self.mockURLSession.set(json: responseJson, responseCode: 201, for: endpoint, httpMethod: "POST")
        self.mockURLSession.set(downloadFileUrl: downloadFileUrl, error: nil, for: endpoint, httpMethod: "POST")

        // -- set up the mock S3 upload succeeded response
        responseJson = ["Arbitrary S3 response" : "We should be ignoring this"]
        self.mockURLSession.set(json: responseJson, responseCode: 200, for: s3url, httpMethod: "PUT")
        
        // TODO: When adapting for result file upload API, here's where to set up the mock upload completed response
        
        // -- try it
        let pfum = ParticipantFileUploadManager.shared
        let expectUploaded = self.expectation(description: "Should have successfully uploaded")
        var tempCopyUrl: URL?
        var succeeded = false
        let succeededObserver = NotificationCenter.default.addObserver(forName: .SBBParticipantFileUploaded, object: nil, queue: nil) { notification in
            succeeded = true
            XCTAssertNotNil(tempCopyUrl, "Temp copy URL is nil in upload succeeded notification observer")
            if let tempCopyUrl = tempCopyUrl {
                self.check(file: tempCopyUrl, willRetry: false, message: "Should not be in retry queue after successful upload")
            }
            
            // make sure we didn't generate any spurious uploads or retries
            let defaults = BridgeSDK.sharedUserDefaults()
            let retryUploads = defaults.dictionary(forKey: pfum.retryUploadsKey)
            let fileUploads = defaults.dictionary(forKey: pfum.participantFileUploadsKey)
            let uploadRequests = defaults.dictionary(forKey: pfum.uploadURLsRequestedKey)
            let uploadsToS3 = defaults.dictionary(forKey: pfum.uploadingToS3Key)
            XCTAssert(retryUploads?.count ?? 0 == 0, "Spurious files left in retryUploads map: \(retryUploads!)")
            XCTAssert(fileUploads?.count ?? 0 == 0, "Spurious files left in participantFileUploads map: \(fileUploads!)")
            XCTAssert(uploadRequests?.count ?? 0 == 0, "Spurious files left in uploadURLsRequested map: \(uploadRequests!)")
            XCTAssert(uploadsToS3?.count ?? 0 == 0, "Spurious files left in uploadingToS3 map: \(uploadsToS3!)")

            // make sure we didn't leave any unreferenced files lying around in the temp upload dir
            let items = try! FileManager.default.contentsOfDirectory(atPath: pfum.tempUploadDirURL.path)
            XCTAssert(items.count == 0, "Files left hanging around in temp upload dir:\n\(items)")

            // make sure all the mock response stuff got "used up"
            for key in self.mockURLSession.jsonForEndpoints.allKeys {
                let responses = self.mockURLSession.jsonForEndpoints[key] as? [Any]
                XCTAssert(responses?.count ?? 0 == 0, "Mock URLSession still has mock json response(s):\n\(self.mockURLSession.jsonForEndpoints)")
            }
            for key in self.mockURLSession.codesforEndpoints.allKeys {
                let responses = self.mockURLSession.codesforEndpoints[key] as? [Any]
                XCTAssert(responses?.count ?? 0 == 0, "Mock URLSession still has mock response code(s):\n\(self.mockURLSession.codesforEndpoints)")
            }
            for key in self.mockURLSession.URLsForEndpoints.allKeys {
                let responses = self.mockURLSession.URLsForEndpoints[key] as? [Any]
                XCTAssert(responses?.count ?? 0 == 0, "Mock URLSession still has (a) mock downloaded response file URL(s):\n\(self.mockURLSession.URLsForEndpoints)")
            }
            for key in self.mockURLSession.errorsForEndpoints.allKeys {
                let responses = self.mockURLSession.errorsForEndpoints[key] as? [Any]
                XCTAssert(responses?.count ?? 0 == 0, "Mock URLSession still has (a) mock error code(s):\n\(self.mockURLSession.errorsForEndpoints)")
            }

            expectUploaded.fulfill()
        }
        let s3FailedObserver = NotificationCenter.default.addObserver(forName: .SBBParticipantFileUploadToS3Failed, object: nil, queue: nil) { notification in
            XCTAssert(false, "S3 upload failed when testing Participant File Upload happy path")
            expectUploaded.fulfill()
        }
        let uploadRequestFailedObserver = NotificationCenter.default.addObserver(forName: .SBBParticipantFileUploadRequestFailed, object: nil, queue: nil) { notification in
            XCTAssert(false, "Initial upload request to Bridge failed when testing Participant File Upload happy path")
            expectUploaded.fulfill()
        }

        tempCopyUrl = pfum.uploadInternal(fileId: testFileId, fileUrl: uploadFileUrl)
        XCTAssertNotNil(tempCopyUrl, "Temp file url is nil when testing participant file upload request with retryable S3 error response")

        self.wait(for: [expectUploaded], timeout: 5.0)
        NotificationCenter.default.removeObserver(uploadRequestFailedObserver)
        NotificationCenter.default.removeObserver(s3FailedObserver)
        NotificationCenter.default.removeObserver(succeededObserver)
        
        XCTAssert(succeeded, "Participant File Upload happy path test did not post successful upload notification")
    }
}

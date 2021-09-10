//
//  MockURLSession.swift
//  BridgeFileUploads
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

import Foundation

// MARK: MockHTTPURLResponse
class MockHTTPURLResponse: HTTPURLResponse {
}

// MARK: MockUploadTask
class MockUploadTask: URLSessionUploadTask {
    var session: MockURLSession
    var request: URLRequest
    var mockResponse: MockHTTPURLResponse?
    
    override func resume() {
        session.delegateQueue.addOperation { [self] in
            (_, mockResponse) = session.dataAndResponse(for: request)
            (session.delegate as? URLSessionTaskDelegate)?.urlSession?(session, task: self, didCompleteWithError: nil)
            session.remove(mockTask: self)
        }
    }
    
    override var response: URLResponse? {
        return mockResponse
    }
    
    init(session: MockURLSession, request: URLRequest) {
        self.session = session
        self.request = request
    }
}

// MARK: MockDownloadTask
class MockDownloadTask: URLSessionDownloadTask {
    var session: MockURLSession
    var request: URLRequest
    var mockResponse: MockHTTPURLResponse?
    
    override func resume() {
        session.delegateQueue.addOperation { [self] in
            (_, mockResponse) = session.dataAndResponse(for: request)
            let (fileUrl, error) = session.downloadFileUrlAndError(for: request)
            session.remove(mockTask: self)
            guard let fileUrl = fileUrl else {
                debugPrint("TEST SETUP ERROR: No download file URL provided for mock download task request.")
                return
            }
            (session.delegate as? URLSessionDownloadDelegate)?.urlSession(self.session, downloadTask: self, didFinishDownloadingTo: fileUrl)
            (session.delegate as? URLSessionTaskDelegate)?.urlSession?(session, task: self, didCompleteWithError: error)
        }
    }
    
    override var response: URLResponse? {
        return mockResponse
    }
    
    init(session: MockURLSession, request: URLRequest) {
        self.session = session
        self.request = request
    }
}

// MARK: MockURLSession
class MockURLSession: URLSession {
    var mockDelegate: URLSessionDelegate?
    public override var delegate: URLSessionDelegate? {
        return mockDelegate
    }

    var mockDelegateQueue: OperationQueue?
    public override var delegateQueue: OperationQueue {
        if mockDelegateQueue == nil {
            let mockDelegateQueue = OperationQueue()
            mockDelegateQueue.maxConcurrentOperationCount = 1
        }
        return mockDelegateQueue!
    }
    
    var jsonForEndpoints = NSMutableDictionary()
    var codesforEndpoints = NSMutableDictionary()
    var URLsForEndpoints = NSMutableDictionary()
    var errorsForEndpoints = NSMutableDictionary()
    var mockTasks = NSMutableArray()
    
    func key(for endpoint: String, httpMethod: String) -> String {
        return httpMethod.appending(endpoint)
    }
    
    func responses(for key: String) -> NSMutableArray {
        var responses = jsonForEndpoints[key] as? NSMutableArray
        if responses == nil {
            responses = NSMutableArray()
            jsonForEndpoints[key] = responses
        }
        return responses!
    }
    
    func codes(for key: String) -> NSMutableArray {
        var codes = codesforEndpoints[key] as? NSMutableArray
        if codes == nil {
            codes = NSMutableArray()
            codesforEndpoints[key] = codes
        }
        return codes!
    }
    
    func set(json: Any?, responseCode: Int, for endpoint: String, httpMethod: String) {
        let key = key(for: endpoint, httpMethod: httpMethod)
        responses(for: key).add(json ?? NSNull())
        codes(for: key).add(responseCode)
    }
    
    func setJsonFromFile(named fileName: String, responseCode: Int, for endpoint: String, httpMethod: String) {
        guard let fileUrl = Bundle(for: type(of: self).self).url(forResource: fileName, withExtension: "json") else {
            debugPrint("WARNING: Failed to get .json resource url for file '\(fileName)'")
            return
        }
        
        var data: Data
        do {
            data = try Data(contentsOf: fileUrl)
        } catch let error {
            debugPrint("WARNING: Failed to get data from fileUrl:\n\(fileUrl)\n\(error)")
            return
        }
        
        var json: Any
        do {
            json = try JSONSerialization.jsonObject(with: data)
        } catch let error {
            debugPrint("WARNING: Failed to decode json file '\(fileUrl)': \(error) ")
            return
        }
        
        set(json: json, responseCode: responseCode, for: endpoint, httpMethod: httpMethod)
    }
    
    func pullNextResponse(for key: String) -> Any? {
        let responses = responses(for: key)
        guard responses.count > 0 else {
            return nil
        }
        let response = responses.object(at: 0)
        responses.removeObject(at: 0)
        if response is NSNull {
            return nil
        }
        return response
    }
    
    func pullNextCode(for key: String) -> Int? {
        let codes = codes(for: key)
        guard codes.count > 0 else {
            return nil
        }
        let code = codes.object(at: 0) as? Int
        codes.removeObject(at: 0)
        return code
    }
    
    func headersContainValidAuth(_ headers: [String: String]?) -> Bool {
        return headers?["Bridge-Session"]?.lowercased() != "expired"
    }
    
    func dataAndResponse(for request: URLRequest) -> (data: Data?, response: MockHTTPURLResponse?) {
        var statusCode: Int?
        var json: Any?
        if headersContainValidAuth(request.allHTTPHeaderFields) {
            let key = key(for: request.url!.path, httpMethod: request.httpMethod!)
            json = pullNextResponse(for: key)
            statusCode = pullNextCode(for: key)
        }
        else {
            statusCode = 401
        }
        
        let response = MockHTTPURLResponse(url: request.url!, statusCode: statusCode ?? 0, httpVersion: nil, headerFields: request.allHTTPHeaderFields)
        var data: Data? = nil
        if json != nil {
            data = try! JSONSerialization.data(withJSONObject: json!)
        }
        
        return (data, response)
    }
    
    func fileUrls(for key: String) -> NSMutableArray {
        var fileUrls = URLsForEndpoints[key] as? NSMutableArray
        if fileUrls == nil {
            fileUrls = NSMutableArray()
            URLsForEndpoints[key] = fileUrls
        }
        return fileUrls!
    }
    
    func errors(for key: String) -> NSMutableArray {
        var errors = errorsForEndpoints[key] as? NSMutableArray
        if errors == nil {
            errors = NSMutableArray()
            errorsForEndpoints[key] = errors
        }
        return errors!
    }
    
    func set(downloadFileUrl fileUrl: URL?, error: Error?, for endpoint: String, httpMethod: String) {
        let key = key(for: endpoint, httpMethod: httpMethod)
        fileUrls(for: key).add(fileUrl ?? NSNull())
        errors(for: key).add(error ?? NSNull())
    }
    
    func pullNextFileUrl(for key: String) -> URL? {
        let fileUrls = fileUrls(for: key)
        
        guard fileUrls.count > 0 else {
            return nil
        }
        
        let fileUrl = fileUrls.firstObject as? URL
        fileUrls.removeObject(at: 0)
        
        return fileUrl
    }
    
    func pullNextError(for key: String) -> Error? {
        let errors = errors(for: key)
        
        guard errors.count > 0 else {
            return nil
        }
        
        let error = errors.firstObject as? Error
        errors.removeObject(at: 0)
        return error
    }
    
    func downloadFileUrlAndError(for request: URLRequest) -> (URL?, Error?) {
        let key = key(for: request.url!.path, httpMethod: request.httpMethod!)
        return (pullNextFileUrl(for: key), pullNextError(for: key))
    }
    
    func doSyncInDelegateQueue(block: @escaping () -> Void) {
        if OperationQueue.current == self.delegateQueue {
            block()
        }
        else {
            let op = BlockOperation(block: block)
            self.delegateQueue.addOperations([op], waitUntilFinished: true)
        }
    }
    
    func add(mockTask: URLSessionTask) {
        doSyncInDelegateQueue {
            self.mockTasks.add(mockTask)
        }
    }
    
    func remove(mockTask: URLSessionTask) {
        doSyncInDelegateQueue {
            self.mockTasks.remove(mockTask)
        }
    }
    
    override func uploadTask(with request: URLRequest, fromFile fileURL: URL) -> URLSessionUploadTask {
        let task = MockUploadTask(session: self, request: request)
        add(mockTask: task)
        return task
    }
    
    override func downloadTask(with request: URLRequest) -> URLSessionDownloadTask {
        let task = MockDownloadTask(session: self, request: request)
        add(mockTask: task)
        return task
    }
}


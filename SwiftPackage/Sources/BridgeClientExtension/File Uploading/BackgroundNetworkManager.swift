//
//  BackgroundNetworkManager.swift
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
import BridgeClient
import JsonModel

protocol URLSessionBackgroundDelegate: URLSessionDataDelegate, URLSessionDownloadDelegate {
}

extension URLRequest {
    mutating fileprivate func addHeaders(_ headers: [String : String]?) {
        let userAgentHeader = IOSBridgeConfig().userAgent
        self.setValue(userAgentHeader, forHTTPHeaderField: "User-Agent")

        let acceptLanguageHeader = Locale.preferredLanguages.joined(separator: ", ")
        self.setValue(acceptLanguageHeader, forHTTPHeaderField: "Accept-Language")

        self.setValue("no-cache", forHTTPHeaderField: "cache-control")
        
        headers?.forEach {
            self.addValue($0.value, forHTTPHeaderField: $0.key)
        }
    }
}

enum HTTPMethod : String {
    case GET, POST, PUT, DELETE
}

class BackgroundNetworkManager: NSObject, URLSessionBackgroundDelegate {

    /// A singleton instance of the manager.
    static let shared = BackgroundNetworkManager()

    /// The identifier (base) for the background URLSession. App extensions will append a unique string to this to distinguish
    /// their background sessions.
    static let backgroundSessionIdentifier = "org.sagebase.backgroundnetworkmanager.session"
    
    /// BackgroundNetworkManager needs access to app configuration and user session info. The app manager should create the singleton
    /// instance and immediately set this value to itself.
    var appManager: UploadAppManager!

    /// We use this custom HTTP request header as a hack to keep track of how many times we've retried a request.
    let retryCountHeader = "X-SageBridge-Retry"
    
    /// This sets the maximum number of times we will retry a request before giving up.
    let maxRetries = 5
    
    /// If set, URLSession(Data/Download)Delegate method calls received by the BackgroundNetworkManager
    /// will be passed through to this object for further handling.
    var backgroundTransferDelegate: URLSessionBackgroundDelegate?
    
    /// The queue used for calling background session delegate methods.
    ///  Also used for creating the singleton background session itself in a thread-safe way.
    ///  Created lazily.
    static let sessionDelegateQueue: OperationQueue = {
        let delegateQueue = OperationQueue()
        delegateQueue.maxConcurrentOperationCount = 1
        return delegateQueue
    }()
            
    /// The singleton background URLSession.
    static var _backgroundSession: URLSession? = nil
    
    /// A singleton map of pending background URLSession completion handlers that have been passed in from the app delegate and not yet called.
    var backgroundSessionCompletionHandlers = [String : () -> Void]()
    
    func isRunningInAppExtension() -> Bool {
        // "An app extension target’s Info.plist file identifies the extension point and may specify some details
        // about your extension. At a minimum, the file includes the NSExtension key and a dictionary of keys and
        // values that the extension point specifies."
        // (see https://developer.apple.com/library/content/documentation/General/Conceptual/ExtensibilityPG/ExtensionCreation.html)
        // We also double-check that the Bundle OS Type Code is not APPL, just to be sure they haven't for some
        // reason added that key to their app's infoDict.
        guard let infoDict = Bundle.main.infoDictionary,
              let packageType = infoDict["CFBundlePackageType"] as? String
            else { return false }
        return (packageType != "APPL") && infoDict["NSExtension"] != nil
    }
    
    /// Private initializer so only the singleton can ever get created.
    private override init() {
        super.init()
    }
    
    /// For encoding objects to be passed to Bridge.
    let jsonEncoder = SerializationFactory.defaultFactory.createJSONEncoder()
    
    /// For decoding objects received from Bridge.
    let jsonDecoder = SerializationFactory.defaultFactory.createJSONDecoder()
    
    /// Access (and if necessary, create) the singleton background URLSession used by the singleton BackgroundNetworkManager.
    /// Make sure it only gets created once, regardless of threading.
    func backgroundSession() -> URLSession {
        if BackgroundNetworkManager._backgroundSession == nil {
            // If it doesn't yet exist, queue up a block of code to create it.
            let createSessionOperation = BlockOperation {
                // Once it's our turn in the operation queue, check if someone else created it
                // in the meantime so we don't clobber it.
                guard BackgroundNetworkManager._backgroundSession == nil else { return }
                
                // OK, create it.
                var sessionIdentifier = BackgroundNetworkManager.backgroundSessionIdentifier
                if self.isRunningInAppExtension() {
                    // Uniquify it from the containing app's BridgeClient background session and those of any other
                    // app extensions or instances thereof with the same containing app that use BridgeClient. Note
                    // that if the extension is gone when the background upload/download finishes, the containing
                    // app will be launched to handle it, not the extension, so this string doesn't need to be
                    // preserved across multiple invocations of the extension, and this way multiple simultaneous
                    // instances of the same extension, if such a thing is possible, wouldn't interfere with
                    // each other.
                    sessionIdentifier.append(UUID().uuidString)
                }
                
                self.createBackgroundSession(with: sessionIdentifier)
            }
            BackgroundNetworkManager.sessionDelegateQueue.addOperations([createSessionOperation], waitUntilFinished: true)
        }
        return BackgroundNetworkManager._backgroundSession!
    }
    
    // internal-use-only method, must always be called on the session delegate queue
    fileprivate func createBackgroundSession(with sessionIdentifier: String) {
        let config = URLSessionConfiguration.background(withIdentifier: sessionIdentifier)
        if let appGroupIdentifier = IOSBridgeConfig().appGroupIdentifier, !appGroupIdentifier.isEmpty {
            config.sharedContainerIdentifier = appGroupIdentifier
        }
        
        BackgroundNetworkManager._backgroundSession = URLSession(configuration: config, delegate: self, delegateQueue: BackgroundNetworkManager.sessionDelegateQueue)
    }
    
    func bridgeBaseURL() -> URL {
        let basePath = IOSBridgeConfig().bridgeEnvironment.basePath()
        guard let baseUrl = URL(string: basePath) else {
            fatalError("Unable to create URL object from string '\(basePath)'")
        }
        
        return baseUrl
    }
    
    func bridgeURL(for urlString: String) -> URL {
        // If the string is a full httpx:// url already, just return it as a URL
        if let fullURL = URL(string: urlString), fullURL.scheme?.hasPrefix("http") ?? false {
            return fullURL
        }
        
        let baseUrl = bridgeBaseURL()
        guard let bridgeUrl = URL(string: urlString, relativeTo: baseUrl) else {
            fatalError("Unable to create URL object from string '\(urlString)' relative to \(baseUrl)")
        }
        
        return bridgeUrl
    }
    
    func queryString(from parameters: [String : String]?) -> String? {
        parameters?.compactMap { (param, value) in
            guard let encodedParam = param.addingPercentEncoding(withAllowedCharacters: CharacterSet.urlQueryAllowed),
                  let encodedValueString = "\"\(value)\"".addingPercentEncoding(withAllowedCharacters: CharacterSet.urlQueryAllowed)
            else {
                return nil
            }
            return "\(encodedParam)=\(encodedValueString)"
        }.joined(separator: "&")
    }
    
    func request(method: HTTPMethod, URLString: String, headers: [String : String]?) -> URLRequest {
        var request = URLRequest(url: bridgeURL(for: URLString))
        request.httpMethod = method.rawValue
        request.httpShouldHandleCookies = false
        request.addHeaders(headers)
        
        debugPrint("Prepared request--URL:\n\(String(describing: request.url?.absoluteString))\nHeaders:\n\(String(describing: request.allHTTPHeaderFields))")
        return request
    }
    
    func request<T>(method: HTTPMethod, URLString: String, headers: [String : String]?, parameters: T) -> URLRequest where T: Encodable {
        var URLString = URLString
        let isGet = (method == .GET)
        
        // for GET requests, the parameters go in the query part of the URL
        if isGet, let queryString = queryString(from: parameters as? [String : String]), !queryString.isEmpty {
            if URLString.contains("?") {
                URLString.append("&\(queryString)")
            }
            else {
                URLString.append("?\(queryString)")
            }
        }

        var request = self.request(method: method, URLString: URLString, headers: headers)
        
        // for non-GET requests, the parameters (if any) go in the request body
        let contentTypeHeader = "Content-Type"
        if !isGet {
            if request.value(forHTTPHeaderField: contentTypeHeader) == nil {
                let ianaCharset = CFStringConvertEncodingToIANACharSetName(CFStringConvertNSStringEncodingToEncoding(String.Encoding.utf8.rawValue)) as String
                request.setValue("application/json; charset=\(ianaCharset)", forHTTPHeaderField: contentTypeHeader)
            }
            do {
                let jsonData = try jsonEncoder.encode(parameters)
                request.httpBody = jsonData
            } catch let error {
                debugPrint("Error encoding parameters for \(method) request to URL \(URLString):\n\(parameters)\n\(error)")
            }
        }
        
        debugPrint("Request body:\n\(String(describing: String(data: request.httpBody ?? Data(), encoding: .utf8)))")
        
        return request
    }
    
    @discardableResult
    func downloadFile(from URLString: String, method: HTTPMethod, httpHeaders: [String : String]?, taskDescription: String) -> URLSessionDownloadTask {
        let request = self.request(method: method, URLString: URLString, headers: httpHeaders)
        return self.downloadFile(with: request, taskDescription: taskDescription)
    }
    
    @discardableResult
    func downloadFile<T>(from URLString: String, method: HTTPMethod, httpHeaders: [String : String]?, parameters: T?, taskDescription: String) -> URLSessionDownloadTask where T: Encodable {
        let request =  self.request(method: method, URLString: URLString, headers: httpHeaders, parameters: parameters)
        return self.downloadFile(with: request, taskDescription: taskDescription)
    }
    
    private func downloadFile(with request: URLRequest, taskDescription: String) -> URLSessionDownloadTask {
        let task = self.backgroundSession().downloadTask(with: request)
        task.taskDescription = taskDescription
        task.resume()
        return task
    }
    
    @discardableResult
    func uploadFile(_ fileURL: URL, httpHeaders: [String : String]?, to urlString: String, taskDescription: String) -> URLSessionUploadTask? {
        guard let url = URL(string: urlString) else {
            debugPrint("Could not create URL from string '\(urlString)")
            return nil
        }
        var request = URLRequest(url: url)
        request.allHTTPHeaderFields = httpHeaders
        request.httpMethod = HTTPMethod.PUT.rawValue
        let task = backgroundSession().uploadTask(with: request, fromFile: fileURL)
        task.taskDescription = taskDescription
        task.resume()
        return task
    }
    
    func restore(backgroundSession: String, completionHandler: @escaping () -> Void) {
        guard backgroundSession.starts(with: BackgroundNetworkManager.backgroundSessionIdentifier) else { return }
        self.backgroundSessionCompletionHandlers[backgroundSession] = completionHandler
        BackgroundNetworkManager.sessionDelegateQueue.addOperation {
            if BackgroundNetworkManager._backgroundSession == nil {
                self.createBackgroundSession(with: backgroundSession)
            }
        }
    }
    
    // MARK: Helpers
    func isTemporaryError(errorCode: Int) -> Bool {
        return (errorCode == NSURLErrorTimedOut || errorCode == NSURLErrorCannotFindHost || errorCode == NSURLErrorCannotConnectToHost || errorCode == NSURLErrorNotConnectedToInternet || errorCode == NSURLErrorSecureConnectionFailed)
    }
    
    // Make sure to only ever call this from the main thread--the session token
    // lives in Kotlin Native code which only allows access from the thread on which
    // the object was originally created. ~emm 2021-09-17
    @discardableResult
    func retry(task: URLSessionDownloadTask) -> Bool {
        guard var request = task.originalRequest else {
            debugPrint("Unable to retry task, as originalRequest is nil:\n\(task)")
            return false
        }
        
        // Try, try again, until we run out of retries.
        var retry = Int(request.value(forHTTPHeaderField: retryCountHeader) ?? "") ?? 0
        guard retry < maxRetries else { return false }
        
        guard let sessionToken = appManager.authManager!.session()?.sessionToken else {
            debugPrint("Unable to retry task--not signed in (auth manager's UserSessionInfo is nil)")
            return false
        }

        retry += 1
        request.setValue("\(retry)", forHTTPHeaderField: retryCountHeader)
        request.setValue(sessionToken, forHTTPHeaderField: "Bridge-Session")

        let newTask = self.backgroundSession().downloadTask(with: request)
        newTask.taskDescription = task.taskDescription
        DispatchQueue.main.asyncAfter(deadline: DispatchTime.now() + pow(2.0, Double(retry))) {
            newTask.resume()
        }
        
        return true
    }
    
    func handleError(_ error: NSError, session: URLSession, task: URLSessionDownloadTask) -> Bool {
        if isTemporaryError(errorCode: error.code) {
            // Retry, and let the caller know we're retrying.
            return retry(task: task)
        }
        
        return false
    }
    
    func handleUnsupportedAppVersion() {
        DispatchQueue.main.async {
            self.appManager.authManager.notifyUIOfBridgeError(statusCode: Ktor_httpHttpStatusCode(value: 410, description: "Unsupported app version"))
        }
    }
    
    func handleServerPreconditionNotMet() {
        DispatchQueue.main.async {
            self.appManager.authManager.notifyUIOfBridgeError(statusCode: Ktor_httpHttpStatusCode(value: 412, description: "User not consented" ))
        }
    }
    
    func handleHTTPErrorResponse(_ response: HTTPURLResponse, session: URLSession, task: URLSessionDownloadTask) -> Bool {
        switch response.statusCode {
        case 401:
            DispatchQueue.main.async {
                self.appManager.authManager!.reauth { [self] error in
                    if let error = error {
                        // Assume BridgeClientKMM will have handled any 410 or 412 error appropriately.
                        debugPrint("Session token auto-refresh failed: \(String(describing: error))")
                        return
                    }
                    
                    debugPrint("Session token auto-refresh succeeded, retrying original request")
                    retry(task: task)
                }
            }
            return true
                
        case 410:
            handleUnsupportedAppVersion()
            
        case 412:
            handleServerPreconditionNotMet()
            
        default:
            // Let the backgroundTransferDelegate deal with it
            break
        }
        
        return false
    }
    
    // MARK: URLSessionDownloadDelegate
    func urlSession(_ session: URLSession, downloadTask: URLSessionDownloadTask, didFinishDownloadingTo location: URL) {
        self.backgroundTransferDelegate?.urlSession(session, downloadTask: downloadTask, didFinishDownloadingTo: location)
    }
    
    // MARK: URLSessionTaskDelegate
    fileprivate func retryFailedDownload(_ task: URLSessionDownloadTask, for session: URLSession, resumeData: Data) {
        let resumeTask = session.downloadTask(withResumeData: resumeData)
        resumeTask.taskDescription = task.taskDescription
        resumeTask.resume()
    }
    
    func urlSession(_ session: URLSession, task: URLSessionTask, didCompleteWithError error: Error?) {
        if let nsError = error as NSError?,
           let downloadTask = task as? URLSessionDownloadTask,
           let resumeData = nsError.userInfo[NSURLSessionDownloadTaskResumeData] as? Data {
            // if there's resume data from a download task, use it to retry
            self.retryFailedDownload(downloadTask, for: session, resumeData: resumeData)
            return
        }

        var retrying = false
        if let downloadTask = task as? URLSessionDownloadTask {
            let httpResponse = task.response as? HTTPURLResponse
            let httpError = (httpResponse?.statusCode ?? 0) >= 400
            if let nsError = error as NSError? {
                retrying = self.handleError(nsError, session: session, task: downloadTask)
            }
            else if httpError {
                retrying = self.handleHTTPErrorResponse(httpResponse!, session: session, task: downloadTask)
            }
        }
        
        if !retrying {
            self.backgroundTransferDelegate?.urlSession?(session, task: task, didCompleteWithError: error)
        }
    }
    
    // MARK: URLSessionDelegate
    func urlSessionDidFinishEvents(forBackgroundURLSession session: URLSession) {
        if let identifier = session.configuration.identifier,
            let completion = self.backgroundSessionCompletionHandlers[identifier] {
            OperationQueue.main.addOperation {
                completion()
            }
            self.backgroundSessionCompletionHandlers.removeValue(forKey: identifier)
        }
        self.backgroundTransferDelegate?.urlSessionDidFinishEvents?(forBackgroundURLSession: session)
    }
    
    func urlSession(_ session: URLSession, didBecomeInvalidWithError error: Error?) {
        if error != nil,
           let identifier = session.configuration.identifier {
            // if it became invalid unintentionally (i.e. due to an error), re-create the session:
            BackgroundNetworkManager.sessionDelegateQueue.addOperation {
                self.createBackgroundSession(with: identifier)
            }
        }
        self.backgroundTransferDelegate?.urlSession?(session, didBecomeInvalidWithError: error)
    }
}

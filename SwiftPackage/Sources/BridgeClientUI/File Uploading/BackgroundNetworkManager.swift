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

protocol URLSessionBackgroundDelegate: URLSessionDataDelegate, URLSessionDownloadDelegate {
}

class BridgeJsonParser {
    /// The .iso8601 date encoding/decoding strategy for JSONEncoder/Decoder uses ISO8601DateFormatter,
    /// which (a) is not a subclass of DateFormatter and (b) only supports the RFC 3339 profile, which does not include
    /// fractional seconds. Bridge always includes fractional seconds in dates.
    
    static let iso8601FormatterWithFractionalSeconds: DateFormatter = {
        let formatter = DateFormatter()
        formatter.calendar = Calendar(identifier: .iso8601)
        formatter.locale = Locale(identifier: "en_US_POSIX")
        formatter.dateFormat = "yyyy-MM-dd'T'HH:mm:ss.SSSXXXXX"
        return formatter
    } ()
    
    /// For encoding objects to be passed to Bridge.
    static let jsonEncoder: JSONEncoder = {
        let encoder = JSONEncoder()
        encoder.dateEncodingStrategy = .formatted(BridgeJsonParser.iso8601FormatterWithFractionalSeconds)
        return encoder
    }()
    
    /// For decoding objects received from Bridge.
    static let jsonDecoder: JSONDecoder = {
        let decoder = JSONDecoder()
        decoder.dateDecodingStrategy = .formatted(BridgeJsonParser.iso8601FormatterWithFractionalSeconds)
        return decoder
    }()
}

class BackgroundNetworkManager: NSObject, URLSessionBackgroundDelegate {

    /// A singleton instance of the manager.
    public static let shared = BackgroundNetworkManager()
    
    /// The identifier (base) for the background URLSession. App extensions will append a unique string to this to distinguish
    /// their background sessions.
    // TODO: Allow users of this singleton to specify their own individually unique identifiers.
    public static let backgroundSessionIdentifier = "org.sagebase.backgroundnetworkmanager.session"
    
    /// We use this custom HTTP request header as a hack to keep track of how many times we've retried a request.
    let retryCountHeader = "X-SageBridge-Retry"
    
    /// This sets the maximum number of times we will retry a request before giving up.
    let maxRetries = 5
    
    /// If set, this object's delegate methods will be called to present UI around critical errors (app update required, etc.).
    public var bridgeErrorUIDelegate: SBBBridgeErrorUIDelegate?
    
    /// If set, URLSession(Data/Download)Delegate method calls received by the BackgroundNetworkManager
    /// will be passed through to this object for further handling.
    // TODO: Allow multiple delegates, one for each unique background session identifier.
    public var backgroundTransferDelegate: URLSessionBackgroundDelegate?
    
    /// The queue used for calling background session delegate methods.
    ///  Also used for creating the singleton background session itself in a thread-safe way.
    ///  Created lazily.
    // TODO: When supporting multiple sessions (below), does it make sense to share one delegate queue among all of them?
    public static let sessionDelegateQueue: OperationQueue = {
        let delegateQueue = OperationQueue()
        delegateQueue.maxConcurrentOperationCount = 1
        return delegateQueue
    }()
            
    /// The singleton background URLSession.
    public static var _backgroundSession: URLSession? = nil
    
    /// A singleton map of pending background URLSession completion handlers that have been passed in from the app delegate and not yet called.
    public static var backgroundSessionCompletionHandlers = [String : () -> Void]()
    
    private static func isRunningInAppExtension() -> Bool {
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
    let jsonEncoder = BridgeJsonParser.jsonEncoder
    
    /// For decoding objects received from Bridge.
    let jsonDecoder = BridgeJsonParser.jsonDecoder
    
    /// Access (and if necessary, create) the singleton background URLSession used by the singleton BackgroundNetworkManager.
    /// Make sure it only gets created once, regardless of threading.
    // TODO: Support creating multiple sessions each with a unique identifer, creating each exactly once.
    func backgroundSession() -> URLSession {
        if BackgroundNetworkManager._backgroundSession == nil {
            // If it doesn't yet exist, queue up a block of code to create it.
            let createSessionOperation = BlockOperation {
                // Once it's our turn in the operation queue, check if someone else created it
                // in the meantime so we don't clobber it.
                guard BackgroundNetworkManager._backgroundSession == nil else { return }
                
                // OK, create it.
                var sessionIdentifier = BackgroundNetworkManager.backgroundSessionIdentifier
                if BackgroundNetworkManager.isRunningInAppExtension() {
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
        if let appGroupIdentifier = BridgeSDK.bridgeInfo.appGroupIdentifier, !appGroupIdentifier.isEmpty {
            config.sharedContainerIdentifier = appGroupIdentifier
        }
        
        BackgroundNetworkManager._backgroundSession = URLSession(configuration: config, delegate: self, delegateQueue: BackgroundNetworkManager.sessionDelegateQueue)
    }
    
    func bridgeBaseURL() -> URL {
        let domainPrefix = "webservices"
        let domainSuffixForEnv = [
            "",
            "-staging",
            "-develop",
            "-custom"
        ]
        
        let bridgeEnv = BridgeSDK.bridgeInfo.environment.rawValue
        guard bridgeEnv < domainSuffixForEnv.count else {
            fatalError("Environment property in BridgeInfo must be an integer in the range 0..\(domainSuffixForEnv.count).")
        }
        
        let bridgeHost = "\(domainPrefix)\(domainSuffixForEnv[bridgeEnv]).sagebridge.org"
        guard let baseUrl = URL(string: "https://\(bridgeHost)") else {
            fatalError("Unable to create URL object from string 'https://\(bridgeHost)'")
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
    
    func queryString(from parameters: Encodable?) -> String? {
        guard let paramDict = parameters as? [String : String] else { return nil }
        
        let allowedChars = CharacterSet.urlQueryAllowed
        var queryParams = Array<String>()
        for (param, value) in paramDict {
            // if either the param name or the value fail to encode to a url %-encoded string, skip this parameter
            var encodedValue: Data
            do {
                encodedValue = try jsonEncoder.encode(value)
            } catch let error {
                debugPrint("Error trying to jsonEncode value:\n\(value)\n\(error)")
                continue
            }
            guard let encodedValueString = String(data: encodedValue, encoding: .utf8)?.addingPercentEncoding(withAllowedCharacters: allowedChars) else { continue }
            guard let encodedParam = param.addingPercentEncoding(withAllowedCharacters: allowedChars) else { continue }
            
            queryParams.append("\(encodedParam)=\(encodedValueString)")
        }
        return queryParams.joined(separator: "&")
    }
    
    func addBasicHeaders(to request: inout URLRequest) {
        let bundle = Bundle.main
        let device = UIDevice.current
        let name = bundle.appName()
        let version = bundle.appVersion()
        let info = device.deviceInfo()
        
        let userAgentHeader = IOSBridgeConfig().userAgent
        request.setValue(userAgentHeader, forHTTPHeaderField: "User-Agent")
        
        let acceptLanguageHeader = Locale.preferredLanguages.joined(separator: ", ")
        request.setValue(acceptLanguageHeader, forHTTPHeaderField: "Accept-Language")
        
        request.setValue("no-cache", forHTTPHeaderField: "cache-control")
    }
    
    func request<T>(method: String, URLString: String, headers: [String : String]?, parameters: T?) -> URLRequest where T: Encodable {
        var URLString = URLString
        let isGet = (method.uppercased() == "GET")
        
        // for GET requests, the parameters go in the query part of the URL
        if isGet {
            if let queryString = queryString(from: parameters), !queryString.isEmpty {
                if URLString.contains("?") {
                    URLString.append("&\(queryString)")
                }
                else {
                    URLString.append("?\(queryString)")
                }
            }
        }
        
        var request = URLRequest(url: bridgeURL(for: URLString))
        request.httpMethod = method
        request.httpShouldHandleCookies = false
        addBasicHeaders(to: &request)
        
        if let headers = headers {
            for (header, value) in headers {
                request.addValue(value, forHTTPHeaderField: header)
            }
        }
        
        // for non-GET requests, the parameters (if any) go in the request body
        let contentTypeHeader = "Content-Type"
        if let parameters = parameters, !isGet {
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
        
        debugPrint("Prepared request--URL:\n\(String(describing: request.url?.absoluteString))\nHeaders:\n\(String(describing: request.allHTTPHeaderFields))\nBody:\n\(String(describing: String(data: request.httpBody ?? Data(), encoding: .utf8)))")
        
        return request
    }
    
    public func downloadFile<T>(from URLString: String, method: String, httpHeaders: [String : String]?, parameters: T?, taskDescription: String) -> URLSessionDownloadTask where T: Encodable {
        let request =  self.request(method: method, URLString: URLString, headers: httpHeaders, parameters: parameters)
        return self.downloadFile(urlRequest: request)
    }
    
    public func downloadFile(urlRequest: URLRequest) {
        let task = self.backgroundSession().downloadTask(with: request)
        task.taskDescription = taskDescription
        task.resume()
        return task
    }
    
    public func uploadFile(_ fileURL: URL, httpHeaders: [String : String]?, to urlString: String, taskDescription: String) -> URLSessionUploadTask? {
        guard let url = URL(string: urlString) else {
            debugPrint("Could not create URL from string '\(urlString)")
            return nil
        }
        var request = URLRequest(url: url)
        request.allHTTPHeaderFields = httpHeaders
        request.httpMethod = "PUT"
        let task = backgroundSession().uploadTask(with: request, fromFile: fileURL)
        task.taskDescription = taskDescription
        task.resume()
        return task
    }
    
    public func restore(backgroundSession: String, completionHandler: @escaping () -> Void) {
        if backgroundSession.starts(with: BackgroundNetworkManager.backgroundSessionIdentifier) {
            BackgroundNetworkManager.backgroundSessionCompletionHandlers[backgroundSession] = completionHandler
            BackgroundNetworkManager.sessionDelegateQueue.addOperation {
                // TODO: Update this when support is added for multiple named background sessions.
                if BackgroundNetworkManager._backgroundSession == nil {
                    self.createBackgroundSession(with: backgroundSession)
                }
            }
        }
    }
    
    // MARK: Helpers
    func isTemporaryError(errorCode: Int) -> Bool {
        return (errorCode == NSURLErrorTimedOut || errorCode == NSURLErrorCannotFindHost || errorCode == NSURLErrorCannotConnectToHost || errorCode == NSURLErrorNotConnectedToInternet || errorCode == NSURLErrorSecureConnectionFailed)
    }
    
    func retry(task: URLSessionTask) -> Bool {
        guard var request = task.originalRequest else {
            debugPrint("Unable to retry task, as originalRequest is nil:\n\(task)")
            return false
        }
        
        // Try, try again, until we run out of retries.
        var retry = Int(request.value(forHTTPHeaderField: retryCountHeader) ?? "") ?? 0
        guard retry < maxRetries else { return false }
        
        retry += 1
        request.setValue("\(retry)", forHTTPHeaderField: retryCountHeader)
        let newTask = self.backgroundSession().downloadTask(with: request)
        newTask.taskDescription = task.taskDescription
        DispatchQueue.main.asyncAfter(deadline: DispatchTime.now() + pow(2.0, Double(retry))) {
            newTask.resume()
        }
        
        return true
    }
    
    func handleError(_ error: NSError, session: URLSession, task: URLSessionTask) -> Bool {
        if isTemporaryError(errorCode: error.code) {
            // Retry, and let the caller know we're retrying.
            return retry(task: task)
        }
        
        return false
    }
    
    func handleUnsupportedAppVersion() {
        let bridgeNetworkManager = SBBComponentManager.component(SBBBridgeNetworkManager.self) as! SBBBridgeNetworkManager
        guard !bridgeNetworkManager.isUnsupportedAppVersion else { return }
        bridgeNetworkManager.isUnsupportedAppVersion = true
        if !(bridgeErrorUIDelegate?.handleUnsupportedAppVersionError?(NSError.sbbUnsupportedAppVersionError(), networkManager: bridgeNetworkManager) ?? false) {
            debugPrint("App Version Not Supported error not handled by error UI delegate")
        }
    }
    
    func handleServerPreconditionNotMet(task: URLSessionTask, response: HTTPURLResponse) {
        if !(bridgeErrorUIDelegate?.handleUserNotConsentedError?(NSError.generateSBBError(forStatusCode: 412), sessionInfo: response, networkManager: nil) ?? false) {
            debugPrint("User Not Consented error not handled by error UI delegate")
        }
    }
    
    func handleHTTPErrorResponse(_ response: HTTPURLResponse, session: URLSession, task: URLSessionTask) -> Bool {
        switch response.statusCode {
        case 401:
            let authMan = NativeAuthenticationManager()
            authMan.reauth { [self] error in
                if let nsError = error as NSError?,
                   nsError.code != SBBErrorCode.serverPreconditionNotMet.rawValue {
                    debugPrint("Session token auto-refresh failed: \(String(describing: error))")
                    if (nsError.code == SBBErrorCode.unsupportedAppVersion.rawValue) {
                        handleUnsupportedAppVersion()
                    }
                    return
                }
                
                debugPrint("Session token auto-refresh succeeded, retrying original request")
                task.originalRequest?.setValue(authMan.session().sessionToken, forHTTPHeaderField: "Bridge-Session")
                let _ = retry(task: task)
            }
            return true
            
        case 410:
            handleUnsupportedAppVersion()
            
        case 412:
            handleServerPreconditionNotMet(task: task, response: response)
            
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
        if let nsError = error as NSError? {
            // if there's resume data from a download task, use it to retry
            if let downloadTask = task as? URLSessionDownloadTask,
               let resumeData = nsError.userInfo[NSURLSessionDownloadTaskResumeData] as? Data {
                self.retryFailedDownload(downloadTask, for: session, resumeData: resumeData)
                return
            }
        }
        
        var retrying = false
        if task.isKind(of: URLSessionDownloadTask.self) {
            let httpResponse = task.response as? HTTPURLResponse
            let httpError = (httpResponse?.statusCode ?? 0) >= 400
            if let nsError = error as NSError? {
                retrying = self.handleError(nsError, session: session, task: task)
            }
            else if httpError {
                retrying = self.handleHTTPErrorResponse(httpResponse!, session: session, task: task)
            }
        }
        
        if !retrying {
            self.backgroundTransferDelegate?.urlSession?(session, task: task, didCompleteWithError: error)
        }
    }
    
    // MARK: URLSessionDelegate
    func urlSessionDidFinishEvents(forBackgroundURLSession session: URLSession) {
        if let identifier = session.configuration.identifier,
            let completion = BackgroundNetworkManager.backgroundSessionCompletionHandlers[identifier] {
            OperationQueue.main.addOperation {
                completion()
            }
            BackgroundNetworkManager.backgroundSessionCompletionHandlers.removeValue(forKey: identifier)
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

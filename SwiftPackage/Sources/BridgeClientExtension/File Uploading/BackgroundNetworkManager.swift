//
//  BackgroundNetworkManager.swift
//  BridgeFileUploads
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

class BackgroundNetworkManager: NSObject, URLSessionBackgroundDelegate, BridgeURLSessionBackgroundDelegate {

    /// The identifier (base) for the background URLSession. App extensions will append a unique string to this to distinguish
    /// their background sessions.
    let backgroundSessionIdentifier = "org.sagebase.backgroundnetworkmanager.session"
    
    /// The queue used for calling background session delegate methods.
    ///  Also used for creating the singleton background session itself in a thread-safe way.
    ///  Created lazily.
    let sessionDelegateQueue: OperationQueue = {
        let delegateQueue = OperationQueue()
        delegateQueue.maxConcurrentOperationCount = 1
        return delegateQueue
    }()
            
    /// The primary background URLSession.
    var primaryBackgroundSession: (any BridgeURLSession)? = nil
    
    /// A map of pending background URLSession completion handlers that have been passed in from the app delegate and not yet called.
    var backgroundSessionCompletionHandlers = [String : () -> Void]()
    
    /// A map of the restored background sessions.
    var restoredSessions = [String : any BridgeURLSession]()
    
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
    
    /// For encoding objects to be passed to Bridge.
    let jsonEncoder = SerializationFactory.defaultFactory.createJSONEncoder()
    
    /// For decoding objects received from Bridge.
    let jsonDecoder = SerializationFactory.defaultFactory.createJSONDecoder()
    
    /// Access (and if necessary, create) the singleton background URLSession used by the singleton BackgroundNetworkManager.
    /// Make sure it only gets created once, regardless of threading.
    func backgroundSession() -> any BridgeURLSession {
        if primaryBackgroundSession == nil {
            // If it doesn't yet exist, queue up a block of code to create it.
            let createSessionOperation = BlockOperation {
                // Once it's our turn in the operation queue, check if someone else created it
                // in the meantime so we don't clobber it.
                guard self.primaryBackgroundSession == nil else { return }
                
                // OK, create it.
                var sessionIdentifier = self.backgroundSessionIdentifier
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
                
                self.primaryBackgroundSession = self.createBackgroundSession(with: sessionIdentifier)
            }
            sessionDelegateQueue.addOperations([createSessionOperation], waitUntilFinished: true)
        }
        return primaryBackgroundSession!
    }
    
    // internal-use-only method, must always be called on the session delegate queue
    fileprivate func createBackgroundSession(with sessionIdentifier: String) -> any BridgeURLSession {
        let config = URLSessionConfiguration.background(withIdentifier: sessionIdentifier)
        if let appGroupIdentifier = IOSBridgeConfig().appGroupIdentifier, !appGroupIdentifier.isEmpty {
            config.sharedContainerIdentifier = appGroupIdentifier
        }
        return URLSession(configuration: config, delegate: self, delegateQueue: sessionDelegateQueue)
    }
    
    
    /// If set, URLSession(Data/Download)Delegate method calls received by the BackgroundNetworkManager
    /// will be passed through to this object for further handling.
    var backgroundTransferHandlers: [BridgeURLSessionHandler] = []
    
    func registerBackgroundTransferHandler(_ handler: BridgeURLSessionHandler) {
        backgroundTransferHandlers.append(handler)
    }
    
    func backgroundTransferHandler(for task: BridgeURLSessionTask) -> BridgeURLSessionHandler? {
        guard let handler = backgroundTransferHandlers.first(where: { $0.canHandle(task: task) })
        else {
            let error = BridgeUnexpectedNullError(category: .notFound, message: "Could not find a handler for URLSessionTask \(task.description).")
            Logger.log(tag: .upload, error: error)
            return nil
        }
        return handler
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
        
        Logger.log(severity: .debug, tag: .upload, message: "Prepared request--URL:\n\(String(describing: request.url?.absoluteString))\nHeaders:\n\(String(describing: request.allHTTPHeaderFields))")
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
                Logger.log(tag: .upload, error: error, message: "Error encoding parameters for \(method) request to URL \(URLString):\n\(parameters)")
            }
        }
        
        Logger.log(severity: .debug, tag: .upload, message: "Request body:\n\(String(describing: String(data: request.httpBody ?? Data(), encoding: .utf8)))")
        
        return request
    }
    
    @discardableResult
    func downloadFile(from URLString: String, method: HTTPMethod, httpHeaders: [String : String]?, taskDescription: String) -> BridgeURLSessionDownloadTask {
        let request = self.request(method: method, URLString: URLString, headers: httpHeaders)
        return self.downloadFile(with: request, taskDescription: taskDescription)
    }
    
    @discardableResult
    func downloadFile<T>(from URLString: String, method: HTTPMethod, httpHeaders: [String : String]?, parameters: T?, taskDescription: String) -> BridgeURLSessionDownloadTask where T: Encodable {
        let request =  self.request(method: method, URLString: URLString, headers: httpHeaders, parameters: parameters)
        return self.downloadFile(with: request, taskDescription: taskDescription)
    }
    
    private func downloadFile(with request: URLRequest, taskDescription: String) -> BridgeURLSessionDownloadTask {
        let task = self.backgroundSession().downloadTask(with: request)
        task.taskDescription = taskDescription
        task.resume()
        return task
    }
    
    @discardableResult
    func uploadFile(_ fileURL: URL, httpHeaders: [String : String]?, to urlString: String, taskDescription: String) -> BridgeURLSessionUploadTask? {
        guard let url = URL(string: urlString) else {
            let message = "Error: Could not create URL from string '\(urlString)"
            Logger.log(tag: .upload, error: BridgeUnexpectedNullError(category: .invalidURL, message: message))
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
        guard backgroundSession.starts(with: self.backgroundSessionIdentifier) else { return }
        self.backgroundSessionCompletionHandlers[backgroundSession] = completionHandler
        self.sessionDelegateQueue.addOperation {
            if self.restoredSessions[backgroundSession] == nil {
                let session = self.createBackgroundSession(with: backgroundSession)
                self.restoredSessions[backgroundSession] = session
                if backgroundSession == self.backgroundSessionIdentifier {
                    self.primaryBackgroundSession = session
                }
            }
        }
    }
    
    // MARK: URLSessionDownloadDelegate
    func urlSession(_ session: URLSession, downloadTask: URLSessionDownloadTask, didFinishDownloadingTo location: URL) {
        self.bridgeUrlSession(session, downloadTask: downloadTask, didFinishDownloadingTo: location)
    }
    func bridgeUrlSession(_ session: any BridgeURLSession, downloadTask: BridgeURLSessionDownloadTask, didFinishDownloadingTo location: URL) {
        (self.backgroundTransferHandler(for: downloadTask) as? BridgeURLSessionDownloadDelegate)?
            .bridgeUrlSession(session, downloadTask: downloadTask, didFinishDownloadingTo: location)
    }
    
    // MARK: URLSessionTaskDelegate

    func urlSession(_ session: URLSession, task: URLSessionTask, didCompleteWithError error: Error?) {
        self.bridgeUrlSession(session, task: task, didCompleteWithError: error)
    }
    func bridgeUrlSession(_ session: any BridgeURLSession, task: BridgeURLSessionTask, didCompleteWithError error: Error?) {
        self.backgroundTransferHandler(for: task)?.bridgeUrlSession(session, task: task, didCompleteWithError: error)
    }
    
    // MARK: URLSessionDelegate
    func urlSessionDidFinishEvents(forBackgroundURLSession session: URLSession) {
        self.bridgeUrlSessionDidFinishEvents(forBackgroundURLSession: session)
    }
    func bridgeUrlSessionDidFinishEvents(forBackgroundURLSession session: any BridgeURLSession) {
        guard let identifier = session.identifier else { return }
        if let completion = self.backgroundSessionCompletionHandlers[identifier] {
            OperationQueue.main.addOperation {
                completion()
            }
            self.backgroundSessionCompletionHandlers.removeValue(forKey: identifier)
        }
        self.sessionDelegateQueue.addOperation {
            // If this is not the primary url session then release it.
            if identifier != self.backgroundSessionIdentifier {
                self.restoredSessions[identifier] = nil
            }
        }
    }
    
    func urlSession(_ session: URLSession, didBecomeInvalidWithError error: Error?) {
        self.bridgeUrlSession(session, didBecomeInvalidWithError: error)
    }
    func bridgeUrlSession(_ session: any BridgeURLSession, didBecomeInvalidWithError error: Error?) {
        if error != nil,
           let identifier = session.identifier {
            // if it became invalid unintentionally (i.e. due to an error), re-create the session:
            self.sessionDelegateQueue.addOperation {
                let hasRestoredSession = self.restoredSessions[identifier] != nil
                let isPrimary = self.primaryBackgroundSession?.identifier == identifier
                if hasRestoredSession || isPrimary {
                    let session = self.createBackgroundSession(with: identifier)
                    if hasRestoredSession {
                        self.restoredSessions[identifier] = session
                    }
                    if isPrimary {
                        self.primaryBackgroundSession = session
                    }
                }
            }
        }
        self.backgroundTransferHandlers.forEach {
            $0.bridgeUrlSession(session, didBecomeInvalidWithError: error)
        }
    }
}

// MARK: URLSession Mocking

enum BridgeURLSessionTaskType : String {
    case upload, download, unknown
}

protocol BridgeURLSession : NSObjectProtocol {
    associatedtype UploadTask : BridgeURLSessionUploadTask
    associatedtype DownloadTask : BridgeURLSessionDownloadTask
    associatedtype SessionTask : BridgeURLSessionTask
    
    var identifier: String? { get }
    var bridgeDelegate: BridgeURLSessionBackgroundDelegate? { get }
    var delegateQueue: OperationQueue { get }
    
    func uploadTask(with request: URLRequest, fromFile fileURL: URL) -> UploadTask
    func downloadTask(with request: URLRequest) -> DownloadTask
    func downloadTask(withResumeData data: Data) -> DownloadTask
    func getAllTasks(completionHandler: @escaping @Sendable ([SessionTask]) -> Void)
}

protocol BridgeURLSessionTask : NSObjectProtocol {
    var taskDescription: String? { get set }
    var taskType: BridgeURLSessionTaskType { get }
    var originalRequest: URLRequest? { get }
    var response: URLResponse? { get }
    func resume()
    func cancel()
}

protocol BridgeURLSessionDownloadTask : BridgeURLSessionTask {
}

protocol BridgeURLSessionUploadTask : BridgeURLSessionTask {
}

protocol BridgeURLSessionHandler : BridgeURLSessionUploadDelegate {
    func canHandle(task: BridgeURLSessionTask) -> Bool
}

protocol BridgeURLSessionUploadDelegate : NSObjectProtocol {
    func bridgeUrlSession(_ session: any BridgeURLSession, task: BridgeURLSessionTask, didCompleteWithError error: Error?)
    func bridgeUrlSession(_ session: any BridgeURLSession, didBecomeInvalidWithError error: Error?)
}

protocol BridgeURLSessionDownloadDelegate : BridgeURLSessionUploadDelegate {
    func bridgeUrlSession(_ session: any BridgeURLSession, downloadTask: BridgeURLSessionDownloadTask, didFinishDownloadingTo location: URL)
}

protocol BridgeURLSessionBackgroundDelegate : BridgeURLSessionDownloadDelegate {
    func bridgeUrlSessionDidFinishEvents(forBackgroundURLSession session: any BridgeURLSession)
}

extension URLSession : BridgeURLSession {
    typealias UploadTask = URLSessionUploadTask
    typealias DownloadTask = URLSessionDownloadTask
    typealias SessionTask = URLSessionTask

    var identifier: String? {
        configuration.identifier
    }
    
    var bridgeDelegate: BridgeURLSessionBackgroundDelegate? {
        delegate as? BridgeURLSessionBackgroundDelegate
    }
}

extension URLSessionTask : BridgeURLSessionTask {
    var taskType: BridgeURLSessionTaskType {
        switch (self) {
        case is URLSessionDownloadTask:
            return .download
        case is URLSessionUploadTask:
            return .upload
        default:
            return .unknown
        }
    }
}

extension URLSessionDownloadTask : BridgeURLSessionDownloadTask {
}

extension URLSessionUploadTask : BridgeURLSessionUploadTask {
}

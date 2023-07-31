//
//  BridgeFileUploadManager.swift
//  BridgeFileUploads
//

import Foundation
import UniformTypeIdentifiers
import CoreServices
import BridgeClient
import JsonModel

#if canImport(UIKit)
import UIKit
#endif

protocol BridgeFileUploadMetadataBlob {
    var userInfo: [String : Any]? { get }
}
protocol BridgeUploadTrackingData : Codable {
    var userInfo: [String : Any]? { get }
}
struct BridgeFileUploadMetadata<T>: Codable, BridgeFileUploadMetadataBlob where T: BridgeUploadTrackingData {
    var bridgeUploadTrackingObject: T
    var s3Headers: [String : String]
    var userInfo: [String : Any]? {
        bridgeUploadTrackingObject.userInfo
    }
}

protocol BridgeFileRetryInfoBlob {}
struct BridgeFileRetryInfo<T>: Codable, BridgeFileRetryInfoBlob where T: BridgeUploadTrackingData {
    var apiString: String
    var originalFilePath: String
    var uploadMetadata: BridgeFileUploadMetadata<T>
    var whenToRetry: Date
}

/// Dictionary encoder/decoder adapted from https://stackoverflow.com/a/52182418
class DictionaryEncoder {
    private let jsonEncoder = SerializationFactory.defaultFactory.createJSONEncoder()

    /// Encodes given Encodable value into an array or dictionary
    func encode<T>(_ value: T) throws -> Any where T: Encodable {
        // if it's already a simple plist type, don't bother encoding/deserializing it
        if value is NSData || value is NSString || value is NSDate || value is NSNumber {
            return value
        }
        let jsonData = try jsonEncoder.encode(value)
        return try JSONSerialization.jsonObject(with: jsonData, options: .allowFragments)
    }
}

class DictionaryDecoder {
    private let jsonDecoder = SerializationFactory.defaultFactory.createJSONDecoder()

    /// Decodes given Decodable type from given array or dictionary
    func decode<T>(_ type: T.Type, from json: Any) throws -> T where T: Decodable {
        // if it's already the requested, simple plist type, don't bother serializing/decoding it
        if json is T && (json is NSData || json is NSString || json is NSDate || json is NSNumber) {
            return json as! T
        }
        let jsonData = try JSONSerialization.data(withJSONObject: json, options: [])
        return try jsonDecoder.decode(type, from: jsonData)
    }
}

/// Support for extended file system attributes from
/// https://stackoverflow.com/questions/38343186/write-extend-file-attributes-swift-example
extension URL {

    /// Get extended attribute.
    func extendedAttribute(forName name: String) throws -> Data  {

        try self.withUnsafeFileSystemRepresentation { fileSystemPath -> Data in

            // Determine attribute size:
            let length = getxattr(fileSystemPath, name, nil, 0, 0, 0)
            guard length >= 0 else { throw URL.posixError(errno) }

            // Create buffer with required size:
            var data = Data(count: length)

            // Retrieve attribute:
            let result =  data.withUnsafeMutableBytes { [count = data.count] in
                getxattr(fileSystemPath, name, $0.baseAddress, count, 0, 0)
            }
            guard result >= 0 else { throw URL.posixError(errno) }
            return data
        }
    }

    /// Set extended attribute.
    func setExtendedAttribute(data: Data, forName name: String) throws {

        try self.withUnsafeFileSystemRepresentation { fileSystemPath in
            let result = data.withUnsafeBytes {
                setxattr(fileSystemPath, name, $0.baseAddress, data.count, 0, 0)
            }
            guard result >= 0 else { throw URL.posixError(errno) }
        }
    }

    /// Remove extended attribute.
    func removeExtendedAttribute(forName name: String) throws {

        try self.withUnsafeFileSystemRepresentation { fileSystemPath in
            let result = removexattr(fileSystemPath, name, 0)
            guard result >= 0 else { throw URL.posixError(errno) }
        }
    }

    /// Get list of all extended attributes.
    func listExtendedAttributes() throws -> [String] {

        try self.withUnsafeFileSystemRepresentation { fileSystemPath -> [String] in
            let length = listxattr(fileSystemPath, nil, 0, 0)
            guard length >= 0 else { throw URL.posixError(errno) }

            // Create buffer with required size:
            var namebuf = Array<CChar>(repeating: 0, count: length)

            // Retrieve attribute list:
            let result = listxattr(fileSystemPath, &namebuf, namebuf.count, 0)
            guard result >= 0 else { throw URL.posixError(errno) }

            // Extract attribute names:
            let list = namebuf.split(separator: 0).compactMap {
                $0.withUnsafeBufferPointer {
                    $0.withMemoryRebound(to: UInt8.self) {
                        String(bytes: $0, encoding: .utf8)
                    }
                }
            }
            return list
        }
    }

    /// Helper function to create an NSError from a Unix errno.
    private static func posixError(_ err: Int32) -> NSError {
        return NSError(domain: NSPOSIXErrorDomain, code: Int(err),
                       userInfo: [NSLocalizedDescriptionKey: String(cString: strerror(err))])
    }
}

/// BridgeFileUploadAPI is a protocol for BridgeFileUploadManager to call for a given Bridge API as it
/// progresses through the upload dance.
protocol BridgeFileUploadAPI {
    /// A partial URL path that uniquely and completely identifies the particular Bridge upload API.
    var apiString: String { get }
    
    /// The Notification.userInfo key for a failed upload/download HTTP status.
    var httpStatusKey: String { get }
    
    /// The Notification.userInfo key for a failed download HTTPResponse body.
    var responseBodyKey: String { get }

    /// Where to keep temporary copies of files being uploaded via this upload API.
    /// Typically this would be a subdirectory of the Application Support Directory.
    var tempUploadDirURL: URL { get }
    
    /// A flag indicating whether or not this particular upload API expects to be notified once
    /// the file has been successfully uploaded to S3.
    var notifiesBridgeWhenUploaded: Bool { get }
    
    /// The BridgeFileUploadManager this API implementation should use.
    var uploadManager: BridgeFileUploadManager { get }
    
    /// Create an instance of BridgeFileUploadMetadata for a file upload.
    func uploadMetadata(for fileId: String, fileUrl: URL, mimeType: String, extras: Codable?) -> BridgeFileUploadMetadataBlob?
    
    /// Return the fileId for the given uploadMetadata.
    func fileId(for uploadMetadata: BridgeFileUploadMetadataBlob) -> String
    
    /// Return the MIME type for the given uploadMetadata.
    func mimeType(for uploadMetadata: BridgeFileUploadMetadataBlob) -> String
    
    /// Return the upload request extras (if any) for the given uploadMetadata.
    func extras(for uploadMetadata: BridgeFileUploadMetadataBlob) -> Codable?
    
    /// Return the S3 pre-signed URL string to which BridgeFileUploadManager should PUT the file.
    func s3UploadUrlString(for uploadMetadata: BridgeFileUploadMetadataBlob) -> String?
    
    /// Return the HTTP headers which BridgeFileUploadManager should set when uploading
    /// the file to S3.
    func s3UploadHeaders(for uploadMetadata: BridgeFileUploadMetadataBlob) -> [String : String]
    
    /// Return the URL string at which to notify Bridge that the upload succeeded.
    /// For implementations where notifiesBridgeWhenUploaded is false, this should return nil.
    func notifyBridgeUrlString(for uploadMetadata: BridgeFileUploadMetadataBlob) -> String?
    
    /// Return a Notification object to be posted to the default NotificationCenter upon
    /// successful completion of the file upload process.
    func fileUploadedNotification(for uploadMetadata: BridgeFileUploadMetadataBlob) -> Notification
    
    /// Return a Notification object to be posted to the default NotificationCenter upon
    /// unrecoverable failure to notify Bridge that the file was successfully uploaded to S3.
    /// Default implementation returns nil. Upload APIs where notifiesBridgeWhenUploaded is true
    /// can override this method to return an appropriate notification if the API cares.
    func reportingUploadToBridgeFailedNotification(for uploadMetadata: BridgeFileUploadMetadataBlob, statusCode: Int, responseBody: String?) -> Notification?
    
    /// Return a Notification object to be posted to the default NotificationCenter upon
    /// unrecoverable failure to upload the file to S3.
    func uploadToS3FailedNotification(for uploadMetadata: BridgeFileUploadMetadataBlob) -> Notification
    
    /// Return a Notification object to be posted to the default NotificationCenter upon
    /// unrecoverable failure to request an upload URL from Bridge.
    func uploadRequestFailedNotification(for uploadMetadata: BridgeFileUploadMetadataBlob, statusCode: Int, responseBody: String?) -> Notification
    
    /// Return true if the upload session in the given metadata is expired.
    func isUploadSessionExpired(for uploadMetadata: BridgeFileUploadMetadataBlob) -> Bool
    
    /// Mark a temp file as having requested upload with the given metadata.
    func markUploadRequested(for relativePath: String, uploadMetadata: BridgeFileUploadMetadataBlob)
    
    /// Retrieve and un-map the temp file upload request's metadata.
    func fetchUploadRequested(for relativePath: String) -> BridgeFileUploadMetadataBlob?
    
    /// Update the upload metadata with the upload object data from Bridge and return the new metadata.
    func update(metadata: BridgeFileUploadMetadataBlob, with jsonData: Data) -> BridgeFileUploadMetadataBlob?
    
    /// Mark a temp file as uploading to S3 with the given metadata.
    func markUploadingToS3(for relativePath: String, uploadMetadata: BridgeFileUploadMetadataBlob)
    
    /// Retrieve and un-map the temp file upload upload-to-S3's metadata.
    @discardableResult
    func fetchUploadingToS3(for relativePath: String) -> BridgeFileUploadMetadataBlob?
    
    /// Retrieve the metadata for a temp file from a given mapping without removing it. Meant for internal use only.
    func retrieveMetadata(from key: String, mappings: [String : Any]?) -> BridgeFileUploadMetadataBlob?
        
    /// Mark a temp file as notifying Bridge of upload success with the given metadata.
    func markNotifyingBridge(for relativePath: String, uploadMetadata: BridgeFileUploadMetadataBlob)
    
    /// Retrieve and un-map the temp file upload notifying-Bridge's metadata.
    func fetchNotifyingBridge(for relativePath: String) -> BridgeFileUploadMetadataBlob?
    
    /// Queue up a request for later retry.
    func enqueueForRetry(delay: TimeInterval, relativePath: String, originalFilePath: String, uploadMetadata: BridgeFileUploadMetadataBlob)
    
    /// If a given file's retry is ready to go, retry the upload and remove it from the given mapping. Return true if the mapping was updated.
    /// Meant for internal use only.
    func retryIfReady(relativePath: String, mappings: inout [String : Any]) -> Bool
    
    /// Remove a file from the retry queue.
    @discardableResult
    func dequeueForRetry(relativePath: String) -> BridgeFileRetryInfoBlob?
    
    /// This method is the face of the Bridge upload APIs.
    func upload(fileId: String, fileUrl: URL, contentType: String?, extras: Codable?)
    
    /// Behaves identically to `upload(fileId:fileUrl:contentType:extras:)` but
    /// returns the temp file copy. For internal use in unit testing only.
    func uploadInternal(fileId: String, fileUrl: URL, contentType: String?, extras: Codable?) -> URL?
    
    /// Send the actual upload request to Bridge.
    /// Meant for internal use only.
    func sendUploadRequest(for relativePath: String, uploadMetadata: BridgeFileUploadMetadataBlob)
    
    /// Let Bridge know the upload succeeded.
    /// Meant for internal use only.
    func notifyBridgeUploadSucceeded(relativePath: String, uploadMetadata: BridgeFileUploadMetadataBlob)
    
    /// Decode the upload request extras object (if any) from data retrieved from the Xattrs of a file
    /// whose upload was requested via this API.
    /// Meant for internal use only.
    func uploadRequestExtras(from data: Data?) -> Codable?
}

/// BridgeFileUploadAPITyped extends BridgeFileUploadAPI with an associated type, which is
/// the Swift (Codable) type of the object the particular API uses to pass parameters back and forth.
/// To support a new Bridge file upload API, create a class that implements this protocol to handle the peculiarities
/// of that particular API, and register an instance of it with the singleton BridgeFileUploadManager for that API.
protocol BridgeFileUploadAPITyped : BridgeFileUploadAPI {
    associatedtype TrackingType where TrackingType: BridgeUploadTrackingData
    associatedtype UploadRequestType where UploadRequestType: Codable
    associatedtype UploadRequestResponseType where UploadRequestResponseType: Codable

    /// Return the upload request object for the given uploadMetadata.
    func uploadRequestObject(for uploadMetadata: BridgeFileUploadMetadataBlob) -> Codable
    
    /// Return the URL string at which BridgeFileUploadManager should request an upload.
    func uploadRequestUrlString(for uploadMetadata: BridgeFileUploadMetadataBlob) -> String
}
    
/// Implementations of functions that require compile-time knowledge of the associated type, but are
/// otherwise the same for all upload APIs.
extension BridgeFileUploadAPITyped {
    
    /// The Notification.userInfo key for a failed upload/download HTTP status.
    var httpStatusKey: String {
        "HttpStatus"
    }
    
    /// The Notification.userInfo key for a failed download HTTPResponse body.
    var responseBodyKey: String {
        "ResponseBody"
    }

    func markUploadRequested(for relativePath: String, uploadMetadata: BridgeFileUploadMetadataBlob) {
        self.uploadManager.persistMapping(from: relativePath, to: uploadMetadata as! BridgeFileUploadMetadata<TrackingType>, defaultsKey: self.uploadManager.uploadURLsRequestedKey)
    }
    
    func fetchUploadRequested(for relativePath: String) -> BridgeFileUploadMetadataBlob? {
        return self.uploadManager.removeMapping(BridgeFileUploadMetadata<TrackingType>.self, from: relativePath, defaultsKey: self.uploadManager.uploadURLsRequestedKey)
    }
    
    func markUploadingToS3(for relativePath: String, uploadMetadata: BridgeFileUploadMetadataBlob) {
        self.uploadManager.persistMapping(from: relativePath, to: uploadMetadata as! BridgeFileUploadMetadata<TrackingType>, defaultsKey: self.uploadManager.uploadingToS3Key)
    }
    
    @discardableResult
    func fetchUploadingToS3(for relativePath: String) -> BridgeFileUploadMetadataBlob? {
        return self.uploadManager.removeMapping(BridgeFileUploadMetadata<TrackingType>.self, from: relativePath, defaultsKey: self.uploadManager.uploadingToS3Key)
    }
    
    // Not exposed in API; cast uploadApi to BridgeFileUploadAPITyped to use this function.
    func retrieveMetadata(from key: String, mappings: [String : Any]?) -> BridgeFileUploadMetadataBlob? {
        return self.uploadManager.retrieveMapping(BridgeFileUploadMetadata<TrackingType>.self, from: key, mappings: mappings)
    }
    
    func markNotifyingBridge(for relativePath: String, uploadMetadata: BridgeFileUploadMetadataBlob) {
        self.uploadManager.persistMapping(from: relativePath, to: uploadMetadata as! BridgeFileUploadMetadata<TrackingType>, defaultsKey: self.uploadManager.notifyingBridgeUploadSucceededKey)
    }
    
    func fetchNotifyingBridge(for relativePath: String) -> BridgeFileUploadMetadataBlob? {
        return self.uploadManager.removeMapping(BridgeFileUploadMetadata<TrackingType>.self, from: relativePath, defaultsKey: self.uploadManager.notifyingBridgeUploadSucceededKey)
    }
    
    func enqueueForRetry(delay: TimeInterval, relativePath: String, originalFilePath: String, uploadMetadata: BridgeFileUploadMetadataBlob) {
        let whenToRetry = Date(timeIntervalSinceNow: delay)
        let retryInfo = BridgeFileRetryInfo<TrackingType>(apiString: self.apiString, originalFilePath: originalFilePath, uploadMetadata: uploadMetadata as! BridgeFileUploadMetadata<TrackingType>, whenToRetry: whenToRetry)
        self.uploadManager.enqueueForRetry(retryInfo: retryInfo, invariantFilePath: relativePath, originalFilePath: originalFilePath, uploadMetadata: uploadMetadata as! BridgeFileUploadMetadata<TrackingType>)
    }
    
    func retryIfReady(relativePath: String, mappings: inout [String : Any]) -> Bool {
        guard let retryInfoPlist = mappings[relativePath] as? [String : Any] else {
            // since it's broken, remove it
            mappings.removeValue(forKey: relativePath)
            return true
        }
        var retryInfo: BridgeFileRetryInfo<TrackingType>
        do {
            retryInfo = try DictionaryDecoder().decode(BridgeFileRetryInfo<TrackingType>.self, from: retryInfoPlist)
        } catch let error {
            Logger.log(tag: .upload, error: error,
                       message: "Error attempting to decode plist object to BridgeFileRetryInfo<\(TrackingType.self)>:\n\(retryInfoPlist)")
            // since it's broken, remove it
            mappings.removeValue(forKey: relativePath)
            return true
        }

        if retryInfo.whenToRetry.timeIntervalSinceNow <= 0.0 {
            // get the fileURL from the original file path
            let fileUrl = URL(fileURLWithPath: retryInfo.originalFilePath)
            
            let uploadMetadata = retryInfo.uploadMetadata
            if !self.isUploadSessionExpired(for: uploadMetadata) {
                Logger.log(severity: .info, message: "Retrying file upload - not expired", metadata: uploadMetadata.userInfo)
                // if we have an upload URL and it's not expired, just retry upload to S3
                // -- restore tracking of what file it's a copy of
                self.uploadManager.persistMapping(from: relativePath, to: fileUrl.path, defaultsKey: self.uploadManager.bridgeFileUploadsKey)
                // -- retry upload to S3
                self.uploadManager.uploadToS3(uploadApi: self, bridgeUploadMetadata: uploadMetadata, invariantFilePath: relativePath)
            }
            else {
                Logger.log(severity: .info, message: "Retrying file upload - session expired - requesting upload URL", metadata: uploadMetadata.userInfo)
                // request a fresh upload URL from Bridge
                self.uploadManager.requestUploadURL(uploadApi: self, invariantFilePath: relativePath, fileUrl: fileUrl, uploadMetadata: uploadMetadata)
            }
            
            // remove it from the list of things needing to be retried
            mappings.removeValue(forKey: relativePath)
            return true
        }
        
        return false
    }
    
    func dequeueForRetry(relativePath: String) -> BridgeFileRetryInfoBlob? {
        return self.uploadManager.dequeueForRetry(TrackingType.self, relativePath: relativePath)
    }

    func upload(fileId: String, fileUrl: URL, contentType: String? = nil, extras: Codable? = nil) {
        self.uploadManager.upload(TrackingType.self, uploadApi: self, fileId: fileId, fileUrl: fileUrl, contentType: contentType, extras: extras)
    }

    func uploadInternal(fileId: String, fileUrl: URL, contentType: String? = nil, extras: Codable? = nil) -> URL? {
        return self.uploadManager.uploadInternal(TrackingType.self, uploadApi: self, fileId: fileId, fileUrl: fileUrl, contentType: contentType, extras: extras)
    }
    
    func sendUploadRequest(for relativePath: String, uploadMetadata: BridgeFileUploadMetadataBlob) {
        // Get the bridge upload object
        guard let bridgeUploadObject = self.uploadRequestObject(for: uploadMetadata) as? UploadRequestType else {
            Logger.log(tag: .upload, error: BridgeUnexpectedNullError(category: .wrongType, message: "Unable to get upload request object (type \(UploadRequestType.self)) from uploadMetadata: \(uploadMetadata)"))
            return
        }

        // Request an uploadUrl for the bridge upload object
        let requestString = self.uploadRequestUrlString(for: uploadMetadata)

        // throw this over to the main queue so we can access Kotlin stuff
        OperationQueue.main.addOperation {
            guard let sessionToken = uploadManager.appManager.sessionToken else {
                Logger.log(tag: .upload, error: BridgeAuthError(), metadata: uploadMetadata.userInfo)
                return
            }
            
            // Set its state as uploadRequested
            uploadManager.persistMapping(from: relativePath, to: uploadMetadata as! BridgeFileUploadMetadata<TrackingType>, defaultsKey: uploadManager.uploadURLsRequestedKey)

            let headers = [
                "Bridge-Session" : sessionToken
            ]

            uploadManager.netManager.downloadFile(from: requestString, method: .POST, httpHeaders: headers, parameters: bridgeUploadObject, taskDescription: relativePath)
        }
    }
    
    func notifyBridgeUploadSucceeded(relativePath: String, uploadMetadata: BridgeFileUploadMetadataBlob) {
        guard let notifyUrl = self.notifyBridgeUrlString(for: uploadMetadata) else {
            // Do not log any error. Logging is handled by the method called if it is an error. - syoung 02/13/2022
            return
        }
        
        // throw this over to the main queue so we can access Kotlin stuff
        OperationQueue.main.addOperation {
            guard let sessionToken = uploadManager.appManager.sessionToken else {
                Logger.log(severity: .warn, tag: .upload, message: "Unable to notify Bridge of upload success--not logged in to an account.")
                return
            }
            
            // Set its state as notifyingBridge
            uploadManager.persistMapping(from: relativePath, to: uploadMetadata as! BridgeFileUploadMetadata<TrackingType>, defaultsKey: uploadManager.notifyingBridgeUploadSucceededKey)

            let headers = [
                "Bridge-Session" : sessionToken
            ]

            uploadManager.netManager.downloadFile(from: notifyUrl, method: .POST, httpHeaders: headers, taskDescription: relativePath)
        }
    }
}

/// The BridgeFileUploadManager handles uploading files to Bridge using an iOS URLSession
/// background session. This allows iOS to deal with any connectivity issues and lets the upload proceed
/// even when the app is suspended.
class BridgeFileUploadManager: SandboxFileManager, BridgeURLSessionDelegate {
    /// A singleton instance of the manager.
    static let shared = BridgeFileUploadManager()
    
    /// The extended file attribute for which API is to be used to upload the file.
    let uploadApiAttributeName = "org.sagebionetworks.bridge.uploadApi"
    
    /// The extended file attribute for the fileId to which this file is being uploaded.
    let fileIdAttributeName = "org.sagebionetworks.bridge.fileId"
    
    /// The extended file attribute for the content (MIME) type of the file being uploaded.
    let contentTypeAttributeName = "org.sagebionetworks.bridge.contentType"
    
    /// The extended file attribute for the upload request extras of the file being uploaded.
    let uploadExtrasAttributeName = "org.sagebionetworks.bridge.uploadExtras"
    
    /// The key under which we store the mappings of temp file -> original file.
    let bridgeFileUploadsKey = "bridgeFileUploadsKey"
    
    /// The key under which we store temp files in the "requested upload URL" state.
    /// This key refers to a mapping of temp file -> BridgeFileUploadMetadata with the participantFile field
    /// containing what was originally passed to Bridge when requesting the upload URL.
    let uploadURLsRequestedKey = "UploadURLsRequestedKey"
    
    /// The key under which we store temp files in the "attempting to upload to S3" state.
    /// This key refers to a mapping of temp file -> BridgeFileUploadMetadata with the participantFile field
    /// containing what was returned from Bridge when we requested the upload URL.
    let uploadingToS3Key = "UploadingToS3Key"
    
    /// The key under which we keep track of uploads in the "notifying Bridge we succeeded" state.
    /// This key refers to a mapping of temp file -> BridgeFileUploadMetadata in its final state.
    let notifyingBridgeUploadSucceededKey = "NotifyingBridgeUploadSucceededKey"
    
    /// The key under which we save download HTTP error response bodies in case we need to
    /// later report them as unrecoverable.
    /// This key refers to a mapping of temp file -> HTTP response body (as a String).
    let downloadErrorResponseBodyKey = "DownloadErrorResponseBodyKey"
    
    /// The key under which we store retryInfo for retrying failed file uploads.
    /// The key refers to a mapping of temp file -> BridgeFileRetryInfo.
    let retryUploadsKey = "RetryUploadsKey"
    
    /// A mapping for implementation-specific details for each registered Bridge upload API.
    var bridgeFileUploadApis = [String : BridgeFileUploadAPI]()
    
    /// The minimum delay before retrying a failed upload (in seconds).
    var delayForRetry: TimeInterval = 5 * 60
    
    /// BridgeFileUploadManager uses the BackgroundNetworkManager singleton to manage its background URLSession tasks.
    let netManager: BackgroundNetworkManager
    
    /// BridgeFileUploadManager needs access to app configuration and user session info.
    var appManager: UploadAppManager! {
        BackgroundNetworkManager.shared.appManager
    }
    
    /// Serial queue for updates to temp file -> original file mappings and upload process state.
    let uploadQueue: OperationQueue
    
    /// User defaults to use for tracking uploads.
    lazy var userDefaults: UserDefaults = {
        // If there's an appGroupIdentifier, use that as the suite name.
        if let suiteName = IOSBridgeConfig().appGroupIdentifier, suiteName.count > 0 {
            return UserDefaults(suiteName: suiteName)!
        }
        return UserDefaults.standard
    }()

    /// Private initializer so only the singleton can ever get created.
    private override init() {
        netManager = BackgroundNetworkManager.shared
        
        self.uploadQueue = self.netManager.backgroundSession().delegateQueue
        
        super.init()
        
        self.netManager.backgroundTransferDelegate = self
    }
    
    internal var appDidBecomeActiveObserver: Any?
    
    internal func onSessionTokenChanged() {
        
        #if canImport(UIKit)
        if appDidBecomeActiveObserver == nil {
            // Set up a listener to retry temporarily-failed uploads whenever the app becomes active
            self.appDidBecomeActiveObserver = NotificationCenter.default.addObserver(forName: UIApplication.didBecomeActiveNotification, object: nil, queue: nil) { notification in
                Logger.log(severity: .info, message: "App became active. Calling checkAndRetryOrphanedUploads()")
                self.checkAndRetryOrphanedUploads()
            }
        }
        #endif
        
        // Also do it right away
        self.checkAndRetryOrphanedUploads()
    }
    
    fileprivate func tempFileFor(inFileURL: URL, uploadApi: BridgeFileUploadAPI) -> URL? {
        guard let (fileURL, tempFileURL) = tempFileFor(inFileURL: inFileURL, uploadDirURL: uploadApi.tempUploadDirURL)
        else {
            return nil
        }

        // ...and get its sandbox-relative part since there are circumstances under
        // which the full path might change (e.g. app update, or during debugging--
        // sim vs device, subsequent run of the same app after a new build)
        let invariantTempFilePath = self.sandboxRelativePath(of: tempFileURL)
        
        // Keep track of what file it's a copy of.
        self.persistMapping(from: invariantTempFilePath, to: fileURL.path, defaultsKey: self.bridgeFileUploadsKey)
        
        return tempFileURL
    }
    
    fileprivate func runOnQueue(_ queue: OperationQueue, sync: Bool, block: @escaping ()->Void) {
        if OperationQueue.current == queue {
            block()
        } else {
            queue.addOperations([BlockOperation(block: block)], waitUntilFinished: sync)
        }
    }
    
    
    fileprivate func persistMapping<T>(from key: String, to value: T, defaultsKey: String) where T: Encodable {
        self.runOnQueue(self.uploadQueue, sync: false) {
            var mappings = self.userDefaults.dictionary(forKey: defaultsKey) ?? [String : Any]()
            var plistValue: Any
            do {
                plistValue = try DictionaryEncoder().encode(value)
            } catch let error {
                Logger.log(tag: .upload, error: error, message: "Error attempting to encode \(T.self) to plist object.")
                return
            }
            mappings[key] = plistValue
            self.userDefaults.setValue(mappings, forKey: defaultsKey)
        }
    }
    
    @discardableResult
    func removeMapping<T>(_ type: T.Type, from key: String, defaultsKey: String) -> T? where T: Decodable {
        var mapping: T?
        self.runOnQueue(self.uploadQueue, sync: true) {
            var mappings = self.userDefaults.dictionary(forKey: defaultsKey)
            if let mappingPlist = mappings?.removeValue(forKey: key) {
                do {
                    mapping = try DictionaryDecoder().decode(type, from: mappingPlist)
                } catch let error {
                    Logger.log(severity: .error, tag: .upload, message: "Error attempting to decode plist object to \(T.self):\n\(mappingPlist)\n\(error)")
                }
            }
            if mappings != nil {
                self.userDefaults.setValue(mappings, forKey: defaultsKey)
            }
        }
        
        return mapping
    }
    
    fileprivate func retrieveMapping<T>(_ type: T.Type, from key: String, mappings: [String : Any]?) -> T? where T: Decodable {
        var mapping: T?
        self.runOnQueue(self.uploadQueue, sync: true) {
            if let mappingPlist = mappings?[key] {
                do {
                    mapping = try DictionaryDecoder().decode(type, from: mappingPlist)
                } catch let error {
                    Logger.log(tag: .upload, error: error, message: "Error attempting to decode plist object to \(T.self):\n\(mappingPlist)")
                }
            }
            else {
                Logger.log(tag: .upload, error: BridgeUnexpectedNullError(category: .missingMapping, message: "in retrieveMapping: Missing mapping for \(key)"))
            }
        }
        return mapping
    }

    
    func resetMappings(for defaultsKey: String) {
        self.runOnQueue(self.uploadQueue, sync: false) {
            self.userDefaults.removeObject(forKey: defaultsKey)
        }
    }
    
    // This func resets the state of the BridgeFileUploadManager, including clearing out all mappings
    // and deleting all temp files.
    // You shouldn't call this directly except in test cases; if you want to put the brakes on all pending
    // uploads, you should invalidate the URLSession associated with this manager, which will cause this
    // to get called.
    func reset() {
        self.runOnQueue(self.uploadQueue, sync: false) {
            // Go through and reset all the mappings, gathering up the temp files that are used as keys
            // so we can delete them afterward.
            var invariantFilePaths = Set<String>()
            for defaultsKey in [
                self.bridgeFileUploadsKey,
                self.uploadURLsRequestedKey,
                self.uploadingToS3Key,
                self.notifyingBridgeUploadSucceededKey,
                self.downloadErrorResponseBodyKey,
                self.retryUploadsKey
            ] {
                // add the temp files used as keys in this mapping
                if let filePaths = self.userDefaults.dictionary(forKey: defaultsKey)?.keys {
                    invariantFilePaths.formUnion(filePaths)
                }
                
                // reset the mapping
                self.resetMappings(for: defaultsKey)
            }
            
            for invariantFilePath in invariantFilePaths {
                self.cleanUpTempFile(filePath: invariantFilePath)
            }
        }
    }
    
    // Find the matching uploadAPI for a given URL.
    fileprivate func uploadApi(for url: URL?) -> BridgeFileUploadAPI? {
        guard let urlPath = url?.path else { return nil }
        let api = bridgeFileUploadApis.keys.first { key in
            return urlPath.contains(key)
        }
        if let api = api {
            return bridgeFileUploadApis[api]
        }
        return nil
    }
        
    /// Upload a  file to Bridge via the specified upload API.
    /// Generally intended to only be called by BridgeFileUploadAPI implementations.
    func upload<T>(_ trackingType: T.Type, uploadApi: BridgeFileUploadAPI, fileId: String, fileUrl: URL, contentType: String? = nil, extras: Codable? = nil) where T: BridgeUploadTrackingData {
        uploadInternal(trackingType, uploadApi: uploadApi, fileId: fileId, fileUrl: fileUrl, contentType: contentType, extras: extras)
        return
    }
    
    // Internal function returns temp file URL for tests, or nil on pre-flight check failures.
    // Should not be called directly except from unit/integration test cases.
    @discardableResult
    func uploadInternal<T>(_ trackingType: T.Type, uploadApi: BridgeFileUploadAPI, fileId: String, fileUrl: URL, contentType: String? = nil, extras: Codable? = nil) -> URL? where T: BridgeUploadTrackingData {
        // Check if this uploadApi is already registered, and if not, do so
        if !self.bridgeFileUploadApis.keys.contains(uploadApi.apiString) {
            self.bridgeFileUploadApis[uploadApi.apiString] = uploadApi
        }
        
        let mimeType = contentType ?? self.mimeTypeFor(fileUrl: fileUrl)
        
        guard let uploadMetadata = uploadApi.uploadMetadata(for: fileId, fileUrl: fileUrl, mimeType: mimeType, extras: extras) as? BridgeFileUploadMetadata<T> else {
            debugPrint("Unable to create upload metadata for uploading \(fileUrl) as \(fileId) with mime type \(mimeType) via upload API \(uploadApi.apiString)--upload request fails")
            return nil
        }
        
        return self.requestUploadURL(uploadApi: uploadApi, invariantFilePath: nil, fileUrl: fileUrl, uploadMetadata: uploadMetadata)
    }
    
    @discardableResult
    fileprivate func requestUploadURL<T>(uploadApi: BridgeFileUploadAPI, invariantFilePath: String?, fileUrl: URL?, uploadMetadata: BridgeFileUploadMetadata<T>) -> URL? where T: Codable {
        var invariantFilePath = invariantFilePath
        guard let fileUrl = fileUrl else {
            let message = "Error: requestUploadURL called with original fileURL as nil"
            Logger.log(tag: .upload, error: BridgeUnexpectedNullError(category: .invalidURL, message: message))
            return nil
        }

        // if no invariant file path was passed in, make a temp local copy of the file at fileUrl and use that
        var fileCopy: URL? = nil
        if invariantFilePath == nil {
            guard let tempFile = self.tempFileFor(inFileURL: fileUrl, uploadApi: uploadApi) else { return nil }
            fileCopy = tempFile
            
            // Set extended attributes on the temp file so we have enough info to retry the upload
            // if all else fails and all we have to work from is the temp file itself.
            do {
                try fileCopy?.setExtendedAttribute(data: uploadApi.apiString.data(using: .utf8)!, forName: self.uploadApiAttributeName)
                try fileCopy?.setExtendedAttribute(data: uploadApi.fileId(for: uploadMetadata).data(using: .utf8)!, forName: self.fileIdAttributeName)
                try fileCopy?.setExtendedAttribute(data: uploadApi.mimeType(for: uploadMetadata).data(using: .utf8)!, forName: self.contentTypeAttributeName)
                if let extrasData = try uploadApi.extras(for: uploadMetadata)?.jsonEncodedData() {
                    try fileCopy?.setExtendedAttribute(data: extrasData, forName: self.uploadExtrasAttributeName)
                }
            } catch let err {
                Logger.log(tag: .upload, error: err, message: "Error trying to set extended attributes for temp file \(fileUrl)")
                return nil
            }
                
            invariantFilePath = self.sandboxRelativePath(of: tempFile)
        }
        else {
            // we already have the file copy--create a URL from its path
            let filePath = self.fullyQualifiedPath(of: invariantFilePath!)
            if filePath.isEmpty {
                let message = "Unable to get fully qualified path from invariantFilePath '\(invariantFilePath!)'"
                Logger.log(tag: .upload, error: BridgeUnexpectedNullError(category: .empty, message: message))
                return nil
            }
            
            fileCopy = URL(fileURLWithPath: filePath)
            guard let fileCopy = fileCopy else {
                let message = "Unable to create URL from file path '\(filePath)'"
                Logger.log(tag: .upload, error: BridgeUnexpectedNullError(category: .invalidURL, message: message))
                return nil
            }
            
            // "touch" the temp file for retry accounting purposes
            self.touch(fileUrl: fileCopy)
            
            // Keep track of what file it's a copy of.
            self.persistMapping(from: invariantFilePath!, to: fileUrl.path, defaultsKey: self.bridgeFileUploadsKey)
        }
        
        guard let invariantFilePath = invariantFilePath else {
            let message = "Failed to get sandbox-relative file path from temp file URL"
            Logger.log(tag: .upload, error: BridgeUnexpectedNullError(category: .invalidURL, message: message))
            return nil
        }
        
        // Send the request to Bridge
        uploadApi.sendUploadRequest(for: invariantFilePath, uploadMetadata: uploadMetadata)
        
        return fileCopy
    }
    
    /// Download delegate method.
    func bridgeUrlSession(_ session: any BridgeURLSession, downloadTask: BridgeURLSessionDownloadTask, didFinishDownloadingTo location: URL) {
        // get the sandbox-relative path to the temp copy of the participant file
        guard let invariantFilePath = downloadTask.taskDescription else {
            let message = "Finished a download task with no taskDescription set"
            Logger.log(tag: .upload, error: BridgeUnexpectedNullError(category: .missingFile, message: message))
            return
        }
        
        // get which API this task is using
        guard let uploadApi = self.uploadApi(for: downloadTask.originalRequest?.url) else  {
            let message = "Unexpected: No uploadApi registered for download task \(downloadTask) (url: \(String(describing: downloadTask.originalRequest?.url)))"
            Logger.log(tag: .upload, error: BridgeUnexpectedNullError(category: .missingFile, message: message))
            return
        }
        
        // Read the downloaded JSON file into a String, and then convert that to a Data object
        var urlContents: String
        do {
            urlContents = try String(contentsOf: location)
        } catch let err {
            Logger.log(tag: .upload, error: err, message: "Error attempting to read contents from background download task at URL \(location) as String")
            return
        }
        
        // check for HTTP errors (we might succeed in "downloading a file" where the "file"
        // in question is just the error response body)
        if let httpResponse = downloadTask.response as? HTTPURLResponse,
           httpResponse.statusCode >= 400 {
            let message = "Request to Bridge endpoint \(String(describing: downloadTask.originalRequest?.url)) for temp file \(invariantFilePath) failed with status \(httpResponse.statusCode) and response body:\n\(urlContents)"
            Logger.log(tag: .upload, error: BridgeHttpError(errorCode: httpResponse.statusCode, message: message))
            
            // 401s on download get retried automatically, so our `urlSession(_:didCompleteWithError:)`
            // delegate method never gets called in that case, so it never would get cleaned up and we
            // don't want an ever-growing list of these clogging up our userDefaults forever. ~emm 2021-06-10
            if httpResponse.statusCode != 401 {
                self.persistMapping(from: invariantFilePath, to: urlContents, defaultsKey: self.downloadErrorResponseBodyKey)
            }
            // now just bail--we'll handle it if and when it makes it to `urlSession(_:, task:, didCompleteWithError:)`.
            return
        }

        // remove the participant file from the uploadRequested list, retrieving its
        // associated upload metadata; or, if not found there, check for and remove it from
        // the notifyingBridge list and we're done
        
        guard let uploadMetadata = uploadApi.fetchUploadRequested(for: invariantFilePath) else {
            // We don't actually care what the mapping is to here, just whether or not one exists
            guard let _ = uploadApi.fetchNotifyingBridge(for: invariantFilePath) else {
                // if it wasn't in either list, log it and bail
                let message = "Unable to retrieve upload metadata for \(invariantFilePath) from either upload request map or notifying Bridge map."
                Logger.log(tag: .upload, error: BridgeUnexpectedNullError(category: .missingFile, message: message))
                return
            }

            // since it was notifying bridge, we're all done at this point, so we
            // can now tie up any loose ends:
            
            // -- remove from retry queue, in case it somehow ended up there
            uploadApi.dequeueForRetry(relativePath: invariantFilePath)
            
            // -- remove the temp file -> original file mapping
            removeMapping(String.self, from: invariantFilePath, defaultsKey: self.bridgeFileUploadsKey)
            
            // -- delete the temp file
            cleanUpTempFile(filePath: invariantFilePath)
            
            return
        }

        guard !urlContents.isEmpty else {
            let message = "Download task finished successfully but string from downloaded file at URL \(location) is empty"
            Logger.log(tag: .upload, error: BridgeUnexpectedNullError(category: .empty, message: message))
            return
        }
        
        guard let jsonData = urlContents.data(using: .utf8) else {
            let message = "Could not convert string contents of downloaded file at URL \(location) to data using .utf8 encoding: \"\(urlContents)\""
            Logger.log(tag: .upload, error: BridgeUnexpectedNullError(category: .corruptData, message: message))
            return
        }

        // deserialize the bridge upload response object from the downloaded JSON data
        // and update the upload metadata with it
        guard let updatedMetadata = uploadApi.update(metadata: uploadMetadata, with: jsonData) else {
            return
        }
        
        uploadToS3(uploadApi: uploadApi, bridgeUploadMetadata: updatedMetadata, invariantFilePath: invariantFilePath)
    }
    
    func uploadToS3(uploadApi: BridgeFileUploadAPI, bridgeUploadMetadata: BridgeFileUploadMetadataBlob,  invariantFilePath: String) {
        guard let uploadUrl = uploadApi.s3UploadUrlString(for: bridgeUploadMetadata) else {
            let message = "Could not get S3 upload URL from file upload metadata: \(bridgeUploadMetadata)"
            Logger.log(tag: .upload, error: BridgeUnexpectedNullError(category: .missingMetadata, message: message))
            return
        }
        
        // get the fully-qualified path of the file to be uploaded
        let filePath = self.fullyQualifiedPath(of: invariantFilePath)
        if filePath.isEmpty {
            let message = "Unable to recover fully qualified path from sandbox-relative path \"\(invariantFilePath)\""
            Logger.log(tag: .upload, error: BridgeUnexpectedNullError(category: .empty, message: message))
            return
        }
        
        // ...and make a URL from it
        let fileUrl = URL(fileURLWithPath: filePath)
        
        // add the file to the uploadingToS3 list
        uploadApi.markUploadingToS3(for: invariantFilePath, uploadMetadata: bridgeUploadMetadata)
        
        // upload the file to S3
        self.upload(fileUrl, to: uploadUrl, for: invariantFilePath, uploadApi: uploadApi, uploadMetadata: bridgeUploadMetadata)
    }

    func upload(_ fileUrl: URL, to uploadUrlString: String, for invariantFilePath: String, uploadApi: BridgeFileUploadAPI, uploadMetadata: BridgeFileUploadMetadataBlob) {
        let headers = uploadApi.s3UploadHeaders(for: uploadMetadata)
        self.netManager.uploadFile(fileUrl, httpHeaders: headers, to: uploadUrlString, taskDescription: invariantFilePath)
    }
    
    /// Call this function to check for and run any retries where the required delay has elapsed.
    func retryUploadsAfterDelay() {
        self.uploadQueue.addOperation {
            guard var retryUploads = self.userDefaults.dictionary(forKey: self.retryUploadsKey) else { return }
            for filePath in retryUploads.keys {
                autoreleasepool {
                    guard let uploadApi = self.apiFromXAttrs(for: filePath, debugMessage: "Couldn't retrieve API from temp file xattrs for \(filePath)") else {
                        return
                    }
                    
                    if uploadApi.retryIfReady(relativePath: filePath, mappings: &retryUploads) {
                        self.userDefaults.setValue(retryUploads, forKey: self.retryUploadsKey)
                    }
                }
            }
        }
    }
    
    fileprivate func cancelTasks(for relativePath: String, tasks: [BridgeURLSessionTask]) -> [BridgeURLSessionTask] {
        var notCanceledTasks = [BridgeURLSessionTask]()
        for task in tasks {
            if task.taskDescription != relativePath {
                notCanceledTasks.append(task)
                continue
            }
            task.cancel()
        }
        return notCanceledTasks
    }
    
    // Check for orphaned uploads and enqueue them for retry. This needs to *not* be run in the
    // uploads queue (which is also the background session's delegate/completion handler queue)
    // to avoid an EXC_BAD_ACCESS crash when invoking getAllTasks.
    fileprivate func checkForOrphanedUploads() {
        // App extensions are severely memory constrained, so don't even try this if we're in one.
        guard !self.netManager.isRunningInAppExtension() else { return }
        
        // Do not attempt to check and retry orphaned uploads if the session token isn't set up.
        guard self.appManager?.sessionToken != nil else { return }
        
        self.netManager.backgroundSession().getAllTasks { tasks in
            var tasks = tasks
            let defaults = self.userDefaults
            
            // Get the set of all temp files for which there is a currently-active background
            // URLSession task.
            var filesInFlight = Set(tasks.map { $0.description })
            
            // Get the mappings from temp file to original file for all in-progress uploads.
            let fileUploads = defaults.dictionary(forKey: self.bridgeFileUploadsKey) ?? [String : Any]()
            
            // Assume uploads in the uploadURLsRequested map that are more than 24 hours old
            // are orphaned. Note that under some unusual circumstances this may lead to
            // duplication of uploads.
            let uploadURLsRequested = defaults.dictionary(forKey: self.uploadURLsRequestedKey) ?? [String : Any]()
            Logger.log(severity: .info, message: "checkForOrphanedUploads: Processing \(uploadURLsRequested.count) uploadURL requests.")
            for invariantFilePath in uploadURLsRequested.keys {
                guard let api = self.apiFromXAttrs(for: invariantFilePath) else { continue }
                guard let metadataBlob = api.retrieveMetadata(from: invariantFilePath, mappings: uploadURLsRequested) else { continue }

                var fileUrl: URL!
                guard self.fileIsADayOld(invariantFilePath: invariantFilePath, fileUrl: &fileUrl)
                else {
                    Logger.log(severity: .info, message: "checkForOrphanedUploads: Exiting upload request resend - file is less than a day old.")
                    continue
                }
                
                // If there is a file in-flight then something went wrong. Cancel before resending
                if let inflight = tasks.first(where: { $0.description == invariantFilePath }) {
                    inflight.cancel()
                    filesInFlight.remove(invariantFilePath)
                }
                
                // If we get all the way here, touch the file to reset the orphanage clock
                // and then send the upload request again.
                Logger.log(severity: .info, message: "checkForOrphanedUploads: Resending upload request.")
                self.touch(fileUrl: fileUrl)
                api.sendUploadRequest(for: invariantFilePath, uploadMetadata: metadataBlob)
            }
            
            // Assume any uploads in the uploadingToS3 map whose sessions are at or past their
            // expiration datetime are orphaned.
            let uploadingToS3 = defaults.dictionary(forKey: self.uploadingToS3Key) ?? [String : Any]()
            Logger.log(severity: .info, message: "checkForOrphanedUploads: Processing \(uploadingToS3.count) uploads to S3.")
            for invariantFilePath in uploadingToS3.keys {
                guard let api = self.apiFromXAttrs(for: invariantFilePath) else { continue }
                guard let metadataBlob = api.retrieveMetadata(from: invariantFilePath, mappings: uploadingToS3) else { continue }
                guard api.isUploadSessionExpired(for: metadataBlob) else { continue }
                guard let originalFilePath = self.retrieveMapping(String.self, from: invariantFilePath, mappings: fileUploads) else { continue }
                
                // ok, the pre-signed upload URL is expired--so cancel any tasks for this file,
                // remove it from the S3 upload mapping, touch it to reset the orphanage clock,
                // and enqueue it for immediate retry
                tasks = self.cancelTasks(for: invariantFilePath, tasks: tasks)
                api.fetchUploadingToS3(for: invariantFilePath)
                let fullPath = self.fullyQualifiedPath(of: invariantFilePath)
                let fileUrl = URL(fileURLWithPath: fullPath)
                self.touch(fileUrl: fileUrl)
                api.enqueueForRetry(delay: 0, relativePath: invariantFilePath, originalFilePath: originalFilePath, uploadMetadata: metadataBlob)
            }
            
            // Assume any attempts to notify Bridge of success for uploads that are more than
            // 24 hours old are orphaned. Note that under some unusual circumstances this may
            // lead to duplicate notifications to Bridge.
            let notifyingBridge = defaults.dictionary(forKey: self.notifyingBridgeUploadSucceededKey) ?? [String : Any]()
            Logger.log(severity: .info, message: "checkForOrphanedUploads: Processing \(notifyingBridge.count) upload success Bridge notifications.")
            for invariantFilePath in notifyingBridge.keys {
                guard let api = self.apiFromXAttrs(for: invariantFilePath) else { continue }
                guard let metadataBlob = api.retrieveMetadata(from: invariantFilePath, mappings: notifyingBridge) else { continue }
                // Assume files with an active urlsession task are not (yet) orphaned, no matter how old.
                guard !filesInFlight.contains(invariantFilePath) else { continue }
                var fileUrl: URL!
                guard self.fileIsADayOld(invariantFilePath: invariantFilePath, fileUrl: &fileUrl) else { continue }
                
                // If we get all the way here, touch the file to reset the orphanage clock
                // and then send the notify request again.
                self.touch(fileUrl: fileUrl)
                api.notifyBridgeUploadSucceeded(relativePath: invariantFilePath, uploadMetadata: metadataBlob)
            }
            
            // Assume any uploads in the bridgeFileUploads map which are not in any other map
            // and have no in-flight tasks and are at least 24 hours old are orphaned.
            Logger.log(severity: .info, message: "checkForOrphanedUploads: Processing \(fileUploads.count) orphaned file uploads.")
            for invariantFilePath in fileUploads.keys {
                guard !filesInFlight.contains(invariantFilePath) else { continue }
                guard !uploadURLsRequested.keys.contains(invariantFilePath) else { continue }
                guard !uploadingToS3.keys.contains(invariantFilePath) else { continue }
                guard !notifyingBridge.keys.contains(invariantFilePath) else { continue }
                var fileUrl: URL!
                guard self.fileIsADayOld(invariantFilePath: invariantFilePath, fileUrl: &fileUrl) else { continue }
                guard let originalFilePath = self.retrieveMapping(String.self, from: invariantFilePath, mappings: fileUploads) else { continue }
                guard let (api, fileId, mimeType, extras) = self.apiInfoFromXAttrs(for: invariantFilePath) else { continue }
                // get the upload metadata using the temp file URL (as the original file likely no longer exists)
                guard let metadataBlob = api.uploadMetadata(for: fileId, fileUrl: fileUrl, mimeType: mimeType, extras: extras) else { continue }
                // touch the file to reset the orphanage clock and enqueue it for immediate retry.
                self.touch(fileUrl: fileUrl)
                api.enqueueForRetry(delay: 0, relativePath: invariantFilePath, originalFilePath: originalFilePath, uploadMetadata: metadataBlob)
            }
            
            // Assume any files lingering in upload temp file directories which are not in any maps
            // and not in any in-flight tasks are orphaned. Note that this assumes all Bridge Upload
            // API implementations put their temp file copies in a subfolder of the app support dir
            // whose name ends in "Uploads".
            let  fileMan = FileManager.default
            guard let appSupportDir = fileMan.urls(for: .applicationSupportDirectory, in: .userDomainMask).first else { return }
            let resourceKeys = Set<URLResourceKey>([.nameKey, .isDirectoryKey])
            guard let dirEnumerator = fileMan.enumerator(at: appSupportDir, includingPropertiesForKeys: Array(resourceKeys), options: .skipsHiddenFiles) else { return }
            var allFiles: [URL] = []
            for case let fileUrl as URL in dirEnumerator {
                guard let resourceValues = try? fileUrl.resourceValues(forKeys: resourceKeys),
                    let isDirectory = resourceValues.isDirectory,
                    let name = resourceValues.name
                    else {
                        continue
                }
                if isDirectory {
                    if !name.hasSuffix("Uploads") {
                        dirEnumerator.skipDescendants()
                    }
                } else {
                    allFiles.append(fileUrl)
                }
            }
            let retryQueue = defaults.dictionary(forKey: self.retryUploadsKey) ?? [String : Any]()
            Logger.log(severity: .info, message: "checkForOrphanedUploads: Processing \(allFiles.count) files found in the upload directory.")
            for fileUrl in allFiles {
                let invariantFilePath = self.sandboxRelativePath(of: fileUrl)
                guard !filesInFlight.contains(invariantFilePath) else { continue }
                guard !fileUploads.keys.contains(invariantFilePath) else { continue }
                guard !uploadURLsRequested.keys.contains(invariantFilePath) else { continue }
                guard !uploadingToS3.keys.contains(invariantFilePath) else { continue }
                guard !notifyingBridge.keys.contains(invariantFilePath) else { continue }
                guard !retryQueue.keys.contains(invariantFilePath) else { continue }
                guard let (api, fileId, mimeType, extras) = self.apiInfoFromXAttrs(for: invariantFilePath) else { continue }
                guard let metadataBlob = api.uploadMetadata(for: fileId, fileUrl: fileUrl, mimeType: mimeType, extras: extras) else { continue }
                // touch the file to reset the orphanage clock and enqueue it for immediate retry. We don't
                // know the original file path, so we'll just use the temp file path.
                self.touch(fileUrl: fileUrl)
                api.enqueueForRetry(delay: 0, relativePath: invariantFilePath, originalFilePath: fileUrl.path, uploadMetadata: metadataBlob)
            }
        }
    }
    
    /// Call this function to check for and retry any orphaned uploads, and update the app's isUploading state  accordingly.
    func checkAndRetryOrphanedUploads() {
        Logger.log(severity: .info, message: "in checkAndRetryOrphanedUploads()")
        // This needs to start out from the main queue to avoid an EXC_BAD_ACCESS crash in
        // checkForOrphanedUploads(), but we also need that function to do its thing before
        // continuing on here and we don't want to potentially deadlock by popping out
        // synchronously to main in there. So we'll do it from here.
        self.runOnQueue(OperationQueue.main, sync: false) {
            self.checkForOrphanedUploads()
            
            self.runOnQueue(self.uploadQueue, sync: false) {
                let uploading = self.uploadsStillInProgress()
                
                // Update the app manager's isUploading status. This needs to be done on the main queue.
                self.runOnQueue(OperationQueue.main, sync: false) {
                    self.appManager.isUploading = uploading
                }
            }
            
            self.retryUploadsAfterDelay()
        }
    }
    
    fileprivate func postAndUpdateUploadingStatus(_ notification: Notification) {
        NotificationCenter.default.post(notification)
        self.checkAndRetryOrphanedUploads()
    }
    
    // The number of uploads still in progress is the total of the number of file uploads currently happening
    // plus the number of previously failed uploads enqueued for retry. This just checks if that number is
    // zero or non-zero.
    //
    // NOTE: This function should only be called on the upload queue.
    fileprivate func uploadsStillInProgress() -> Bool {
        var uploadsCount: Int = 0
        if let fileUploads = self.userDefaults.dictionary(forKey: self.bridgeFileUploadsKey) {
            uploadsCount = uploadsCount + fileUploads.count
        }
        if let retries = self.userDefaults.dictionary(forKey: self.retryUploadsKey) {
            uploadsCount = uploadsCount + retries.count
        }
        Logger.log(severity: .info, message: "Number of uploads in progress = \(uploadsCount)")
        return uploadsCount != 0
    }
    
    // Put a file into the retry queue so we can try again later.
    func enqueueForRetry<T>(retryInfo: BridgeFileRetryInfo<T>, invariantFilePath: String, originalFilePath: String, uploadMetadata: BridgeFileUploadMetadata<T>) where T: Codable {
        self.persistMapping(from: invariantFilePath, to: retryInfo, defaultsKey: self.retryUploadsKey)
    }
    
    // Remove a file from the retry queue.
    func dequeueForRetry<T>(_ type: T.Type, relativePath: String) -> BridgeFileRetryInfo<T>? where T: Codable {
        return self.removeMapping(BridgeFileRetryInfo<T>.self, from: relativePath, defaultsKey: self.retryUploadsKey)
    }
    
    // Helper for task delegate method in case of HTTP error on Bridge upload request or
    // upload success notification request.
    fileprivate func handleHTTPDownloadStatusCode(_ statusCode: Int, uploadApi: BridgeFileUploadAPI, downloadTask: BridgeURLSessionDownloadTask, invariantFilePath: String) {
        
        // remove the participant file from either the uploadRequested or notifyingBridge list,
        // retrieving its associated upload metadata
        var uploadMetadata: BridgeFileUploadMetadataBlob
        var wasNotifyingBridge = false
        if let metadata = uploadApi.fetchUploadRequested(for: invariantFilePath) {
            uploadMetadata = metadata
        }
        else if let metadata = uploadApi.fetchNotifyingBridge(for: invariantFilePath) {
            uploadMetadata = metadata
            wasNotifyingBridge = true
        }
        else {
            let message = "Unable to retrieve BridgeFileUploadMetadataBlob for \(String(describing: invariantFilePath))"
            Logger.log(tag: .upload, error: BridgeUnexpectedNullError(category: .missingMetadata, message: message))
            return
        }

        // remove the file from the temp -> orig mappings, and retrieve the original file path
        guard let originalFilePath = removeMapping(String.self, from: invariantFilePath, defaultsKey: self.bridgeFileUploadsKey) else {
            let message =
            """
            Unexpected NULL: No original file path found mapped from temp file path \(invariantFilePath)
                Status Code: \(statusCode)
                API: \(uploadApi.apiString)
                Download task: \(downloadTask)
            """
            Logger.log(tag: .upload, error: BridgeUnexpectedNullError(category: .missingFile, message: message))
           return
        }
        
        // remove the file from the temp -> download error response body mappings,
        // and retrieve the response body, if any
        let responseBody = removeMapping(String.self, from: invariantFilePath, defaultsKey: self.downloadErrorResponseBodyKey)
        
        if wasNotifyingBridge {
            // TODO: emm 2021-08-19 queue up just the success notification request to Bridge for later retry?
            // (Bridge-iOS-SDK did not do this, and original upload API uses S3 notifications as a backup)
        }
        else {
            // server errors should be retried
            if statusCode >= 500 {
                // initial request failed due to server issue--queue for complete retry
                uploadApi.enqueueForRetry(delay: self.delayForRetry, relativePath: invariantFilePath, originalFilePath: originalFilePath, uploadMetadata: uploadMetadata)
                return
            }
        }

        var failedNotification: Notification
        if wasNotifyingBridge {
            // post a notification that reporting upload success to Bridge failed
            failedNotification = uploadApi.reportingUploadToBridgeFailedNotification(for: uploadMetadata, statusCode: statusCode, responseBody: responseBody)!
        }
        else {
            // post a notification that the file upload request to Bridge failed unrecoverably
            failedNotification = uploadApi.uploadRequestFailedNotification(for: uploadMetadata, statusCode: statusCode, responseBody: responseBody)
        }
        cleanUpTempFile(filePath: invariantFilePath)
        self.postAndUpdateUploadingStatus(failedNotification)
    }

    // Helper for task delegate method in case of HTTP error on S3 upload.
    fileprivate func handleHTTPUploadStatusCode(_ statusCode: Int, uploadApi: BridgeFileUploadAPI, tempFilePath: String, originalFilePath: String,  uploadMetadata: BridgeFileUploadMetadataBlob) {
        switch statusCode {
        case 403, 409, 500, 503:
            // 403: for our purposes means the pre-signed url timed out before starting the actual upload to S3.
            // 409: in our case it could only mean a temporary conflict (resource locked by another process, etc.) that should be retried.
            // 500: means internal server error ("We encountered an internal error. Please try again.")
            // 503: means service not available or the requests are coming too fast, so try again later.
            // In any case, we'll retry after a minimum delay to avoid spamming retries.
            uploadApi.enqueueForRetry(delay: self.delayForRetry, relativePath: tempFilePath, originalFilePath: originalFilePath, uploadMetadata: uploadMetadata)

        default:
            // iOS handles redirects automatically so only e.g. 304 resource not changed etc. from the 300 range should end up here
            // (along with all unhandled 4xx and 5xx of course).
            let error = BridgeHttpError(errorCode: statusCode, message: "Participant file upload to S3 of file \(originalFilePath) failed with HTTP response status code \(statusCode)--unhandled, will not retry")
            Logger.log(tag: .upload, error: error)
            
            // post a notification that the file upload to S3 failed unrecoverably
            let uploadFailedNotification = uploadApi.uploadToS3FailedNotification(for: uploadMetadata)
            cleanUpTempFile(filePath: tempFilePath)
            self.postAndUpdateUploadingStatus(uploadFailedNotification)
        }
    }

    /// Task delegate method.
    private func _urlSession(_ session: any BridgeURLSession, task: BridgeURLSessionTask, didCompleteWithError error: Error?) {
        
        // get the sandbox-relative path to the temp copy of the participant file
        guard let invariantFilePath = task.taskDescription else {
            let message = "Unexpected: Finished a background session task with no taskDescription set"
            Logger.log(tag: .upload, error: BridgeUnexpectedNullError(category: .missingFile, message: message))
            return
        }
        
        // check that the file still exists before going any further; if we just
        // got done notifying Bridge of success, then it won't, and we're done.
        let fullPath = self.fullyQualifiedPath(of: invariantFilePath)
        guard FileManager.default.fileExists(atPath: fullPath) else {
            return
        }
        
        // get which API this task is using from the temp copy's xattrs
        guard let uploadApi = self.apiFromXAttrs(for: invariantFilePath, debugMessage: "Unexpected: No uploadApi marked for temp file \(invariantFilePath)") else {
            return
        }

        if let downloadTask = task as? BridgeURLSessionDownloadTask {
            // If an HTTP error response from Bridge gets through to here, we need to handle it.
            // Otherwise, we're done here.
            guard let httpResponse = task.response as? HTTPURLResponse,
                  httpResponse.statusCode >= 400 else {
                return
            }
                        
            self.handleHTTPDownloadStatusCode(httpResponse.statusCode, uploadApi: uploadApi, downloadTask: downloadTask, invariantFilePath: invariantFilePath)
            return
        }
        
        // remove the file from the upload requests, and retrieve its BridgeFileUploadMetadata object
        guard let uploadMetadata = uploadApi.fetchUploadingToS3(for: invariantFilePath) else {
            let message = "No BridgeFileUploadMetadataBlob found mapped for temp file \(invariantFilePath)"
            Logger.log(tag: .upload, error: BridgeUnexpectedNullError(category: .missingFile, message: message))
            return
        }
        
        // remove the file from the temp -> orig mappings, and retrieve the original file path
        guard let originalFilePath = removeMapping(String.self, from: invariantFilePath, defaultsKey: self.bridgeFileUploadsKey) else {
            let message =
            """
            Unexpected: No original file path found mapped from temp file path \(invariantFilePath)
              Task: \(task)
              Session: \(session)
              Error: \(String(describing: error))
            """
            Logger.log(tag: .upload, error: BridgeUnexpectedNullError(category: .missingFile, message: message))
            return
        }
        
        // remove the file from the retry queue if it's in there (as it might be if an URLSession was invalidated
        // due to an error)
        
        uploadApi.dequeueForRetry(relativePath: invariantFilePath)
        
        // any error that makes it all the way through to here would be the result of something like a
        // malformed request, so log it, post a failed upload notification, clean up the temp file,
        // and bail out
        if let error = error {
            Logger.log(tag: .upload, error: error, message: "Error uploading file \(originalFilePath) to S3")
            let uploadFailedNotification = uploadApi.uploadToS3FailedNotification(for: uploadMetadata)
            cleanUpTempFile(filePath: invariantFilePath)
            self.postAndUpdateUploadingStatus(uploadFailedNotification)
            return
        }
        
        // check the response for HTTP errors and handle accordingly
        guard let httpResponse = task.response as? HTTPURLResponse else {
            let message = "Upload task response is not an HTTPURLResponse"
            Logger.log(tag: .upload, error: BridgeUnexpectedNullError(category: .wrongType, message: message))
            return
        }
        
        let statusCode = httpResponse.statusCode
        if statusCode >= 300 {
            self.handleHTTPUploadStatusCode(statusCode, uploadApi: uploadApi, tempFilePath: invariantFilePath, originalFilePath: originalFilePath, uploadMetadata: uploadMetadata)
            return
        }
        
        // if reporting to Bridge, do that, otherwise clean up now
        if uploadApi.notifiesBridgeWhenUploaded {
            uploadApi.notifyBridgeUploadSucceeded(relativePath: invariantFilePath, uploadMetadata: uploadMetadata)
        }
        else {
            cleanUpTempFile(filePath: invariantFilePath)
        }
        
        // post a notification that the file uploaded
        let uploadedNotification = uploadApi.fileUploadedNotification(for: uploadMetadata)
        self.postAndUpdateUploadingStatus(uploadedNotification)
    }
    
    /// Session delegate method.
    func bridgeUrlSession(_ session: any BridgeURLSession, didBecomeInvalidWithError error: Error?) {
        guard error != nil else {
            // If the URLSession was deliberately invalidated (i.e., error is nil) then we assume
            // the intention is to cancel and forget all incomplete uploads, including retries.
            // This might be used e.g. to clear out all pending uploads if we receive a 412
            // (Not Consented) error from Bridge or if the participant withdraws from the study.
            self.reset()
            return
        }
        
        // If the URLSession was invalidated due to an error then we want to recover from that,
        // so we copy all incomplete uploads into the retry queue just to be sure. But we also
        // leave them in their current state in the mappings in case the error only broke it
        // on our end and iOS could still come through for us.
        self.runOnQueue(self.uploadQueue, sync: false) {
            guard let originalFilePaths = self.userDefaults.dictionary(forKey: self.bridgeFileUploadsKey) else {
                // nothing to see here, move along
                return
            }
            
            let uploadsRequested = self.userDefaults.dictionary(forKey: self.uploadURLsRequestedKey)
            let uploadsToS3 = self.userDefaults.dictionary(forKey: self.uploadingToS3Key)
            
            // Get the temp copy and original file path for each file currently in the upload process and
            // copy it to the upload queue with its s3 metadata.
            for invariantFilePath in originalFilePaths.keys {
                guard let uploadApi = self.apiFromXAttrs(for: invariantFilePath, debugMessage: "Unexpected: couldn't retrieve API from temp file xattrs for \(invariantFilePath)") else {
                    continue
                }

                guard let originalFilePath = self.retrieveMapping(String.self, from: invariantFilePath, mappings: originalFilePaths),
                      let uploadMetadata = uploadApi.retrieveMetadata(from: invariantFilePath, mappings: uploadsToS3) ??
                        uploadApi.retrieveMetadata(from: invariantFilePath, mappings: uploadsRequested) else {
                    continue
                }
                uploadApi.enqueueForRetry(delay: self.delayForRetry, relativePath: invariantFilePath, originalFilePath: originalFilePath, uploadMetadata: uploadMetadata)
            }
        }
    }

    func apiFromXAttrs(for filePath: String, debugMessage: String? = nil) -> BridgeFileUploadAPI? {
        self.apiInfoFromXAttrs(for: filePath, debugMessage: debugMessage)?.uploadApi
    }
    
    func apiInfoFromXAttrs(for filePath: String, debugMessage: String? = nil) -> (uploadApi: BridgeFileUploadAPI, fileId: String, contentType: String, extras: Codable?)? {
        do {
            return try self._apiInfoFromXAttrs(for: filePath)
        } catch {
            Logger.log(tag: .upload, error: error, message: debugMessage)
            return nil
        }
    }
    
    func _apiInfoFromXAttrs(for filePath: String) throws -> (uploadApi: BridgeFileUploadAPI, fileId: String, contentType: String, extras: Codable?) {
        let fullPath = self.fullyQualifiedPath(of: filePath)
        guard FileManager.default.fileExists(atPath: fullPath) else {
            let message = "Unexpected: Attempting to retrieve upload API info for temp file with invariant path '\(filePath) but temp file does not exist at '\(fullPath)"
            throw BridgeUnexpectedNullError(category: .missingFile, message: message)
        }
        let tempFile = URL(fileURLWithPath: fullPath)

        let apiStringData = try tempFile.extendedAttribute(forName: self.uploadApiAttributeName)
        let fileIdData = try tempFile.extendedAttribute(forName: self.fileIdAttributeName)
        let contentTypeData = try tempFile.extendedAttribute(forName: self.contentTypeAttributeName)

        // extras is an optional attribute so we don't care if it isn't present
        let extrasData = try? tempFile.extendedAttribute(forName: self.uploadExtrasAttributeName)
        
        guard let apiString = String(data: apiStringData, encoding: .utf8) else {
            let message = "Unexpected: Could not convert apiStringData to a utf8 string: \(apiStringData)"
            throw BridgeUnexpectedNullError(category: .missingAttributes, message: message)
        }
        guard let api = self.bridgeFileUploadApis[apiString] else {
            let message = "Unexpected: Could not retrieve BridgeFileUploadAPI for \(apiString) from list of registered upload APIs"
            throw BridgeUnexpectedNullError(category: .missingAttributes, message: message)
        }
        guard let fileId = String(data: fileIdData, encoding: .utf8) else {
            let message = "Unexpected: Could not convert fileIdData to a utf8 string: \(fileIdData)"
            throw BridgeUnexpectedNullError(category: .missingAttributes, message: message)
        }
        guard let contentType = String(data: contentTypeData, encoding: .utf8) else {
            let message = "Unexpected: Could not convert contentTypeData to a utf8 string: \(contentTypeData)"
            throw BridgeUnexpectedNullError(category: .missingAttributes, message: message)
        }
        let extras = api.uploadRequestExtras(from: extrasData)

        return (uploadApi: api, fileId: fileId, contentType: contentType, extras: extras)
    }
    
    func cleanUpTempFile(filePath: String) {
        self.runOnQueue(self.uploadQueue, sync: false) {
            self.removeTempFile(filePath: filePath)
        }
    }
    
    // MARK: Moved from BackgroundNetworkManager - syoung 07/27/2023

    /// We use this custom HTTP request header as a hack to keep track of how many times we've retried a request.
    let retryCountHeader = "X-SageBridge-Retry"
    
    /// This sets the maximum number of times we will retry a request before giving up.
    let maxRetries = 5
    
    func bridgeUrlSession(_ session: any BridgeURLSession, task: BridgeURLSessionTask, didCompleteWithError error: Error?) {
        if let nsError = error as NSError?,
           let downloadTask = task as? BridgeURLSessionDownloadTask,
           let resumeData = nsError.userInfo[NSURLSessionDownloadTaskResumeData] as? Data {
            // if there's resume data from a download task, use it to retry
            self.retryFailedDownload(downloadTask, for: session, resumeData: resumeData)
            return
        }

        var retrying = false
        if let downloadTask = task as? BridgeURLSessionDownloadTask {
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
            _urlSession(session, task: task, didCompleteWithError: error)
        }
    }
    
    fileprivate func retryFailedDownload(_ task: BridgeURLSessionDownloadTask, for session: any BridgeURLSession, resumeData: Data) {
        let resumeTask = session.downloadTask(withResumeData: resumeData)
        resumeTask.taskDescription = task.taskDescription
        resumeTask.resume()
    }
    
    func isTemporaryError(errorCode: Int) -> Bool {
        return (errorCode == NSURLErrorTimedOut || errorCode == NSURLErrorCannotFindHost || errorCode == NSURLErrorCannotConnectToHost || errorCode == NSURLErrorNotConnectedToInternet || errorCode == NSURLErrorSecureConnectionFailed)
    }
    
    // Make sure to only ever call this from the main thread--the session token
    // lives in Kotlin Native code which only allows access from the thread on which
    // the object was originally created. ~emm 2021-09-17
    @discardableResult
    func retry(task: BridgeURLSessionDownloadTask) -> Bool {
        guard var request = task.originalRequest else {
            let message = "Unable to retry upload task, as originalRequest is nil:\n\(task)"
            Logger.log(tag: .upload, error: BridgeUnexpectedNullError(category: .corruptData, message: message))
            return false
        }
        
        // Try, try again, until we run out of retries.
        var retry = Int(request.value(forHTTPHeaderField: retryCountHeader) ?? "") ?? 0
        guard retry < maxRetries else {
            Logger.log(severity: .info, message: "Retry attempts (\(retry)) exceeds max retry count (\(maxRetries)).")
            return false
        }
        
        guard let sessionToken = appManager.sessionToken else {
            Logger.log(severity: .warn, tag: .upload, message: "Unable to retry task--not signed in (auth manager's UserSessionInfo is nil)")
            return false
        }

        retry += 1
        request.setValue("\(retry)", forHTTPHeaderField: retryCountHeader)
        request.setValue(sessionToken, forHTTPHeaderField: "Bridge-Session")

        let newTask = netManager.backgroundSession().downloadTask(with: request)
        newTask.taskDescription = task.taskDescription
        DispatchQueue.main.asyncAfter(deadline: DispatchTime.now() + pow(2.0, Double(retry))) {
            newTask.resume()
        }
        
        return true
    }
    
    func handleError(_ error: NSError, session: any BridgeURLSession, task: BridgeURLSessionDownloadTask) -> Bool {
        if isTemporaryError(errorCode: error.code) {
            // Retry, and let the caller know we're retrying.
            return retry(task: task)
        }
        
        return false
    }
    
    func handleUnsupportedAppVersion() {
        self.appManager.notifyUIOfBridgeError(410, description: "Unsupported app version")
    }
    
    func handleServerPreconditionNotMet() {
        self.appManager.notifyUIOfBridgeError(412, description: "User not consented")
    }
    
    func handleHTTPErrorResponse(_ response: HTTPURLResponse, session: any BridgeURLSession, task: BridgeURLSessionDownloadTask) -> Bool {
        switch response.statusCode {
        case 401:
            self.appManager.reauthenticate { success in
                if success {
                    Logger.log(severity: .info, tag: .upload, message: "Session token auto-refresh succeeded, retrying original request")
                    self.retry(task: task)
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
}


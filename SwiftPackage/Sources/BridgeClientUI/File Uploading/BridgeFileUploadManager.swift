//
//  BridgeFileUploadManager.swift
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
import UIKit
import UniformTypeIdentifiers
import CoreServices
import BridgeClient
import JsonModel

protocol BridgeFileUploadMetadataBlob {}
struct BridgeFileUploadMetadata<T>: Codable, BridgeFileUploadMetadataBlob where T: Codable {
    var bridgeUploadTrackingObject: T
    var s3Headers: [String : String]
}

protocol BridgeFileRetryInfoBlob {}
struct BridgeFileRetryInfo<T>: Codable, BridgeFileRetryInfoBlob where T: Codable {
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
    
    /// This method is the public face of the Bridge upload APIs.
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
    associatedtype TrackingType where TrackingType: Codable
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
    
    // Not exposed in public API; cast uploadApi to BridgeFileUploadAPITyped to use this function.
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
            debugPrint("Error attempting to decode plist object to BridgeFileRetryInfo<\(TrackingType.self)>:\n\(retryInfoPlist)\n\(error)")
            // since it's broken, remove it
            mappings.removeValue(forKey: relativePath)
            return true
        }

        if retryInfo.whenToRetry.timeIntervalSinceNow <= 0.0 {
            // get the fileURL from the original file path
            let fileUrl = URL(fileURLWithPath: retryInfo.originalFilePath)
            
            let uploadMetadata = retryInfo.uploadMetadata
            if !self.isUploadSessionExpired(for: uploadMetadata) {
                // if we have an upload URL and it's not expired, just retry upload to S3
                // -- restore tracking of what file it's a copy of
                self.uploadManager.persistMapping(from: relativePath, to: fileUrl.path, defaultsKey: self.uploadManager.bridgeFileUploadsKey)
                // -- retry upload to S3
                self.uploadManager.uploadToS3(uploadApi: self, bridgeUploadMetadata: uploadMetadata, invariantFilePath: relativePath)
            }
            else {
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

    public func upload(fileId: String, fileUrl: URL, contentType: String? = nil, extras: Codable? = nil) {
        self.uploadManager.upload(TrackingType.self, uploadApi: self, fileId: fileId, fileUrl: fileUrl, contentType: contentType, extras: extras)
    }

    public func uploadInternal(fileId: String, fileUrl: URL, contentType: String? = nil, extras: Codable? = nil) -> URL? {
        return self.uploadManager.uploadInternal(TrackingType.self, uploadApi: self, fileId: fileId, fileUrl: fileUrl, contentType: contentType, extras: extras)
    }
    
    public func sendUploadRequest(for relativePath: String, uploadMetadata: BridgeFileUploadMetadataBlob) {
        // Get the bridge upload object
        guard let bridgeUploadObject = self.uploadRequestObject(for: uploadMetadata) as? UploadRequestType else {
            debugPrint("Unable to get upload request object (type \(UploadRequestType.self)) from uploadMetadata: \(uploadMetadata)")
            return
        }

        // Request an uploadUrl for the bridge upload object
        let requestString = self.uploadRequestUrlString(for: uploadMetadata)

        // throw this over to the main queue so we can access Kotlin stuff
        OperationQueue.main.addOperation {
            guard let sessionToken = uploadManager.appManager.session?.sessionToken else {
                debugPrint("Unable to request an upload URL from Bridge--not logged in to an account.")
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
    
    public func notifyBridgeUploadSucceeded(relativePath: String, uploadMetadata: BridgeFileUploadMetadataBlob) {
        guard let notifyUrl = self.notifyBridgeUrlString(for: uploadMetadata) else {
            debugPrint("Unexpected: Could not get URL to notify Bridge of upload success from file upload metadata: \(uploadMetadata)")
            return
        }
        
        // throw this over to the main queue so we can access Kotlin stuff
        OperationQueue.main.addOperation {
            guard let sessionToken = uploadManager.appManager.session?.sessionToken else {
                debugPrint("Unable to notify Bridge of upload success--not logged in to an account.")
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
public class BridgeFileUploadManager: NSObject, URLSessionBackgroundDelegate {
    /// A singleton instance of the manager.
    public static let shared = BridgeFileUploadManager()
    
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
    var appManager: BridgeClientAppManager! {
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
        
        // Set up a listener to retry temporarily-failed uploads whenever the app becomes active
        NotificationCenter.default.addObserver(forName: UIApplication.didBecomeActiveNotification, object: nil, queue: nil) { notification in
            self.checkAndRetryOrphanedUploads()
            self.retryUploadsAfterDelay()
        }
        
        // Also do it right away
        self.checkAndRetryOrphanedUploads()
        self.retryUploadsAfterDelay()
    }
    
    fileprivate func touch(fileUrl: URL) {
        let coordinator = NSFileCoordinator(filePresenter: nil)
        coordinator.coordinate(writingItemAt: fileUrl, options: .contentIndependentMetadataOnly, error: nil) { (writeUrl) in
            do {
                try FileManager.default.setAttributes([.modificationDate : Date()], ofItemAtPath: writeUrl.path)
            } catch let err {
                debugPrint("FileManager failed to update the modification date of \(fileUrl): \(err)")
            }
        }
    }
    
    fileprivate func modificationDate(of fileUrl: URL) -> Date? {
        let coordinator = NSFileCoordinator(filePresenter: nil)
        var modDate: Date? = nil
        coordinator.coordinate(readingItemAt: fileUrl, options: .immediatelyAvailableMetadataOnly, error: nil) { (readUrl) in
            do {
                let attributes = try FileManager.default.attributesOfItem(atPath: readUrl.path)
                modDate = attributes[.modificationDate] as? Date
            } catch let err {
                debugPrint("FileManager failed to read the modification date of \(fileUrl): \(err)")
            }
        }
        return modDate
    }
    
    fileprivate func tempFileFor(inFileURL: URL, uploadApi: BridgeFileUploadAPI) -> URL? {
        // Normalize the file url--i.e. /private/var-->/var (see docs for
        // resolvingSymlinksInPath, which removes /private as a special case
        // even though /var is actually a symlink to /private/var in this case).
        let fileURL = inFileURL.resolvingSymlinksInPath()
        
        let filePath = fileURL.path
        
        // Use a UUID for the temp file's name
        let tempFileURL = uploadApi.tempUploadDirURL.appendingPathComponent(UUID().uuidString)
        
        // ...and get its sandbox-relative part since there are circumstances under
        // which the full path might change (e.g. app update, or during debugging--
        // sim vs device, subsequent run of the same app after a new build)
        let invariantTempFilePath = self.sandboxRelativePath(of: tempFileURL.path)

        // Use a NSFileCoordinator to make a temp local copy so the app can delete
        // the original as soon as the upload call returns.
        let coordinator = NSFileCoordinator(filePresenter: nil)
        var coordError: NSError?
        var copyError: Any?
        coordinator.coordinate(readingItemAt: fileURL, options: .forUploading, writingItemAt: tempFileURL, options: NSFileCoordinator.WritingOptions(rawValue: 0), error: &coordError) { (readURL, writeURL) in
            do {
                try FileManager.default.copyItem(at: readURL, to: writeURL)
            } catch let err {
                debugPrint("Error copying Participant File \(fileURL) to temp file \(String(describing: invariantTempFilePath)) for upload: \(err)")
                copyError = err
            }
        }
        if copyError != nil {
            return nil
        }
        if let err = coordError {
            debugPrint("File coordinator error copying Participant File \(fileURL) to temp file \(String(describing: invariantTempFilePath)) for upload: \(err)")
            return nil
        }
        
        // "touch" the temp file for retry accounting purposes
        self.touch(fileUrl: tempFileURL)
        
        // Keep track of what file it's a copy of.
        self.persistMapping(from: invariantTempFilePath, to: filePath, defaultsKey: self.bridgeFileUploadsKey)
        
        return tempFileURL
    }
    
    fileprivate func persistMapping<T>(from key: String, to value: T, defaultsKey: String) where T: Encodable {
        let block = {
            var mappings = self.userDefaults.dictionary(forKey: defaultsKey) ?? [String : Any]()
            var plistValue: Any
            do {
                plistValue = try DictionaryEncoder().encode(value)
            } catch let error {
                debugPrint("Error attempting to encode \(T.self) to plist object: \(error)")
                return
            }
            mappings[key] = plistValue
            self.userDefaults.setValue(mappings, forKey: defaultsKey)
        }
        
        if OperationQueue.current == self.uploadQueue {
            block()
        }
        else {
            self.uploadQueue.addOperation(block)
        }
    }
    
    @discardableResult
    func removeMapping<T>(_ type: T.Type, from key: String, defaultsKey: String) -> T? where T: Decodable {
        var mapping: T?
        let block = {
            var mappings = self.userDefaults.dictionary(forKey: defaultsKey)
            if let mappingPlist = mappings?.removeValue(forKey: key) {
                do {
                    mapping = try DictionaryDecoder().decode(type, from: mappingPlist)
                } catch let error {
                    debugPrint("Error attempting to decode plist object to \(T.self):\n\(mappingPlist)\n\(error)")
                }
            }
            if mappings != nil {
                self.userDefaults.setValue(mappings, forKey: defaultsKey)
            }
        }
        if OperationQueue.current == self.uploadQueue {
            block()
        }
        else {
            self.uploadQueue.addOperations( [BlockOperation(block: block)], waitUntilFinished: true)
        }
        
        return mapping
    }
    
    fileprivate func retrieveMapping<T>(_ type: T.Type, from key: String, mappings: [String : Any]?) -> T? where T: Decodable {
        var mapping: T?
        let block = {
            if let mappingPlist = mappings?[key] {
                do {
                    mapping = try DictionaryDecoder().decode(type, from: mappingPlist)
                } catch let error {
                    debugPrint("Error attempting to decode plist object to \(T.self):\n\(mappingPlist)\n\(error)")
                }
            }
        }
        if OperationQueue.current == self.uploadQueue {
            block()
        }
        else {
            self.uploadQueue.addOperations( [BlockOperation(block: block)], waitUntilFinished: true)
        }

        return mapping
    }

    
    func resetMappings(for defaultsKey: String) {
        let block = {
            self.userDefaults.removeObject(forKey: defaultsKey)
        }
        
        if OperationQueue.current == self.uploadQueue {
            block()
        }
        else {
            self.uploadQueue.addOperation(block)
        }
    }
    
    // This func resets the state of the BridgeFileUploadManager, including clearing out all mappings
    // and deleting all temp files.
    // You shouldn't call this directly except in test cases; if you want to put the brakes on all pending
    // uploads, you should invalidate the URLSession associated with this manager, which will cause this
    // to get called.
    func reset() {
        let block = {
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
        
        if OperationQueue.current == self.uploadQueue {
            block()
        }
        else {
            self.uploadQueue.addOperation(block)
        }
    }
    
    fileprivate func mimeTypeFor(fileUrl: URL) -> String {
        if #available(iOS 14.0, *) {
            guard let typeRef = UTTypeReference(filenameExtension: fileUrl.pathExtension),
                  let mimeType = typeRef.preferredMIMEType else {
                return "application/octet-stream"
            }
            return mimeType
        } else {
            guard let UTI = UTTypeCreatePreferredIdentifierForTag(kUTTagClassFilenameExtension, fileUrl.pathExtension as CFString, nil),
                  let mimeType = UTTypeCopyPreferredTagWithClass(UTI as! CFString, kUTTagClassMIMEType)?.takeUnretainedValue() else {
                return "application/octet-stream"
            }
            return mimeType as String
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
    func upload<T>(_ trackingType: T.Type, uploadApi: BridgeFileUploadAPI, fileId: String, fileUrl: URL, contentType: String? = nil, extras: Codable? = nil) where T: Codable {
        uploadInternal(trackingType, uploadApi: uploadApi, fileId: fileId, fileUrl: fileUrl, contentType: contentType, extras: extras)
        return
    }
    
    // Internal function returns temp file URL for tests, or nil on pre-flight check failures.
    // Should not be called directly except from unit/integration test cases.
    @discardableResult
    func uploadInternal<T>(_ trackingType: T.Type, uploadApi: BridgeFileUploadAPI, fileId: String, fileUrl: URL, contentType: String? = nil, extras: Codable? = nil) -> URL? where T: Codable {
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
            debugPrint("Error: requestUploadURL called with original fileURL as nil")
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
                debugPrint("Error trying to set extended attributes for temp file \(fileUrl): \(err)")
                return nil
            }
                
            invariantFilePath = self.sandboxRelativePath(of: tempFile.path)
        }
        else {
            // we already have the file copy--create a URL from its path
            let filePath = self.fullyQualifiedPath(of: invariantFilePath!)
            if filePath.isEmpty {
                debugPrint("Error: unable to get fully qualified path from invariantFilePath '\(invariantFilePath!)'")
                return nil
            }
            
            fileCopy = URL(fileURLWithPath: filePath)
            guard let fileCopy = fileCopy else {
                debugPrint("Error: unable to create URL from file path '\(filePath)'")
                return nil
            }
            
            // "touch" the temp file for retry accounting purposes
            self.touch(fileUrl: fileCopy)
            
            // Keep track of what file it's a copy of.
            self.persistMapping(from: invariantFilePath!, to: fileUrl.path, defaultsKey: self.bridgeFileUploadsKey)
        }
        
        guard let invariantFilePath = invariantFilePath else {
            debugPrint("Failed to get sandbox-relative file path from temp file URL")
            return nil
        }
        
        // Send the request to Bridge
        uploadApi.sendUploadRequest(for: invariantFilePath, uploadMetadata: uploadMetadata)
        
        return fileCopy
    }
    
    /// Download delegate method.
    public func urlSession(_ session: URLSession, downloadTask: URLSessionDownloadTask, didFinishDownloadingTo location: URL) {
        // get the sandbox-relative path to the temp copy of the participant file
        guard let invariantFilePath = downloadTask.taskDescription else {
            debugPrint("Unexpected: Finished a download task with no taskDescription set")
            return
        }
        
        // get which API this task is using
        guard let uploadApi = self.uploadApi(for: downloadTask.originalRequest?.url) else  {
            debugPrint("Unexpected: No uploadApi registered for download task \(downloadTask) (url: \(String(describing: downloadTask.originalRequest?.url)))")
            return
        }
        
        // Read the downloaded JSON file into a String, and then convert that to a Data object
        var urlContents: String
        do {
            urlContents = try String(contentsOf: location)
        } catch let err {
            debugPrint("Error attempting to read contents from background download task at URL \(location) as String: \(err)")
            return
        }
        
        // check for HTTP errors (we might succeed in "downloading a file" where the "file"
        // in question is just the error response body)
        if let httpResponse = downloadTask.response as? HTTPURLResponse,
           httpResponse.statusCode >= 400 {
            debugPrint("Request to Bridge endpoint \(String(describing: downloadTask.originalRequest?.url)) for temp file \(invariantFilePath) failed with status \(httpResponse.statusCode) and response body:\n\(urlContents)")
            
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
                debugPrint("Unexpected: Unable to retrieve upload metadata for \(invariantFilePath) from either upload request map or notifying Bridge map.")
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
            debugPrint("Unexpected: Download task finished successfully but string from downloaded file at URL \(location) is empty")
            return
        }
        
        guard let jsonData = urlContents.data(using: .utf8) else {
            debugPrint("Unexpected: Could not convert string contents of downloaded file at URL \(location) to data using .utf8 encoding: \"\(urlContents)\"")
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
            debugPrint("Unexpected: Could not get S3 upload URL from file upload metadata: \(bridgeUploadMetadata)")
            return
        }
        
        // get the fully-qualified path of the file to be uploaded
        let filePath = self.fullyQualifiedPath(of: invariantFilePath)
        if filePath.isEmpty {
            debugPrint("Unable to recover fully qualified path from sandbox-relative path \"\(invariantFilePath)\"")
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
    public func retryUploadsAfterDelay() {
        self.uploadQueue.addOperation {
            guard var retryUploads = self.userDefaults.dictionary(forKey: self.retryUploadsKey) else { return }
            for filePath in retryUploads.keys {
                autoreleasepool {
                    guard let uploadApi = self.apiFromXAttrs(for: filePath) else {
                        debugPrint("Unexpected: couldn't retrieve API from temp file xattrs for \(filePath)")
                        return
                    }
                    
                    if uploadApi.retryIfReady(relativePath: filePath, mappings: &retryUploads) {
                        self.userDefaults.setValue(retryUploads, forKey: self.retryUploadsKey)
                    }
                }
            }
        }
    }
    
    fileprivate func cancelTasks(for relativePath: String, tasks: [URLSessionTask]) -> [URLSessionTask] {
        var notCanceledTasks = [URLSessionTask]()
        for task in tasks {
            if task.description != relativePath {
                notCanceledTasks.append(task)
                continue
            }
            task.cancel()
        }
        return notCanceledTasks
    }
    
    /// Call this function to check for and retry any orphaned uploads.
    public func checkAndRetryOrphanedUploads() {
        // App extensions are severely memory constrained, so don't even try this if we're in one.
        guard !self.netManager.isRunningInAppExtension() else { return }
        self.netManager.backgroundSession().getAllTasks { tasks in
            var tasks = tasks
            let defaults = self.userDefaults
            let oneDay: TimeInterval = 60 * 60 * 24
            
            // Get the set of all temp files for which there is a currently-active background
            // URLSession task.
            let filesInFlight = tasks.rsd_flatMapSet { task in
                task.description
            }
            
            // Get the mappings from temp file to original file for all in-progress uploads.
            let fileUploads = defaults.dictionary(forKey: self.bridgeFileUploadsKey) ?? [String : Any]()
            
            // Assume uploads in the uploadURLsRequested map that are more than 24 hours old
            // are orphaned. Note that under some unusual circumstances this may lead to
            // duplication of uploads.
            let uploadURLsRequested = defaults.dictionary(forKey: self.uploadURLsRequestedKey) ?? [String : Any]()
            for invariantFilePath in uploadURLsRequested.keys {
                guard let api = self.apiFromXAttrs(for: invariantFilePath) else { continue }
                guard let metadataBlob = api.retrieveMetadata(from: invariantFilePath, mappings: uploadURLsRequested) else { continue }
                // Assume files with an active urlsession task are not (yet) orphaned, no matter how old.
                guard !filesInFlight.contains(invariantFilePath) else { continue }
                let fullPath = self.fullyQualifiedPath(of: invariantFilePath)
                let fileUrl = URL(fileURLWithPath: fullPath)
                guard let modDate = self.modificationDate(of: fileUrl) else { continue }
                guard Date().timeIntervalSince(modDate) > oneDay else { continue }
                
                // If we get all the way here, touch the file to reset the orphanage clock
                // and then send the upload request again.
                self.touch(fileUrl: fileUrl)
                api.sendUploadRequest(for: invariantFilePath, uploadMetadata: metadataBlob)
            }
            
            // Assume any uploads in the uploadingToS3 map whose sessions are at or past their
            // expiration datetime are orphaned.
            let uploadingToS3 = defaults.dictionary(forKey: self.uploadingToS3Key) ?? [String : Any]()
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
            for invariantFilePath in notifyingBridge.keys {
                guard let api = self.apiFromXAttrs(for: invariantFilePath) else { continue }
                guard let metadataBlob = api.retrieveMetadata(from: invariantFilePath, mappings: notifyingBridge) else { continue }
                // Assume files with an active urlsession task are not (yet) orphaned, no matter how old.
                guard !filesInFlight.contains(invariantFilePath) else { continue }
                let fullPath = self.fullyQualifiedPath(of: invariantFilePath)
                let fileUrl = URL(fileURLWithPath: fullPath)
                guard let modDate = self.modificationDate(of: fileUrl) else { continue }
                guard Date().timeIntervalSince(modDate) > oneDay else { continue }
                
                // If we get all the way here, touch the file to reset the orphanage clock
                // and then send the notify request again.
                self.touch(fileUrl: fileUrl)
                api.notifyBridgeUploadSucceeded(relativePath: invariantFilePath, uploadMetadata: metadataBlob)
            }
            
            // Assume any uploads in the bridgeFileUploads map which are not in any other map
            // and have no in-flight tasks are orphaned.
            for invariantFilePath in fileUploads.keys {
                guard !filesInFlight.contains(invariantFilePath) else { continue }
                guard !uploadURLsRequested.keys.contains(invariantFilePath) else { continue }
                guard !uploadingToS3.keys.contains(invariantFilePath) else { continue }
                guard !notifyingBridge.keys.contains(invariantFilePath) else { continue }
                guard let originalFilePath = self.retrieveMapping(String.self, from: invariantFilePath, mappings: fileUploads) else { continue }
                guard let (api, fileId, mimeType, extras) = self.apiInfoFromXAttrs(for: invariantFilePath) else { continue }
                // get the upload metadata using the temp file URL (as the original file likely no longer exists)
                let fullPath = self.fullyQualifiedPath(of: invariantFilePath)
                let fileUrl = URL(fileURLWithPath: fullPath)
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
            for fileUrl in allFiles {
                let invariantFilePath = self.sandboxRelativePath(of: fileUrl.path)
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
    fileprivate func handleHTTPDownloadStatusCode(_ statusCode: Int, uploadApi: BridgeFileUploadAPI, downloadTask: URLSessionDownloadTask, invariantFilePath: String) {
        
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
                debugPrint("Unexpected: Unable to retrieve BridgeFileUploadMetadataBlob for \(String(describing: invariantFilePath))")
                return
        }

        // remove the file from the temp -> orig mappings, and retrieve the original file path
        guard let originalFilePath = removeMapping(String.self, from: invariantFilePath, defaultsKey: self.bridgeFileUploadsKey) else {
            debugPrint("Unexpected: No original file path found mapped from temp file path \(invariantFilePath)")
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
        NotificationCenter.default.post(failedNotification)
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
            debugPrint("Participant file upload to S3 of file \(originalFilePath) failed with HTTP response status code \(statusCode)--unhandled, will not retry")
            
            // post a notification that the file upload to S3 failed unrecoverably
            let uploadFailedNotification = uploadApi.uploadToS3FailedNotification(for: uploadMetadata)
            cleanUpTempFile(filePath: tempFilePath)
            NotificationCenter.default.post(uploadFailedNotification)
        }
    }

    /// Task delegate method.
    public func urlSession(_ session: URLSession, task: URLSessionTask, didCompleteWithError error: Error?) {
        
        // get the sandbox-relative path to the temp copy of the participant file
        guard let invariantFilePath = task.taskDescription else {
            debugPrint("Unexpected: Finished a background session task with no taskDescription set")
            return
        }
        
        // check that the file still exists before going any further; if we just
        // got done notifying Bridge of success, then it won't, and we're done.
        let fullPath = self.fullyQualifiedPath(of: invariantFilePath)
        guard FileManager.default.fileExists(atPath: fullPath) else {
            return
        }
        
        // get which API this task is using from the temp copy's xattrs
        guard let uploadApi = self.apiFromXAttrs(for: invariantFilePath) else  {
            debugPrint("Unexpected: No uploadApi marked for temp file \(invariantFilePath)")
            return
        }

        if let downloadTask = task as? URLSessionDownloadTask {
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
            debugPrint("Unexpected: No BridgeFileUploadMetadataBlob found mapped for temp file \(invariantFilePath)")
            return
        }
        
        // remove the file from the temp -> orig mappings, and retrieve the original file path
        guard let originalFilePath = removeMapping(String.self, from: invariantFilePath, defaultsKey: self.bridgeFileUploadsKey) else {
            debugPrint("Unexpected: No original file path found mapped from temp file path \(invariantFilePath)")
            return
        }
        
        // remove the file from the retry queue if it's in there (as it might be if an URLSession was invalidated
        // due to an error)
        
        uploadApi.dequeueForRetry(relativePath: invariantFilePath)
        
        // any error that makes it all the way through to here would be the result of something like a
        // malformed request, so log it, post a failed upload notification, clean up the temp file,
        // and bail out
        if let error = error {
            debugPrint("Error uploading file \(originalFilePath) to S3: \(error)")
            let uploadFailedNotification = uploadApi.uploadToS3FailedNotification(for: uploadMetadata)
            cleanUpTempFile(filePath: invariantFilePath)
            NotificationCenter.default.post(uploadFailedNotification)
            return
        }
        
        // check the response for HTTP errors and handle accordingly
        guard let httpResponse = task.response as? HTTPURLResponse else {
            debugPrint("Unexpected: Upload task response is not an HTTPURLResponse")
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
        NotificationCenter.default.post(uploadedNotification)
    }
    
    /// Session delegate method.
    public func urlSession(_ session: URLSession, didBecomeInvalidWithError error: Error?) {
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
        let block = {
            guard let originalFilePaths = self.userDefaults.dictionary(forKey: self.bridgeFileUploadsKey) else {
                // nothing to see here, move along
                return
            }
            
            let uploadsRequested = self.userDefaults.dictionary(forKey: self.uploadURLsRequestedKey)
            let uploadsToS3 = self.userDefaults.dictionary(forKey: self.uploadingToS3Key)
            
            // Get the temp copy and original file path for each file currently in the upload process and
            // copy it to the upload queue with its s3 metadata.
            for invariantFilePath in originalFilePaths.keys {
                guard let uploadApi = self.apiFromXAttrs(for: invariantFilePath) else {
                    debugPrint("Unexpected: couldn't retrieve API from temp file xattrs for \(invariantFilePath)")
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
        
        if OperationQueue.current == self.uploadQueue {
            block()
        }
        else {
            self.uploadQueue.addOperation(block)
        }
    }

    func apiFromXAttrs(for filePath: String) -> BridgeFileUploadAPI? {
        let (uploadApi, _, _, _) = self.apiInfoFromXAttrs(for: filePath) ?? (nil, nil, nil, nil)
        return uploadApi
    }
    
    func apiInfoFromXAttrs(for filePath: String) -> (uploadApi: BridgeFileUploadAPI, fileId: String, contentType: String, extras: Codable?)? {
        let fullPath = self.fullyQualifiedPath(of: filePath)
        guard FileManager.default.fileExists(atPath: fullPath) else {
            debugPrint("Unexpected: Attempting to retrieve upload API info for temp file with invariant path '\(filePath) but temp file does not exist at '\(fullPath)")
            return nil
        }
        let tempFile = URL(fileURLWithPath: fullPath)
        var apiStringData: Data
        var fileIdData: Data
        var contentTypeData: Data
        var extrasData: Data?
        do {
            apiStringData = try tempFile.extendedAttribute(forName: self.uploadApiAttributeName)
            fileIdData = try tempFile.extendedAttribute(forName: self.fileIdAttributeName)
            contentTypeData = try tempFile.extendedAttribute(forName: self.contentTypeAttributeName)
        } catch let err {
            debugPrint("Error attempting to retrieve xattrs \(self.uploadApiAttributeName), \(self.fileIdAttributeName), and \(self.contentTypeAttributeName) from file at \(fullPath): \(err)")
            return nil
        }
        // extras is an optional attribute so we don't care if it isn't present
        extrasData = try? tempFile.extendedAttribute(forName: self.uploadExtrasAttributeName)
        
        guard let apiString = String(data: apiStringData, encoding: .utf8) else {
            debugPrint("Unexpected: Could not convert apiStringData to a utf8 string: \(apiStringData)")
            return nil
        }
        guard let api = self.bridgeFileUploadApis[apiString] else {
            debugPrint("Unexpected: Could not retrieve BridgeFileUploadAPI for \(apiString) from list of registered upload APIs")
            return nil
        }
        guard let fileId = String(data: fileIdData, encoding: .utf8) else {
            debugPrint("Unexpected: Could not convert fileIdData to a utf8 string: \(fileIdData)")
            return nil
        }
        guard let contentType = String(data: contentTypeData, encoding: .utf8) else {
            debugPrint("Unexpected: Could not convert contentTypeData to a utf8 string: \(contentTypeData)")
            return nil
        }
        let extras = api.uploadRequestExtras(from: extrasData)

        return (uploadApi: api, fileId: fileId, contentType: contentType, extras: extras)
    }
    
    func cleanUpTempFile(filePath: String) {
        let block = {
            let fullPath = self.fullyQualifiedPath(of: filePath)
            guard FileManager.default.fileExists(atPath: fullPath) else {
                debugPrint("Unexpected: Attempting to clean up temp file with invariant path '\(filePath) but temp file does not exist at '\(fullPath)")
                return
            }
            let tempFile = URL(fileURLWithPath: fullPath)
            let coordinator = NSFileCoordinator(filePresenter: nil)
            var fileCoordinatorError: NSError?
            coordinator.coordinate(writingItemAt: tempFile, options: .forDeleting, error: &fileCoordinatorError) { fileUrl in
                do {
                    try FileManager.default.removeItem(at: fileUrl)
                } catch let err {
                    debugPrint("Error attempting to remove file at \(fileUrl): \(err)")
                }
            }
            if let fileCoordinatorError = fileCoordinatorError {
                debugPrint("Error coordinating deletion of file \(tempFile): \(fileCoordinatorError)")
            }
        }

        if OperationQueue.current == self.uploadQueue {
            block()
        }
        else {
            self.uploadQueue.addOperation(block)
        }
    }
    
    /// MARK: Handle converting between sandbox-relative and fully-qualified file paths.
    private lazy var baseDirectory: String = {
        var baseDirectory: String
        if let appGroupIdentifier = IOSBridgeConfig().appGroupIdentifier, appGroupIdentifier.count > 0, let baseDirUrl = FileManager.default.containerURL(forSecurityApplicationGroupIdentifier: appGroupIdentifier) {
            // normalize the path--i.e. /private/var-->/var (see docs for URL.resolvingSymlinksInPath, which removes /private as a special case
            // even though /var is actually a symlink to /private/var in this case)
            baseDirectory = baseDirUrl.resolvingSymlinksInPath().path
        }
        else {
            baseDirectory = NSHomeDirectory()
        }
        return baseDirectory
    }()
    
    private lazy var sandboxRegex: String = {
        let UUIDRegexPattern = "[0-9a-fA-F]{8}-[0-9a-fA-F]{4}-[0-9a-fA-F]{4}-[0-9a-fA-F]{4}-[0-9a-fA-F]{12}"
        let sandboxPath = self.baseDirectory
        // simulator and device have the app uuid in a different location in the path,
        // and it might change in the future, so:
        let rangeOfLastUUID = sandboxPath.range(of: UUIDRegexPattern, options: [.regularExpression, .backwards])
        let beforeUUID = sandboxPath[..<(rangeOfLastUUID?.lowerBound ?? sandboxPath.startIndex)]
        let afterUUID = sandboxPath[(rangeOfLastUUID?.upperBound ?? sandboxPath.startIndex)...]
        var regex = "^"
        if beforeUUID.count > 0 {
            regex.append("\\Q\(beforeUUID)\\E")
        }
        regex.append(UUIDRegexPattern)
        if afterUUID.count > 0 {
            regex.append("\\Q\(afterUUID)\\E")
        }
        return regex
    }()
    
    func sandboxRelativePath(of path: String) -> String {
        // normalize the path--i.e. /private/var-->/var (see docs for URL.resolvingSymlinksInPath, which removes /private as a special case
        // even though /var is actually a symlink to /private/var in this case)
        let normalizedPath = URL(fileURLWithPath: path).resolvingSymlinksInPath().path
        let range = normalizedPath.range(of: self.sandboxRegex, options: [.regularExpression])
        // if it didn't match the sandbox regex, this will just give back normalizedPath
        return String(normalizedPath[(range?.upperBound ?? normalizedPath.startIndex)...])
    }
    
    func fullyQualifiedPath(of path: String) -> String {
        // normalize the path--i.e. /private/var-->/var (see docs for URL.resolvingSymlinksInPath, which removes /private as a special case
        // even though /var is actually a symlink to /private/var in this case)
        let normalizedPath = URL(fileURLWithPath: path).resolvingSymlinksInPath().path

        // check if it's already a full path first
        guard let range = normalizedPath.range(of: self.sandboxRegex, options: [.regularExpression]), !range.isEmpty else {
            // nope, not already a full path
            return (self.baseDirectory as NSString).appendingPathComponent(path) as String
        }
        
        // if we matched the sandboxRegex it was a full path already
        // so just return the normalized version of it.
        return normalizedPath
    }

}

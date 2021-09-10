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
import UniformTypeIdentifiers
import CoreServices
import BridgeClient

public struct ParticipantFile: Codable {
    var fileId : String?
    var mimeType: String
    var createdOn: Date?
    var downloadUrl: String?
    var uploadUrl: String?
    var expiresOn: Date?
    var type: String = "ParticipantFile"
}

struct BridgeFileUploadMetadata<T>: Codable where T: Codable {
    var bridgeUploadObject: T
    var s3Headers: [String : String]
}

struct BridgeFileRetryInfo<T>: Codable where T: Codable {
    var apiString: String
    var originalFilePath: String
    var uploadMetadata: BridgeFileUploadMetadata<T>
    var whenToRetry: Date
}

/// Dictionary encoder/decoder adapted from https://stackoverflow.com/a/52182418
class DictionaryEncoder {
    private let jsonEncoder = BridgeJsonParser.jsonEncoder

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
    private let jsonDecoder = BridgeJsonParser.jsonDecoder

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

        let data = try self.withUnsafeFileSystemRepresentation { fileSystemPath -> Data in

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
        return data
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

        let list = try self.withUnsafeFileSystemRepresentation { fileSystemPath -> [String] in
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
        return list
    }

    /// Helper function to create an NSError from a Unix errno.
    private static func posixError(_ err: Int32) -> NSError {
        return NSError(domain: NSPOSIXErrorDomain, code: Int(err),
                       userInfo: [NSLocalizedDescriptionKey: String(cString: strerror(err))])
    }
}

extension Notification.Name {
    /// Notification name posted by the `BridgeFileUploadManager` when a participant file upload completes.
    public static let SBBParticipantFileUploaded = Notification.Name(rawValue: "SBBParticipantFileUploaded")
    
    /// Notification name posted by the `BridgeFileUploadManager` when a participant file upload request to Bridge fails.
    public static let SBBParticipantFileUploadRequestFailed = Notification.Name(rawValue: "SBBParticipantFileUploadRequestFailed")
    
    /// Notification name posted by the `BridgeFileUploadManager` when a participant file upload attempt to S3 fails unrecoverably.
    public static let SBBParticipantFileUploadToS3Failed = Notification.Name(rawValue: "SBBParticipantFileUploadToS3Failed")
}

/// BridgeFileUploadAPI is a protocol for BridgeFileUploadManager to call for a given Bridge API as it
/// progresses through the upload dance.  To support a new Bridge file upload API, create a class
/// that implements this protocol to handle the peculiarities of that particular API, and register an instance
/// of it with the singleton BridgeFileUploadManager for that API.
/// The associated type T is the Swift (Codable) type of the object the particular API uses to pass parameters
/// back and forth.
protocol BridgeFileUploadAPI {
    associatedtype T where T: Codable
    
    /// A partial URL path that uniquely and completely identifies the particular Bridge upload API.
    let apiString: String
    
    /// Where to keep temporary copies of files being uploaded via this upload API.
    /// Typically this would be a subdirectory of the Application Support Directory.
    let tempUploadDirURL: URL
    
    /// A flag indicating whether or not this particular upload API expects to be notified once
    /// the file has been successfully uploaded to S3.
    let notifiesBridgeWhenUploaded: Bool
    
    /// Create an instance of BridgeFileUploadMetadata for a file upload.
    /// The bridgeUploadObject field should contain an instance of type T, filled in for the original request to Bridge.
    /// The s3Headers dictionary should contain the HTTP headers that will be needed for the S3 upload.
    func uploadMetadata(for fileId: String, fileURL: URL, mimeType: String) -> BridgeFileUploadMetadata<T>
    
    /// Return the fileId for the given uploadMetadata.
    func fileId(for uploadMetadata: BridgeFileUploadMetadata<T>) -> String
    
    /// Return the MIME type for the given uploadMetadata.
    func mimeType(for uploadMetadata: BridgeFileUploadMetadata<T>) -> String
    
    /// Return the URL string at which BridgeFileUploadManager should request an upload.
    func uploadRequestUrlString(for uploadMetadata: BridgeFileUploadMetadata<T>) -> String
    
    /// Return the S3 pre-signed URL string to which BridgeFileUploadManager should PUT the file.
    func s3UploadUrlString(for uploadMetadata: BridgeFileUploadMetadata<T>) -> String
    
    /// Return the HTTP headers which BridgeFileUploadManager should set when uploading
    /// the file to S3.
    func s3UploadHeaders(for uploadMetadata: BridgeFileUploadMetadata<T>) -> [String : String]
    
    /// Return a Notification object to be posted to the default NotificationCenter upon
    /// successful completion of the file upload process.
    func fileUploadedNotification(for uploadMetadata: BridgeFileUploadMetadata<T>) -> Notification
    
    /// Return a Notification object to be posted to the default NotificationCenter upon
    /// unrecoverable failure to notify Bridge that the file was successfully uploaded to S3.
    /// Default implementation returns nil. Upload APIs where notifiesBridgeWhenUploaded is true
    /// can override this method to return an appropriate notification if the API cares.
    func reportingUploadToBridgeFailedNotification(for uploadMetadata: BridgeFileUploadMetadata<T>) -> Notification?
    
    /// Return a Notification object to be posted to the default NotificationCenter upon
    /// unrecoverable failure to upload the file to S3.
    func uploadToS3FailedNotification(for uploadMetadata: BridgeFileUploadMetadata<T>) -> Notification
    
    /// Return a Notification object to be posted to the default NotificationCenter upon
    /// unrecoverable failure to request an upload URL from Bridge.
    func uploadRequestFailedNotification(for uploadMetadata: BridgeFileUploadMetadata<T>) -> Notification?
}

extension BridgeFileUploadAPI<T> {
    /// Access the associated type.
    let bridgeUploadObjectType: Type = T
    
    /// Default implementation for upload APIs that don't involve notifying Bridge when done.
    func reportingUploadToBridgeFailedNotification(for uploadMetadata: BridgeFileUploadMetadata<T>) -> Notification? {
        return nil
    }

    /// This method is the public face of the Bridge upload APIs.
    final public func upload(fileId: String, fileUrl: URL, contentType: String? = nil) {
        BridgeFileUploadManager.shared.upload(uploadApi: self, fileId: fileId, fileUrl: fileUrl, contentType: contentType)
    }
}

/// The BridgeFileUploadManager handles uploading files to Bridge using an iOS URLSession
/// background session. This allows iOS to deal with any connectivity issues and lets the upload proceed
/// even when the app is suspended.
class BridgeFileUploadManager: NSObject, URLSessionBackgroundDelegate {
    
    /// A singleton instance of the manager.
    public static let shared = BridgeFileUploadManager()
    
    /// The extended file attribute for which API is to be used to upload the file.
    let uploadApiAttributeName = "org.sagebionetworks.bridge.uploadApi"
    
    /// The extended file attribute for the fileId to which this file is being uploaded.
    let fileIdAttributeName = "org.sagebionetworks.bridge.fileId"
    
    /// The extended file attribute for the content (MIME) type of the file being uploaded.
    let contentTypeAttributeName = "org.sagebionetworks.bridge.contentType"
    
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
    
    /// The Notification.userInfo key for the uploaded file's upload object from Bridge.
    let bridgeUploadObjectKey = "BridgeUploadObject"
    
    /// The Notification.userInfo key for the uploaded file's original (on-device) path.
    let filePathKey = "FilePath"
    
    /// The Notification.userInfo key for a failed upload/download HTTP status.
    let httpStatusKey = "HttpStatus"
    
    /// The Notification.userInfo key for a failed download HTTPResponse body.
    let responseBodyKey = "ResponseBody"
    
    /// The Notification.userInfo key for the Bridge API URL at which one can (with appropriate authentication headers)
    /// DELETE the uploaded file, or GET it back (via redirect).
    let requestUrlKey = "RequestUrl"
    
    /// A mapping for implementation-specific details for each registered Bridge upload API.
    let bridgeFileUploadApis = [String : BridgeFileUploadAPI]
    
    /// The minimum delay before retrying a failed upload (in seconds).
    var delayForRetry: TimeInterval = 5 * 60
    
    /// BridgeFileUploadManager uses the BackgroundNetworkManager singleton to manage its background URLSession tasks.
    let netManager: BackgroundNetworkManager
    
    /// Where to store our copies of the files being uploaded.
    let tempUploadDirURL: URL
    
    /// Serial queue for updates to temp file -> original file mappings and upload process state.
    let uploadQueue: OperationQueue

    /// Private initializer so only the singleton can ever get created.
    private override init() {
        netManager = BackgroundNetworkManager.shared
        
        guard let appSupportDir = FileManager.default.urls(for: FileManager.SearchPathDirectory.applicationSupportDirectory, in: FileManager.SearchPathDomainMask.userDomainMask).first
        else {
            fatalError("BridgeFileUploadManager unable to generate participant file temp upload dir URL from app support directory")
        }
        
        self.tempUploadDirURL = appSupportDir.appendingPathComponent("ParticipantFileUploads")
        do {
            try FileManager.default.createDirectory(at: self.tempUploadDirURL, withIntermediateDirectories: true, attributes: nil)
        } catch let err {
            fatalError("BridgeFileUploadManager unable to create participant file temp upload dir: \(err)")
        }
        
        self.uploadQueue = self.netManager.backgroundSession().delegateQueue
        
        super.init()
        
        self.netManager.backgroundTransferDelegate = self
        
        // Set up a listener to retry temporarily-failed uploads whenever the app becomes active
        NotificationCenter.default.addObserver(forName: UIApplication.didBecomeActiveNotification, object: nil, queue: nil) { notification in
            self.retryUploadsAfterDelay()
        }
        
        // Also do it right away
        self.retryUploadsAfterDelay()
    }
    
    fileprivate func tempFileFor(inFileURL: URL) -> URL? {
        // Normalize the file url--i.e. /private/var-->/var (see docs for
        // resolvingSymlinksInPath, which removes /private as a special case
        // even though /var is actually a symlink to /private/var in this case).
        let fileURL = inFileURL.resolvingSymlinksInPath()
        
        let filePath = fileURL.path
        
        // Use a UUID for the temp file's name
        let tempFileURL = self.tempUploadDirURL.appendingPathComponent(UUID().uuidString)
        
        // ...and get its sandbox-relative part since there are circumstances under
        // which the full path might change (e.g. app update, or during debugging--
        // sim vs device, subsequent run of the same app after a new build)
        let invariantTempFilePath = (tempFileURL.path as NSString).sandboxRelativePath()!

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
        coordinator.coordinate(writingItemAt: tempFileURL, options: .contentIndependentMetadataOnly, error: nil) { (writeURL) in
            do {
                try FileManager.default.setAttributes([.modificationDate : Date()], ofItemAtPath: writeURL.path)
            } catch let err {
                debugPrint("FileManager failed to update the modification date of \(tempFileURL): \(err)")
            }
        }
        
        // Keep track of what file it's a copy of.
        self.persistMapping(from: invariantTempFilePath, to: filePath, defaultsKey: self.bridgeFileUploadsKey)
        
        return tempFileURL
    }
    
    fileprivate func persistMapping<T>(from key: String, to value: T, defaultsKey: String) where T: Encodable {
        let block = {
            let userDefaults = BridgeSDK.sharedUserDefaults()
            var mappings = userDefaults.dictionary(forKey: defaultsKey) ?? Dictionary()
            var plistValue: Any
            do {
                plistValue = try DictionaryEncoder().encode(value)
            } catch let error {
                debugPrint("Error attempting to encode \(T.self) to plist object: \(error)")
                return
            }
            mappings[key] = plistValue
            userDefaults.setValue(mappings, forKey: defaultsKey)
        }
        
        if OperationQueue.current == self.uploadQueue {
            block()
        }
        else {
            self.uploadQueue.addOperation(block)
        }
    }
    
    func removeMapping<T>(_ type: T.Type, from key: String, defaultsKey: String) -> T? where T: Decodable {
        var mapping: T?
        let block = {
            let userDefaults = BridgeSDK.sharedUserDefaults()
            var mappings = userDefaults.dictionary(forKey: defaultsKey)
            if let mappingPlist = mappings?.removeValue(forKey: key) {
                do {
                    mapping = try DictionaryDecoder().decode(type, from: mappingPlist)
                } catch let error {
                    debugPrint("Error attempting to decode plist object to \(T.self):\n\(mappingPlist)\n\(error)")
                }
            }
            if mappings != nil {
                userDefaults.setValue(mappings, forKey: defaultsKey)
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
    
    // Only call this on the upload queue
    fileprivate func retrieveMapping<T>(_ type: T.Type, from key: String, mappings: [String : Any]?) -> T? where T: Decodable {
        var mapping: T?
        if let mappingPlist = mappings?[key] {
            do {
                mapping = try DictionaryDecoder().decode(type, from: mappingPlist)
            } catch let error {
                debugPrint("Error attempting to decode plist object to \(T.self):\n\(mappingPlist)\n\(error)")
            }
        }

        return mapping
    }

    
    func resetMappings(for defaultsKey: String) {
        let block = {
            let userDefaults = BridgeSDK.sharedUserDefaults()
            userDefaults.removeObject(forKey: defaultsKey)
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
            let userDefaults = BridgeSDK.sharedUserDefaults()

            // Go through and reset all the mappings, gathering up the temp files that are used as keys
            // so we can delete them afterward.
            var invariantFilePaths = Set<String>()
            for defaultsKey in [
                self.bridgeFileUploadsKey,
                self.uploadURLsRequestedKey,
                self.uploadingToS3Key,
                self.downloadErrorResponseBodyKey,
                self.retryUploadsKey
            ] {
                // add the temp files used as keys in this mapping
                if let filePaths = userDefaults.dictionary(forKey: defaultsKey)?.keys {
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
    public func upload<T>(uploadApi: BridgeFileUploadAPI<T>, fileId: String, fileUrl: URL, contentType: String? = nil) {
        let _ = uploadInternal(uploadApi: uploadApi, fileId: fileId, fileUrl: fileUrl, contentType: contentType)
        return
    }
    
    // Internal function returns temp file URL for tests, or nil on pre-flight check failures.
    // Should not be called directly except from unit/integration test cases.
    func uploadInternal<T>(uploadApi: BridgeFileUploadAPI<T>, fileId: String, fileUrl: URL, contentType: String? = nil) -> URL? {
        // Check if this uploadApi is already registered, and if not, do so
        if !self.bridgeFileUploadApis.keys.contains(uploadApi.apiString) {
            self.bridgeFileUploadApis[uploadApi.apiString] = uploadApi
        }
        
        let mimeType = contentType ?? self.mimeTypeFor(fileUrl: fileUrl)
        
        let uploadMetadata = uploadApi.uploadMetadata(for: fileId, fileURL: fileUrl, mimeType: mimeType)
        
        return self.requestUploadURL(uploadApi: uploadApi, invariantFilePath: nil, fileUrl: fileUrl, uploadMetadata: uploadMetadata)
    }
    
    fileprivate func requestUploadURL<T>(uploadApi: BridgeFileUploadAPI<T>, invariantFilePath: String?, fileUrl: URL?, uploadMetadata: BridgeFileUploadMetadata<T>) -> URL? {
        let bridgeUploadObject = uploadMetadata.bridgeUploadObject
        var invariantFilePath = invariantFilePath
        guard let fileUrl = fileUrl else {
            debugPrint("Error: requestUploadURL called with original fileURL as nil")
            return nil
        }

        // if no invariant file path was passed in, make a temp local copy of the file at fileUrl and use that
        var fileCopy: URL? = nil
        if invariantFilePath == nil {
            guard let tempFile = self.tempFileFor(inFileURL: fileUrl) else { return nil }
            fileCopy = tempFile
            
            // Set extended attributes on the temp file so we have enough info to retry the upload
            // if all else fails and all we have to work from is the temp file itself.
            fileCopy?.setExtendedAttribute(data: uploadApi.apiString.data(using: .utf8), forName: self.uploadApiAttributeName)
            fileCopy?.setExtendedAttribute(data: uploadApi.fileId(for: uploadMetadata), forName: self.fileIdAttributeName)
            fileCopy?.setExtendedAttribute(data: uploadApi.mimeType(for: uploadMetadata), forName: self.contentTypeAttributeName)
            invariantFilePath = (tempFile.path as NSString).sandboxRelativePath()
        }
        else {
            // we already have the file copy--create a URL from its path
            let filePath = (invariantFilePath! as NSString).fullyQualifiedPath()
            guard let filePath = filePath  else {
                debugPrint("Error: unable to get fully qualified path from invariantFilePath '\(invariantFilePath!)'")
                return nil
            }
            
            fileCopy = URL(fileURLWithPath: filePath)
            guard let fileCopy = fileCopy else {
                debugPrint("Error: unable to create URL from file path '\(filePath)'")
                return nil
            }
            
            // "touch" the temp file for retry accounting purposes
            let coordinator = NSFileCoordinator(filePresenter: nil)
            coordinator.coordinate(writingItemAt: fileCopy, options: .contentIndependentMetadataOnly, error: nil) { (writeURL) in
                do {
                    try FileManager.default.setAttributes([.modificationDate : Date()], ofItemAtPath: writeURL.path)
                } catch let err {
                    debugPrint("FileManager failed to update the modification date of \(fileCopy): \(err)")
                }
            }
            
            // Keep track of what file it's a copy of.
            self.persistMapping(from: invariantFilePath!, to: fileUrl.path, defaultsKey: self.bridgeFileUploadsKey)
        }
        
        guard let invariantFilePath = invariantFilePath else {
            debugPrint("Failed to get sandbox-relative file path from temp file URL")
            return nil
        }
        
        // Set its state as uploadRequested
        self.persistMapping(from: invariantFilePath, to: uploadMetadata, defaultsKey: self.uploadURLsRequestedKey)
        
        // Request an uploadUrl for the bridgeUploadObject
        let requestString = uploadApi.uploadRequestUrlString(for: uploadMetadata)
        let headers = NSMutableDictionary([
            "Bridge-Session" : NativeAuthenticationManager().session().sessionToken
        ])
        
        BridgeSDK.authManager.addAuthHeader(toHeaders: headers)

        let _ = self.netManager.downloadFile(from: requestString, method: "POST", httpHeaders: headers as? [String : String], parameters: bridgeUploadObject, taskDescription: invariantFilePath)
        
        return fileCopy
    }
    
    /// Download delegate method.
    func urlSession(_ session: URLSession, downloadTask: URLSessionDownloadTask, didFinishDownloadingTo location: URL) {
        // get the sandbox-relative path to the temp copy of the participant file
        guard let invariantFilePath = downloadTask.taskDescription else {
            debugPrint("Unexpected: Finished a download task with no taskDescription set")
            return
        }
        
        // get which API this task is using
        guard let uploadApi = self.uploadApi(for: downloadTask.originalRequest?.url) else  {
            debugPrint("Unexpected: No uploadApi registered for download task \(downloadTask) (url: \(downloadTask.originalRequest?.url))")
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
            debugPrint("Request to Bridge to upload file \(invariantFilePath) via \(uploadApi.apiString) failed with status \(httpResponse.statusCode) and response body:\n\(urlContents)")
            
            // 401s on download get retried automatically, so our `urlSession(_:didCompleteWithError:)`
            // delegate method never gets called in that case, so it never would get cleaned up and we
            // don't want an ever-growing list of these clogging up our userDefaults forever. ~emm 2021-06-10
            if httpResponse.statusCode != 401 {
                self.persistMapping(from: invariantFilePath, to: urlContents, defaultsKey: self.downloadErrorResponseBodyKey)
            }
            // now just bail--we'll handle it if and when it makes it to `urlSession(_:, task:, didCompleteWithError:)`.
            return
        }

        // remove the participant file from the uploadRequested list, retrieving its associated upload metadata
        guard var uploadMetadata = self.removeMapping(BridgeFileUploadMetadata<uploadApi.bridgeUploadObjectType>.self, from: invariantFilePath, defaultsKey: self.uploadURLsRequestedKey)  else {
            debugPrint("Unexpected: Unable to retrieve BridgeFileUploadMetadata for \(invariantFilePath)")
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

        // deserialize the bridgeUploadObject from the downloaded JSON data and
        // update the upload metadata with it
        do {
            uploadMetadata.bridgeUploadObject = try self.netManager.jsonDecoder.decode(uploadApi.bridgeUploadObjectType, from: jsonData)
        } catch let err {
            debugPrint("Unexpected: Could not parse contents of downloaded file at URL \(location) as a \(uploadApi.bridgeUploadObjectType) object: \"\(urlContents)\"\n\terror:\(err)")
            return
        }
        
        uploadToS3(uploadApi: uploadApi, bridgeUploadMetadata: uploadMetadata, invariantFilePath: invariantFilePath)
    }
    
    func uploadToS3<T>(uploadApi: BridgeFileUploadAPI, bridgeUploadMetadata: BridgeFileUploadMetadata<T>,  invariantFilePath: String) {
        guard let uploadUrl = uploadApi.s3UploadUrlString(for: bridgeUploadMetadata) else {
            debugPrint("Unexpected: Could not get S3 upload URL from file upload metadata: \(bridgeUploadMetadata)")
            return
        }
        
        // get the fully-qualified path of the file to be uploaded
        guard let filePath = (invariantFilePath as NSString).fullyQualifiedPath(), !filePath.isEmpty else {
            debugPrint("Unable to recover fully qualified path from sandbox-relative path \"\(invariantFilePath)\"")
            return
        }
        
        // ...and make a URL from it
        let fileUrl = URL(fileURLWithPath: filePath)
        
        // add the file to the uploadingToS3 list
        self.persistMapping(from: invariantFilePath, to: bridgeUploadMetadata, defaultsKey: self.uploadingToS3Key
        )
        
        // upload the file to S3
        let headers = uploadApi.s3UploadHeaders(for: bridgeUploadMetadata)
        let _ = self.netManager.uploadFile(fileUrl, httpHeaders: headers, to: uploadUrl, taskDescription: invariantFilePath)
    }
    
    /// Call this function to check for and run any retries where the required delay has elapsed.
    public func retryUploadsAfterDelay() {
        self.uploadQueue.addOperation {
            let userDefaults = BridgeSDK.sharedUserDefaults()
            guard var retryUploads = userDefaults.dictionary(forKey: self.retryUploadsKey) else { return }
            for filePath in retryUploads.keys {
                autoreleasepool {
                    guard let retryInfoPlist = retryUploads[filePath] as? [String : Any] else { return }
                    var retryInfo: BridgeFileRetryInfo
                    do {
                        retryInfo = try DictionaryDecoder().decode(BridgeFileRetryInfo.self, from: retryInfoPlist)
                    } catch let error {
                        debugPrint("Error attempting to decode plist object to BridgeFileRetryInfo:\n\(retryInfoPlist)\n\(error)")
                        return
                    }

                    if retryInfo.whenToRetry.timeIntervalSinceNow <= 0.0 {
                        // get the fileURL from the original file path
                        let fileUrl = URL(fileURLWithPath: retryInfo.originalFilePath)
                        
                        let uploadMetadata = retryInfo.uploadMetadata
                        if (uploadMetadata.bridgeUploadObject.expiresOn?.timeIntervalSinceNow ?? 0.0) > 0.0 {
                            // if we have an upload URL and it's not expired, just retry upload to S3
                            // -- restore tracking of what file it's a copy of
                            self.persistMapping(from: filePath, to: fileUrl.path, defaultsKey: self.bridgeFileUploadsKey)
                            // -- retry upload to S3
                            self.uploadToS3(participantFile: uploadMetadata.bridgeUploadObject, contentLengthString: uploadMetadata.contentLengthString, invariantFilePath: filePath)
                        }
                        else {
                            // request a fresh upload URL from Bridge
                            let _ = self.requestUploadURL(invariantFilePath: filePath, fileUrl: fileUrl, uploadMetadata: uploadMetadata)
                        }
                        
                        // remove it from the list of things needing to be retried
                        retryUploads.removeValue(forKey: filePath)
                        userDefaults.setValue(retryUploads, forKey: self.retryUploadsKey)
                    }
                }
            }
        }
    }
    
    // Put a file into the retry queue so we can try again later.
    func enqueueForRetry(uploadApi: BridgeFileUploadAPI, invariantFilePath: String, originalFilePath: String, uploadMetadata: BridgeFileUploadMetadata) {
        let whenToRetry = Date(timeIntervalSinceNow: self.delayForRetry)
        let retryInfo = BridgeFileRetryInfo<uploadApi.bridgeUploadObjectType>(apiString: uploadApi.apiString, originalFilePath: originalFilePath, uploadMetadata: uploadMetadata, whenToRetry: whenToRetry)
        self.persistMapping(from: invariantFilePath, to: retryInfo, defaultsKey: self.retryUploadsKey)
    }
    
    // Helper for task delegate method in case of HTTP error on Bridge upload request.
    fileprivate func handleHTTPDownloadStatusCode(_ statusCode: Int, uploadApi: BridgeFileUploadAPI, downloadTask: URLSessionDownloadTask, invariantFilePath: String) {
        
        // remove the participant file from the uploadRequested list, retrieving its associated S3 metadata
        guard let uploadMetadata = self.removeMapping(BridgeFileUploadMetadata<uploadApi.bridgeUploadObjectType>.self, from: invariantFilePath, defaultsKey: self.uploadURLsRequestedKey) else {
            debugPrint("Unexpected: Unable to retrieve BridgeFileUploadMetadata for \(String(describing: invariantFilePath))")
            return
        }

        // remove the file from the temp -> orig mappings, and retrieve the original file path
        guard let originalFilePath = removeMapping(String.self, from: invariantFilePath, defaultsKey: self.bridgeFileUploadsKey) else {
            debugPrint("Unexpected: No original file path found mapped from temp file path \(invariantFilePath)")
            return
        }
        
        // remove the file from the temp -> download error response body mappings, and retrieve the response body, if any
        let responseBody = removeMapping(String.self, from: invariantFilePath, defaultsKey: self.downloadErrorResponseBodyKey)
        
        // server errors should be retried
        if statusCode >= 500 {
            self.enqueueForRetry(uploadApi: uploadApi, invariantFilePath: invariantFilePath, originalFilePath: originalFilePath, uploadMetadata: uploadMetadata)
            return
        }
        
        // post a notification that the file upload request to Bridge failed unrecoverably
        var userInfo: [AnyHashable : Any] = [
            self.filePathKey: originalFilePath,
            self.bridgeUploadObjectKey: uploadMetadata.bridgeUploadObject,
            self.httpStatusKey: statusCode
        ]
        
        // add the error response body, if any, to the userInfo
        if let responseBody = responseBody {
            userInfo[self.responseBodyKey] = responseBody
        }
                
        let uploadFailedNotification = Notification(name: .SBBParticipantFileUploadRequestFailed, object: nil, userInfo: userInfo)
        cleanUpTempFile(filePath: invariantFilePath)
        NotificationCenter.default.post(uploadFailedNotification)
    }

    // Helper for task delegate method in case of HTTP error on S3 upload.
    fileprivate func handleHTTPUploadStatusCode(_ statusCode: Int, uploadApi: BridgeFileUploadAPI, tempFilePath: String, originalFilePath: String,  uploadMetadata: BridgeFileUploadMetadata) {
        switch statusCode {
        case 403, 409, 500, 503:
            // 403: for our purposes means the pre-signed url timed out before starting the actual upload to S3.
            // 409: in our case it could only mean a temporary conflict (resource locked by another process, etc.) that should be retried.
            // 500: means internal server error ("We encountered an internal error. Please try again.")
            // 503: means service not available or the requests are coming too fast, so try again later.
            // In any case, we'll retry after a minimum delay to avoid spamming retries.
            self.enqueueForRetry(uploadApi: uploadApi, invariantFilePath: tempFilePath, originalFilePath: originalFilePath, uploadMetadata: uploadMetadata)

        default:
            // iOS handles redirects automatically so only e.g. 304 resource not changed etc. from the 300 range should end up here
            // (along with all unhandled 4xx and 5xx of course).
            debugPrint("Participant file upload to S3 of file \(originalFilePath) failed with HTTP response status code \(statusCode)--unhandled, will not retry")
            
            // post a notification that the file upload to S3 failed unrecoverably
            let userInfo: [AnyHashable : Any] = [self.filePathKey: originalFilePath, self.bridgeUploadObjectKey: uploadMetadata.bridgeUploadObject]
            let uploadFailedNotification = Notification(name: .SBBParticipantFileUploadToS3Failed, object: nil, userInfo: userInfo)
            cleanUpTempFile(filePath: tempFilePath)
            NotificationCenter.default.post(uploadFailedNotification)
        }
    }

    /// Task delegate method.
    func urlSession(_ session: URLSession, task: URLSessionTask, didCompleteWithError error: Error?) {
        
        // get which API this task is using
        guard let uploadApi = self.uploadApi(for: task.originalRequest?.url) else  {
            debugPrint("Unexpected: No uploadApi registered for task \(task) (url: \(task.originalRequest?.url))")
            return
        }
        
        // get the sandbox-relative path to the temp copy of the participant file
        guard let invariantFilePath = task.taskDescription else {
            debugPrint("Unexpected: Finished a background session task with no taskDescription set")
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
        
        // remove the file from the upload requests, and retrieve its ParticipantFile object
        guard let uploadMetadata = removeMapping(BridgeFileUploadMetadata<uploadApi.bridgeUploadObjectType>.self, from: invariantFilePath, defaultsKey: self.uploadingToS3Key) else {
            debugPrint("Unexpected: No BridgeFileUploadMetadata<\(uploadApi.bridgeUploadObjectType)> found mapped for temp file \(invariantFilePath)")
            return
        }
        
        let bridgeUploadObject = uploadMetadata.bridgeUploadObject
        
        // remove the file from the temp -> orig mappings, and retrieve the original file path
        guard let originalFilePath = removeMapping(String.self, from: invariantFilePath, defaultsKey: self.bridgeFileUploadsKey) else {
            debugPrint("Unexpected: No original file path found mapped from temp file path \(invariantFilePath)")
            return
        }
        
        // remove the file from the retry queue if it's in there (as it might be if an URLSession was invalidated
        // due to an error)
        let _ = removeMapping(BridgeFileRetryInfo.self, from: invariantFilePath, defaultsKey: self.retryUploadsKey)
        
        // set up the userInfo for an upload failed/succeeded notification
        var userInfo: [AnyHashable : Any] = [self.filePathKey: originalFilePath, self.bridgeUploadObjectKey: participantFile]

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
        
        // post a notification that the file uploaded
        let uploadedNotification = uploadApi.fileUploadedNotification(for: uploadMetadata)
        cleanUpTempFile(filePath: invariantFilePath)
        NotificationCenter.default.post(uploadedNotification)
    }
    
    /// Session delegate method.
    func urlSession(_ session: URLSession, didBecomeInvalidWithError error: Error?) {
        if error != nil {
            // If the URLSession was deliberately invalidated (i.e., error is nil) then we assume
            // the intention is to cancel and forget all incomplete uploads, including retries.
            // This might be used e.g. to clear out all pending uploads if we receive a 412
            // (Not Consented) error from Bridge or if the participant withdraws from the study.
            self.reset()
        }
        else {
            // If the URLSession was invalidated due to an error then we want to recover from that,
            // so we copy all incomplete uploads into the retry queue just to be sure. But we also
            // leave them in their current state in the mappings in case the error only broke it
            // on our end and iOS could still come through for us.
            let block = {
                let userDefaults = BridgeSDK.sharedUserDefaults()

                guard let originalFilePaths = userDefaults.dictionary(forKey: self.bridgeFileUploadsKey) else {
                    // nothing to see here, move along
                    return
                }
                
                let uploadsRequested = userDefaults.dictionary(forKey: self.uploadURLsRequestedKey)
                let uploadsToS3 = userDefaults.dictionary(forKey: self.uploadingToS3Key)
                
                // Get the temp copy and original file path for each file currently in the upload process and
                // copy it to the upload queue with its s3 metadata.
                for invariantFilePath in originalFilePaths.keys {
                    guard let uploadApi = self.apiFromXAttrs(for: invariantFilePath) else {
                        debugPrint("Unexpected: couldn't retrieve API from temp file xattrs for \(invariantFilePath)")
                        continue
                    }
                    guard let originalFilePath = self.retrieveMapping(String.self, from: invariantFilePath, mappings: originalFilePaths),
                          let uploadMetadata = self.retrieveMapping(BridgeFileUploadMetadata<uploadApi.bridgeUploadObjectType>.self, from: invariantFilePath, mappings: uploadsToS3) ??
                            self.retrieveMapping(BridgeFileUploadMetadata<uploadApi.bridgeUploadObjectType>.self, from: invariantFilePath, mappings: uploadsRequested) else {
                        continue
                    }
                    self.enqueueForRetry(invariantFilePath: invariantFilePath, originalFilePath: originalFilePath, uploadMetadata: uploadMetadata)
                }
            }
            
            if OperationQueue.current == self.uploadQueue {
                block()
            }
            else {
                self.uploadQueue.addOperation(block)
            }
        }
    }
    
    func apiFromXAttrs(for filePath: String) -> BridgeFileUploadAPI? {
        guard let fullPath = (filePath as NSString).fullyQualifiedPath() else {
            debugPrint("Unexpected: Could not form fully qualified path from '\(filePath)'")
            return nil
        }
        guard FileManager.default.fileExists(atPath: fullPath) else {
            debugPrint("Unexpected: Attempting to retrieve upload API for temp file with invariant path '\(filePath) but temp file does not exist at '\(fullPath)")
            return nil
        }
        let tempFile = URL(fileURLWithPath: fullPath)
        guard let apiStringData = tempFile.extendedAttribute(forName: self.uploadApiAttributeName) else {
            debugPrint("Unexpected: file at \(fullPath) does not have attribute \(self.uploadApiAttributeName)")
            return nil
        }
        guard let apiString = String(data: apiStringData, encoding: .utf8) else {
            debugPrint("Unexpected: Could not convert apiStringData to a utf8 string: \(apiStringData)")
            return nil
        }
        
        return self.bridgeFileUploadApis[apiString]
    }
    
    func cleanUpTempFile(filePath: String) {
        let block = {
            guard let fullPath = (filePath as NSString).fullyQualifiedPath() else {
                debugPrint("Unexpected: Could not form fully qualified path from '\(filePath)'")
                return
            }
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
}

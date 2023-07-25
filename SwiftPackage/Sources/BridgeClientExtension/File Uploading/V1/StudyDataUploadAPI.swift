//
//  StudyDataUploadAPI.swift
//  BridgeFileUploads
//

//import Foundation
import UniformTypeIdentifiers
import CoreServices
import BridgeClient
import JsonModel
import CommonCrypto

struct UploadRequest : Codable, Equatable, Hashable {
    /* File name */
    let name: String
    /* The size of the object in bytes. A standard HTTP header. For more information, go to [http://www.w3.org/Protocols/rfc2616/rfc2616-sec14.html#sec14.13](http://www.w3.org/Protocols/rfc2616/rfc2616-sec14.html#sec14.13)  */
    let contentLength: Int
    /* The base64-encoded, 128-bit MD5 digest of the object body. */
    let contentMd5: String
    /* A standard MIME type. For more information, go to [http://www.w3.org/Protocols/rfc2616/rfc2616-sec14.html#sec14.17](http://www.w3.org/Protocols/rfc2616/rfc2616-sec14.html#sec14.17)  */
    let contentType: String
    /* True if the upload is encrypted. False if it is not encrypted. If not specified, defaults to true. */
    let encrypted: Bool?
    /* JSON map with key value pairs representing metadata for this upload, as submitted by the app. This corresponds with the uploadMetadataFieldDefinitions configured in the app. */
    let metadata: JsonElement?
    /* True if the upload is zipped. False if it is a single file. If not specified, defaults to true. */
    let zipped: Bool?
    
    var type: String = "UploadRequest"
}

struct UploadSession : Codable, Equatable, Hashable {
    /* The upload ID. The client needs to use this ID to call Bridge when the upload is complete.  */
    let id: String?
    /* A pre-signed URL for doing a PUT upload of the data. The URL will remain valid for 24 hours once created on the Bridge side.  */
    let url: String
    /* The ISO 8601 date and time stamp at which this session will expire.  */
    let expires: Date?
    
    var type: String = "UploadSession"
}

struct StudyDataUploadObject: Codable, BridgeUploadTrackingData {
    var uploadRequest: UploadRequest
    var uploadSession: UploadSession?
    
    var userInfo: [String : Any]? {
        uploadRequest.metadata.flatMap {
            if case .object(let ret) = $0 {
                return ret
            } else {
                return nil
            }
        }
    }
}

public struct StudyDataUploadExtras: Codable {
    var encrypted: Bool?
    var metadata: JsonElement?
    var zipped: Bool?
}

extension Notification.Name {
    /// Notification name posted by the `BridgeFileUploadManager` when a study file upload completes.
    public static let SBBStudyFileUploaded = Notification.Name(rawValue: "SBBStudyFileUploaded")
    
    /// Notification name posted by the `BridgeFileUploadManager` when a study file upload request to Bridge fails.
    public static let SBBStudyFileUploadRequestFailed = Notification.Name(rawValue: "SBBStudyFileUploadRequestFailed")
    
    /// Notification name posted by the `BridgeFileUploadManager` when a study file upload attempt to S3 fails unrecoverably.
    public static let SBBStudyFileUploadToS3Failed = Notification.Name(rawValue: "SBBStudyFileUploadToS3Failed")
    
    /// Notification name posted by the `BridgeFileUploadManager` when attempting to notify Bridge
    /// of a successful upload fails unrecoverably.
    public static let SBBStudyFileUploadBridgeNotificationFailed = Notification.Name(rawValue: "SBBStudyFileUploadBridgeNotificationFailed")
}

public class StudyDataUploadAPI: BridgeFileUploadAPITyped {
    typealias TrackingType = StudyDataUploadObject
    typealias UploadRequestType = UploadRequest
    typealias UploadRequestResponseType = UploadSession

    /// A singleton instance of the API.
    public static let shared = StudyDataUploadAPI()

    /// The Notification.userInfo key for the uploaded file's fileId.
    let fileNameKey = "FileName"
    
    public private(set) var apiString: String = "v3/uploads"
    
    public private(set) var tempUploadDirURL: URL
    
    public private(set) var notifiesBridgeWhenUploaded: Bool = true
    
    public private(set) var uploadManager: BridgeFileUploadManager
    
    /// Private initializer so only the singleton can ever get created.
    private init() {
        self.uploadManager = BridgeFileUploadManager.shared
        
        // Set up a directory to keep temp copies of files being uploaded
        do {
            let appSupportDir = try FileManager.default.sharedAppSupportDirectory()
            self.tempUploadDirURL = appSupportDir.appendingPathComponent("StudyDataUploads")
            try FileManager.default.createDirectory(at: self.tempUploadDirURL, withIntermediateDirectories: true, attributes: nil)
        }
        catch {
            fatalError("StudyDataUploadAPI unable to create temp upload directory: \(error)")
        }
        
        // Register this upload API with the file upload manager
        self.uploadManager.bridgeFileUploadApis[self.apiString] = self
    }
    
    // adapted from https://stackoverflow.com/a/32166735
    func md5base64(data: Data) -> String {
        let length = Int(CC_MD5_DIGEST_LENGTH)
        var digestData = Data(count: length)
        _ = digestData.withUnsafeMutableBytes { digestBytes -> UInt8 in
            data.withUnsafeBytes { messageBytes -> UInt8 in
                if let messageBytesBaseAddress = messageBytes.baseAddress, let digestBytesBlindMemory = digestBytes.bindMemory(to: UInt8.self).baseAddress {
                    let messageLength = CC_LONG(data.count)
                    // Ignore the deprecation warning. The form of pre-signed S3 URLs used
                    // by Bridge for these uploads requires that we give the base64encoded
                    // MD5 hash in the HTTP headers.
                    CC_MD5(messageBytesBaseAddress, messageLength, digestBytesBlindMemory)
                }
                return 0
            }
        }
        return digestData.base64EncodedString()
    }
        
    func uploadMetadata(for fileId: String, fileUrl: URL, mimeType: String, extras: Codable? = nil) -> BridgeFileUploadMetadataBlob? {
        // Get the file size and MD5 hash before making the temp copy, in case something goes wrong
        let contentLength: Int?
        do {
            contentLength = try fileUrl.resourceValues(forKeys: [.fileSizeKey]).fileSize
        } catch let err {
            Logger.log(tag: .upload, error: err, message: "Error trying to get content length of study data file at \(fileUrl)")
            return nil
        }
        guard let contentLength = contentLength else {
            Logger.log(tag: .upload, error: BridgeUnexpectedNullError(category: .empty, message: "Error: Study data file content length is nil"))
            return nil
        }

        var contentMD5String: String
        do {
            let fileData = try Data(contentsOf: fileUrl, options: [.alwaysMapped, .uncached])
            contentMD5String = self.md5base64(data: fileData)
        } catch let err {
            Logger.log(tag: .upload, error: err, message: "Error trying to get memory-mapped data of participant file at \(fileUrl) in order to calculate its base64encoded MD5 hash.")
            return nil
        }
        
        let uploadExtras = extras as? StudyDataUploadExtras ?? StudyDataUploadExtras(encrypted: nil, metadata: nil, zipped: nil)
        let uploadRequest = UploadRequest(name: fileId, contentLength: contentLength, contentMd5: contentMD5String, contentType: mimeType, encrypted: uploadExtras.encrypted, metadata: uploadExtras.metadata, zipped: uploadExtras.zipped)

        let studyDataUpload = StudyDataUploadObject(uploadRequest: uploadRequest)
        
        let headers = [
            "Content-Length": String(contentLength),
            "Content-Type": mimeType,
            "Content-MD5": contentMD5String
        ]
        
        return BridgeFileUploadMetadata(bridgeUploadTrackingObject: studyDataUpload, s3Headers: headers)
    }
    
    func uploadRequestObject(for uploadMetadata: BridgeFileUploadMetadataBlob) -> Codable {
        return (uploadMetadata as! BridgeFileUploadMetadata<TrackingType>).bridgeUploadTrackingObject.uploadRequest
    }
    
    func fileId(for uploadMetadata: BridgeFileUploadMetadataBlob) -> String {
        return (uploadMetadata as! BridgeFileUploadMetadata<TrackingType>).bridgeUploadTrackingObject.uploadRequest.name
    }
    
    func mimeType(for uploadMetadata: BridgeFileUploadMetadataBlob) -> String {
        return (uploadMetadata as! BridgeFileUploadMetadata<TrackingType>).bridgeUploadTrackingObject.uploadRequest.contentType
    }
    
    func extras(for uploadMetadata: BridgeFileUploadMetadataBlob) -> Codable? {
        let request = (uploadMetadata as! BridgeFileUploadMetadata<TrackingType>).bridgeUploadTrackingObject.uploadRequest
        return StudyDataUploadExtras(encrypted: request.encrypted, metadata: request.metadata, zipped: request.zipped)
    }
    
    func uploadRequestUrlString(for uploadMetadata: BridgeFileUploadMetadataBlob) -> String {
        return self.apiString
    }
    
    func s3UploadUrlString(for uploadMetadata: BridgeFileUploadMetadataBlob) -> String? {
        return (uploadMetadata as! BridgeFileUploadMetadata<TrackingType>).bridgeUploadTrackingObject.uploadSession?.url
    }
    
    func s3UploadHeaders(for uploadMetadata: BridgeFileUploadMetadataBlob) -> [String : String] {
        let metadata = uploadMetadata as! BridgeFileUploadMetadata<TrackingType>
        return metadata.s3Headers
    }
    
    func notifyBridgeUrlString(for uploadMetadata: BridgeFileUploadMetadataBlob) -> String? {
        guard let uploadId = (uploadMetadata as! BridgeFileUploadMetadata<TrackingType>).bridgeUploadTrackingObject.uploadSession?.id else {
            let message = "Could not get URL to notify Bridge of upload success from file upload metadata: \(uploadMetadata)"
            Logger.log(tag: .upload, error: BridgeUnexpectedNullError(category: .missingIdentifier, message: message))
            return nil
        }
        return "\(self.apiString)/\(uploadId)/complete"
    }
    
    func fileUploadedNotification(for uploadMetadata: BridgeFileUploadMetadataBlob) -> Notification {
        let metadata = uploadMetadata as! BridgeFileUploadMetadata<TrackingType>
        let userInfo: [AnyHashable : Any] = [
            self.fileNameKey: metadata.bridgeUploadTrackingObject.uploadRequest.name
        ]
        let uploadedNotification = Notification(name: .SBBStudyFileUploaded, object: nil, userInfo: userInfo)
        return uploadedNotification
    }
    
    func reportingUploadToBridgeFailedNotification(for uploadMetadata: BridgeFileUploadMetadataBlob, statusCode: Int, responseBody: String?) -> Notification? {
        let metadata = uploadMetadata as! BridgeFileUploadMetadata<TrackingType>
        var userInfo: [AnyHashable : Any] = [
            self.fileNameKey: metadata.bridgeUploadTrackingObject.uploadRequest.name,
            self.httpStatusKey: statusCode
        ]
        
        // add the error response body, if any, to the userInfo
        if let responseBody = responseBody {
            userInfo[self.responseBodyKey] = responseBody
        }
                
        let reportingFailedNotification = Notification(name: .SBBStudyFileUploadBridgeNotificationFailed, object: nil, userInfo: userInfo)
        return reportingFailedNotification
    }
    
    func uploadToS3FailedNotification(for uploadMetadata: BridgeFileUploadMetadataBlob) -> Notification {
        let metadata = uploadMetadata as! BridgeFileUploadMetadata<TrackingType>
        let userInfo: [AnyHashable : Any] = [
            self.fileNameKey: metadata.bridgeUploadTrackingObject.uploadRequest.name
        ]
        let uploadFailedNotification = Notification(name: .SBBStudyFileUploadToS3Failed, object: nil, userInfo: userInfo)
        return uploadFailedNotification
    }
    
    func uploadRequestFailedNotification(for uploadMetadata: BridgeFileUploadMetadataBlob, statusCode: Int, responseBody: String?) -> Notification {
        let metadata = uploadMetadata as! BridgeFileUploadMetadata<TrackingType>
        var userInfo: [AnyHashable : Any] = [
            self.fileNameKey: metadata.bridgeUploadTrackingObject.uploadRequest.name,
            self.httpStatusKey: statusCode
        ]
        
        // add the error response body, if any, to the userInfo
        if let responseBody = responseBody {
            userInfo[self.responseBodyKey] = responseBody
        }
                
        let uploadFailedNotification = Notification(name: .SBBStudyFileUploadRequestFailed, object: nil, userInfo: userInfo)
        return uploadFailedNotification
    }
    
    func isUploadSessionExpired(for uploadMetadata: BridgeFileUploadMetadataBlob) -> Bool {
        return ((uploadMetadata as! BridgeFileUploadMetadata<TrackingType>).bridgeUploadTrackingObject.uploadSession?.expires?.timeIntervalSinceNow ?? 0.0) <= 0.0
    }
    
    func update(metadata: BridgeFileUploadMetadataBlob, with jsonData: Data) -> BridgeFileUploadMetadataBlob? {
        // deserialize the bridgeUploadObject from the downloaded JSON data and
        // update the upload metadata with it
        guard var uploadMetadata = metadata as? BridgeFileUploadMetadata<TrackingType> else {
            let message = "Metadata blob was not of the expected type BridgeFileUploadMetadata<\(TrackingType.self)>: \(metadata)"
            Logger.log(tag: .upload, error: BridgeUnexpectedNullError(category: .wrongType, message: message))
            return nil
        }
        do {
            uploadMetadata.bridgeUploadTrackingObject.uploadSession = try self.uploadManager.netManager.jsonDecoder.decode(UploadRequestResponseType.self, from: jsonData)
        } catch let err {
            // it's not an upload request response so log it (just in case it's something unexpected) and return nil
            Logger.log(severity: .warn, tag: .upload, message: "Could not parse contents of downloaded file as a \(UploadRequestResponseType.self) object, ignoring: \"\(String(describing: String(data: jsonData, encoding: .utf8)))\"\n\terror:\(err)")
            return nil
        }
        return uploadMetadata
    }
    
    func uploadRequestExtras(from data: Data?) -> Codable? {
        guard let data = data else { return nil }
        do {
            return try self.uploadManager.netManager.jsonDecoder.decode(StudyDataUploadExtras.self, from: data)
        } catch let err {
            Logger.log(severity: .info, tag: .upload, message: "Unexpected: Could not parse Xattrs upload extras data as a \(StudyDataUploadExtras.self) object: \"\(String(describing: String(data: data, encoding: .utf8)))\"\n\terror:\(err)")
            return nil
        }
    }
}


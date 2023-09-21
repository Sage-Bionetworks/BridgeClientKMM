//
//  ParticipantFileUploadAPI.swift
//  BridgeFileUploads
//

//import Foundation
import UniformTypeIdentifiers
import CoreServices
import BridgeClient

struct ParticipantFile: Codable, BridgeUploadTrackingData {
    let fileId : String
    let mimeType: String
    let createdOn: Date?
    var downloadUrl: String?
    var uploadUrl: String?
    var expiresOn: Date?
    var type: String = "ParticipantFile"
    
    var userInfo: [String : Any]? {
        nil
    }
}

extension Notification.Name {
    /// Notification name posted by the `BridgeFileUploadManager` when a participant file upload completes.
    static let SBBParticipantFileUploaded = Notification.Name(rawValue: "SBBParticipantFileUploaded")

    /// Notification name posted by the `BridgeFileUploadManager` when a participant file upload request to Bridge fails.
    static let SBBParticipantFileUploadRequestFailed = Notification.Name(rawValue: "SBBParticipantFileUploadRequestFailed")

    /// Notification name posted by the `BridgeFileUploadManager` when a participant file upload attempt to S3 fails unrecoverably.
    static let SBBParticipantFileUploadToS3Failed = Notification.Name(rawValue: "SBBParticipantFileUploadToS3Failed")
}

class ParticipantFileUploadAPI: BridgeFileUploadAPITyped {
    typealias TrackingType = ParticipantFile
    typealias UploadRequestType = ParticipantFile
    typealias UploadRequestResponseType = ParticipantFile

    /// The Notification.userInfo key for the uploaded file's ParticipantFile object from Bridge.
    let participantFileKey = "ParticipantFile"
    
    /// The Notification.userInfo key for the uploaded file's fileId.
    let fileIdKey = "FileId"
    
    /// The Notification.userInfo key for the Bridge API URL at which one can (with appropriate authentication headers)
    /// DELETE the uploaded file, or GET it back (via redirect).
    let requestUrlKey = "RequestUrl"

    private(set) var apiString: String = "v3/participants/self/files/"
    
    private(set) var tempUploadDirURL: URL
    
    private(set) var notifiesBridgeWhenUploaded: Bool = false
    
    weak private(set) var uploadManager: BridgeFileUploadManager!
    
    static var uploadSubdirectory: String = "ParticipantFileUploads"
    
    init(uploadManager: BridgeFileUploadManager) {

        // Set up a directory to keep temp copies of files being uploaded
        do {
            let appSupportDir = try FileManager.default.sharedAppSupportDirectory()
            self.tempUploadDirURL = appSupportDir.appendingPathComponent(Self.uploadSubdirectory)
            try FileManager.default.createDirectory(at: self.tempUploadDirURL, withIntermediateDirectories: true, attributes: nil)
        }
        catch {
            fatalError("ParticipantFileUploadAPI unable to create participant file temp upload dir: \(error)")
        }
        
        self.uploadManager = uploadManager
    }
    
    func uploadMetadata(for fileId: String, fileUrl: URL, mimeType: String, extras: Codable? = nil) -> BridgeFileUploadMetadataBlob? {
        var createdOn: Date?
        do {
            let attrs = try FileManager.default.attributesOfItem(atPath: fileUrl.path)
            createdOn = (attrs as NSDictionary).fileCreationDate()
        } catch {
            // if we can't get a creation date from the file, set it to now
            createdOn = Date()
        }
        
        let participantFile = ParticipantFile(fileId: fileId, mimeType: mimeType, createdOn: createdOn)
        
        let headers = [
            "Content-Type": participantFile.mimeType,
        ]
        
        return BridgeFileUploadMetadata(bridgeUploadTrackingObject: participantFile, s3Headers: headers)
    }
    
    func uploadRequestObject(for uploadMetadata: BridgeFileUploadMetadataBlob) -> Codable {
        return (uploadMetadata as! BridgeFileUploadMetadata<TrackingType>).bridgeUploadTrackingObject
    }
    
    func fileId(for uploadMetadata: BridgeFileUploadMetadataBlob) -> String {
        return (uploadMetadata as! BridgeFileUploadMetadata<TrackingType>).bridgeUploadTrackingObject.fileId
    }
    
    func mimeType(for uploadMetadata: BridgeFileUploadMetadataBlob) -> String {
        return (uploadMetadata as! BridgeFileUploadMetadata<TrackingType>).bridgeUploadTrackingObject.mimeType
    }
    
    func extras(for uploadMetadata: BridgeFileUploadMetadataBlob) -> Codable? {
        return nil
    }
    
    func uploadRequestUrlString(for uploadMetadata: BridgeFileUploadMetadataBlob) -> String {
        return self.apiString.appending(fileId(for: uploadMetadata))
    }
    
    func s3UploadUrlString(for uploadMetadata: BridgeFileUploadMetadataBlob) -> String? {
        return (uploadMetadata as! BridgeFileUploadMetadata<TrackingType>).bridgeUploadTrackingObject.uploadUrl
    }
    
    func s3UploadHeaders(for uploadMetadata: BridgeFileUploadMetadataBlob) -> [String : String] {
        let metadata = uploadMetadata as! BridgeFileUploadMetadata<TrackingType>
        let participantFile = metadata.bridgeUploadTrackingObject
        let uploadUrl = participantFile.uploadUrl
        var s3Headers = metadata.s3Headers
        
        // Fill in any needed headers that weren't available when the metadata was created/last updated
        if s3Headers["Content-Type"] == nil {
            s3Headers["Content-Type"] = participantFile.mimeType
        }
        
        if s3Headers["Host"] == nil {
            if let uploadUrl = uploadUrl,
               let host = URL(string: uploadUrl)?.host {
                s3Headers["Host"] = host
            }
            else {
                s3Headers["Host"] = "org-sagebridge-participantfile-prod.s3.amazonaws.com"
            }
        }
        
        return s3Headers
    }
    
    func notifyBridgeUrlString(for uploadMetadata: BridgeFileUploadMetadataBlob) -> String? {
        return nil
    }
    
    func fileUploadedNotification(for uploadMetadata: BridgeFileUploadMetadataBlob) -> Notification {
        let metadata = uploadMetadata as! BridgeFileUploadMetadata<TrackingType>
        let uploadRequestPath = uploadRequestUrlString(for: metadata)
        let requestUrl = self.uploadManager.netManager.bridgeURL(for: uploadRequestPath)
        let userInfo: [AnyHashable : Any] = [
            self.fileIdKey: metadata.bridgeUploadTrackingObject.fileId,
            self.participantFileKey: metadata.bridgeUploadTrackingObject,
            self.requestUrlKey: requestUrl
        ]
        let uploadedNotification = Notification(name: .SBBParticipantFileUploaded, object: nil, userInfo: userInfo)
        return uploadedNotification
    }
    
    func reportingUploadToBridgeFailedNotification(for uploadMetadata: BridgeFileUploadMetadataBlob, statusCode: Int, responseBody: String?) -> Notification? {
        return nil
    }
    
    func uploadToS3FailedNotification(for uploadMetadata: BridgeFileUploadMetadataBlob) -> Notification {
        let metadata = uploadMetadata as! BridgeFileUploadMetadata<TrackingType>
        let userInfo: [AnyHashable : Any] = [
            self.fileIdKey: metadata.bridgeUploadTrackingObject.fileId,
            self.participantFileKey: metadata.bridgeUploadTrackingObject
        ]
        let uploadFailedNotification = Notification(name: .SBBParticipantFileUploadToS3Failed, object: nil, userInfo: userInfo)
        return uploadFailedNotification
    }
    
    func uploadRequestFailedNotification(for uploadMetadata: BridgeFileUploadMetadataBlob, statusCode: Int, responseBody: String?) -> Notification {
        let metadata = uploadMetadata as! BridgeFileUploadMetadata<TrackingType>
        var userInfo: [AnyHashable : Any] = [
            self.fileIdKey: metadata.bridgeUploadTrackingObject.fileId,
            self.participantFileKey: metadata.bridgeUploadTrackingObject,
            self.httpStatusKey: statusCode
        ]
        
        // add the error response body, if any, to the userInfo
        if let responseBody = responseBody {
            userInfo[self.responseBodyKey] = responseBody
        }
                
        let uploadFailedNotification = Notification(name: .SBBParticipantFileUploadRequestFailed, object: nil, userInfo: userInfo)
        return uploadFailedNotification
    }
    
    func isUploadSessionExpired(for uploadMetadata: BridgeFileUploadMetadataBlob) -> Bool {
        return ((uploadMetadata as! BridgeFileUploadMetadata<TrackingType>).bridgeUploadTrackingObject.expiresOn?.timeIntervalSinceNow ?? 0.0) <= 0.0
    }
    
    func update(metadata: BridgeFileUploadMetadataBlob, with jsonData: Data) -> BridgeFileUploadMetadataBlob? {
        // deserialize the bridgeUploadObject from the downloaded JSON data and
        // update the upload metadata with it
        guard var uploadMetadata = metadata as? BridgeFileUploadMetadata<TrackingType> else {
            let message = "Metadata blob was not of the expected type BridgeFileUploadMetadata<\(TrackingType.self)>: \(metadata)"
            Logger.log(tag: .upload, error: BridgeUnexpectedNullError(category: .missingMetadata, message: message))
            return nil
        }
        do {
            uploadMetadata.bridgeUploadTrackingObject = try self.uploadManager.netManager.jsonDecoder.decode(UploadRequestResponseType.self, from: jsonData)
        } catch let err {
            Logger.log(tag: .upload, error: err, message: "Could not parse contents of downloaded file as a \(UploadRequestResponseType.self) object: \"\(String(describing: String(data: jsonData, encoding: .utf8)))\"")
            return nil
        }
        return uploadMetadata
    }
    
    func uploadRequestExtras(from data: Data?) -> Codable? {
        return nil
    }
}


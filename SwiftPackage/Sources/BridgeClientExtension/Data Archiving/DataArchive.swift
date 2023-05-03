//
//  DataArchive.swift
//

import Foundation
import BridgeArchiver
import JsonModel
import ResultModel
import BridgeClient

// Errors are thrown by server if the size is more that 100,000,000 bytes.
// Note: I am not sure why its not 100 mb = 104857600 bytes, but messaging
// suggests that this is the actual limit. syoung 06/13/2022
let kFileSizeLimit = 100_000_000

fileprivate let kMetadataFilename                 = "metadata.json"
fileprivate let kScheduledActivityGuidKey         = "scheduledActivityGuid"
fileprivate let kScheduleIdentifierKey            = "scheduleIdentifier"
fileprivate let kScheduledOnKey                   = "scheduledOn"
fileprivate let kScheduledActivityLabelKey        = "activityLabel"
fileprivate let kDataGroups                       = "dataGroups"

/// The public final class to use for uploading using Exporter v3.
public final class StudyDataUploadArchive : DataArchive {
}

/// Wrapper for tying a ``BridgeArchiver`` to an uploaded assessment archive.
open class DataArchive : NSObject, Identifiable {
    public let id: UUID = .init()
    
    /// The identifier for this archive.
    public let identifier: String
    
    /// The schedule associated with this archive (if any).
    public let schedule: AssessmentScheduleInfo?
    
    /// A timestamp for the data archive that can be mapped to an adherence record so
    /// that the record created by this library can be marked as "uploaded" in the
    /// asynchronous upload request.
    ///
    /// - Note: This is different from a `createdOn` date would timestamp when the
    /// **archive** was created rather than when the **assessment** was started.
    /// If this archive is not associated with an assessment then this should be
    /// left as nil.
    public final internal(set) var adherenceStartedOn: Date?
    
    /// This name conflicts with the `ResultArchiveBuilder` protocol.
    @available(*, deprecated, message: "Use `adherenceStartedOn` instead. This will be deleted in future builds.")
    public final var startedDate: Date? {
        get { adherenceStartedOn }
        set { adherenceStartedOn = newValue }
    }
    
    /// The data groups that are set as metadata on this archive.
    public let dataGroups: [String]?
    
    /// Has the archive been zipped?
    public final internal(set) var isCompleted: Bool = false
    
    /// The local file URL for the encrypted archive.
    public final private(set) var encryptedURL: URL?
    
    /// A list of all the files included in the archive.
    public final var files: [FileEntry] {
        archiver.files
    }
    
    /// The manifest that gets added to the archive as part of the metadata.
    public final private(set) var manifest: [FileInfo] = []
    
    private let archiver: BridgeArchiver
    
    public init?(identifier: String,
                 schedule: AssessmentScheduleInfo? = nil,
                 startedOn: Date? = nil,
                 dataGroups: [String]? = nil) {
        guard let archiver = BridgeArchiver() else { return nil }
        self.archiver = archiver
        self.identifier = identifier
        self.schedule = schedule
        self.dataGroups = dataGroups
        self.adherenceStartedOn = startedOn
        super.init()
    }
    
    /// Is the archive empty?
    public final func isEmpty() -> Bool {
        archiver.files.count == 0
    }
    
    /// Clean up and delete the archive.
    public final func remove() {
        try? archiver.remove()
    }
    
    /// Add a file to this archive.
    ///
    /// - Parameters:
    ///   - data: The data to encode to add as a file.
    ///   - fileInfo: The file info to include in the manifest.
    public final func addFile(data: Data, fileInfo: FileInfo) throws {
        try _addFile(data: data, filepath: fileInfo.filename, createdOn: fileInfo.timestamp, contentType: fileInfo.contentType)
        self.manifest.append(fileInfo)
    }

    @available(*, deprecated, message: "Use `addFile(data:fileInfo:)` instead.")
    public final func addFile(data: Data, filepath: String, createdOn: Date = Date(), contentType: String? = nil) throws {
        try _addFile(data: data, filepath: filepath, createdOn: createdOn, contentType: contentType)
    }
    
    private func _addFile(data: Data, filepath: String, createdOn: Date, contentType: String?) throws {
        guard data.count <= kFileSizeLimit
        else {
            let error = BridgeArchiveError(category: .exceedsAllowedLimit,
                                           message: "File size exceeds allowed limit. filepath=\(filepath), filesize=\(data.count)")
            Logger.log(tag: .upload, error: error)
            return
        }
        try archiver.addFile(data: data, filepath: filepath, createdOn: createdOn, contentType: contentType)
    }
    
    /// Close the archive (but do not encrypt or delete).
    public final func completeArchive() throws {
        let metadata = ArchiveMetadata(files: manifest)
        let metadataDictionary = try metadata.jsonEncodedDictionary()
        try addMetadata(metadataDictionary)
        isCompleted = true
    }
    
    func addMetadata(_ metadata: [String : Any]) throws {
        // Set up the activity metadata.
        var metadataDictionary: [String : Any] = metadata
        
        // Add metadata values from the schedule.
        if let schedule = self.schedule {
            metadataDictionary[kScheduledActivityGuidKey] = schedule.instanceGuid
            metadataDictionary[kScheduleIdentifierKey] = schedule.session.instanceGuid
            metadataDictionary[kScheduledOnKey] = ISO8601TimestampFormatter.string(from: schedule.session.scheduledOn)
            metadataDictionary[kScheduledActivityLabelKey] = schedule.assessmentInfo.label
        }
        
        // Add the current data groups.
        if let dataGroups = dataGroups {
            metadataDictionary[kDataGroups] = dataGroups.joined(separator: ",")
        }
        
        let data = try JSONSerialization.data(withJSONObject: metadataDictionary, options: [.prettyPrinted, .withoutEscapingSlashes])
        try _addFile(data: data, filepath: kMetadataFilename, createdOn: Date(), contentType: "json")
    }
    
    /// Encrypt the upload using the pem file at the given path.
    ///
    /// - Parameter pemFile: The path to the pem file to use to encrypt the archive.
    /// - Returns: The URL to the encrypted archive.
    @discardableResult
    public final func encryptArchive(using pemFile: String) throws -> URL {
        self.encryptedURL = try archiver.encryptArchive(using: pemFile)
        return self.encryptedURL!
    }
    
    #if DEBUG
    /// When testing an app, it can be helpful to be able to inspect the archive. This allows the developer to store an unencrypted
    /// copy of the archive. This method should **not** be made public or be exposed without the `#if DEBUG` flag.
    internal func copyTestArchive() {
        guard let url = archiver.archiveURL else { return }
        do {
            let fileManager = FileManager.default
            
            let outputDirectory = try IOSBridgeConfig().sharedDocumentDirectory()
            let dirURL = outputDirectory.appendingPathComponent("archives", isDirectory: true)
            try FileManager.default.createDirectory(at: dirURL, withIntermediateDirectories: true, attributes: nil)
            
            // Scrub non-alphanumeric characters from the identifer
            var characterSet = CharacterSet.alphanumerics
            characterSet.invert()
            var filename = identifier
            while let range = filename.rangeOfCharacter(from: characterSet) {
                filename.removeSubrange(range)
            }
            filename.append("-")
            let dateFormatter = DateFormatter()
            dateFormatter.locale = Locale(identifier: "en_US_POSIX")
            dateFormatter.dateFormat = "yyyy-MM-dd'T'HHmm"
            let dateString = dateFormatter.string(from: Date())
            filename.append(dateString)
            let debugURL = dirURL.appendingPathComponent(filename, isDirectory: false).appendingPathExtension("zip")
            try fileManager.copyItem(at: url, to: debugURL)
            Logger.log(severity: .info, message: "Copied archive to \(debugURL)")
            
        } catch let err {
            Logger.log(severity: .info, message: "Failed to copy archive: \(err)")
        }
    }
    #endif
}

struct BridgeArchiveError : Error, CustomNSError {
    static var errorDomain: String { "BridgeClientUI.ArchiveError" }
    
    let category: Category
    let message: String
    
    var errorCode: Int {
        category.rawValue
    }
    
    var errorUserInfo: [String : Any] {
        [NSLocalizedFailureReasonErrorKey: message]
    }
    
    enum Category : Int {
        case exceedsAllowedLimit = -200
    }
}

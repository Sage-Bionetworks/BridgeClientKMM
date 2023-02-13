//
//  DataArchive.swift
//

import Foundation
import BridgeArchiver
import JsonModel
import BridgeClient

// Errors are thrown by server if the size is more that 100,000,000 bytes.
// Note: I am not sure why its not 100 mb = 104857600 bytes, but messaging
// suggests that this is the actual limit. syoung 06/13/2022
let kFileSizeLimit = 100000000

/// Wrapper for tying a ``BridgeArchiver`` to an uploaded archive.
open class DataArchive : NSObject, Identifiable {
    public let id: UUID = .init()
    
    /// The identifier for this archive.
    public let identifier: String
    
    private let archiver: BridgeArchiver
    
    /// The schedule used to start this task (if any).
    public let schedule: AssessmentScheduleInfo?
    
    /// A timestamp for the data archive that is distinct from when the archive was created.
    public var startedOn: Date? = nil
    
    /// Has the archive been zipped?
    public final internal(set) var isCompleted: Bool = false
    
    /// The local file URL for the encrypted archive.
    public final private(set) var encryptedURL: URL?
    
    /// A list of all the files included in the archive.
    public var files: [FileEntry] {
        archiver.files
    }
    
    public init?(identifier: String, schedule: AssessmentScheduleInfo? = nil) {
        guard let archiver = BridgeArchiver() else { return nil }
        self.archiver = archiver
        self.identifier = identifier
        self.schedule = schedule
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
    
    /// Add a file to the archive.
    ///
    /// - Parameters:
    ///   - data: The data to be added.
    ///   - filepath: The file path for the added data.
    ///   - createdOn: The timestamp for when the data was created.
    ///   - contentType: The content type of the data.
    public final func addFile(data: Data, filepath: String, createdOn: Date = Date(), contentType: String? = nil) throws {
        guard data.count <= kFileSizeLimit
        else {
            let error = BridgeArchiveError(category: .exceedsAllowedLimit,
                                           message: "File size exceeds allowed limit. filepath=\(filepath), filesize=\(data.count)")
            Logger.log(tag: .upload, error: error)
            return
        }
        try archiver.addFile(data: data, filepath: filepath, createdOn: createdOn, contentType: contentType)
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

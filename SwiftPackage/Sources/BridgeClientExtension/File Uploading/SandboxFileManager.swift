// Created 7/25/23
// swift-tools-version:5.0

import Foundation
import UniformTypeIdentifiers
import CommonCrypto
import BridgeClient

/// The file manager for converting converting between sandbox-relative and fully-qualified file paths.
class SandboxFileManager: NSObject {
    
    func touch(fileUrl: URL) {
        let coordinator = NSFileCoordinator(filePresenter: nil)
        coordinator.coordinate(writingItemAt: fileUrl, options: .contentIndependentMetadataOnly, error: nil) { (writeUrl) in
            do {
                try FileManager.default.setAttributes([.modificationDate : Date()], ofItemAtPath: writeUrl.path)
            } catch let err {
                Logger.log(tag: .upload, error: err, message: "FileManager failed to update the modification date of \(fileUrl)")
            }
        }
    }
    
    func modificationDate(of fileUrl: URL) -> Date? {
        let coordinator = NSFileCoordinator(filePresenter: nil)
        var modDate: Date? = nil
        coordinator.coordinate(readingItemAt: fileUrl, options: .immediatelyAvailableMetadataOnly, error: nil) { (readUrl) in
            do {
                let attributes = try FileManager.default.attributesOfItem(atPath: readUrl.path)
                modDate = attributes[.modificationDate] as? Date
            } catch let err {
                Logger.log(tag: .upload, error: err, message: "FileManager failed to read the modification date of \(fileUrl)")
            }
        }
        return modDate
    }
    
    func tempFileFor(inFileURL: URL, uploadDirURL: URL) -> (originalFile:URL, tempFile:URL)? {
        // Normalize the file url--i.e. /private/var-->/var (see docs for
        // resolvingSymlinksInPath, which removes /private as a special case
        // even though /var is actually a symlink to /private/var in this case).
        let fileURL = inFileURL.resolvingSymlinksInPath()
        
        // Use a UUID for the temp file's name
        let tempFileURL = uploadDirURL.appendingPathComponent(UUID().uuidString)
        
        // Copy the file to the temp file
        guard copyFile(from: fileURL, to: tempFileURL) else {
            return nil
        }
        
        // "touch" the temp file for retry accounting purposes
        self.touch(fileUrl: tempFileURL)
        
        return (fileURL, tempFileURL)
    }
    
    func copyFile(from fileURL: URL, to tempFileURL: URL) -> Bool {
        // Use a NSFileCoordinator to make a temp local copy so the app can delete
        // the original as soon as the upload call returns.
        let coordinator = NSFileCoordinator(filePresenter: nil)
        var coordError: NSError?
        var copyError: Any?
        coordinator.coordinate(readingItemAt: fileURL, options: .forUploading, writingItemAt: tempFileURL, options: NSFileCoordinator.WritingOptions(rawValue: 0), error: &coordError) { (readURL, writeURL) in
            do {
                try FileManager.default.copyItem(at: readURL, to: writeURL)
            } catch let err {
                Logger.log(tag: .upload, error: err, message: "Error copying upload file \(fileURL) to temp file \(tempFileURL) for upload.")
                copyError = err
            }
        }
        if copyError != nil {
            return false
        }
        if let err = coordError {
            Logger.log(tag: .upload, error: err, message: "File coordinator error copying upload file \(fileURL) to temp file \(tempFileURL) for upload.")
            return false
        }
        return true
    }
    
    func mimeTypeFor(fileUrl: URL) -> String {
        guard let typeRef = UTTypeReference(filenameExtension: fileUrl.pathExtension),
              let mimeType = typeRef.preferredMIMEType else {
            return "application/octet-stream"
        }
        return mimeType
    }
    
    func fileIsADayOld(invariantFilePath: String, fileUrl: inout URL!) -> Bool {
        let oneDay: TimeInterval = 60 * 60 * 24
        let fullPath = self.fullyQualifiedPath(of: invariantFilePath)
        fileUrl = URL(fileURLWithPath: fullPath)
        guard let modDate = self.modificationDate(of: fileUrl) else { return false }
        return Date().timeIntervalSince(modDate) > oneDay
    }

    func removeTempFile(filePath: String) {
        let fullPath = self.fullyQualifiedPath(of: filePath)
        guard FileManager.default.fileExists(atPath: fullPath) else {
            let message = "Unexpected: Attempting to clean up temp file with invariant path '\(filePath) but temp file does not exist at '\(fullPath)"
            Logger.log(tag: .upload, error: BridgeUnexpectedNullError(category: .missingFile, message: message))
            return
        }
        let tempFile = URL(fileURLWithPath: fullPath)
        let coordinator = NSFileCoordinator(filePresenter: nil)
        var fileCoordinatorError: NSError?
        coordinator.coordinate(writingItemAt: tempFile, options: .forDeleting, error: &fileCoordinatorError) { fileUrl in
            do {
                try FileManager.default.removeItem(at: fileUrl)
            } catch let err {
                Logger.log(tag: .upload, error: err, message: "Error attempting to remove file at \(fileUrl)")
            }
        }
        if let fileCoordinatorError = fileCoordinatorError {
            Logger.log(tag: .upload, error: fileCoordinatorError, message: "Error coordinating deletion of file \(tempFile)")
        }
    }
    
    lazy var appGroupIdentifier: String? = IOSBridgeConfig().appGroupIdentifier.flatMap { $0.isEmpty ? nil : $0 } {
        didSet {
            if oldValue != appGroupIdentifier {
                self.baseDirectory = getBaseDirectory()
                self.sandboxRegex = getSandboxRegex()
            }
        }
    }
    
    lazy var baseDirectory: String = getBaseDirectory()
    private func getBaseDirectory() -> String {
        if let appGroupIdentifier = self.appGroupIdentifier,
           let baseDirUrl = FileManager.default.containerURL(forSecurityApplicationGroupIdentifier: appGroupIdentifier) {
            // normalize the path--i.e. /private/var-->/var (see docs for URL.resolvingSymlinksInPath, which removes /private as a special case
            // even though /var is actually a symlink to /private/var in this case)
            return baseDirUrl.pathResolvingAllSymlinks()
        }
        else {
            return NSHomeDirectory()
        }
    }
    
    private lazy var sandboxRegex: String = getSandboxRegex()
    private func getSandboxRegex() -> String {
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
    }
    
    func sandboxRelativePath(of url: URL) -> String {
        // normalize the path--i.e. /private/var-->/var (see docs for URL.resolvingSymlinksInPath, which removes /private as a special case
        // even though /var is actually a symlink to /private/var in this case)
        let normalizedPath = url.pathResolvingAllSymlinks()
        let range = normalizedPath.range(of: self.sandboxRegex, options: [.regularExpression])
        // if it didn't match the sandbox regex, this will just give back normalizedPath
        return String(normalizedPath[(range?.upperBound ?? normalizedPath.startIndex)...])
    }
    
    func fullyQualifiedPath(of path: String) -> String {
        // normalize the path--i.e. /private/var-->/var (see docs for URL.resolvingSymlinksInPath, which removes /private as a special case
        // even though /var is actually a symlink to /private/var in this case)
        let normalizedPath = URL(fileURLWithPath: path).pathResolvingAllSymlinks()

        // check if it's already a full path first
        guard let range = normalizedPath.range(of: self.sandboxRegex, options: [.regularExpression]), !range.isEmpty else {
            // nope, not already a full path
            return (self.baseDirectory as NSString).appendingPathComponent(path) as String
        }
        
        // if we matched the sandboxRegex it was a full path already
        // so just return the normalized version of it.
        return normalizedPath
    }
    
    func fileURL(of path: String) -> URL {
        URL(fileURLWithPath: fullyQualifiedPath(of: path))
    }
    
    /// Return the file size of the file at this URL.
    func fileContentLength(_ fileUrl: URL) -> Int? {
        do {
            guard let contentLength = try fileUrl.resourceValues(forKeys: [.fileSizeKey]).fileSize,
                  contentLength > 0
            else {
                Logger.log(tag: .upload, error: BridgeUnexpectedNullError(category: .empty, message: "Error: file content length is nil or empty"))
                return nil
            }
            return contentLength
        } catch let err {
            Logger.log(tag: .upload, error: err, message: "Error trying to get content length of file at \(self)")
            return nil
        }
    }
    
    /// Return the MD5 hash for this file.
    func fileMD5String(_ fileUrl: URL) -> String? {
        do {
            let fileData = try Data(contentsOf: fileUrl, options: [.alwaysMapped, .uncached])
            return fileData.md5base64()
        } catch let err {
            Logger.log(tag: .upload, error: err, message: "Error trying to get memory-mapped data of participant file at \(self) in order to calculate its base64encoded MD5 hash.")
            return nil
        }
    }

}

extension URL {
    
    /// Resolves any symlinks in the path of a file URL.
    ///
    /// If the `isFileURL` is false, this method returns `self.path`.
    func pathResolvingAllSymlinks() -> String {
        guard self.isFileURL else { return path }
        // resolvingSymlinksInPath will only work if the file exists. This checks for the case where the file
        // has not been created yet. syoung 08/22/2022
        let path = self.resolvingSymlinksInPath().path
        let privatePrefix = "/private"
        if path.hasPrefix(privatePrefix) {
            return String(path[privatePrefix.endIndex...])
        }
        else {
            return path
        }
    }
}

extension FileManager {
    func sharedAppSupportDirectory() throws -> URL {
        if let appGroupId = IOSBridgeConfig().appGroupIdentifier,
           let url = self.containerURL(forSecurityApplicationGroupIdentifier: appGroupId) {
            return url
        }
        else {
            return try self.url(for: .applicationSupportDirectory, in: .userDomainMask, appropriateFor: nil, create: true)
        }
    }
}

extension Data {
    // adapted from https://stackoverflow.com/a/32166735
    func md5base64() -> String {
        let length = Int(CC_MD5_DIGEST_LENGTH)
        var digestData = Data(count: length)
        _ = digestData.withUnsafeMutableBytes { digestBytes -> UInt8 in
            self.withUnsafeBytes { messageBytes -> UInt8 in
                if let messageBytesBaseAddress = messageBytes.baseAddress, let digestBytesBlindMemory = digestBytes.bindMemory(to: UInt8.self).baseAddress {
                    let messageLength = CC_LONG(self.count)
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
}


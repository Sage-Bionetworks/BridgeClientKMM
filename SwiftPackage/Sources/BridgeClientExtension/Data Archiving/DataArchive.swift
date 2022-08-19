//
//  DataArchive.swift
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
import BridgeArchiver
import JsonModel

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
    
    /// Has the archive been zipped?
    public final internal(set) var isCompleted: Bool = false
    
    /// The local file URL for the encrypted archive.
    public final private(set) var encryptedURL: URL?
    
    /// A list of all the files included in the archive.
    public var files: [FileEntry] {
        archiver.files
    }
    
    public init?(identifier: String) {
        guard let archiver = BridgeArchiver() else { return nil }
        self.archiver = archiver
        self.identifier = identifier
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
            debugPrint("File size exceeds allowed limit. filepath=\(filepath), filesize=\(data.count)")
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
            
            let outputDirectory = try fileManager.url(for: .documentDirectory, in: .userDomainMask, appropriateFor: nil, create: true)
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
            debugPrint("Copied archive to \(debugURL)")
            
        } catch let err {
            debugPrint("Failed to copy archive: \(err)")
        }
    }
    #endif
}


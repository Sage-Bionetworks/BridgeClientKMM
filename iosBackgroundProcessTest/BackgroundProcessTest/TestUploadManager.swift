// Created 8/29/23
// swift-tools-version:5.0

import Foundation

/// Fake upload manager that is used to test background processing
class TestUploadManager : NSObject, BackgroundProcessSyncDelegate {

    lazy var syncManager: BackgroundProcessSyncManager = .init(delegate: self)
    
    let subdir = "UrbanDictionary"
    lazy var uploadDirURL: URL? = {
        do {
            let baseURL = try FileManager.default.sharedAppSupportDirectory()
            let url: URL
            if #available(iOS 16.0, *) {
                url = baseURL.appending(component: subdir, directoryHint: .isDirectory)
            } else {
                url = baseURL.appendingPathComponent(subdir)
            }
            try FileManager.default.createDirectory(at: url, withIntermediateDirectories: true, attributes: nil)
            return url
        } catch {
            Logger.log(tag: .upload, error: error, message: "Error trying to create the uploads directory.")
            return nil
        }
    }()
    
    @MainActor
    func onLaunch(backgroundProcessId: String?) {
        syncManager.onLaunch(backgroundProcessId: backgroundProcessId)
    }
    
    var shouldScheduleBackgroundProcess: Bool {
        true
    }
    
    func retryBackgroundProcess(isBackground: Bool) async throws {
        let dir = uploadDirURL!
        for ii in 0..<10 {
            print("retry: START \(ii)")
            let url = testURL()
            let (data, _) = try await URLSession.shared.data(from: url)
            let fileURL = dir.appendingPathComponent("\(UUID()).json")
            try data.write(to: fileURL)
            try await Task.sleep(nanoseconds: 5 * 1_000_000_000)
            print("retry: END \(ii)")
        }
    }

    func testURL() -> URL {
        URL(string: "https://www.urbandictionary.com/random.php")!
    }
}

extension FileManager {
    func sharedAppSupportDirectory() throws -> URL {
        try self.url(for: .applicationSupportDirectory, in: .userDomainMask, appropriateFor: nil, create: true)
    }
}


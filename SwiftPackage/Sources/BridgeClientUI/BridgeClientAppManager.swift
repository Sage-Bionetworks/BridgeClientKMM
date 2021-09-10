//
//  BridgeClientAppManager.swift
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

import SwiftUI
import BridgeClient
import JsonModel


fileprivate let kOnboardingStateKey = "isOnboardingFinished"

public let kPreviewStudyId = "xcode_preview"

open class BridgeClientAppManager : ObservableObject {
    
    public enum AppState : String {
        case launching, login, onboarding, main
    }

    public let isPreview: Bool
    public let platformConfig: IOSPlatformConfig
    public let pemPath: String?
        
    @Published public var title: String
    @Published public var appState: AppState = .launching
    @Published public var isUploadingResults: Bool = false
    
    @Published public var appConfig: AppConfig? {
        didSet {
            updateAppState()
        }
    }
    
    @Published public var userSessionInfo: UserSessionInfo? {
        didSet {
            didSetUserSessionInfo(oldValue: oldValue)
            updateAppState()
        }
    }
    
    open func didSetUserSessionInfo(oldValue: UserSessionInfo?) {
        // Do nothing. Allows subclass override of `userSessionInfo.didSet`.
    }
    
    @Published public var isOnboardingFinished: Bool = UserDefaults.standard.bool(forKey: kOnboardingStateKey) {
        didSet {
            UserDefaults.standard.set(isOnboardingFinished, forKey: kOnboardingStateKey)
            updateAppState()
        }
    }
    
    private var appConfigManager: NativeAppConfigManager!
    public private(set) var authManager: NativeAuthenticationManager!
    
    /// The local notification manager is a singleton that can be set up as the notification delegate (to handle snoozing)
    lazy public var localNotificationManager : LocalNotificationManager = LocalNotificationManager()
    
    public convenience init(appId: String, pemPath: String? = nil) {
        self.init(platformConfig: PlatformConfigImpl(appId: appId), pemPath: pemPath)
    }
    
    public init(platformConfig: IOSPlatformConfig, pemPath: String? = nil) {
        self.pemPath = pemPath ?? Bundle.main.path(forResource: platformConfig.appId, ofType: "pem")
        self.platformConfig = platformConfig
        self.title = self.platformConfig.localizedAppName
        self.isPreview = (platformConfig.appId == kPreviewStudyId)
        if !self.isPreview {
            IOSBridgeConfig().initialize(platformConfig: self.platformConfig)
        }

        // Set up the background network manager singleton and make us its app manager
        let bnm = BackgroundNetworkManager.shared
        bnm.appManager = self
}
    
    public func appWillFinishLaunching(_ launchOptions: [UIApplication.LaunchOptionsKey : Any]? ) {

        // Initialize koin
        #if DEBUG
            let enableNetworkLogs = true
        #else
            let enableNetworkLogs = false
        #endif
        KoinKt.doInitKoin(enableNetworkLogs: enableNetworkLogs)
        
        // Hook up app config
        self.appConfigManager = NativeAppConfigManager() { appConfig, _ in
            self.appConfig = appConfig ?? self.appConfig
        }
        self.appConfigManager.observeAppConfig()
        
        // Hook up user session info
        self.authManager = NativeAuthenticationManager() { userSessionInfo in
            guard userSessionInfo == nil || !userSessionInfo!.isEqual(userSessionInfo) else { return }
            self.userSessionInfo = userSessionInfo
        }
        self.userSessionInfo = self.authManager.session()
        self.authManager.observeUserSessionInfo()
        
        // Update the app state
        updateAppState()
    }
    
    public func handleEvents(for backgroundSession: String, completionHandler: @escaping () -> Void) {
        BackgroundNetworkManager.shared.restore(backgroundSession: backgroundSession, completionHandler: completionHandler)
    }
    
    public func loginWithExternalId(_ externalId: String, password: String, completion: @escaping ((BridgeClient.ResourceStatus) -> Void)) {
        self.authManager.signInExternalId(externalId: externalId, password: password) { (userSessionInfo, status) in
            guard status == ResourceStatus.success || status == ResourceStatus.failed else { return }
            self.userSessionInfo = userSessionInfo
            completion(status)
        }
    }
    
    public func signOut() {
        authManager.signOut()
        isOnboardingFinished = false
        userSessionInfo = nil
    }
    
    private func updateAppState() {
        if appConfig == nil {
            appState = .launching
        }
        else if userSessionInfo == nil {
            appState = .login
        }
        else if !isOnboardingFinished {
            appState = .onboarding
        }
        else {
            appState = .main
        }
    }
    
    public func encryptAndUpload(_ archives: [DataArchive]) {
        DispatchQueue.global().async {

            // Encrypt the files.
            var encryptedArchives = [String : URL]()
            if let path = self.pemPath {
                archives.forEach { archive in
                    do {
                        let encryptedArchive = try archive.encryptArchive(using: path)
                        encryptedArchives[archive.identifier] = encryptedArchive
                    } catch let err {
                        print("Failed to encrypt archive. \(err)")
                    }
                }
            }

            DispatchQueue.main.async {
                self.isUploadingResults = true
                encryptedArchives.forEach { (id, url) in
                    // TODO: emm 2021-08-19 Find out what metadata scientists want us to mark uploads with for
                    // exporter v3, and figure out how to get it here--maybe by putting it on the DataArchive?
                    // In any case, it needs to consist of Json key-value pairs.
                    let exporterV3Metadata: JsonElement? = nil
                    let extras = StudyDataUploadExtras(encrypted: true, metadata: exporterV3Metadata, zipped: true)
                    StudyDataUploadAPI.shared.upload(fileId: id, fileUrl: url, contentType: "application/zip", extras: extras)
                    do {
                        try FileManager.default.removeItem(at: url)
                    } catch let err {
                        print("Failed to delete encrypted archive \(id) at \(url). \(err)")
                    }
                }
            }
        }
    }
}


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

/// This class is intended to be used as the `BridgeClient` app singleton. It manages login, app state,
/// app configuration, user configuration, notifications, and uploading files to Bridge services. It is intended
/// to be used in conjunction with a `UIApplicationDelegate` to handle start up and background
/// uploading.
///
/// At a minimum, the app must implement the following methods in the app delegate:
/// ```
/// class AppDelegate: UIResponder, UIApplicationDelegate {
///     let bridgeManager = BridgeClientAppManager(appId: PrivateKeys.shared.appId, pemPath: PrivateKeys.shared.pemPath)
///
///     func application(_ application: UIApplication, willFinishLaunchingWithOptions launchOptions: [UIApplication.LaunchOptionsKey : Any]?) -> Bool {
///         bridgeManager.appWillFinishLaunching(launchOptions)
///         return super.application(application, willFinishLaunchingWithOptions: launchOptions)
///     }
///
///     func application(_ application: UIApplication, handleEventsForBackgroundURLSession identifier: String,
///        completionHandler: @escaping () -> Void) {
///         bridgeManager.handleEvents(for: identifier, completionHandler: completionHandler)
///     }
/// }
/// ```
///
/// - SeeAlso: ``SingleStudyAppManager`` which subclasses ``BridgeClientAppManager``
///             to support features of a single study sign-in that is required to get a timeline for the participant.
/// 
open class BridgeClientAppManager : ObservableObject {
    
    /// The  "state" of the app. SwiftUI relies upon observance patterns that do not work with Kotlin classes
    /// because those classes are not threadsafe. The state handling of SwiftUI relies upon being able to
    /// process observed changes on a background thread so the Kotlin classes must be wrapped. This
    /// state enum is used to allow the app content view to change the UI to match the login state.
    ///
    /// - Example:
    /// ```
    ///    struct ContentView: View {
    ///        @EnvironmentObject var bridgeManager: SingleStudyAppManager
    ///        @StateObject var todayViewModel: TodayTimelineViewModel = .init()
    ///
    ///        var body: some View {
    ///            switch bridgeManager.appState {
    ///            case .launching:
    ///                LaunchView()
    ///            case .login:
    ///                LoginView()
    ///            case .onboarding:
    ///                OnboardingView()
    ///            case .main:
    ///                MainView()
    ///                    .environmentObject(todayViewModel)
    ///                    .assessmentInfoMap(.init(extensions: MTBIdentifier.allCases))
    ///                    .fullScreenCover(isPresented: $todayViewModel.isPresentingAssessment) {
    ///                        MTBAssessmentView(todayViewModel)
    ///                            .edgesIgnoringSafeArea(.all)
    ///                    }
    ///                    .statusBar(hidden: todayViewModel.isPresentingAssessment)
    ///            }
    ///        }
    ///    }
    /// ```
    public enum AppState : String {
        case launching, login, onboarding, main
    }

    /// Is this manager used for previewing the app? (Unit tests, SwiftUI Preview, etc.)
    public let isPreview: Bool
    
    /// The configuration bits that need to be set on the 'BridgeClient.xcframework' in order to connect to
    /// Bridge services.
    public let platformConfig: IOSPlatformConfig
    
    /// The path to the pem file that is used to encrypt data being uploaded to Bridge.
    ///
    /// - Note: Data should be encrypted so that it is not stored insecurely on the phone (while waiting
    ///         for an upload connection).
    public let pemPath: String?
        
    /// The title of the app to display. By default, this is the localized display name of the app that is shown
    /// to the participant in their phone home screen.
    @Published public var title: String
    
    /// The "state" of the app.
    @Published public var appState: AppState = .launching
    
    /// Is the app currently uploading results?
    /// TODO: syoung 10/27/2021 This flag is currently never being reset. https://sagebionetworks.jira.com/browse/BMC-244
    @Published public var isUploadingResults: Bool = false
    
    /// A threadsafe observer for the `BridgeClient.UserSessionInfo` for the current user.
    public let appConfig: AppConfigObserver = .init()
    
    // Do not expose publicly. This class is not threadsafe.
    var config: AppConfig? {
        didSet {
            appConfig.appConfig = config
            didUpdateAppConfig()
            updateAppState()
        }
    }
    
    /// Called when the `BridgeClient.AppConfig` is updated.
    func didUpdateAppConfig() {
        // Do nothing. Allows subclass override of `config.didSet`.
    }
    
    /// A threadsafe observer for the `BridgeClient.UserSessionInfo` for the current user.
    public let userSessionInfo: UserSessionInfoObserver = .init()
    
    // Do not expose publicly. This class is not threadsafe.
    var session: UserSessionInfo? {
        didSet {
            userSessionInfo.userSessionInfo = session
            didUpdateUserSessionInfo()
            updateAppState()
        }
    }
    
    /// Called when the `BridgeClient.UserSessionInfo` is updated.
    func didUpdateUserSessionInfo() {
        // Do nothing. Allows subclass override of `session.didSet`.
    }
    
    /// Has the participant been shown the onboarding flow?
    @Published public var isOnboardingFinished: Bool = UserDefaults.standard.bool(forKey: kOnboardingStateKey) {
        didSet {
            UserDefaults.standard.set(isOnboardingFinished, forKey: kOnboardingStateKey)
            updateAppState()
        }
    }
    
    private var appConfigManager: NativeAppConfigManager!
    internal private(set) var authManager: NativeAuthenticationManager!
    
    /// The local notification manager is a singleton that can be set up as the notification delegate (to handle snoozing).
    lazy public var localNotificationManager : LocalNotificationManager = LocalNotificationManager()
    
    /// Convenience initializer for intializing a bridge manager with just an app id and pem file.
    ///
    /// Both the APP ID and the CMS Public Key (ie. pem file) are accessible through the [Bridge Study Manager](https://research.sagebridge.org).
    /// Once logged into an "app" (which can host multiple "studies"), select "Server Config -> Settings" from the menu.
    ///
    /// - Parameters:
    ///   - appId: The "APP ID" is shown in the upper right corner of the [Bridge Study Manager](https://research.sagebridge.org).
    ///   - pemPath: The path to the pem file (as an embedded resource) to use for encrypting uploads. The pem file can be downloaded
    ///     from the [Bridge Study Manager](https://research.sagebridge.org) by going "Server Settings -> Settings"
    ///     and tapping on the button labeled "Download CMS Public Key..." and saving the file to a secure location.
    public convenience init(appId: String, pemPath: String? = nil) {
        self.init(platformConfig: PlatformConfigImpl(appId: appId), pemPath: pemPath)
    }
    
    /// Initialize the bridge manager with a custom platform config.
    ///
    /// - Parameters:
    ///   - platformConfig: The platform config to use to set up the connection to Bridge.
    ///   - pemPath: The path to the location of the pem file to use when encrypting uploads.
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
        
        // Register the file upload APIs so that retries can happen
        let _ = ParticipantFileUploadAPI.shared
        let _ = StudyDataUploadAPI.shared
    }
    
    /// **Required:** This method should be called by the app delegate when the app is launching in either `willLaunch` or `didLaunch`.
    open func appWillFinishLaunching(_ launchOptions: [UIApplication.LaunchOptionsKey : Any]? ) {

        // Initialize koin
        #if DEBUG
            let enableNetworkLogs = true
        #else
            let enableNetworkLogs = false
        #endif
        KoinKt.doInitKoin(enableNetworkLogs: enableNetworkLogs)
        
        // Hook up app config
        self.appConfigManager = NativeAppConfigManager() { appConfig, _ in
            self.config = appConfig ?? self.config
        }
        self.appConfigManager.observeAppConfig()
        
        // Hook up user session info
        self.authManager = NativeAuthenticationManager() { userSessionInfo in
            guard userSessionInfo == nil || !userSessionInfo!.isEqual(userSessionInfo) else { return }
            self.session = userSessionInfo
        }
        self.session = self.authManager.session()
        self.authManager.observeUserSessionInfo()
        
        // Update the app state
        updateAppState()
    }
    
    /// **Required:** This method should be called by the app delegate in the implementation of
    /// `application(:, handleEventsForBackgroundURLSession:, completionHandler:)` and is used to
    /// restore a background upload session.
    public final func handleEvents(for backgroundSession: String, completionHandler: @escaping () -> Void) {
        BackgroundNetworkManager.shared.restore(backgroundSession: backgroundSession, completionHandler: completionHandler)
    }
    
    /// Login with the given external ID and password.
    ///
    /// - Parameters:
    ///   - externalId: The external ID to use as the signin credentials.
    ///   - password: The password to use as the signin credentials.
    ///   - completion: The completion handler that is called with the server response.
    public final func loginWithExternalId(_ externalId: String, password: String, completion: @escaping ((BridgeClient.ResourceStatus) -> Void)) {
        self.authManager.signInExternalId(externalId: externalId, password: password) { (userSessionInfo, status) in
            guard status == ResourceStatus.success || status == ResourceStatus.failed else { return }
            self.session = userSessionInfo
            completion(status)
        }
    }
    
    /// Sign out the current user.
    open func signOut() {
        localNotificationManager.clearAll()
        authManager.signOut()
        isOnboardingFinished = false
        self.session = nil
    }
    
    // @Protected - Only this class should call this method and only subclasses should implement.
    func updateAppState() {
        if appConfig.isLaunching {
            appState = .launching
        }
        else if !userSessionInfo.isAuthenticated {
            appState = .login
        }
        else if !isOnboardingFinished {
            appState = .onboarding
        }
        else {
            appState = .main
        }
    }
    
    /// Encrypt and upload the given data archives.
    ///
    /// - Parameter archives: The archives to encrypt and upload.
    public final func encryptAndUpload(_ archives: [DataArchive]) {
        DispatchQueue.global().async {

            // Encrypt the files.
            if let path = self.pemPath {
                archives.forEach { archive in
                    do {
                        try archive.encryptArchive(using: path)
                    } catch let err {
                        print("ERROR: Failed to encrypt \(archive.identifier). \(err)")
                    }
                }
            }

            DispatchQueue.main.async {
                self.isUploadingResults = true
                archives.forEach { archive in
                    var exporterV3Metadata: JsonElement? = nil
                    if let schedule = (archive as? AbstractResultArchive)?.schedule {
                        exporterV3Metadata = JsonElement([
                            "instanceGuid": schedule.instanceGuid,
                            "eventTimestamp": schedule.session.eventTimestamp
                        ])
                    }
                    let extras = StudyDataUploadExtras(encrypted: true, metadata: exporterV3Metadata, zipped: true)
                    let id = archive.identifier
                    guard let url = archive.encryptedURL else {
                        print("WARNING! Cannot upload \(id)")
                        return
                    }
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


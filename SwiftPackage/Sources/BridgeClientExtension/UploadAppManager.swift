//
//  UploadAppManager.swift
//
//

import Foundation
import BridgeClient
import JsonModel

public let kPreviewStudyId = "xcode_preview"
public let kStudyIdKey = "studyId"
fileprivate let kUserSessionIdKey = "userSessionId"

open class UploadAppManager : ObservableObject {
    
    /// The configuration bits that need to be set on the 'BridgeClient.xcframework' in order to connect to
    /// Bridge services.
    public let platformConfig: IOSPlatformConfig
    
    /// Is this manager used for previewing the app? (Unit tests, SwiftUI Preview, etc.)
    public let isPreview: Bool
    
    /// The UserDefaults that should be used for this app.
    public var sharedUserDefaults: UserDefaults
    
    /// Has the participant previously logged in successfully (either now or previously)?
    public var hasLoggedIn: Bool {
        userSessionId != nil
    }
    
    /// Is this a new login?
    public var isNewLogin: Bool = true
    
    /// Store the last user session id used for login.
    var userSessionId: String? {
        get { sharedUserDefaults.string(forKey: kUserSessionIdKey) }
        set {
            sharedUserDefaults.set(newValue, forKey: kUserSessionIdKey)
            Logger.logWriter?.setUserId(newValue)
        }
    }

    /// The path to the pem file that is used to encrypt data being uploaded to Bridge.
    ///
    /// - Note: Data should be encrypted so that it is not stored insecurely on the phone (while waiting
    ///         for an upload connection).
    public var pemPath: String? { self.uploadProcessor.pemPath }
        
    /// The title of the app to display. By default, this is the localized display name of the app that is shown
    /// to the participant in their phone home screen.
    @Published public var title: String
    
    /// Is the app currently uploading results or user files? This status is maintained and updated by BridgeFileUploadManager.
    @Published public var isUploading: Bool = false {
        didSet {
            updateNetworkMonitoring()
        }
    }
    
    /// Is the app currently connected to the internet? This status is only monitored if the app is uploading data.
    @Published public var networkStatus: NetworkStatus = .unknown
    
    /// The status of the app as reported by bridge services.
    @Published public var bridgeAppStatus: BridgeClient.AppStatus = .supported {
        didSet {
            updateAppState()
        }
    }
    
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
    open func didUpdateAppConfig() {
        // Do nothing. Allows subclass override of `config.didSet`.
    }
    
    /// A threadsafe observer for the `BridgeClient.UserSessionInfo` for the current user.
    public let userSessionInfo: UserSessionInfoObserver = .init()
    
    var sessionToken: String? {
        authManager.session().flatMap { $0.sessionToken.isEmpty ? nil : $0.sessionToken }
    }
    
    // Do not expose publicly. This class is not threadsafe.
    private var session: UserSessionInfo?
    
    /// Called when the `BridgeClient.UserSessionInfo` is updated.
    open func didUpdateUserSessionInfo() {
        // Do nothing. Allows subclass override of `session.didSet`.
    }
    
    enum UpdateUserSessionType : Int {
        case launch, login, signout, observed
    }
    
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
    public enum AppState : String, StringEnumSet, Comparable {
        case launching, login, onboarding, main, error
    }
    
    /// The "state" of the app.
    @Published public var appState: AppState = .launching
    
    /// Call to set up the user session before callback from the observer fires.
    @MainActor
    public final func handleUserLogin(_ session: UserSessionInfo?) {
        updateUserSessionStatus(session, updateType: .login)
    }
    
    @MainActor
    final func updateUserSessionStatus(_ session: UserSessionInfo?, updateType: UpdateUserSessionType) {
        if updateType == .observed, let oldSession = self.session, oldSession.isEqual(session) {
            // If the old session and the new session haven't changed and the message was sent by the observer,
            // then just return without updating state.
            return
        }
        
        let oldToken = self.session?.sessionToken
        
        Logger.log(severity: .info, message: "Updating UserSessionInfo. updateType='\(updateType)', sessionToken='\(session?.sessionToken ?? "NULL")'")
        
        self.session = session
        updateNetworkMonitoring()
        self.isNewLogin = (updateType == .login || updateType == .signout)
        self.uploadProcessor.isTestUser = session?.dataGroups?.contains("test_user") ?? false
        if updateType == .login {
            // If this is a login, then update the stored user session id
            self.userSessionId = session?.id
        }
        else if updateType == .signout {
            // If this is a signout, then nil out the stored user session id
            self.userSessionId = nil
        }
        self.userSessionInfo.userSessionInfo = session
        
        // If this app has custom handling of a failure to reauthenticate, then exit early.
        if updateType == .observed || updateType == .launch,
           userSessionInfo.loginState == .reauthFailed,
           handleReauthFailed() {
           return
        }

        didUpdateUserSessionInfo()
        updateAppState()
        
        // If we have a session token and it is different from the old one then check orphaned files.
        if let newToken = session?.sessionToken, !newToken.isEmpty, newToken != oldToken {
            Logger.log(severity: .info, message: "Session token updated: newToken='\(newToken)', oldToken='\(oldToken ?? "")'")
            uploadManagerV1.onSessionTokenChanged()
        }
    }
    
    private let uploadProcessor: ArchiveUploadProcessor
    private let backgroundProcessId: String?
    private var appConfigManager: NativeAppConfigManager!
    public private(set) var authManager: NativeAuthenticationManager!
    private var pendingUploadObserver: PendingUploadObserver!
    let backgroundNetworkManager: BackgroundNetworkManager = .init()
    lazy private(set) var uploadManagerV1: BridgeFileUploadManager = .init(netManager: backgroundNetworkManager, appManager: self)
    lazy private(set) var uploadManagerV2: UploadManager = .init(backgroundNetworkManager: backgroundNetworkManager)
    
    /// Convenience initializer for intializing a bridge manager with just required properties.
    ///
    /// Both the APP ID and the CMS Public Key (ie. pem file) are accessible through the [Bridge Study Manager](https://research.sagebridge.org).
    /// Once logged into an "app" (which can host multiple "studies"), select "Server Config -> Settings" from the menu.
    ///
    /// - Parameters:
    ///   - appId: The "APP ID" is shown in the upper right corner of the [Bridge Study Manager](https://research.sagebridge.org).
    ///   - pemPath: The path to the pem file (as an embedded resource) to use for encrypting uploads. The pem file can be downloaded
    ///     from the [Bridge Study Manager](https://research.sagebridge.org) by going "Server Settings -> Settings"
    ///     and tapping on the button labeled "Download CMS Public Key..." and saving the file to a secure location.
    ///   - backgroundProcessId: The background process ID registered in the "info.plist" used to allow processing pending uploads
    ///     in the background.
    ///   - appGroupId: The app group ID to use when setting up files that are shared with an app extension.
    ///   - defaultConsentGuid: The default consent guid for this app (where the app includes in-app consent).
    public convenience init(appId: String, pemPath: String, backgroundProcessId: String, appGroupId: String? = nil, defaultConsentGuid: String? = nil) {
        self.init(platformConfig: PlatformConfigImpl(appId: appId, appGroupIdentifier: appGroupId, defaultConsentGuid: defaultConsentGuid), pemPath: pemPath, backgroundProcessId: backgroundProcessId)
    }
    
    public enum MockType {
        case unitTest, preview
    }
    
    /// A special manager that is used in unit testing and SwiftUI preview.
    /// - Parameter mockType: The type of mock manager to initialize.
    public convenience init(mockType: MockType) {
        let appId = mockType == .preview ? kPreviewStudyId : "not-a-real-appid"
        self.init(appId: appId, pemPath: "", backgroundProcessId: "")
    }
    
    @available(*, deprecated, message: "Use initializer with non-nil pem path and background process Id")
    public convenience init(appId: String, appGroupId: String? = nil, pemPath: String? = nil, defaultConsentGuid: String? = nil) {
        self.init(platformConfig: PlatformConfigImpl(appId: appId, appGroupIdentifier: appGroupId, defaultConsentGuid: defaultConsentGuid), pemPath: pemPath)
    }
    
    @available(*, deprecated, message: "Use initializer with non-nil pem path and background process Id")
    public convenience init(platformConfig: IOSPlatformConfig, pemPath: String? = nil) {
        let pemPath = pemPath ?? Bundle.main.path(forResource: platformConfig.appId, ofType: "pem") ?? ""
        self.init(platformConfig: platformConfig, pemPath: pemPath, backgroundProcessId: "")
    }
    
    /// Initialize the bridge manager with a custom platform config.
    ///
    /// - Parameters:
    ///   - platformConfig: The platform config to use to set up the connection to Bridge.
    ///   - pemPath: The path to the location of the pem file to use when encrypting uploads.
    ///   - backgroundProcessId: The background process ID registered in the "info.plist" used to allow processing pending uploads in the background.
    public init(platformConfig: IOSPlatformConfig, pemPath: String, backgroundProcessId: String) {
        self.title = platformConfig.localizedAppName
        self.platformConfig = platformConfig
        
        self.isPreview = (platformConfig.appId == kPreviewStudyId)
        if !self.isPreview {
            self.sharedUserDefaults = platformConfig.appGroupIdentifier.flatMap { .init(suiteName: $0) } ?? .standard
            IOSBridgeConfig().initialize(platformConfig: self.platformConfig)
        }
        else {
            self.sharedUserDefaults = UserDefaults.standard
        }
        
        // Create the archive upload processor
        self.uploadProcessor = .init(pemPath: pemPath, sharedUserDefaults: self.sharedUserDefaults)
        self.backgroundProcessId = backgroundProcessId.isEmpty ? nil : backgroundProcessId
        
        // Is this a new login (in which case we need to get the adherence records)
        self.isNewLogin = (self.userSessionId == nil)
    }
    
    /// **Required:** This method should be called by the app delegate when the app is launching in either `willLaunch` or `didLaunch`.
    @MainActor
    public func setup() {
        
        // Before anything else, set the user id so that failures in setup have that information.
        Logger.logWriter?.setUserId(userSessionId)

        // Initialize koin
        Logger.log(severity: .info, message: "Initializing Koin")
        #if DEBUG
            let enableNetworkLogs = true
        #else
            let enableNetworkLogs = false
        #endif
        KoinKt.doInitKoin(enableNetworkLogs: enableNetworkLogs)
        
        // Setup upload processor
        Logger.log(severity: .info, message: "Hook up upload processor")
        self.uploadProcessor.uploadManager = uploadManagerV2
        
        // Hook up app config
        Logger.log(severity: .info, message: "Hook up app config")
        self.appConfigManager = NativeAppConfigManager() { appConfig, _ in
            self.config = appConfig ?? self.config
        }
        self.appConfigManager.observeAppConfig()
        
        // Hook up user session info and bridge app status
        Logger.log(severity: .info, message: "Hook up user session info and bridge app status")
        self.authManager = NativeAuthenticationManager() { userSessionInfo in
            self.updateUserSessionStatus(userSessionInfo, updateType: .observed)
        }
        Logger.log(severity: .info, message: "Getting current app status")
        self.bridgeAppStatus = self.authManager.currentAppStatus()
        self.authManager.observeAppStatus { status in
            DispatchQueue.main.async {
                self.bridgeAppStatus = status
            }
        }
        Logger.log(severity: .info, message: "Getting current session state")
        let userState = self.authManager.sessionState()
        self.userSessionInfo.loginError = userState.error
        if userState.error == nil {
            // Only update during launch if the call did not throw an exception.
            // Otherwise, we have to wait until the observer comes back.
            self.updateUserSessionStatus(session, updateType: .launch)
        }
        self.authManager.observeUserSessionInfo()
        
        // Hook up upload observer
        Logger.log(severity: .info, message: "Hook up upload observer")
        self.pendingUploadObserver = PendingUploadObserver() { count in
            self.isUploading = (count.intValue > 0)
        }
        self.pendingUploadObserver.observePendingUploadCount()
        
        // Setup the upload manager
        Logger.log(severity: .info, message: "Setup the upload manager")
        self.uploadManagerV2.onLaunch(backgroundProcessId: backgroundProcessId)
    }
    
    /// **Required:** This method should be called by the app delegate in the implementation of
    /// `application(:, handleEventsForBackgroundURLSession:, completionHandler:)` and is used to
    /// restore a background upload session.
    @MainActor
    public final func handleEvents(for backgroundSession: String, completionHandler: @escaping () -> Void) {
        backgroundNetworkManager.restore(backgroundSession: backgroundSession, completionHandler: completionHandler)
    }
    
    /// Wrapper used to allow `BridgeClientAppManager` to call through to a single sign-in handler.
    public final func signInOrReauth(email: String?, externalId: String?, password: String, completion: @escaping ((BridgeClient.ResourceStatus) -> Void)) {
        if let email = email {
            self.authManager.signInEmail(userName: email, password: password) { (userSessionInfo, status) in
                self.finishSignIn(userSessionInfo: userSessionInfo, status: status, completion: completion)
            }
        }
        else if let externalId: String {
            self.authManager.signInExternalId(externalId: externalId, password: password) { (userSessionInfo, status) in
                self.finishSignIn(userSessionInfo: userSessionInfo, status: status, completion: completion)
            }
        }
        else {
            self.authManager.reauthWithCredentials(password: password) { (userSessionInfo, status) in
                self.finishSignIn(userSessionInfo: userSessionInfo, status: status, completion: completion)
            }
        }
    }
    
    final func finishSignIn(userSessionInfo: UserSessionInfo?, status: BridgeClient.ResourceStatus, completion: @escaping ((BridgeClient.ResourceStatus) -> Void)) {
        guard status != .pending else { return }
        Task {
            if status == .success || status == .failed {
                await self.handleUserLogin(userSessionInfo)
            }
            completion(status)
        }
    }
    
    /// If the app gets into a state where reauth fails, default behavior is to do nothing. App developer is responsible for overriding this
    /// and handling however is appropriate for their app.
    ///
    /// @Protected - Only this class should call this method and only subclasses should implement.
    /// - Returns: `true` if *this* app will handle reauth failures, otherwise `false` to use default handling (show login)
    @MainActor
    open func handleReauthFailed() -> Bool {
        // Default is to do nothing. App must decide how to handle this.
        false
    }
    
    /// Sign out the current user.
    @MainActor
    public final func signOut() {
        NotificationCenter.default.post(name: Self.BridgeClientWillSignOut, object: self)
        willSignOut()
        updateUserSessionStatus(nil, updateType: .signout)
        authManager.signOut()
        didSignOut()
        NotificationCenter.default.post(name: Self.BridgeClientDidSignOut, object: self)
    }
    
    /// A notification that the participant is about to be signed out.
    public static let BridgeClientWillSignOut: Notification.Name = .init("BridgeClientWillSignOut")
    
    /// A notification that the participant has been signed out.
    public static let BridgeClientDidSignOut: Notification.Name = .init("BridgeClientDidSignOut")
    
    /// The current user will sign out.
    /// @Protected - Only this class should call this method and only subclasses should implement.
    @MainActor
    open func willSignOut() {
    }
    
    /// The current user did sign out.
    /// @Protected - Only this class should call this method and only subclasses should implement.
    @MainActor
    open func didSignOut() {
    }
    
    /// @Protected - Only this class should call this method and only subclasses should implement.
    open func updateAppState() {
        // Do nothing. Allows subclass override setup and app state changes.
    }
    
    lazy private var networkMonitor: NetworkMonitor = .init() { [weak self] newStatus in
        guard let strongSelf = self else { return }
        Task {
            await MainActor.run {
                let oldStatus = strongSelf.networkStatus
                if newStatus == .connected, oldStatus != .unknown {
                    // only check for uploads if the new status is connected and the previous
                    // status was *not* connected.
                    strongSelf.uploadManagerV2.checkAndRetryUploads()
                }
                strongSelf.networkStatus = newStatus
            }
        }
    }
    
    private func updateNetworkMonitoring() {
        // This is not thread protected so it should always be called from the main thread
        if isUploading || !userSessionInfo.isAuthenticated {
            networkMonitor.startIfNeeded()
        }
        else {
            networkMonitor.cancel()
        }
    }
    
    /// Encrypt and upload an archive created with the given builder.
    ///
    /// - Parameter builder: The archive builder.
    public final func encryptAndUpload(using builder: ArchiveBuilder) {
        OperationQueue.main.addOperation {
            self.isUploading = true
        }
        uploadProcessor.encryptAndUpload(using: builder)
    }
    
    func notifyUIOfBridgeError(_ value: Int32, description: String) {
        DispatchQueue.main.async {
            self.authManager.notifyUIOfBridgeError(statusCode: .init(value: value, description: description))
        }
    }
    
    func reauthenticate(_ completion: @escaping (Bool) -> Void) {
        DispatchQueue.main.async {
            guard let authManager = self.authManager else {
                Logger.log(severity: .warn, message: "AuthManager has not been initialized. Cannot reauthenticate.")
                completion(false)
                return
            }
            
            authManager.reauth { error in
                if let error = error {
                    // Assume BridgeClientKMM will have handled any 410 or 412 error appropriately.
                    self.userSessionInfo.loginError = "Reauth Failed: \(error.message ?? "Unknown Error")"
                    Logger.log(severity: .warn, message: "Session token auto-refresh failed: \(error)")
                }
                completion(error == nil)
            }
        }
    }
}

/// A convenience method for ensuring that a given result is processed on the main thread.
func processResultOnMainThread<T>(_ process: () -> T?) -> T? {
    var ret: T? = nil
    if Thread.isMainThread {
        ret = process()
    } else {
        DispatchQueue.main.sync {
            ret = process()
        }
    }
    return ret
}

/// A convenience method for ensuring that a given result is processed on the main thread.
func processOnMainThread(_ process: () -> Void) {
    if Thread.isMainThread {
        process()
    } else {
        DispatchQueue.main.sync {
            process()
        }
    }
}

//
//  UploadAppManager.swift
//
//

import Foundation
import BridgeClient
import JsonModel
import Network

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
    public var pemPath: String? { uploadProcessor.pemPath }
    private let uploadProcessor: ArchiveUploadProcessor
        
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
    }
    
    private var appConfigManager: NativeAppConfigManager!
    public private(set) var authManager: NativeAuthenticationManager!
    
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
    public convenience init(appId: String, appGroupId: String? = nil, pemPath: String? = nil, defaultConsentGuid: String? = nil) {
        self.init(platformConfig: PlatformConfigImpl(appId: appId, appGroupIdentifier: appGroupId, defaultConsentGuid: defaultConsentGuid), pemPath: pemPath)
    }
    
    /// Initialize the bridge manager with a custom platform config.
    ///
    /// - Parameters:
    ///   - platformConfig: The platform config to use to set up the connection to Bridge.
    ///   - pemPath: The path to the location of the pem file to use when encrypting uploads.
    public init(platformConfig: IOSPlatformConfig, pemPath: String? = nil) {
        let pemPath = pemPath ?? Bundle.main.path(forResource: platformConfig.appId, ofType: "pem")
        self.uploadProcessor = .init(pemPath: pemPath)
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

        // Is this a new login (in which case we need to get the adherence records)
        self.isNewLogin = (self.userSessionId == nil)

        // Set up the background network manager singleton and make us its app manager
        let bnm = BackgroundNetworkManager.shared
        bnm.appManager = self
        
        // Register the file upload APIs so that retries can happen
        let _ = ParticipantFileUploadAPI.shared
        let _ = StudyDataUploadAPI.shared
    }
    
    /// **Required:** This method should be called by the app delegate when the app is launching in either `willLaunch` or `didLaunch`.
    @MainActor
    public func setup() {
        
        // Before anything else, set the user id so that failures in setup have that information.
        Logger.logWriter?.setUserId(userSessionId)

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
        
        // Hook up user session info and bridge app status
        self.authManager = NativeAuthenticationManager() { userSessionInfo in
            self.updateUserSessionStatus(userSessionInfo, updateType: .observed)
        }
        self.bridgeAppStatus = self.authManager.currentAppStatus()
        self.authManager.observeAppStatus { status in
            DispatchQueue.main.async {
                self.bridgeAppStatus = status
            }
        }
        let userState = self.authManager.sessionState()
        self.userSessionInfo.loginError = userState.error
        self.updateUserSessionStatus(userState.sessionInfo, updateType: .launch)
        self.authManager.observeUserSessionInfo()
    }
    
    /// **Required:** This method should be called by the app delegate in the implementation of
    /// `application(:, handleEventsForBackgroundURLSession:, completionHandler:)` and is used to
    /// restore a background upload session.
    @MainActor
    public final func handleEvents(for backgroundSession: String, completionHandler: @escaping () -> Void) {
        BackgroundNetworkManager.shared.restore(backgroundSession: backgroundSession, completionHandler: completionHandler)
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
        willSignOut()
        updateUserSessionStatus(nil, updateType: .signout)
        authManager.signOut()
        didSignOut()
    }
    
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
    
    private let networkMonitoringQueue = DispatchQueue(label: "org.sagebase.NetworkConnectivityMonitor.\(UUID())")
    private var networkMonitor: NWPathMonitor?
    
    private func updateNetworkMonitoring() {
        // This is not thread protected so it should always be called from the main thread
        if isUploading || !userSessionInfo.isAuthenticated {
            startMonitoringNetwork()
        }
        else {
            stopMonitoringNetwork()
        }
    }
    
    private func stopMonitoringNetwork() {
        networkMonitor?.cancel()
        networkMonitor = nil
    }

    private func startMonitoringNetwork() {
        guard networkMonitor == nil else { return }
        let networkMonitor = NWPathMonitor()
        self.networkMonitor = networkMonitor
        networkMonitor.pathUpdateHandler = { [weak self] path in
            guard let strongSelf = self else { return }
            DispatchQueue.main.async {
                switch path.status {
                case .unsatisfied:
                    if #available(iOS 14.2, *), path.unsatisfiedReason == .cellularDenied {
                        strongSelf.networkStatus = .cellularDenied
                    } else {
                        strongSelf.networkStatus = .notConnected
                    }
                case .satisfied:
                    strongSelf.networkStatus = .connected
                default:
                    strongSelf.networkStatus = .unknown
                }
            }
        }
        networkMonitor.start(queue: networkMonitoringQueue)
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
    
    /// Encrypt and upload the given data archives.
    ///
    /// - Parameter archives: The archives to encrypt and upload.
    public final func encryptAndUpload(_ archives: [DataArchive]) {
        OperationQueue.main.addOperation {
            self.isUploading = true
        }
        uploadProcessor.encryptAndUpload(archives)
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

final class ArchiveUploadProcessor {
    
    let pemPath: String?
    var isTestUser: Bool = false
    
    init(pemPath: String?) {
        self.pemPath = pemPath
    }
    
    func encryptAndUpload(using builder: ArchiveBuilder) {
        Task.detached(priority: .medium) {
            await self._encryptAndUpload(using: builder)
        }
    }
    
    @MainActor
    private func _encryptAndUpload(using builder: ArchiveBuilder) async {
        do {
            let archive = try await builder.buildArchive()
            // Copy the startedOn date (if available) from the builder to the archive.
            if let resultBuilder = builder as? ResultArchiveBuilder, archive.startedOn == nil {
                archive.startedOn = resultBuilder.startedOn
            }
            await _copyTest(archive: archive)
            let encrypted = await _encrypt(archive: archive)
            await _upload(archive: archive, encrypted: encrypted)
        } catch {
            Logger.log(error: error, message: "Failed to archive and upload \(builder.identifier)")
        }
    }
    
    func encryptAndUpload(_ archives: [DataArchive]) {
        Task.detached(priority: .medium) {
            await self._encryptAndUpload(archives)
        }
    }

    @MainActor
    private func _encryptAndUpload(_ archives: [DataArchive]) async {
        await withTaskGroup(of: Void.self) { group in
            archives.forEach { archive in
                group.addTask {
                    await self._copyTest(archive: archive)
                    let encrypted = await self._encrypt(archive: archive)
                    await self._upload(archive: archive, encrypted: encrypted)
                }
            }
        }
    }
    
    private func _copyTest(archive: DataArchive) async {
        #if DEBUG
        if isTestUser {
            archive.copyTestArchive()
        }
        #endif
    }
    
    private func _encrypt(archive: DataArchive) async -> Bool {
        guard let path = self.pemPath else { return false }
        do {
            try archive.encryptArchive(using: path)
            return true
        } catch {
            Logger.log(error: error, message: "Failed to encrypt \(archive.identifier)")
            return false
        }
    }
    
    @MainActor
    private func _upload(archive: DataArchive, encrypted: Bool) async {
        guard let url = archive.encryptedURL else {
            let message = "Cannot upload archive. Missing encryption."
            assertionFailure(message)   // Throw an assert to alert the developer that the pem file is missing.
            Logger.log(error: BridgeUnexpectedNullError(category: .missingFile, message: message))
            return
        }
        _uploadEncrypted(id: archive.identifier, url: url, schedule: archive.schedule, startedOn: archive.startedOn)
    }
    
    @MainActor
    private func _uploadEncrypted(id: String, url: URL, schedule: AssessmentScheduleInfo?, startedOn: Date?) {
        var dictionary: [String : JsonSerializable] = schedule.map { schedule in
            ["instanceGuid": schedule.instanceGuid,
             "eventTimestamp": schedule.session.eventTimestamp,
             "sessionInstanceGuid": schedule.session.instanceGuid,
             "assessmentIdentifier": schedule.assessmentIdentifier,
            ]
        } ?? [:]
        if let startedOn = startedOn {
            dictionary["startedOn"] = startedOn.jsonObject()
        }
        let exporterV3Metadata: JsonElement? = dictionary.count > 0 ? .object(dictionary) : nil
        let extras = StudyDataUploadExtras(encrypted: true, metadata: exporterV3Metadata, zipped: true)
        StudyDataUploadAPI.shared.upload(fileId: id, fileUrl: url, contentType: "application/zip", extras: extras)
        do {
            try FileManager.default.removeItem(at: url)
        } catch let err {
            Logger.log(error: err, message: "Failed to delete encrypted archive \(id) at \(url)")
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

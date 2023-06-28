//
//  BridgeClientAppManager.swift
//

import SwiftUI
import Combine
import BridgeClient
import BridgeClientExtension
import JsonModel

fileprivate let kOnboardingStateKey = "isOnboardingFinished"

public protocol ReauthPasswordHandler {
    func storedPassword(for session: UserSessionInfoObserver) -> String?
    func clearStoredPassword()
}

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
open class BridgeClientAppManager : UploadAppManager {
    
    /// Has the participant been shown the onboarding flow?
    @Published public var isOnboardingFinished: Bool = UserDefaults.standard.bool(forKey: kOnboardingStateKey) {
        didSet {
            UserDefaults.standard.set(isOnboardingFinished, forKey: kOnboardingStateKey)
            updateAppState()
        }
    }

    /// The local notification manager is a singleton that can be set up as the notification delegate (to handle snoozing).
    lazy public var localNotificationManager : LocalNotificationManager = LocalNotificationManager()
    
#if os(iOS)
    /// **Required:** This method should be called by the app delegate when the app is launching in either `willLaunch` or `didLaunch`.
    @MainActor
    open func finishLaunchingApp(_ launchOptions: [UIApplication.LaunchOptionsKey : Any]?) {
        setup()
    }
    
    @MainActor
    @available(*, deprecated, message: "Call `finishLaunchingApp(:)` instead.")
    open func appWillFinishLaunching(_ launchOptions: [UIApplication.LaunchOptionsKey : Any]? ) {
        finishLaunchingApp(launchOptions)
    }
#endif

    /// Login with the given external ID and password.
    ///
    /// - Parameters:
    ///   - externalId: The external ID to use as the signin credentials.
    ///   - password: The password to use as the signin credentials.
    ///   - completion: The completion handler that is called with the server response.
    public final func loginWithExternalId(_ externalId: String, password: String, completion: @escaping ((BridgeClient.ResourceStatus) -> Void)) {
        self.signInOrReauth(email: nil, externalId: externalId, password: password, completion: completion)
    }
    
    /// Login with the given email and password.
    ///
    /// - Parameters:
    ///   - email: The external ID to use as the signin credentials.
    ///   - password: The password to use as the signin credentials.
    ///   - completion: The completion handler that is called with the server response.
    public final func loginWithEmail(_ email: String, password: String, completion: @escaping ((BridgeClient.ResourceStatus) -> Void)) {
        self.signInOrReauth(email: email, externalId: nil, password: password, completion: completion)
    }
    
    /// Reauthenticate with the given password
    ///
    /// - Parameters:
    ///   - password: The password to use as the signin credentials.
    ///   - completion: The completion handler that is called with the server response.
    public final func reauthWithCredentials(password: String, completion: @escaping ((BridgeClient.ResourceStatus) -> Void)) {
        self.signInOrReauth(email: nil, externalId: nil, password: password, completion: completion)
    }
    
    // @Protected - Only this class should call this method and only subclasses should implement.
    override open func willSignOut() {
        localNotificationManager.clearAll()
        isOnboardingFinished = false
        super.willSignOut()
    }
    
    // @Protected - Only this class should call this method and only subclasses should implement.
    override open func updateAppState() {
        appState = fetchAppState()
    }
    
    public final func fetchAppState() -> AppState {
        if bridgeAppStatus != .supported {
            Logger.log(severity: .info, message: "Updating app state to `error`. bridgeAppStatus != .supported")
            return .error
        }
        else if appConfig.isLaunching || userSessionInfo.loginState == .launching || reauthStatus == .pending {
            Logger.log(severity: .info, message: "Updating app state to `launching`.\nappConfig.isLaunching=\(appConfig.isLaunching)\nuserSessionInfo.loginState=\(userSessionInfo.loginState)\nreauthStatus=\(reauthStatus == .pending)")
            return .launching
        }
        else if !userSessionInfo.isAuthenticated {
            Logger.log(severity: .info, message: "Updating app state to `login`. User not authenticated. loginState=\(userSessionInfo.loginState)")
            return .login
        }
        else if !isOnboardingFinished {
            Logger.log(severity: .info, message: "Updating app state to `onboarding`.")
            return .onboarding
        }
        else {
            Logger.log(severity: .info, message: "Updating app state to `main`.")
            return .main
        }
    }
    
    // MARK: Reauth handling
    
    public var reauthPasswordHandler: ReauthPasswordHandler? = nil
    var reauthStatus: ResourceStatus?
    
    /// Override the default (which is to do nothing) and check to see if there is a
    /// ``ReauthPasswordHandler`` set to get the password for this app.
    open override func handleReauthFailed() -> Bool {
        if let password = reauthPasswordHandler?.storedPassword(for: userSessionInfo) {
            reauthStatus = .pending
            #if DEBUG
            print("Attempting reauth recovery\nemail: '\(userSessionInfo.email ?? "NULL")'\nexternalId: '\(userSessionInfo.externalId ?? "NULL")'\npassword: '\(password)'")
            #endif
            reauthWithCredentials(password: password) { [weak self] status in
                DispatchQueue.main.async {
                    self?.reauthStatus = status
                    if status == .failed {
                        self?.reauthPasswordHandler?.clearStoredPassword()
                        self?.userSessionInfo.loginError = "Failed to reauth using stored credentials."
                    }
                    self?.updateAppState()
                }
            }
            return true
        }
        else {
            return false
        }
    }
}


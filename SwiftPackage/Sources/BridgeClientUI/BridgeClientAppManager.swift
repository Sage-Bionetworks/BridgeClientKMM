//
//  BridgeClientAppManager.swift
//

import SwiftUI
import BridgeClient
import BridgeClientExtension
import JsonModel

fileprivate let kOnboardingStateKey = "isOnboardingFinished"

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
        case launching, login, onboarding, main
    }
    
    /// The "state" of the app.
    @Published public var appState: AppState = .launching
    
    /// Has the participant been shown the onboarding flow?
    @Published public var isOnboardingFinished: Bool = UserDefaults.standard.bool(forKey: kOnboardingStateKey) {
        didSet {
            UserDefaults.standard.set(isOnboardingFinished, forKey: kOnboardingStateKey)
            updateAppState()
        }
    }

    /// The local notification manager is a singleton that can be set up as the notification delegate (to handle snoozing).
    lazy public var localNotificationManager : LocalNotificationManager = LocalNotificationManager()
    
    /// **Required:** This method should be called by the app delegate when the app is launching in either `willLaunch` or `didLaunch`.
    open func appWillFinishLaunching(_ launchOptions: [UIApplication.LaunchOptionsKey : Any]? ) {
        setup()
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
            Task {
                await self.setUserSessionInfo(userSessionInfo)
                completion(status)
            }
        }
    }
    
    /// Login with the given email and password.
    ///
    /// - Parameters:
    ///   - email: The external ID to use as the signin credentials.
    ///   - password: The password to use as the signin credentials.
    ///   - completion: The completion handler that is called with the server response.
    public final func loginWithEmail(_ email: String, password: String, completion: @escaping ((BridgeClient.ResourceStatus) -> Void)) {
        self.authManager.signInEmail(userName: email, password: password) { (userSessionInfo, status) in
            guard status == ResourceStatus.success || status == ResourceStatus.failed else { return }
            Task {
                await self.setUserSessionInfo(userSessionInfo)
                completion(status)
            }
        }
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
        if appConfig.isLaunching || userSessionInfo.isLaunching {
            return .launching
        }
        else if !userSessionInfo.isAuthenticated {
            return .login
        }
        else if !isOnboardingFinished {
            return .onboarding
        }
        else {
            return .main
        }
    }
}


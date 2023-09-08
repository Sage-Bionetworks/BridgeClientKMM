// Created 8/28/23
// swift-tools-version:5.0

import SwiftUI


let bgTaskId = "org.sagebase.BackgroundProcessTest"

class AppDelegate : UIResponder, UIApplicationDelegate {
    
    let manager = TestUploadManager()
    
    func application(_ application: UIApplication, didFinishLaunchingWithOptions launchOptions: [UIApplication.LaunchOptionsKey : Any]? = nil) -> Bool {
        
        manager.onLaunch(backgroundProcessId: bgTaskId)
        
        return true
    }
}

@main
struct BackgroundProcessTestApp: App {
    @UIApplicationDelegateAdaptor(AppDelegate.self) var appDelegate
    
    var body: some Scene {
        WindowGroup {
            ContentView()
        }
    }
}

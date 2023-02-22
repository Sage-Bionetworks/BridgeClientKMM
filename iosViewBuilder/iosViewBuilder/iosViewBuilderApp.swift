// Created 2/21/23
// swift-tools-version:5.0

import SwiftUI

@main
struct iosViewBuilderApp: App {
    var body: some Scene {
        WindowGroup {
            ContentView()
        }
    }
}

extension Bundle {
    static var module: Bundle { .main }
}

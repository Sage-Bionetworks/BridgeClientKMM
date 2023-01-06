//
//  PreviewCustomTabView.swift
//

import SwiftUI
import BridgeClientUI

struct PreviewCustomTabView: View {
    let placement: VerticalAlignment
    
    @State var selectedTab : Tab = .profile
    
    enum Tab : String, CaseIterable, EnumTabItem {
        case profile, notifications, settings
        
        var bundle: Bundle? { nil }
        
        func title() -> Text {
            switch self {
            case .profile:
                return Text("PROFILE")
            case .notifications:
                return Text("NOTIFICATIONS")
            case .settings:
                return Text("SETTINGS")
            }
        }
    }
    
    var body: some View {
        CustomTabView(selectedTab: $selectedTab, tabs: Tab.allCases, placement: placement) { tab in
            switch tab {
            case .profile:
                Text("Showing Profile")
            case .notifications:
                Text("Showing Notifications")
            case .settings:
                Text("Showing Settings")
            }
        }
        .onAppear {
            print("whoohoo")
        }
    }
}

struct PreviewCustomTabView_Previews: PreviewProvider {
    static var previews: some View {
        Group {
            PreviewCustomTabView(placement: .top)
            PreviewCustomTabView(placement: .bottom)
        }
    }
}

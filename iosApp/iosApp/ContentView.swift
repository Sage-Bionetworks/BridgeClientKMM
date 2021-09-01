import SwiftUI
import BridgeClient
import BridgeClientUI

// TODO: syoung 06/07/2021 Build example app?

struct ContentView: View {
    @EnvironmentObject var bridgeManager: SingleStudyAppManager
    
    var body: some View {
        switch bridgeManager.appState {
        case .launching:
            Text("Launching")
        case .login:
            ExternalIdLoginView()
        default:
            Text("Main")
        }
    }
}

struct ContentView_Previews: PreviewProvider {
    static var previews: some View {
        Group {
            ContentView()
                .environmentObject(SingleStudyAppManager(appId: kPreviewStudyId))
        }
    }
}


//
//  PreviewStudyInfoView.swift
//

import SwiftUI
import BridgeClient
import BridgeClientUI

struct PreviewStudyInfoView: View {
    @State var selectedTab: StudyInfoView.Tab = .about
    var body: some View {
        StudyInfoView($selectedTab)
            .environmentObject(SingleStudyAppManager(appId: kPreviewStudyId))
    }
}

struct PreviewStudyInfoView_Previews: PreviewProvider {
    static var previews: some View {
        PreviewStudyInfoView()
    }
}

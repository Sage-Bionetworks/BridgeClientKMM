//
//  PreviewPrivacyNoticeView.swift
//

import SwiftUI
import BridgeClientUI

struct PreviewPrivacyNoticeView: View {
    @State var selectedTab: PrivacyNotice.Category = .weWill
    var body: some View {
        PrivacyNoticeView(selectedTab: $selectedTab)
            .environmentObject(SingleStudyAppManager(appId: kPreviewStudyId))
    }
}

struct PreviewPrivacyNoticeView_Previews: PreviewProvider {
    static var previews: some View {
        PreviewPrivacyNoticeView()
    }
}

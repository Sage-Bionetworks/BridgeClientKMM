//
//  PreviewEndOfStudyView.swift
//

import SwiftUI
import BridgeClientUI

struct PreviewEndOfStudyView: View {
    var body: some View {
        EndOfStudyView()
    }
}

struct PreviewEndOfStudyView_Previews: PreviewProvider {
    static var previews: some View {
        PreviewEndOfStudyView()
            .environmentObject(SingleStudyAppManager(appId: kPreviewStudyId))
    }
}

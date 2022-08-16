//
//  MainView.swift
//  BiAffectPreview
//
//  Copyright © 2022 BiAffect. All rights reserved.
//
// Redistribution and use in source and binary forms, with or without modification,
// are permitted provided that the following conditions are met:
//
// 1.  Redistributions of source code must retain the above copyright notice, this
// list of conditions and the following disclaimer.
//
// 2.  Redistributions in binary form must reproduce the above copyright notice,
// this list of conditions and the following disclaimer in the documentation and/or
// other materials provided with the distribution.
//
// 3.  Neither the name of the copyright holder(s) nor the names of any contributors
// may be used to endorse or promote products derived from this software without
// specific prior written permission. No license is granted to the trademarks of
// the copyright holders even if such marks are included in this software.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE
// FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
// DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
// SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
// CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
// OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//

import SwiftUI
import BridgeClientUI

struct MainView: View {
    @EnvironmentObject var bridgeManager: SingleStudyAppManager
    @StateObject var viewModel: ViewModel = .init()
    
    enum Tab: String, CaseIterable, EnumTabItem {
        case today, history
        
        var bundle: Bundle? { nil }
        
        func title() -> Text {
            switch self {
            case .today:
                return Text("Home")
            case .history:
                return Text("Past Activities")
            }
        }
    }
    
    class ViewModel : ObservableObject {
        @Published var selectedTab: Tab = .today
    }

    var body: some View {
        CustomTabView(selectedTab: $viewModel.selectedTab, tabs: Tab.allCases, placement: .bottom) { tab in
            switch tab {
            case .today:
                todayView()
            case .history:
                HistoryView()
            }
        }
        .environmentObject(viewModel)
    }
    
    @ViewBuilder
    func todayView() -> some View {
        if bridgeManager.isStudyComplete {
            EndOfStudyView()
                .transition(.opacity)
                .animation(.easeIn)
        }
        else {
            TodayView()
        }
    }
}

struct MainView_Previews: PreviewProvider {
    static var previews: some View {
        MainView()
            .environmentObject(SingleStudyAppManager(appId: kPreviewStudyId))
            .environmentObject(TodayTimelineViewModel())
    }
}

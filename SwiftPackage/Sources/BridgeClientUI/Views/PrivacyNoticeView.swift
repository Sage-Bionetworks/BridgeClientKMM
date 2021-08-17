//
//  PrivacyNoticeView.swift
//
//  Copyright © 2021 Sage Bionetworks. All rights reserved.
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
import BridgeClient
import SharedMobileUI

public struct PrivacyNoticeView: View {
    @EnvironmentObject private var bridgeManager: SingleStudyAppManager
    @State private var privacyNotice: PrivacyNotice = PrivacyNotice.default
    @Binding private var selectedTab: PrivacyNotice.Category
    
    private let privacyPolicyShareView = URLActivityViewRepresentable(
        Bundle.main.url(forResource: "PrivacyPolicy", withExtension: "pdf"))
    
    public init(selectedTab: Binding<PrivacyNotice.Category>) {
        self._selectedTab = selectedTab
    }
    
    public var body: some View {
        VStack(spacing: 0) {
            header()
            tabBar()
            
            ScrollView {
                LazyVStack(spacing: 32) {
                    let notices = privacyNotice.notices.filter { $0.category == selectedTab }
                    ForEach(notices) { notice in
                        HStack(spacing: 24) {
                            Image(decorative: notice.icon, bundle: .module)
                                .frame(width: 48, height: 48)
                            Text(notice.text)
                                .font(.poppinsFont(14, relativeTo: .body, weight: .regular))
                                .foregroundColor(.textForeground)
                                .frame(maxWidth: .infinity, alignment: .leading)
                        }
                    }
                    Button(action: privacyPolicyShareView.share) {
                        Label("Full Notice", systemImage: "square.and.arrow.up", bundle: .module)
                    }
                    .buttonStyle(RoundedButtonStyle())
                    privacyPolicyShareView
                }
                .padding(.vertical, 32)
                .padding(.horizontal, 42)
            }
            .background(Color.sageWhite.edgesIgnoringSafeArea(.bottom))
        }
        .background(Color.screenBackground.edgesIgnoringSafeArea(.all))
        .onAppear {
            if let notice = bridgeManager.appConfig?.decodePrivacyNotice() {
                privacyNotice = notice
            }
        }
    }
    
    @ViewBuilder
    private func header() -> some View {
        HStack {
            Image(decorative: "privacy.notice.icon", bundle: .module)
            Text("Privacy Notice", bundle: .module)
                .font(.playfairDisplayFont(21, relativeTo: .title2, weight: .regular))
                .foregroundColor(.textForeground)
        }
        .padding(20)
    }
    
    @ViewBuilder
    private func tabBar() -> some View {
        HStack(spacing: 2) {
            ForEach(PrivacyNotice.Category.allCases, id: \.rawValue) { tab in
                Button(action: { selectedTab = tab }) {
                    switch tab {
                    case .weWill:
                        Text("We will", bundle: .module)
                    case .weWont:
                        Text("We won't", bundle: .module)
                    case .youCan:
                        Text("You can", bundle: .module)
                    }
                }
                .frame(height: 49.0)
                .frame(minWidth: 0, maxWidth: .infinity)
                .font(.poppinsFont(14))
                .foregroundColor(.textForeground)
                .background(tabBackground(selected: selectedTab == tab))
            }
        }
        .padding(.horizontal, 0)
    }
    
    @ViewBuilder
    private func tabBackground(selected: Bool) -> some View {
        if selected {
            ZStack(alignment: .bottom) {
                Color.sageWhite
                    .shadow(color: .black.opacity(0.2), radius: 4, x: 0, y: 5)
                Color.accentColor
                    .frame(height: 2)
            }
        }
        else {
            Color.hexF0F0F0
        }
    }
}

// Modified from https://stackoverflow.com/questions/56819360/swiftui-exporting-or-sharing-files

class URLActivityViewController : UIViewController {
    
    var excludedActivityTypes: [UIActivity.ActivityType]? = nil

    @objc func shareURL(_ url: URL) {
        let vc = UIActivityViewController(activityItems: [url], applicationActivities: [])
        vc.excludedActivityTypes = excludedActivityTypes
        present(vc,
                animated: true,
                completion: nil)
        vc.popoverPresentationController?.sourceView = self.view
    }
}

struct URLActivityViewRepresentable : UIViewControllerRepresentable {

    private let viewController = URLActivityViewController()
    
    var url: URL?
    
    init(_ url: URL? = nil) {
        self.url = url
    }

    func makeUIViewController(context: Context) -> URLActivityViewController {
        viewController
    }
    
    func updateUIViewController(_ uiViewController: URLActivityViewController, context: Context) {
        //
    }
    
    func share() {
        guard let fileURL = self.url else { return }
        viewController.shareURL(fileURL)
    }
}

// syoung 08/16/2021 SwiftUI fails to build complex UI in a shared framework. Therefore, the preview
// for this element is in iosApp.
struct PrivacyNoticeView_Previews: PreviewProvider {
    static var previews: some View {
        Text("Hello, World")
    }
}


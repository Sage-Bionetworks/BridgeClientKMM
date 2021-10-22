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
    @State private var showFullNotice: Bool = false
    
    let fullPolicyURL = Bundle.main.url(forResource: "PrivacyPolicy", withExtension: "pdf")
    
    public init(selectedTab: Binding<PrivacyNotice.Category>) {
        self._selectedTab = selectedTab
    }
    
    let bodyFont = DesignSystem.fontRules.bodyFont(at: 1, isEmphasis: false)
    
    public var body: some View {
        ScreenBackground {
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
                                    .font(bodyFont)
                                    .foregroundColor(.textForeground)
                                    .frame(maxWidth: .infinity, alignment: .leading)
                            }
                        }
                        fullPolicyButton()
                    }
                    .padding(.vertical, 32)
                    .padding(.horizontal, 42)
                }
                .background(Color.sageWhite.edgesIgnoringSafeArea(.all))
            }
        }
        .onAppear {
            if let notice = bridgeManager.appConfig?.decodePrivacyNotice() {
                privacyNotice = notice
            }
        }
    }
    
    @ViewBuilder
    private func fullPolicyButton() -> some View {
        if let url = fullPolicyURL {
            Button(action: { self.showFullNotice = true }) {
                Label("Full Notice", systemImage: "square.and.arrow.up", bundle: .module)
            }
            .disabled(self.showFullNotice)
            .buttonStyle(RoundedButtonStyle())
            
            DocumentPreview($showFullNotice, url: url)
                .accentColor(.init("LinkColor"))
        }
        else {
            EmptyView()
        }
    }
    
    @ViewBuilder
    private func header() -> some View {
        HStack {
            Image(decorative: "privacy.notice.icon", bundle: .module)
            Text("Privacy Notice", bundle: .module)
                .font(DesignSystem.fontRules.headerFont(at: 1))
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
                .font(DesignSystem.fontRules.headerFont(at: 6))
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

// syoung 09/17/2021 Showing the share sheet for sharing the PDF (as the button suggests)
// is mad slow and can take *several* seconds to load. This is a work-around intended to
// show a preview of the PDF document and gives them the option to print, save to file,
// air drop, etc.
// https://stackoverflow.com/questions/60354684/presenting-uidocumentinteractioncontroller-with-uiviewcontrollerrepresentable-in

struct DocumentPreview: UIViewControllerRepresentable {
    private var isActive: Binding<Bool>
    private let viewController = UIViewController()
    private let docController: UIDocumentInteractionController

    init(_ isActive: Binding<Bool>, url: URL) {
        self.isActive = isActive
        self.docController = UIDocumentInteractionController(url: url)
    }

    func makeUIViewController(context: UIViewControllerRepresentableContext<DocumentPreview>) -> UIViewController {
        return viewController
    }

    func updateUIViewController(_ uiViewController: UIViewController, context: UIViewControllerRepresentableContext<DocumentPreview>) {
        if self.isActive.wrappedValue && docController.delegate == nil { // to not show twice
            docController.delegate = context.coordinator
            self.docController.presentPreview(animated: true)
        }
    }

    func makeCoordinator() -> Coordinator {
        return Coordinator(owner: self)
    }

    final class Coordinator: NSObject, UIDocumentInteractionControllerDelegate { // works as delegate
        let owner: DocumentPreview
        init(owner: DocumentPreview) {
            self.owner = owner
        }
        
        func documentInteractionControllerViewControllerForPreview(_ controller: UIDocumentInteractionController) -> UIViewController {
            return owner.viewController
        }

        func documentInteractionControllerDidEndPreview(_ controller: UIDocumentInteractionController) {
            // Unlink on next run loop.
            DispatchQueue.main.async {
                self.owner.isActive.wrappedValue = false
                controller.delegate = nil
            }
        }
    }
}

// syoung 08/16/2021 SwiftUI fails to build complex UI in a shared framework. Therefore, the preview
// for this element is in iosApp.
struct PrivacyNoticeView_Previews: PreviewProvider {
    static var previews: some View {
        Text("Hello, World")
    }
}


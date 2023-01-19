//
//  PrivacyNoticeView.swift
//

import SwiftUI
import BridgeClient
import SharedMobileUI
import WebKit

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
            if let notice = bridgeManager.appConfig.decodePrivacyNotice() {
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
            .fullScreenCover(isPresented: $showFullNotice) {
                PDFShareView(url: url, done: { self.showFullNotice = false })
                    .accentColor(.init("LinkColor"))
            }
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
                        Text("We won’t", bundle: .module)
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

struct PDFShareView: View {
    let url: URL
    let done: (() -> Void)
    let shareView: PDFViewRepresentable
    
    init(url: URL, done: @escaping (() -> Void)) {
        self.url = url
        self.done = done
        self.shareView = .init(url: url)
    }

    var body: some View {
        NavigationView {
            ZStack {
                shareView
            }
            .toolbar {
                ToolbarItem(placement: .navigationBarLeading) {
                    Button(action: done) {
                        Text("Done")
                    }
                }
                ToolbarItem(placement: .navigationBarTrailing) {
                    Button(action: shareView.share) {
                        Image(systemName: "square.and.arrow.up")
                    }
                }
            }
        }
    }
    
    struct PDFViewRepresentable : UIViewControllerRepresentable {

        let viewController: PDFViewController
        
        init(url: URL) {
            self.viewController = .init(url: url)
        }

        func makeUIViewController(context: Context) -> PDFViewController {
            viewController
        }
        
        func updateUIViewController(_ uiViewController: PDFViewController, context: Context) {
            //
        }
        
        func share() {
            viewController.shareURL()
        }
        
        class PDFViewController : UIViewController, WKNavigationDelegate {
            
            let url: URL
            var webView: WKWebView!
            
            init(url: URL) {
                self.url = url
                super.init(nibName: nil, bundle: nil)
            }
            
            required init?(coder: NSCoder) {
                fatalError("init(coder:) has not been implemented")
            }
            
            override func loadView() {
                webView = WKWebView()
                webView.navigationDelegate = self
                view = webView
            }
            
            override func viewDidLoad() {
                super.viewDidLoad()
                webView.load(.init(url: url))
            }

            @objc func shareURL() {
                let vc = UIActivityViewController(activityItems: [url], applicationActivities: [])
                present(vc,
                        animated: true,
                        completion: nil)
            }
        }
    }
}

// syoung 08/16/2021 SwiftUI fails to build complex UI in a shared framework. Therefore, the preview
// for this element is in iosApp.
struct PrivacyNoticeView_Previews: PreviewProvider {
    static var previews: some View {
        Text("Hello, World!")
    }
}


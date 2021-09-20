//
//  StudyInfoView.swift
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

public struct StudyInfoView: View {
    @EnvironmentObject private var bridgeManager: SingleStudyAppManager
    @StateObject private var viewModel: StudyInfoViewModel = .init()
    
    @State private var selectedTab: Tab = .about
    
    public init() {
    }
    
    enum Tab : String, CaseIterable, EnumTabItem {
        case about, contact
        
        var bundle: Bundle? { .module }

        func title() -> Text {
            switch self {
            case .about:
                return Text("ABOUT THE STUDY", bundle: .module)
            case .contact:
                return Text("CONTACT & SUPPORT", bundle: .module)
            }
        }
    }
    
    public var body: some View {
        CustomTabView(selectedTab: $selectedTab, tabs: Tab.allCases, placement: .top) { tab in
            ScrollView {
                switch tab {
                case .about:
                    AboutStudyView()
                case .contact:
                    ContactAndSupportView()
                }
            }
        }
        .environmentObject(viewModel)
        .background(Color.screenBackground.edgesIgnoringSafeArea(.all))
        .onAppear {
            viewModel.onAppear(bridgeManager)
        }
    }
}

public struct AboutStudyView: View {
    @EnvironmentObject private var viewModel: StudyInfoViewModel
    
    @State var isPresentingPrivacyNotice: Bool = false
    @State var privacyNoticeTab: PrivacyNotice.Category = .weWill
    
    private let horizontalPadding: CGFloat = 26
    
    // MARK: About
    
    public var body: some View {
        VStack(spacing: 0) {
            mainAboutView()
            privacyPolicyButton()
        }
    }
    
    @ViewBuilder
    private func mainAboutView() -> some View {
        VStack(alignment: .leading, spacing: 26) {
            aboutHeader()
            aboutBody()
                .foregroundColor(.textForeground)
            LineView()
                .padding(.horizontal, horizontalPadding)
            ForEach(viewModel.studyContacts) { contact in
                studyInfo(contact)
                    .padding(.horizontal, horizontalPadding)
            }
            Spacer()
        }
        .background(Color.sageWhite)
        .padding(.all, 16)
    }
    
    @ViewBuilder
    private func aboutHeader() -> some View {
        if let url = viewModel.studyLogoUrl {
            LogoImage(url: url)
                .background(viewModel.backgroundColor)
        }
        else {
            Text(viewModel.institutionName.localizedUppercase)
                .foregroundColor(viewModel.foregroundColor)
                .padding(.vertical, 28)
                .padding(.horizontal, horizontalPadding)
                .frame(maxWidth: .infinity, alignment: .leading)
                .background(viewModel.backgroundColor)
        }
    }
    
    @ViewBuilder
    private func aboutBody() -> some View {
        Text(viewModel.title)
            .font(.playfairDisplayFont(18, relativeTo: .title, weight: .regular))
            .padding(.top, 6)
            .padding(.horizontal, horizontalPadding)
        if let details = viewModel.details {
            Text(details)
                .font(.latoFont(15, relativeTo: .body, weight: .regular))
                .fixedSize(horizontal: false, vertical: true)
                .padding(.horizontal, horizontalPadding)
        }
    }
    
    @ViewBuilder
    private func studyInfo(_ contact: StudyContact) -> some View {
        VStack(alignment: .leading, spacing: 2) {
            Text(contact.name)
                .font(.latoFont(14, relativeTo: .title2, weight: .bold))
            contact.position
                .font(.latoFont(12, relativeTo: .title3, weight: .regular))
        }
        .foregroundColor(.textForeground)
    }
    
    @ViewBuilder
    private func privacyPolicyButton() -> some View {
        Button(action: showPrivacyNotice) {
            Label("Review Privacy Notice", image: "privacy.notice.icon", bundle: .module)
        }
        .buttonStyle(RoundedButtonStyle(horizontalPadding: 16))
        .padding(.top, 4)
        .padding(.horizontal, horizontalPadding)
        .padding(.bottom, 32)
        .fullScreenCover(isPresented: $isPresentingPrivacyNotice) {
            VStack(alignment: .leading, spacing: 0) {
                Button(action: hidePrivacyNotice) {
                    Label("Back", systemImage: "arrow.left", bundle: .module)
                        .font(.latoFont(14, relativeTo: .title2, weight: .regular))
                        .foregroundColor(.textForeground)
                        .padding(.horizontal, 16)
                }
                PrivacyNoticeView(selectedTab: $privacyNoticeTab)
            }
            .background(Color.screenBackground.edgesIgnoringSafeArea(.top))
        }
    }
    
    private func showPrivacyNotice() {
        isPresentingPrivacyNotice = true
    }
    
    private func hidePrivacyNotice() {
        isPresentingPrivacyNotice = false
    }
}

public struct ContactAndSupportView: View {
    @EnvironmentObject private var bridgeManager: SingleStudyAppManager
    @EnvironmentObject private var viewModel: StudyInfoViewModel
        
    public var body: some View {
        VStack(alignment: .leading, spacing: 25) {
            Spacer()
            section(title: Text("General Support", bundle: .module),
                    body: Text("For general questions about the study or to withdraw from the study, please contact:", bundle: .module),
                    contacts: viewModel.supportContacts)
            withdrawalInfoView()
            LineView()
            section(title: Text("Your Participant Rights", bundle: .module),
                    body: Text("For questions about your rights as a research participant, please contact:", bundle: .module),
                    contacts: viewModel.irbContacts)
            Spacer()
        }
        .padding(.horizontal, 26)
        .foregroundColor(.textForeground)
        .background(Color.sageWhite)
        .padding(.all, 16)
    }
    
    // MARK: Section Header
    
    @ViewBuilder
    private func section(title: Text, body: Text, contacts: [StudyContact]) -> some View {
        VStack(alignment: .leading, spacing: 0) {
            title
                .font(.poppinsFont(18, relativeTo: .title2, weight: .regular))
                .padding(.bottom, 8)
            body
                .font(.latoFont(12, relativeTo: .footnote, weight: .regular))
                .fixedSize(horizontal: false, vertical: true)
        }
        .frame(maxWidth: .infinity)
        
        ForEach(contacts) {
            contactView($0)
                .padding(.horizontal, 16)
        }
    }
    
    // MARK: Protocol ID
    
    private func protocolIdLabel() -> Text {
        Text("IRB Protocol ID: ", bundle: .module) + Text(viewModel.study?.irbProtocolId ?? "")
    }
    
    // MARK: Contact Info
    
    @ViewBuilder
    private func contactView(_ contact: StudyContact) -> some View {
        VStack(alignment: .leading, spacing: 10) {
            VStack(alignment: .leading, spacing: 2) {
                Text(contact.name)
                    .font(.poppinsFont(14, relativeTo: .title2, weight: .bold))
                contact.position
                    .font(.latoFont(12, relativeTo: .title3, weight: .regular))
            }
            .padding(.leading, 26)
            if let phone = contact.phone {
                contactValue(phone, contactType: .phone)
            }
            if let email = contact.email {
                contactValue(email, contactType: .email)
            }
            if contact.isIRB {
                protocolIdLabel()
                    .font(.latoFont(12, relativeTo: .title3, weight: .regular))
                    .padding(.leading, 26)
            }
        }
    }
    
    @ViewBuilder
    private func contactValue(_ value: String, contactType: ContactType) -> some View {
        
        let imageName = contactType.rawValue
        let label = label(for: contactType)
        let url = url(value, contactType: contactType)
        
        Link(destination: url) {
            Label(title: {
                Text(value)
                    .font(.latoFont(12, relativeTo: .title3, weight: .regular))
            },
            icon: {
                CompositeTintedImage("\(imageName).background", foreground: "\(imageName).foreground", bundle: .module)
                    .accessibility(label: label)
            })
        }
    }
    
    private func label(for contactType: ContactType) -> Text {
        switch contactType {
        case .phone:
            return Text("Phone", bundle: .module)
        case .email:
            return Text("Email", bundle: .module)
        }
    }
    
    private func url(_ value: String, contactType: ContactType) -> URL {
        switch contactType {
        case .phone:
            return URL(string: "tel:\(value.components(separatedBy: .phoneDigits.inverted).joined())")!
        case .email:
            return URL(string: "mailto:\(value)")!
        }
    }
    
    private enum ContactType : String, CaseIterable {
        case phone, email
    }
    
    // MARK: Withdrawal Info
    
    @ViewBuilder
    private func withdrawalInfoView() -> some View {
        VStack(alignment: .leading, spacing: 16) {
            if let phone = viewModel.participantPhone {
                withdrawalHeader(Text("To withdraw from this study, you’ll need the Study ID and the phone number you registered with:", bundle: .module))
                withdrawalRow(Text("Study ID: ", bundle: .module), bridgeManager.studyId!)
                withdrawalRow(Text("Registration Phone Number: ", bundle: .module), phone.nationalFormat ?? phone.number)
            }
            else {
                withdrawalHeader(Text("To withdraw from this study, you’ll need the following info:", bundle: .module))
                withdrawalRow(Text("Study ID: ", bundle: .module), bridgeManager.studyId!)
                withdrawalRow(Text("Participant ID: ", bundle: .module), viewModel.participantId ?? "")
            }
        }
        .font(.latoFont(12, relativeTo: .body, weight: .regular))
        .padding(.top, 19)
        .padding(.horizontal, 32)
        .padding(.bottom, 26)
        .frame(maxWidth: .infinity)
        .background(Color.accentColor)
        .cornerRadius(10)
    }
    
    @ViewBuilder
    private func withdrawalHeader(_ label: Text) -> some View {
        label
            .fixedSize(horizontal: false, vertical: true)
    }
    
    private func withdrawalRow(_ label: Text, _ value: String) -> Text {
        label.bold() + Text(value)
    }
}

extension CharacterSet {
    static let phoneDigits: CharacterSet = .init(charactersIn: "0123456789")
}


// syoung 08/16/2021 SwiftUI fails to build complex UI in a shared framework. Therefore, the preview
// for this element is in iosApp.
struct StudyInfoView_Previews: PreviewProvider {
    static var previews: some View {
        Text("Hello, World")
    }
}

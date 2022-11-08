//
//  StudyInfoView.swift
//

import SwiftUI
import BridgeClient 
import SharedMobileUI

public struct StudyInfoView: View {
    @EnvironmentObject private var bridgeManager: SingleStudyAppManager
    @Binding private var selectedTab: Tab
    
    public init(_ selectedTab: Binding<Tab>) {
        self._selectedTab = selectedTab
    }
    
    public enum Tab : String, CaseIterable, EnumTabItem {
        case about, contact
        
        public var bundle: Bundle? { .module }

        public func title() -> Text {
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
            ScreenBackground {
                ScrollView {
                    switch tab {
                    case .about:
                        AboutStudyView()
                    case .contact:
                        ContactAndSupportView()
                    }
                }
            }
        }
    }
}

public struct AboutStudyView: View {
    @EnvironmentObject private var bridgeManager: SingleStudyAppManager
    
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
            let studyContacts = filterStudyContacts()
            ForEach(studyContacts) { contact in
                studyInfo(contact)
                    .padding(.horizontal, horizontalPadding)
            }
            Spacer()
        }
        .background(Color.sageWhite)
        .padding(.all, 16)
    }
    
    func filterStudyContacts() -> [StudyContact] {
        guard let contacts = bridgeManager.study?.contacts else { return [] }
        
        let studyRoles: [StudyContact.Role] = [.principalInvestigator, .investigator, .sponsor]
        var studyContacts = contacts
            .filter { studyRoles.contains($0.role) }
            .sorted(by: { studyRoles.firstIndex(of: $0.role)! < studyRoles.firstIndex(of: $1.role)! })

        if let firstContact = studyContacts.first(where: { $0.affiliation != nil }) {
            studyContacts.insert(StudyContact(name: firstContact.affiliation!, role: .institution), at: 1)
        }

        return studyContacts
    }
    
    @ViewBuilder
    private func aboutHeader() -> some View {
        if let study = bridgeManager.study,
            let url = study.studyLogoUrl {
            LogoImage(url: url)
                .background(study.backgroundColor)
        }
        else {
            EmptyView()
        }
    }
    
    @ViewBuilder
    private func aboutBody() -> some View {
        Text(bridgeManager.study?.name ?? Bundle.localizedAppName)
            .font(DesignSystem.fontRules.headerFont(at: 2))
            .padding(.top, 6)
            .padding(.horizontal, horizontalPadding)
        if let details = bridgeManager.study?.details {
            Text(details)
                .font(DesignSystem.fontRules.bodyFont(at: 1, isEmphasis: false))
                .fixedSize(horizontal: false, vertical: true)
                .padding(.horizontal, horizontalPadding)
        }
    }
    
    @ViewBuilder
    private func studyInfo(_ contact: StudyContact) -> some View {
        VStack(alignment: .leading, spacing: 2) {
            Text(contact.name)
                .font(DesignSystem.fontRules.headerFont(at: 5))
            contact.position
                .font(DesignSystem.fontRules.bodyFont(at: 2, isEmphasis: false))
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
            ScreenBackground {
                VStack(alignment: .leading, spacing: 0) {
                    Button(action: hidePrivacyNotice) {
                        Label("Back", systemImage: "arrow.left", bundle: .module)
                            .font(DesignSystem.fontRules.headerFont(at: 6))
                            .foregroundColor(.textForeground)
                            .padding(.horizontal, 16)
                    }
                    PrivacyNoticeView(selectedTab: $privacyNoticeTab)
                }
            }
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

    public var body: some View {
        VStack(alignment: .leading, spacing: 25) {
            Spacer()
            section(title: Text("General Support", bundle: .module),
                    body: Text("For general questions about the study or to withdraw from the study, please contact:", bundle: .module),
                    contactRoles: [.studySupport, .technicalSupport])
            withdrawalInfoView()
            LineView()
            section(title: Text("Your Participant Rights", bundle: .module),
                    body: Text("For questions about your rights as a research participant, please contact:", bundle: .module),
                    contactRoles: [.irb])
            Spacer()
        }
        .padding(.horizontal, 26)
        .foregroundColor(.textForeground)
        .background(Color.sageWhite)
        .padding(.all, 16)
    }
    
    // MARK: Section Header
    
    @ViewBuilder
    private func section(title: Text, body: Text, contactRoles: [StudyContact.Role]) -> some View {
        VStack(alignment: .leading, spacing: 0) {
            title
                .font(DesignSystem.fontRules.headerFont(at: 4))
                .padding(.bottom, 8)
            body
                .font(DesignSystem.fontRules.bodyFont(at: 1, isEmphasis: false))
        }
        .frame(maxWidth: .infinity)
        .fixedSize(horizontal: false, vertical: true)
        
        let contacts = bridgeManager.study?.contacts.filter { contactRoles.contains($0.role) } ?? []
        ForEach(contacts) {
            contactView($0)
                .padding(.horizontal, 16)
        }
    }
    
    // MARK: Protocol ID
    
    private func protocolIdLabel() -> Text {
        Text("IRB Protocol ID: ", bundle: .module) + Text(bridgeManager.study?.protocolInfo?.protocolId ?? "")
    }
    
    // MARK: Contact Info
    
    @ViewBuilder
    private func contactView(_ contact: StudyContact) -> some View {
        VStack(alignment: .leading, spacing: 10) {
            VStack(alignment: .leading, spacing: 2) {
                Text(contact.name)
                    .font(DesignSystem.fontRules.headerFont(at: 5))
                contact.position
                    .font(DesignSystem.fontRules.bodyFont(at: 2, isEmphasis: false))
            }
            .padding(.leading, 26)
            if let phone = contact.phone {
                contactValue(phone, contactType: .phone)
            }
            if let email = contact.email {
                contactValue(email, contactType: .email)
            }
            if contact.role == .irb {
                protocolIdLabel()
                    .font(DesignSystem.fontRules.bodyFont(at: 2, isEmphasis: false))
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
                    .font(DesignSystem.fontRules.bodyFont(at: 2, isEmphasis: false))
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
            let studyId = bridgeManager.study?.identifier ?? ""
            if let phone = bridgeManager.userSessionInfo.phone {
                withdrawalHeader(Text("To withdraw from this study, you’ll need the Study ID and the phone number you registered with:", bundle: .module))
                withdrawalRow(Text("Study ID: ", bundle: .module), studyId)
                withdrawalRow(Text("Registration Phone Number: ", bundle: .module), phone)
            }
            else if let participantId = bridgeManager.userSessionInfo.participantId(for: studyId) {
                withdrawalHeader(Text("To withdraw from this study, you’ll need the following info:", bundle: .module))
                withdrawalRow(Text("Study ID: ", bundle: .module), studyId)
                withdrawalRow(Text("Participant ID: ", bundle: .module), participantId)
            }
            else {
                EmptyView()
            }
        }
        .font(DesignSystem.fontRules.bodyFont(at: 2, isEmphasis: false))
        .padding(.top, 19)
        .padding(.horizontal, 32)
        .padding(.bottom, 26)
        .fixedSize(horizontal: false, vertical: true)
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
        Text("Hello, World!")
    }
}

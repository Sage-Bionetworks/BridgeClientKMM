//
//  StudyInfoViewModel.swift
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
import SharedMobileUI
import BridgeClient

open class StudyInfoViewModel : ObservableObject {
    
    @Published open var study: Study! {
        didSet {
            updateInfo()
        }
    }
    
    @Published open var institutionName: String = ""
    @Published open var studyLogoUrl: String?
    @Published open var foregroundColor: Color = .textForeground
    @Published open var backgroundColor: Color = .clear
    @Published open var title: String = ""
    @Published open var details: String?
    @Published open var supportContacts: [StudyContact] = []
    @Published open var irbContacts: [StudyContact] = []
    @Published open var studyContacts: [StudyContact] = []
    
    @Published open var participantPhone: Phone?
    @Published open var participantId: String?
    
    public init(isPreview: Bool = false) {
        if isPreview {
            self.study = previewStudy
            self.participantId = "123456"
            updateInfo()
        }
    }

    // MARK: Set up
    
    open func onAppear(_ bridgeManager: SingleStudyAppManager) {
        guard let study = bridgeManager.study ?? (bridgeManager.isPreview ? previewStudy : nil)
        else {
            return
        }
        self.study = study
        self.participantPhone = bridgeManager.userSessionInfo?.phone
        self.participantId = bridgeManager.userSessionInfo?.participantId(for: study.identifier) ?? (bridgeManager.isPreview ? "123456" : nil)
        updateInfo()
    }
    
    open func updateInfo() {
        self.title = study.name
        self.details = study.details
        self.studyLogoUrl = study.studyLogoUrl
        
        if let hex = study.colorScheme?.foreground,
           let color = Color.init(hex: hex) {
            self.foregroundColor = color
        }
        
        if let hex = study.colorScheme?.background,
           let color = Color.init(hex: hex) {
            self.backgroundColor = color
        }
           
        guard let contacts = study.contacts
        else {
            return
        }
        
        self.irbContacts = contacts.compactMap { contact in
            guard contact.role == .irb else { return nil }
            return StudyContact(contact)
        }
        self.supportContacts = contacts.compactMap { contact in
            guard contact.role == .studySupport else { return nil }
            return StudyContact(contact)
        }
        
        let studyRoles: [ContactRole] = [.principalInvestigator, .investigator, .sponsor]
        let studyContacts = contacts
            .filter { studyRoles.contains($0.role) }
            .sorted(by: { studyRoles.firstIndex(of: $0.role)! < studyRoles.firstIndex(of: $1.role)! })
        
        guard let firstContact = studyContacts.first(where: { $0.affiliation != nil })
        else {
            return
        }
        
        self.institutionName = firstContact.affiliation!
        self.studyContacts = studyContacts.map { StudyContact($0) }
        self.studyContacts.insert(StudyContact(name: self.institutionName, position: Text("Institution")), at: 1)
    }
}

public struct StudyContact : Identifiable {
    public var id: String { "\(name)|\(position)" }
    public let name: String
    public let position: Text
    public let phone: String?
    public let email: String?
    public let isIRB: Bool
    
    public init(_ contact: BridgeClient.Contact) {
        self.name = contact.name
        self.position = contact.position.map { Text($0) } ?? {
            switch contact.role {
            case .investigator:
                return Text("Investigator")
            case .irb:
                return Text("IRB/Ethics Board of Record")
            case .principalInvestigator:
                return Text("Principal Investigator")
            case .sponsor:
                return Text("Funder")
            default:
                return Text("Study Support")
            }
        }()
        self.email = contact.email
        self.phone = contact.phone.map { $0.nationalFormat ?? $0.number }
        self.isIRB = (contact.role == .irb)
    }
    
    public init(name: String, position: Text, phone: String? = nil, email: String? = nil, isIRB: Bool = false) {
        self.name = name
        self.position = position
        self.email = email
        self.phone = phone
        self.isIRB = isIRB
    }
}

let previewStudy = Study(identifier: kPreviewStudyId,
                         name: "Xcode Preview Study",
                         phase: StudyPhase.design,
                         version: 1,
                         details: "Description about the study. Lorem ipsum about the study written by the research team that they want to share to participants.\n\nLorem ipsum about the study written by the research team that they want to share to participants. Lorem ipsum about the study written by the research team that they want to share to participants.",
                         clientData: nil,
                         irbName: "University of San Diego",
                         irbDecisionOn: nil,
                         irbExpiresOn: nil,
                         irbDecisionType: nil,
                         irbProtocolName: nil,
                         irbProtocolId: "2039480923",
                         studyLogoUrl: nil,
                         colorScheme: nil,
                         institutionId: nil,
                         scheduleGuid: nil,
                         keywords: nil,
                         diseases: nil,
                         studyDesignTypes: nil,
                         signInTypes: nil,
                         contacts: previewContacts,
                         deleted: nil,
                         createdOn: nil,
                         modifiedOn: nil,
                         type: nil)

let previewContacts = [
    Contact(role: ContactRole.studySupport,
            name: "Christine Larsson",
            position: "Study Researcher",
            affiliation: nil,
            address: nil,
            email: "CLarsson@institution.edu",
            phone: Phone(number: "206-555-1212", regionCode: "us", nationalFormat: "(206) 555-1212", type: "Phone"),
            jurisdiction: nil,
            type: "Contact"),
    Contact(role: ContactRole.irb,
            name: "University of San Diego",
            position: "IRB/Ethics Board of Record",
            affiliation: nil,
            address: nil,
            email: "institution@institution.edu",
            phone: Phone(number: "206-555-1212", regionCode: "us", nationalFormat: "(206) 555-1234", type: "Phone"),
            jurisdiction: nil,
            type: "Contact"),
    Contact(role: ContactRole.principalInvestigator,
            name: "Christine Larsson",
            position: "Lead Principle Investigator",
            affiliation: "University of San Diego",
            address: nil,
            email: nil,
            phone: nil,
            jurisdiction: nil,
            type: "Contact"),
    Contact(role: ContactRole.sponsor,
            name: "National Institute of Aging",
            position: "Funder",
            affiliation: nil,
            address: nil,
            email: nil,
            phone: nil,
            jurisdiction: nil,
            type: "Contact"),
]


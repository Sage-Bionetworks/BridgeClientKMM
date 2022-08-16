//
//  StudyObserver.swift
//
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
import JsonModel
import SharedMobileUI

/// This is a threadsafe wrapper for the Kotlin class ``BridgeClient.Study``.
public final class StudyObserver : ObservableObject, Identifiable {
    public var id: String { identifier }
    
    /// The identifier for this study.
    public let identifier: String
    
    /// The name of the study.
    @Published public var name: String?
    
    /// A lifecycle phase for the study.
    @Published public var phase: Phase?
    
    /// The type of sign in used by this study.
    @Published public var signInTypes: [SignInType]?

    /// An in-depth description of this study for prospective participants, or to show participants after
    /// they have joined a study (the “about” screen for the study).
    @Published public var details: String?
    
    /// An identification number for the study that has been assigned by the sponsor or institution running the study.
    @Published public var institutionId: String?
    
    /// A list of contacts for this study.
    @Published public var contacts: [StudyContact] = []
    
    /// The protocol information for this study.
    @Published public var protocolInfo: IRBProtocolInfo?

    /// The branding color for the institution or study.
    @Published public var backgroundColor: Color = .clear
    
    /// The foreground color to use for text.
    @Published public var foregroundColor: Color = .textForeground
    
    /// An URL to a logo for the study.
    @Published public var studyLogoUrl: String?
    
    /// Client data for a study should be in a syntactically valid JSON format. It will be returned as is to
    /// the client (as JSON). It can contain any information that is useful to study authoring tools or
    /// administration tools that is not part of the Bridge data model.
    @Published public var clientData: Data?
    
    /// Has all the study information been loaded? Since this same observer is used for both a signed in and
    /// *not* signed in study, we may need additional info after signin before continuing to onboarding.
    @Published public var allLoaded: Bool = false
    
    public init(identifier: String) {
        self.identifier = identifier
    }
    
    /// Update the observer from the bridge study.
    /// - Parameter study: The study object to use to update the observer.
    /// - Returns: `false` if the `identifier` does not match and the update failed, otherwise `true`.
    @discardableResult
    public func update(from study: BridgeClient.Study) -> Bool {
        return processResultOnMainThread {
            guard self.identifier == study.identifier
            else {
                return false
            }
            
            self.name = study.name
            self.phase = .init(bridgeValue: study.phase)
            self.signInTypes = study.signInTypes?.compactMap { .init(bridgeValue: $0) }
            self.details = study.details
            self.institutionId = study.institutionId
            self.studyLogoUrl = study.studyLogoUrl
            self.updateColors(study.colorScheme)
            self.clientData = study.clientDataJson()
            self.allLoaded = true
            
            self.contacts = study.contacts?.map { .init($0) } ?? []
            if let irbContact = findIRBContact(study) {
                self.protocolInfo = .init(contact: irbContact,
                                          protocolName: study.irbProtocolName,
                                          protocolId: study.irbProtocolId)
            }
            
            return true
        } ?? false
    }
    
    /// Update the observer from the bridge study info.
    /// - Parameter studyInfo: The study info object to use to update the observer.
    /// - Returns: `false` if the `identifier` does not match and the update failed, otherwise `true`.
    @discardableResult
    public func update(from studyInfo: BridgeClient.StudyInfo) -> Bool {
        return processResultOnMainThread {
            guard self.identifier == studyInfo.identifier || studyInfo.identifier == nil
            else {
                return false
            }
            
            self.name = studyInfo.name
            self.phase = studyInfo.phase.flatMap{ .init(bridgeValue: $0) }
            self.signInTypes = studyInfo.signInTypes?.compactMap { .init(bridgeValue: $0) }
            self.details = studyInfo.details
            self.studyLogoUrl = studyInfo.studyLogoUrl
            self.updateColors(studyInfo.colorScheme)
            
            return true
        } ?? false
    }
    
    private func findIRBContact(_ study: BridgeClient.Study) -> StudyContact? {
        return study.irbName.flatMap {
            contactName in self.contacts.first(where: { $0.name == contactName })
        } ?? self.contacts.first(where: { $0.role == .irb })
    }
    
    private func updateColors(_ colorScheme: BridgeClient.ColorScheme?) {
        self.foregroundColor = colorScheme?.foreground.flatMap { .init(hex: $0) } ?? .textForeground
        self.backgroundColor = colorScheme?.background.flatMap { .init(hex: $0) } ?? .clear
    }
    
    /// A lifecycle phase for the study.
    public enum Phase : String, CaseIterable {
        /// If not set, the study is in the LEGACY phase, and no domain logic will be applied to the study, enrollments, etc.
        case legacy
        /// Study is being designed and tested and has not begun. All accounts created in this phase are marked as test
        /// accounts, and schedules are still mutable. The study is not visible in public registries.
        case design
        /// Study has launched and is visible in public registries, and accepting new participants through some form of
        /// enrollment. The schedule is published when the study is transitioned to this phase, and can no longer change.
        case recruitment
        /// The study is no longer accepting new participants, but participants are still active in the study. The study is no
        /// longer visible in public registries and will no longer accept new sign ups.
        case inFlight = "in_flight"
        /// All participants have completed the study protocol, and the data is being analyzed. For IRBs, this study is still
        /// open and it should still be available in administrative UIs for reporting, but no mobile or desktop
        /// participant-facing client should be engaged with the study.
        case analysis
        /// Analysis has been completed and the study has been reported to the IRB. The study can now be logically
        /// deleted.
        case completed
        /// The study was withdrawn before completion. It can be withdrawn from any other phase, and at that point it
        /// can be logically deleted.
        case withdrawn
        
        init?(bridgeValue: BridgeClient.StudyPhase) {
            self.init(rawValue: bridgeValue.serialName ?? "null")
        }
    }
    
    public enum SignInType : String {
        case emailPassword = "email_password"
        case phonePassword = "phone_password"
        case externalIdPassword = "external_id_password"
        case emailMessage = "email_message"
        case phoneMessage = "phone_message"
        
        init?(bridgeValue: BridgeClient.SignInType) {
            self.init(rawValue: bridgeValue.serialName ?? "null")
        }
    }
}

/// IRB protocol information.
public struct IRBProtocolInfo : Hashable, Identifiable {
    public var id: Int { self.hashValue }
    
    /// The primary IRB contact for this study.
    public let contact: StudyContact
    
    /// The name of the protocol as it was submitted to the IRB for approval.
    public let protocolName: String?
    
    /// An identification number for the study that has been assigned by the IRB.
    public let protocolId: String?
}

/// This is a threadsafe wrapper for the Kotlin class ``BridgeClient.Contact``.
public struct StudyContact : Hashable, Identifiable {
    public var id: Int { self.hashValue }
    
    public let name: String
    public let affiliation: String?
    public let jurisdiction: String?
    public let phone: String?
    public let email: String?
    public let address: Address?
    public let role: Role
    
    public var position: Text {
        if let value = self.positionValue {
            return Text(value)
        }
        switch role {
        case .institution:
            return Text("Institution", bundle: .module)
        case .investigator:
            return Text("Investigator", bundle: .module)
        case .irb:
            return Text("IRB/Board of Ethics", bundle: .module)
        case .principalInvestigator:
            return Text("Principal Investigator", bundle: .module)
        case .sponsor:
            return Text("Funder", bundle: .module)
        case .studySupport:
            return Text("Study Support", bundle: .module)
        case .technicalSupport:
            return Text("Technical Support", bundle: .module)
        }
    }
    private let positionValue: String?
    
    public enum Role : String {
        case institution
        case principalInvestigator
        case investigator
        case irb
        case sponsor
        case studySupport
        case technicalSupport
        
        init(_ role: BridgeClient.ContactRole) {
            switch role {
            case .investigator:
                self = .investigator
            case .irb:
                self = .irb
            case .principalInvestigator:
                self = .principalInvestigator
            case .sponsor:
                self = .sponsor
            case .studySupport:
                self = .studySupport
            case .technicalSupport:
                self = .technicalSupport
            default:
                self = .institution
            }
        }
    }
    
    public struct Address : Hashable, Codable {
        public let placeName: String?
        public let street: String?
        public let mailRouting: String?
        public let city: String?
        public let division: String?
        public let postalCode: String?
        public let country: String?
        
        init(_ address: BridgeClient.Address) {
            self.placeName = address.placeName
            self.street = address.street
            self.mailRouting = address.mailRouting
            self.city = address.city
            self.division = address.division
            self.postalCode = address.postalCode
            self.country = address.country
        }
    }
    
    // WARNING: Do not expose publicly. This initializer is *not* threadsafe and
    // must only be called on the main thread. - syoung 10/25/2021
    init(_ contact: BridgeClient.Contact) {
        self.name = contact.name
        self.positionValue = contact.position
        self.email = contact.email
        self.phone = contact.phone.map { $0.nationalFormat ?? $0.number }
        self.address = contact.address.map { .init($0) }
        self.affiliation = contact.affiliation
        self.jurisdiction = contact.jurisdiction
        self.role = .init(contact.role)
    }
    
    public init(name: String,
                role: Role,
                position: String? = nil,
                affiliation: String? = nil,
                jurisdiction: String? = nil,
                phone: String? = nil,
                email: String? = nil,
                address: Address? = nil) {
        self.name = name
        self.role = role
        self.email = email
        self.phone = phone
        self.address = address
        self.positionValue = position
        self.affiliation = affiliation
        self.jurisdiction = jurisdiction
    }
}

/// A convenience method for ensuring that a given result is processed on the main thread.
func processResultOnMainThread<T>(_ process: () -> T?) -> T? {
    var ret: T? = nil
    if Thread.isMainThread {
        ret = process()
    } else {
        DispatchQueue.main.sync {
            ret = process()
        }
    }
    return ret
}

/// A convenience method for ensuring that a given result is processed on the main thread.
func processOnMainThread(_ process: () -> Void) {
    if Thread.isMainThread {
        process()
    } else {
        DispatchQueue.main.sync {
            process()
        }
    }
}

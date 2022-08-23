//
//  SingleStudyAppManager.swift
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
import BridgeClientExtension

fileprivate let kStudyIdKey = "studyId"

/// An app manager that can be used with apps that require participants to be signed in to a single study
/// at a time. The timeline and history for a participant are calculated for a given study. While they *could*
/// be part of more than one study, only one study is the "main" study that is tracked for these kinds of
/// events.
public final class SingleStudyAppManager : BridgeClientAppManager {
    
    /// The identifier of the current study.
    public var studyId: String? {
        study?.identifier
    }
    
    /// The study is an observer that can be populated and/or updated with either a `BridgeClient.StudyInfo`
    /// object or a `BridgeClient.Study` object. This object is threadsafe and observable.
    @Published public var study: StudyObserver? {
        didSet {
            UserDefaults.standard.set(study?.id, forKey: kStudyIdKey)
        }
    }
    
    /// Has the participant "completed" this study?
    @Published public var isStudyComplete: Bool = false
    
    override public func didUpdateUserSessionInfo() {
        super.didUpdateUserSessionInfo()
        updateStudy()
    }

    private var studyManager: NativeStudyManager?

    public override init(platformConfig: IOSPlatformConfig, pemPath: String? = nil) {
        super.init(platformConfig: platformConfig, pemPath: pemPath)
        let studyId = self.isPreview ? previewStudy.identifier : UserDefaults.standard.string(forKey: kStudyIdKey)
        self.study = studyId.map { .init(identifier: $0) }
        if self.isPreview {
            self.study?.update(from: previewStudy)
        }
    }
    
    public override func appWillFinishLaunching(_ launchOptions: [UIApplication.LaunchOptionsKey : Any]?) {
        super.appWillFinishLaunching(launchOptions)
        updateStudy()
    }
    
    public override func signOut() {
        try? studyManager?.onCleared()
        studyManager = nil
        study = nil
        observedStudyId = nil
        super.signOut()
    }
    
    private var observedStudyId: String?
    
    private func updateStudy() {
        // Only update if the user is authenticated.
        guard userSessionInfo.isAuthenticated, userSessionInfo.studyIds.count > 0
        else {
            return
        }
        
        // Check that something has changed which means that we need to
        // reset the study observer.
        let studyIds = userSessionInfo.studyIds
        let previousStudyId = observedStudyId
        var studyId = study?.id
        if studyId == nil || !studyIds.contains(studyId!) {
            studyId = studyIds.first
        }
        guard let studyId = studyId,
                (studyId != previousStudyId || study?.id != studyId || studyManager == nil)
        else {
            return
        }
        
        // If the study observer is nil or does not match the identifier
        // of the study to observe, then initialize a new one.
        if self.study?.id != studyId {
            self.study = .init(identifier: studyId)
        }

        // Set up an observer for changes to the study.
        try? studyManager?.onCleared()
        self.observedStudyId = studyId
        self.studyManager = .init(studyId: studyId) { study in
            self.study?.update(from: study)
        }
        self.studyManager!.observeStudy()
    }
    
    override public func updateAppState() {
        if appConfig.isLaunching {
            appState = .launching
        }
        else if !userSessionInfo.isAuthenticated {
            appState = .login
        }
        else if study == nil {
            // syoung 09/14/2021 On iOS 14.4, SwiftUI is not recognizing and updating on
            // changes to the study object and is hanging on the launch screen. Instead,
            // use the `appState` published property to manage the state of the root view.
            appState = .launching
        }
        else if !isOnboardingFinished {
            appState = .onboarding
        }
        else {
            appState = .main
        }
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

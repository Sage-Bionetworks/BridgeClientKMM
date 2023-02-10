//
//  SingleStudyAppManager.swift
//

import SwiftUI
import BridgeClient
import BridgeClientExtension

public final class SingleStudyAppManager : AbstractSingleStudyAppManager {
}

/// An app manager that can be used with apps that require participants to be signed in to a single study
/// at a time. The timeline and history for a participant are calculated for a given study. While they *could*
/// be part of more than one study, only one study is the "main" study that is tracked for these kinds of
/// events.
open class AbstractSingleStudyAppManager : BridgeClientAppManager {
    
    /// The identifier of the current study.
    public final var studyId: String? {
        study?.identifier
    }
    
    /// The study is an observer that can be populated and/or updated with either a `BridgeClient.StudyInfo`
    /// object or a `BridgeClient.Study` object. This object is threadsafe and observable.
    @Published open var study: StudyObserver? {
        didSet {
            sharedUserDefaults.set(study?.id, forKey: kStudyIdKey)
        }
    }
    
    /// Has the participant "completed" this study?
    @Published open var isStudyComplete: Bool = false
    
    override open func didUpdateUserSessionInfo() {
        super.didUpdateUserSessionInfo()
        updateStudy()
    }

    private var studyManager: NativeStudyManager?
    private var notificationManager: NativeScheduledNotificationManager?

    public override init(platformConfig: IOSPlatformConfig, pemPath: String? = nil) {
        super.init(platformConfig: platformConfig, pemPath: pemPath)
        let studyId = self.isPreview ? previewStudy.identifier : sharedUserDefaults.string(forKey: kStudyIdKey)
        self.study = studyId.map { .init(identifier: $0) }
        if self.isPreview {
            self.study?.update(from: previewStudy)
        }
    }
    
    open override func finishLaunchingApp(_ launchOptions: [UIApplication.LaunchOptionsKey : Any]?) {
        super.finishLaunchingApp(launchOptions)
        updateStudy()
        // Schedule notifications
        try? notificationManager?.onCleared()
        notificationManager = .init()
        
        if (studyId != nil) {
            notificationManager?.observeNotifications(studyId: studyId!) { notificationList in
                self.localNotificationManager.setupNotifications(notificationList)
            }
        }
    }
    
    open override func willSignOut() {
        try? studyManager?.onCleared()
        studyManager = nil
        study = nil
        observedStudyId = nil
        try? notificationManager?.onCleared()
        notificationManager = nil
        super.willSignOut()
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
    
    override open func updateAppState() {
        let state = fetchAppState()
        if state >= .onboarding, study == nil {
            // syoung 09/14/2021 On iOS 14.4, SwiftUI is not recognizing and updating on
            // changes to the study object and is hanging on the launch screen. Instead,
            // use the `appState` published property to manage the state of the root view.
            appState = .launching
        }
        else {
            appState = state
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

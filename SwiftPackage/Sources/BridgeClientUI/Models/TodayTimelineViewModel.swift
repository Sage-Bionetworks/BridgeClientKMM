//
//  TodayTimelineViewModel.swift
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

open class TodayTimelineViewModel : NSObject, ObservableObject {
    
    @Published open var today: Date = Date()
    @Published open var studyId: String?
    @Published open var sessions: [TimelineSession] = []
    
    /// A flag that can be used to set whether or not a view is presenting the assessment. How the assessment is
    /// presented is up to the views built specifically for a given application.
    @Published open var isPresentingAssessment: Bool = false
    
    /// The assessment that is currently (or most recently) selected.
    ///
    /// This is *not* marked as `@Published` because the state of this value may be persisted after the assessment
    /// has been dismissed. Instead, manage presentation using the published ``isPresentingAssessment``
    /// flag. This was the cleanest way that I could figure out to allow for conformance to both the Sage Research
    /// task view controller delegate and the SwiftUI requirement that views and view builders are structs.
    ///
    public var selectedAssessment: AssessmentScheduleInfo?
            
    private var schedules: [NativeScheduledSessionWindow] = [] {
        didSet {
            let newSessions: [TimelineSession] = schedules.map { schedule in
                guard let existingSession = self.sessions.first(where: { $0.instanceGuid == schedule.instanceGuid })
                else {
                    return TimelineSession(schedule)
                }
                existingSession.window = schedule
                return existingSession
            }
            self.sessions = newSessions
        }
    }
    
    public private(set) var bridgeManager: SingleStudyAppManager!
    
    private var timelineManager: NativeTimelineManager! {
        willSet {
            try? timelineManager?.onCleared()
        }
    }
    
    public override init() {
        super.init()
        NotificationCenter.default.addObserver(forName: UIApplication.willEnterForegroundNotification, object: nil, queue: .main) { _ in
            self.updateSessionState()
        }
    }
    
    deinit {
        try? timelineManager?.onCleared()
    }
    
    /// Filter the ``sessions`` and return only those sessions that should be shown for a given ``state``.
    open func filterSchedules(for state: TimelineSession.SessionState) -> [TimelineSession] {
        var todayFound: Bool = false
        return sessions.filter {
            guard $0.state == state else { return false }
            switch $0.state {
            case .availableNow:
                return true
            case .upNext:
                if $0.window.startDateTime.isToday {
                    todayFound = true
                    return true
                } else {
                    return !todayFound
                }
            default:
                return false
            }
        }
    }
    
    /// Called by the view that owns this view model so that it can set up the view on appearance.
    ///
    /// This allows the `View` that uses this model to pass the `SingleStudyAppManager` after
    /// initialization.
    /// 
    /// - Parameter bridgeManager: The bridge manager for this app.
    open func onAppear(bridgeManager: SingleStudyAppManager, previewSchedules: [NativeScheduledSessionWindow] = []) {
        self.bridgeManager = bridgeManager
        self.studyId = bridgeManager.studyId ?? kPreviewStudyId
        if !bridgeManager.isPreview {
            self.timelineManager = NativeTimelineManager(studyId: studyId!, includeAllNotifications: true, alwaysIncludeNextDay: true) { timelineSlice in
                DispatchQueue.main.async {
                    self.today = timelineSlice.instantInDay
                    self.schedules = timelineSlice.scheduledSessionWindows
                    // syoung 07/08/2021 Ideally, we will get to a point where the database does work to parse
                    // the timeline and allow using a separate manager for getting the notifications. For now,
                    // since this is a somewhat expensive operation, return the notifications with the "today"
                    // schedules.
                    self.bridgeManager.localNotificationManager.setupNotifications(timelineSlice.notifications)
                }
            }
            self.timelineManager.observeTodaySchedule()
        }
        else {
            self.schedules = previewSchedules
        }
    }
    
    private func updateSessionState() {
        let now = Date()
        self.sessions.forEach { $0.updateState(now) }
        if !self.today.isToday {
            self.today = now
            self.refreshSchedules()
        }
    }
    
    /// Force a refresh of the schedules.
    open func refreshSchedules() {
        self.timelineManager?.refreshTodaySchedule()
    }
    
    /// Update an adherence record used by this timeline.
    ///
    /// - Parameters:
    ///     - scheduleInfo: The schedule info to use to update the adherence records.
    ///     - startedOn: When the assessment was started. If nil, then the assessment was *not* shown and this update is used to mark the `clientData` or `declined` state only.
    ///     - endedOn: When the assessment was ended. If nil, then the assessment was *not* finished but the `clientData` or `declined` state may have changed.
    ///     - declined: Did the participant "decline" to finish? In other words, do they want to skip this assessment?
    ///     - clientData: Any `JsonSerializable` object that should be stored with this adherence record.
    open func updateAdherenceRecord(scheduleInfo: AssessmentScheduleInfo, startedOn: Date?, endedOn: Date?, declined: Bool, clientData: JsonSerializable?) {
        let record = NativeAdherenceRecord(instanceGuid: scheduleInfo.instanceGuid,
                                           eventTimestamp: scheduleInfo.session.eventTimestamp,
                                           timezoneIdentifier: TimeZone.current.identifier,
                                           startedOn: startedOn,
                                           finishedOn: endedOn,
                                           declined: .init(booleanLiteral: declined),
                                           clientData: clientData?.toBridgeClientJsonElement())
        self.timelineManager.updateAdherenceRecord(record: record)
        
        // Look for a view model to update so that the completion status is updated immediately upon
        // dismissing the view instead of whenever the bridge repos get updated.
        guard let (session, assessment) = findTimelineModel(sessionGuid: scheduleInfo.session.instanceGuid,
                                                            assessmentGuid: scheduleInfo.instanceGuid)
        else {
            print("WARNING! Could not find schedule from guid")
            return
        }

        if endedOn != nil && !declined && !session.window.persistent {
            assessment.isCompleted = true
            session.updateState()
        }
    }
    
    /// Returns the `TimelineSession` and `TimelineAssessment` for the current ``selectedAssessment``.
    public final func current() -> (session: TimelineSession, assessment: TimelineAssessment)? {
        guard let selected = self.selectedAssessment else { return nil }
        return findTimelineModel(sessionGuid: selected.session.instanceGuid, assessmentGuid: selected.instanceGuid)
    }
    
    /// Returns the `TimelineSession` and `TimelineAssessment` for the given ``TimelineSession/instanceGuid``
    /// and ``TimelineAssessment/instanceGuid``.
    ///
    /// - Parameters:
    ///     - sessionGuid: The session `instanceGuid`.
    ///     - assessmentGuid: The assessment `instanceGuid`.
    public final func findTimelineModel(sessionGuid: String, assessmentGuid: String) -> (session: TimelineSession, assessment: TimelineAssessment)? {
        guard let window = sessions.first(where: { $0.instanceGuid == sessionGuid }),
              let assessment = window.assessments.first(where: { $0.instanceGuid == assessmentGuid })
        else {
            return nil
        }
        return (window, assessment)
    }
}


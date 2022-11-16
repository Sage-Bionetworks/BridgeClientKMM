//
//  TodayTimelineViewModel.swift
//

import SwiftUI
import BridgeClient
import BridgeClientExtension
import JsonModel
import ResultModel

fileprivate let kUserSessionIdKey = "userSessionId"

/// This is a view model that can be used to back the data presented to the user for a schedule timeline.
///
/// The default view implementation is the ``TodayView``. That design supports *either* permanently
/// available schedules *or* a chronological list where the assessments are grouped by session.
///
public final class TodayTimelineViewModel : AbstractTodayTimelineViewModel {
}

/// The ``TodayTimelineViewModel`` is final the ``TodayView`` references this as an `EnvironmentObject`.
open class AbstractTodayTimelineViewModel : NSObject, ObservableObject, ScheduledAssessmentHandler {
    
    /// Current date. This is updated to match the date used in calculating timelines when the timeline is updated.
    @Published open var today: Date = Date()
    /// The identifier of the study that is associated with this timeline.
    @Published open var studyId: String?
    /// The list of sessions for "today" and "next day". An update is triggered by the app entering the foreground
    /// *or* a session changing state.
    @Published open var sessions: [TodayTimelineSession] = []
    /// Is the session state loading?
    @Published open var isLoading: Bool = true
    
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
            self.isLoading = false
            let newSessions: [TodayTimelineSession] = schedules.map { schedule in
                guard let existingSession = self.sessions.first(where: { $0.instanceGuid == schedule.instanceGuid })
                else {
                    return TodayTimelineSession(schedule)
                }
                existingSession.window = schedule
                return existingSession
            }
            self.sessions = filterSessions(newSessions)
        }
    }
    
    /// Today timelines use a one-to-one mapping to a single study and are not designed to support participants who
    /// are in more than one study. As such, this connects to an instance (or subclass) of a `SingleStudyAppManager`.
    /// The view that uses this model must hook up the manager - typically by calling `onAppear()`.
    public private(set) var bridgeManager: SingleStudyAppManager!
    
    public private(set) var timelineManager: NativeTimelineManager! {
        willSet {
            try? timelineManager?.onCleared()
        }
    }
    
    private var filterSessions: (([TodayTimelineSession]) -> [TodayTimelineSession])
    
    public init(filterSessions: (([TodayTimelineSession]) -> [TodayTimelineSession])? = nil) {
        self.filterSessions = filterSessions ?? { $0 }
        super.init()
        NotificationCenter.default.addObserver(forName: UIApplication.willEnterForegroundNotification, object: nil, queue: .main) { _ in
            self.updateSessionState()
        }
    }
    
    deinit {
        try? timelineManager?.onCleared()
    }
    
    /// Filter the ``sessions`` and return only those sessions that should be shown for a given ``state``.
    open func filterSchedules(for state: TodayTimelineSession.SessionState) -> [TodayTimelineSession] {
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
        // Exit early if nothing has changed.
        guard self.bridgeManager == nil ||
              self.studyId != bridgeManager.studyId ||
              self.userSessionId != bridgeManager.userSessionInfo.identifier
        else {
            return
        }
        
        // Store whether or not this is a new login
        let isNewLogin = self.userSessionId != bridgeManager.userSessionInfo.identifier
        
        // Set new values
        self.bridgeManager = bridgeManager
        self.studyId = bridgeManager.studyId ?? kPreviewStudyId
        self.userSessionId = bridgeManager.userSessionInfo.identifier
        
        // Update views
        if !bridgeManager.isPreview {
            self.timelineManager = NativeTimelineManager(studyId: studyId!, includeAllNotifications: true, alwaysIncludeNextDay: true, scheduleMutator: nil) { timelineSlice in
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
            self.timelineManager.observeTodaySchedule(isNewLogin: isNewLogin)
        }
        else {
            self.schedules = previewSchedules
        }
    }
    
    var userSessionId: String? {
        get { bridgeManager?.sharedUserDefaults.string(forKey: kUserSessionIdKey) }
        set { bridgeManager?.sharedUserDefaults.set(newValue, forKey: kUserSessionIdKey) }
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
    @MainActor
    open func updateAdherenceRecord(scheduleInfo: AssessmentScheduleInfo, startedOn: Date, endedOn: Date? = nil, declined: Bool = false, clientData: JsonSerializable? = nil) {

        // Create and write an adherence record.
        let record = NativeAdherenceRecord(instanceGuid: scheduleInfo.instanceGuid,
                                           eventTimestamp: scheduleInfo.session.eventTimestamp,
                                           timezoneIdentifier: TimeZone.current.identifier,
                                           startedOn: startedOn,
                                           finishedOn: endedOn,
                                           declined: .init(booleanLiteral: declined),
                                           clientData: clientData?.toBridgeClientJsonElement())
        self.timelineManager?.updateAdherenceRecord(record: record)
        
        // Look for a view model to update so that the completion status is updated immediately upon
        // dismissing the view instead of whenever the bridge repos get updated.
        if let (session, assessment) = findTimelineModel(sessionGuid: scheduleInfo.session.instanceGuid, assessmentGuid: scheduleInfo.instanceGuid),
           (endedOn != nil || declined), !session.window.persistent {
            assessment.isCompleted = (endedOn != nil)
            assessment.isDeclined = declined
            session.updateState()
        }
    }
    
    /// Returns the `TimelineSession` and `TimelineAssessment` for the current ``selectedAssessment``.
    public final func current() -> (session: TodayTimelineSession, assessment: TodayTimelineAssessment)? {
        guard let selected = self.selectedAssessment else { return nil }
        return findTimelineModel(sessionGuid: selected.session.instanceGuid, assessmentGuid: selected.instanceGuid)
    }
    
    /// Returns the `TimelineSession` and `TimelineAssessment` for the given ``TimelineSession/instanceGuid``
    /// and ``TimelineAssessment/instanceGuid``.
    ///
    /// - Parameters:
    ///     - sessionGuid: The session `instanceGuid`.
    ///     - assessmentGuid: The assessment `instanceGuid`.
    public final func findTimelineModel(sessionGuid: String, assessmentGuid: String) -> (session: TodayTimelineSession, assessment: TodayTimelineAssessment)? {
        guard let window = sessions.first(where: { $0.instanceGuid == sessionGuid }),
              let assessment = window.assessments.first(where: { $0.instanceGuid == assessmentGuid })
        else {
            return nil
        }
        return (window, assessment)
    }
    
    // MARK: ScheduledAssessmentHandler
    
    @MainActor
    public func fetchAssessmentConfig(for scheduleInfo: AssessmentScheduleInfo) async throws -> ScheduledAssessmentConfig {
        guard let (_, assessment) = self.findTimelineModel(sessionGuid: scheduleInfo.session.instanceGuid, assessmentGuid: scheduleInfo.instanceGuid)
        else {
            throw ValidationError.unexpectedNull("Could not find assessment with instanceGuid=\(scheduleInfo.instanceGuid)")
        }
        
        return await withCheckedContinuation { continuation in
            self.timelineManager.fetchAssessmentConfig(instanceGuid: assessment.instanceGuid, assessmentInfo: assessment.assessmentInfo) { nativeConfig in
                DispatchQueue.main.async {
                    continuation.resume(returning: .init(scheduleInfo: scheduleInfo, config: nativeConfig.config, restoreResult: nativeConfig.restoredResult))
                }
            }
        }
    }
    
    @MainActor
    public func updateAssessmentStatus(_ scheduleInfo: AssessmentScheduleInfo, status: ScheduledAssessmentStatus) {
        guard scheduleInfo == selectedAssessment else { return }
        
        switch status {
        case .declined(let startedOn):
            updateAdherenceRecord(scheduleInfo: scheduleInfo, startedOn: startedOn, declined: true)
            dismissAssessment(scheduleInfo)
            
        case .saveForLater(let result):
            if let jsonElement = result.toBridgeClientJsonElement(),
               let (session, _) = self.findTimelineModel(sessionGuid: scheduleInfo.session.instanceGuid, assessmentGuid: scheduleInfo.instanceGuid) {
                timelineManager.saveAssessmentResult(instanceGuid: scheduleInfo.instanceGuid, json: jsonElement, expiresOn: session.window.endDateTime)
            }
            updateAdherenceRecord(scheduleInfo: scheduleInfo, startedOn: result.startDate)
            dismissAssessment(scheduleInfo)
        
        case .restartLater:
            dismissAssessment(scheduleInfo)
            
        case .error(let error):
            debugPrint("Assessment \(scheduleInfo.assessmentInfo.identifier) finished early due to error. \(error)")
            dismissAssessment(scheduleInfo)
            
        case .saveAndFinish(let archiveBuilder):
            save(scheduleInfo, archiveBuilder)
            dismissAssessment(scheduleInfo)
            
        case .readyToSave(let archiveBuilder):
            save(scheduleInfo, archiveBuilder)
            
        case .finished:
            dismissAssessment(scheduleInfo)
        }
    }
    
    @MainActor
    private func save(_ scheduleInfo: AssessmentScheduleInfo, _ archiveBuilder: ResultArchiveBuilder) {
        bridgeManager.encryptAndUpload(using: archiveBuilder)
        updateAdherenceRecord(scheduleInfo: scheduleInfo,
                              startedOn: archiveBuilder.startedOn,
                              endedOn: archiveBuilder.endedOn,
                              clientData: archiveBuilder.adherenceData)
        timelineManager.clearAssessmentResult(instanceGuid: scheduleInfo.instanceGuid)
    }
    
    @MainActor
    private func dismissAssessment(_ scheduleInfo: AssessmentScheduleInfo) {
        isPresentingAssessment = false
        selectedAssessment = nil
    }
}


/// The `TodayTimelineSession` is an `ObservableObject` that wraps a Kotlin Native
/// ``NativeScheduledSessionWindow``.
public final class TodayTimelineSession : ObservableObject, Identifiable {
    public final var id: String { self.instanceGuid }
    
    public final let instanceGuid: String
    
    /// The Kotlin Native session window information that backs this object.
    fileprivate var window: BridgeClient.NativeScheduledSessionWindow {
        didSet {
            let newAssessments: [TodayTimelineAssessment] = window.assessments.map { nativeAssessment in
                guard let existingAssessment = self.assessments.first(where: { $0.instanceGuid == nativeAssessment.instanceGuid })
                else {
                    return TodayTimelineAssessment(nativeAssessment)
                }
                existingAssessment.assessment = nativeAssessment
                return existingAssessment
            }
            self.assessments = newAssessments
            _updateStateOnMainThread()
        }
    }
    
    // WARNING: Do not expose publicly. This property is *not* threadsafe and
    // must only be called on the main thread. - syoung 10/25/2021
    var sessionInfo: BridgeClient.SessionInfo {
        window.sessionInfo
    }
    
    /// The assessments included in this session.
    @Published public var assessments: [TodayTimelineAssessment]

    /// The ``state`` is used to allow SwiftUI to respond in a performant way to what is essentially a
    /// cascading if statement about the state of the session.
    @Published public var state: SessionState = .upNext
    
    /// A simple, `Identifiable` enum for describing the session state.
    public enum SessionState : Int, CaseIterable {
        case completed, expired, availableNow, upNext
    }
    
    /// Are the assessments in this session persistent? As in, can they be performed more than once?
    public let persistent: Bool
    
    /// The current text to display for the section header based on the ``state``.
    ///
    /// - Note: This is *not* published b/c this should only ever change in association with a change
    ///         to the ``state`` of the session window.
    public var dateString: String = ""
    
    /// A timer that is fired when this session is going to change state based on the current time.
    private var updateTimer: Timer?
    
    // WARNING: Do not expose publicly. This initializer is *not* threadsafe and
    // must only be called on the main thread. - syoung 10/25/2021
    init(_ window: BridgeClient.NativeScheduledSessionWindow) {
        self.instanceGuid = window.instanceGuid
        self.persistent = window.persistent
        self.window = window
        self.assessments = window.assessments.map { TodayTimelineAssessment($0) }
        self._updateStateOnMainThread()
    }
    
    /// Update the session ``state``.
    public func updateState(_ now: Date = Date()) {
        if Thread.isMainThread {
            _updateStateOnMainThread(now)
        }
        else {
            DispatchQueue.main.async {
                self._updateStateOnMainThread(now)
            }
        }
    }
    
    private func _updateStateOnMainThread(_ now: Date = Date()) {
        
        // Determine availability.
        let availableNow = window.availableNow(now)
        let isExpired = window.isExpired(now)
        let performInOrder = window.performInOrder && !window.persistent
        var found = false
        var finishedOn: Date?
        let isCompleted = self.assessments.reduce(true) { (initial, assessment) in
            let isNext = !found && !(assessment.isCompleted || assessment.isDeclined)
            assessment.isEnabled = availableNow && (!performInOrder || isNext)
            assessment.assessmentScheduleInfo = .init(session: self.window, assessment: assessment.assessment)
            if isNext { found = true }
            if let newFinishedOn = assessment.finishedOn,
               (finishedOn == nil || finishedOn! < newFinishedOn) {
                finishedOn = newFinishedOn
            }
            return initial && assessment.isCompleted
        }
        
        // Set up the session state and timer.
        setupSessionState(availableNow: availableNow, isExpired: isExpired, isCompleted: isCompleted, finishedOn: finishedOn)
        setupTimer(now)
    }
    
    private func setupSessionState(availableNow: Bool, isExpired: Bool, isCompleted: Bool, finishedOn: Date?) {
        if window.persistent && availableNow {
            self.dateString = window.dueDateString
            self.state = .availableNow
        }
        else if isCompleted {
            self.dateString = (finishedOn ?? Date()).localizeDate(hasTimeOfDay: true)
            self.state = .completed
        }
        else if isExpired {
            self.dateString = window.dueDateString
            self.state = .expired
        }
        else if !availableNow {
            self.dateString = window.availableDateString
            self.state = .upNext
        }
        else {
            self.dateString = window.dueDateString
            self.state = .availableNow
        }
    }
    
    /// The timer is used to update the session state when it's going to change due to a date-time trigger.
    private func setupTimer(_ now: Date) {
        updateTimer?.invalidate()
        if self.state == .availableNow, window.endDateTime != .distantFuture {
            let timeInterval = window.endDateTime.timeIntervalSince(now) + 1
            updateTimer = Timer.scheduledTimer(withTimeInterval: timeInterval, repeats: false) { [weak self] _ in
                self?.state = .expired
            }
        }
        else if self.state == .upNext {
            let timeInterval = window.startDateTime.timeIntervalSince(now) + 1
            updateTimer = Timer.scheduledTimer(withTimeInterval: timeInterval, repeats: false) { [weak self] _ in
                guard let strongSelf = self else { return }
                strongSelf.dateString = strongSelf.window.dueDateString
                strongSelf.state = .availableNow
            }
        }
        else {
            updateTimer = nil
        }
    }
}


/// The `TodayTimelineAssessment` is an `ObservableObject` that wraps a Kotlin Native
/// ``NativeScheduledAssessment``.
public final class TodayTimelineAssessment : ObservableObject, Identifiable {
    public var id: String { self.instanceGuid }
    
    public let instanceGuid: String
    
    /// The Kotlin Native assessment information that backs this object.
    fileprivate var assessment: NativeScheduledAssessment {
        didSet {
            self.isCompleted = assessment.isCompleted
            self.isDeclined = assessment.isDeclined
        }
    }
    
    // WARNING: Do not expose publicly. This property is *not* threadsafe and
    // must only be called on the main thread. - syoung 10/25/2021
    var assessmentInfo: BridgeClient.AssessmentInfo {
        assessment.assessmentInfo
    }
    
    /// The thread-safe information needed to access and update scheduled assessments.
    public fileprivate(set) var assessmentScheduleInfo: AssessmentScheduleInfo!
    
    /// Is the assessment enabled?
    @Published public var isEnabled: Bool
    
    /// Is the assessment completed?
    @Published public var isCompleted: Bool {
        didSet {
            self.finishedOn = finishedOn ?? Date()
        }
    }
    
    /// Has the assessment been declined (participant asked *not* to finish)?
    @Published public var isDeclined: Bool
            
    /// When was it finished?
    @Published public var finishedOn: Date?
    
    // WARNING: Do not expose publicly. This initializer is *not* threadsafe and
    // must only be called on the main thread. - syoung 10/25/2021
    public init(_ assessment: NativeScheduledAssessment, isEnabled: Bool = true) {
        self.instanceGuid = assessment.instanceGuid
        self.assessment = assessment
        self.isCompleted = assessment.isCompleted
        self.isDeclined = assessment.isDeclined
        self.isEnabled = isEnabled
        self.finishedOn = assessment.adherenceRecords?
            .filter({ $0.finishedOn != nil })
            .sorted(by: { $0.finishedOn! < $1.finishedOn! })
            .last?.finishedOn
    }
}

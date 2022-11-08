//
//  TodayTimelineViewModelTests.swift
//

import XCTest
import BridgeClient
import BridgeClientExtension
@testable import BridgeClientUI

final class TodayTimelineViewModelTests: XCTestCase {
    
    func testFilterSchedule() {
        guard previewSessionBEnd.isToday else {
            debugPrint("WARNING! Unit test will not work near midnight.")
            return
        }
        
        let bridgeManager = SingleStudyAppManager(appId: kPreviewStudyId)
        let todayManager = TodayTimelineViewModel()
        todayManager.onAppear(bridgeManager: bridgeManager, previewSchedules: previewSchedulesA)
        
        let sessions = todayManager.sessions
        
        XCTAssertEqual(sessions.count, 3)
        XCTAssertEqual(sessions.first?.assessments.count, 3)
        XCTAssertEqual(sessions.first?.sessionInfo.guid, "current_SessionA")
        XCTAssertEqual(sessions.last?.assessments.count, 5)
        XCTAssertEqual(sessions.last?.sessionInfo.guid, "upNext_SessionC")
        
        let availableNow = todayManager.filterSchedules(for: .availableNow)
        XCTAssertEqual(availableNow.count, 1)
        XCTAssertEqual(availableNow.first?.sessionInfo.guid, "current_SessionA")
        
        let upNext = todayManager.filterSchedules(for: .upNext)
        XCTAssertEqual(upNext.count, 1)
        XCTAssertEqual(upNext.first?.sessionInfo.guid, "upNext_SessionB")
    }
    
    func testFindTimelineModel() {
        guard previewSessionBEnd.isToday else {
            debugPrint("WARNING! Unit test will not work near midnight.")
            return
        }
        
        let bridgeManager = SingleStudyAppManager(appId: kPreviewStudyId)
        let todayManager = TodayTimelineViewModel()
        todayManager.onAppear(bridgeManager: bridgeManager, previewSchedules: previewSchedulesA)
        
        let sessions = todayManager.sessions
        guard let session = sessions.last, let assessment = session.assessments.last else {
            XCTFail("Session or Assessment is empty")
            return
        }
        
        let result = todayManager.findTimelineModel(sessionGuid: session.instanceGuid, assessmentGuid: assessment.instanceGuid)
        XCTAssertNotNil(result)
    }
    
    func testTodayTimelineSession_UpdateCompleted() {
        let window = previewSchedulesA[1]
        let session = TodayTimelineSession(window)
        XCTAssertEqual(session.state, .upNext)
        
        session.updateState(previewSessionBStart.addingTimeInterval(5))
        XCTAssertEqual(session.state, .availableNow)
        
        session.assessments.forEach { $0.isCompleted = true }
        session.updateState(previewSessionBStart.addingTimeInterval(10))
        XCTAssertEqual(session.state, .completed)
    }
    
    func testTodayTimelineSession_UpdateExpired() {
        let window = previewSchedulesA[1]
        let session = TodayTimelineSession(window)
        XCTAssertEqual(session.state, .upNext)
        
        session.updateState(previewSessionBEnd.addingTimeInterval(5))
        XCTAssertEqual(session.state, .expired)
    }
    
    func testUpdateSessionState_Declined() {
        let window = previewSchedulesA[0]
        let session = TodayTimelineSession(window)
        XCTAssertEqual(session.state, .availableNow)
        
        guard session.assessments.count >= 2 else {
            XCTFail("Assessments have been editted and no longer meet initial assumptions.")
            return
        }
        
        // Check initial assumptions
        let assessmentA = session.assessments[0]
        XCTAssertTrue(assessmentA.isEnabled)
        XCTAssertFalse(assessmentA.isDeclined)
        XCTAssertFalse(assessmentA.isCompleted)
        let assessmentB = session.assessments[1]
        XCTAssertFalse(assessmentB.isEnabled)
        XCTAssertFalse(assessmentB.isDeclined)
        XCTAssertFalse(assessmentB.isCompleted)
        
        assessmentA.isDeclined = true
        session.updateState()
        
        // Check new state
        XCTAssertTrue(assessmentB.isEnabled)
    }
    
    func testUpdateSessionState_Completed() {
        let window = previewSchedulesA[0]
        let session = TodayTimelineSession(window)
        XCTAssertEqual(session.state, .availableNow)
        
        guard session.assessments.count >= 2 else {
            XCTFail("Assessments have been editted and no longer meet initial assumptions.")
            return
        }
        
        // Check initial assumptions
        let assessmentA = session.assessments[0]
        XCTAssertTrue(assessmentA.isEnabled)
        XCTAssertFalse(assessmentA.isDeclined)
        XCTAssertFalse(assessmentA.isCompleted)
        let assessmentB = session.assessments[1]
        XCTAssertFalse(assessmentB.isEnabled)
        XCTAssertFalse(assessmentB.isDeclined)
        XCTAssertFalse(assessmentB.isCompleted)
        
        assessmentA.isCompleted = true
        session.updateState()
        
        // Check new state
        XCTAssertTrue(assessmentB.isEnabled)
    }
    
    @MainActor
    func testUpdateAdherenceRecord_Declined() {
        guard previewSessionBEnd.isToday else {
            debugPrint("WARNING! Unit test will not work near midnight.")
            return
        }
        
        let bridgeManager = SingleStudyAppManager(appId: kPreviewStudyId)
        let todayManager = TodayTimelineViewModel()
        todayManager.onAppear(bridgeManager: bridgeManager, previewSchedules: previewSchedulesA)
        
        let sessions = todayManager.sessions
        let session = sessions[0]
        XCTAssertEqual(session.state, .availableNow)
        
        // Check initial assumptions
        guard session.assessments.count >= 2 else {
            XCTFail("Assessments have been editted and no longer meet initial assumptions.")
            return
        }

        let assessmentA = session.assessments[0]
        XCTAssertTrue(assessmentA.isEnabled)
        XCTAssertFalse(assessmentA.isDeclined)
        XCTAssertFalse(assessmentA.isCompleted)
        let assessmentB = session.assessments[1]
        XCTAssertFalse(assessmentB.isEnabled)
        XCTAssertFalse(assessmentB.isDeclined)
        XCTAssertFalse(assessmentB.isCompleted)
        
        todayManager.updateAdherenceRecord(scheduleInfo: assessmentA.assessmentScheduleInfo,
                                                 startedOn: Date(),
                                                 endedOn: nil,
                                                 declined: true,
                                                 clientData: nil)
        
        // Check new state
        XCTAssertTrue(assessmentA.isDeclined)
        XCTAssertTrue(assessmentB.isEnabled)
    }
}

let previewAssessments = assessmentLabels.map {
        NativeScheduledAssessment(identifier: $0)
    }

let previewToday = Date()
let previewStart = previewToday.startOfDay()
let previewEnd = previewToday.endOfPeriod(14)

let previewSessionBStart = previewToday.addingTimeInterval(30)
let previewSessionBEnd = previewSessionBStart.addingTimeInterval(30)

let previewTrigger = ISO8601DateFormatter().string(from: Date())
let previewSchedulesA = [
    NativeScheduledSessionWindow(guid: "current_SessionA",
                                 index: 0,
                                 startDateTime: previewStart,
                                 endDateTime: previewEnd,
                                 persistent: false,
                                 hasStartTimeOfDay: false,
                                 hasEndTimeOfDay: false,
                                 assessments: Array(previewAssessments[0..<3]),
                                 performanceOrder: .sequential),
    NativeScheduledSessionWindow(guid: "upNext_SessionB",
                                 index: 1,
                                 startDateTime: previewSessionBStart,
                                 endDateTime: previewSessionBEnd,
                                 persistent: false,
                                 hasStartTimeOfDay: true,
                                 hasEndTimeOfDay: false,
                                 assessments: Array(previewAssessments[3..<8]),
                                 performanceOrder: .sequential),
    NativeScheduledSessionWindow(guid: "upNext_SessionC",
                                 index: 2,
                                 startDateTime: previewStart.addingTimeInterval(36*60*60),
                                 endDateTime: previewEnd,
                                 persistent: false,
                                 hasStartTimeOfDay: true,
                                 hasEndTimeOfDay: false,
                                 assessments: Array(previewAssessments[3..<8]),
                                 performanceOrder: .sequential)
]

extension Date {
    fileprivate func endOfPeriod(_ days: Int) -> Date {
        let calendar = Calendar.current
        let start = calendar.startOfDay(for: self)
        return calendar.date(byAdding: .day, value: days, to: start, wrappingComponents: false)!
    }
}

extension NativeScheduledSessionWindow {
    fileprivate convenience init(guid: String,
                                 index: Int,
                                 startDateTime: Date,
                                 endDateTime: Date,
                                 persistent: Bool,
                                 hasStartTimeOfDay: Bool,
                                 hasEndTimeOfDay: Bool,
                                 assessments: [NativeScheduledAssessment],
                                 performanceOrder: PerformanceOrder) {
        self.init(instanceGuid: "guid_\(index)",
              eventTimestamp: previewTrigger,
              startDateTime: startDateTime,
              endDateTime: endDateTime,
              persistent: persistent,
              hasStartTimeOfDay: hasStartTimeOfDay,
              hasEndTimeOfDay: hasEndTimeOfDay,
              assessments: assessments,
              sessionInfo: .init(guid: guid,
                                 label: "Some Activities",
                                 symbol: nil,
                                 performanceOrder: performanceOrder,
                                 timeWindowGuids: nil,
                                 minutesToComplete: nil,
                                 notifications: nil,
                                 type: "SessionInfo"),
              startEventId: "timeline_retreived")
    }
}

extension NativeScheduledAssessment {
    fileprivate convenience init(identifier: String, isCompleted: Bool = false) {
        self.init(instanceGuid: UUID().uuidString,
                  assessmentInfo: AssessmentInfo(identifier: identifier),
                  isCompleted: isCompleted,
                  isDeclined: false,
                  adherenceRecords: nil)
    }
}

extension AssessmentInfo {
    fileprivate convenience init(identifier: String) {
        self.init(key: identifier,
                  guid: UUID().uuidString,
                  appId: kPreviewStudyId,
                  identifier: identifier,
                  revision: nil,
                  label: identifier,
                  minutesToComplete: 3,
                  colorScheme: nil,
                  configUrl: "http://foo.org",
                  type: "AssessmentInfo")
    }
}

fileprivate let assessmentLabels = [
    "Arranging Pictures",
    "Arrow Matching",
    "Shape-Color Sorting",
    "Faces & Names A",
    "Number-Symbol Match",
    "Faces & Names B",
    "Sequences",
    "Spelling",
    "Word Meaning",
]


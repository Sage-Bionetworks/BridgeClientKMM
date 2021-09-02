//
//  TodayTimelineViewModelTests.swift
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

import XCTest
import BridgeClient
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
        XCTAssertEqual(sessions.first?.window.sessionInfo.guid, "current_SessionA")
        XCTAssertEqual(sessions.last?.assessments.count, 5)
        XCTAssertEqual(sessions.last?.window.sessionInfo.guid, "upNext_SessionC")
        
        let availableNow = todayManager.filterSchedules(for: .availableNow)
        XCTAssertEqual(availableNow.count, 1)
        XCTAssertEqual(availableNow.first?.window.sessionInfo.guid, "current_SessionA")
        
        let upNext = todayManager.filterSchedules(for: .upNext)
        XCTAssertEqual(upNext.count, 1)
        XCTAssertEqual(upNext.first?.window.sessionInfo.guid, "upNext_SessionB")
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
              sessionInfo: SessionInfo(guid: guid,
                                       label: "Some Activities",
                                       startEventId: "foo",
                                       performanceOrder: performanceOrder,
                                       timeWindowGuids: nil,
                                       minutesToComplete: nil,
                                       notifications: nil,
                                       type: "SessionInfo"))
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
        self.init(key: identifier, guid: UUID().uuidString, appId: kPreviewStudyId, identifier: identifier, revision: nil, label: identifier, minutesToComplete: 3, colorScheme: nil, type: "AssessmentInfo")
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


//
//  PreviewTodayView.swift
//

import SwiftUI
import BridgeClient
@testable import BridgeClientUI

struct PreviewTodayView: View {
    @StateObject var bridgeManager: SingleStudyAppManager = .init(appId: kPreviewStudyId)
    @StateObject var viewModel: TodayTimelineViewModel = .init()
    
    private let previewSchedules: [NativeScheduledSessionWindow]
    init(_ previewSchedules: [NativeScheduledSessionWindow] = []) {
        self.previewSchedules = previewSchedules
    }
    
    var body: some View {
        TodayView(previewSchedules)
            .assessmentInfoMap(.init(extensions: MTBIdentifier.allCases))
            .environmentObject(bridgeManager)
            .environmentObject(viewModel)
            .fullScreenCover(isPresented: $viewModel.isPresentingAssessment) {
                XcodePreview(viewModel: viewModel)
            }
    }
}

struct PreviewTodayView_Previews: PreviewProvider {
    static var previews: some View {
        PreviewTodayView(previewSchedulesA)
        PreviewTodayView(previewSchedulesB)
        PreviewTodayView(previewSchedulesA)
            .environment(\.sizeCategory, .accessibilityExtraExtraLarge)
    }
}


// XCode Previews

fileprivate struct XcodePreview : View {
    @ObservedObject var viewModel: TodayTimelineViewModel
    
    var body: some View {
        Text(viewModel.selectedAssessment?.assessmentInfo.label ?? "Preview")
            .onTapGesture {
                if let selected = viewModel.selectedAssessment,
                   let (session, assessment) = viewModel.findTimelineModel(sessionGuid: selected.session.instanceGuid, assessmentGuid: selected.instanceGuid) {
                    assessment.isCompleted = true
                    session.updateState()
                }
                viewModel.isPresentingAssessment = false
            }
    }
}

let previewAssessments = assessmentLabels.map {
        NativeScheduledAssessment(identifier: $0)
    }

func previewAssessmentCompleted() -> TodayTimelineAssessment {
    let assessment = TodayTimelineAssessment(previewAssessments[0])
    assessment.isCompleted = true
    return assessment
}

let previewToday = Date()
let previewStart = previewToday.startOfDay()
let previewEnd = previewToday.endOfPeriod(14)

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
                                 index: 0,
                                 startDateTime: previewStart.addingTimeInterval(20*60*60),
                                 endDateTime: previewStart.addingTimeInterval(21*60*60),
                                 persistent: false,
                                 hasStartTimeOfDay: true,
                                 hasEndTimeOfDay: false,
                                 assessments: Array(previewAssessments[3..<8]),
                                 performanceOrder: .sequential),
    NativeScheduledSessionWindow(guid: "upNext_SessionC",
                                 index: 0,
                                 startDateTime: previewStart.addingTimeInterval(36*60*60),
                                 endDateTime: previewEnd,
                                 persistent: false,
                                 hasStartTimeOfDay: true,
                                 hasEndTimeOfDay: false,
                                 assessments: Array(previewAssessments[3..<8]),
                                 performanceOrder: .sequential)
]

let previewSchedulesB = [
    NativeScheduledSessionWindow(guid: "current_SessionA",
                                 index: 0,
                                 startDateTime: previewStart,
                                 endDateTime: previewEnd,
                                 persistent: false,
                                 hasStartTimeOfDay: false,
                                 hasEndTimeOfDay: false,
                                 assessments: Array(previewAssessments[0..<3]),
                                 performanceOrder: .sequential),
    NativeScheduledSessionWindow(guid: "upNext_SessionC",
                                 index: 0,
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
                                       symbol: nil,
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
        self.init(key: identifier, guid: UUID().uuidString, appId: kPreviewStudyId, identifier: identifier, revision: nil, label: identifier, minutesToComplete: 3, colorScheme: assessmentColors[identifier], configUrl: "nil", type: "AssessmentInfo")
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

fileprivate let assessmentColors: [String : BridgeClient.ColorScheme] = [
    "Arranging Pictures": .init(foreground: "#CCE5D5"),
    "Arrow Matching" : .init(foreground: "#F4B795"),
    "Faces & Names A" : .init(foreground: "#CCE5D5"),
    "Faces & Names B" : .init(foreground: "#CCE5D5"),
    "Number-Symbol Match": .init(foreground: "#D2CBE8"),
    "Sequences" : .init(foreground: "#ABBCE8"),
    "Shape-Color Sorting" : .init(foreground: "#F4B795"),
    "Spelling" : .init(foreground: "#95CFF4"),
    "Word Meaning" : .init(foreground: "#95CFF4"),
]

extension BridgeClient.ColorScheme {
    fileprivate convenience init(foreground: String) {
        self.init(foreground: foreground, background: nil, activated: nil, inactivated: nil, type: nil)
    }
}

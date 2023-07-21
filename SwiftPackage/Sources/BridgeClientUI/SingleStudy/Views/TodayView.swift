//
//  TodayScheduleView.swift
//

import SwiftUI
import BridgeClientExtension
import BridgeClient
import SharedMobileUI

/// The "Today" view used by Mobile Toolbox app and any other app with the same open-ended design of multiple studies with wildly
/// varying timing for sessions where messaging the participant about whether or not they have completed uploading their data is important.
public struct TodayView: View {
    @EnvironmentObject private var bridgeManager: SingleStudyAppManager
    @EnvironmentObject private var viewModel: TodayTimelineViewModel
    
    private let previewSchedules: [NativeScheduledSessionWindow]
    public init(_ previewSchedules: [NativeScheduledSessionWindow] = []) {
        self.previewSchedules = previewSchedules
    }
    
    public var body: some View {
        GenericTodayWrapperView<TodayFinishedView>(viewModel: viewModel)
            .onAppear {
                viewModel.onAppear(bridgeManager: bridgeManager, previewSchedules: previewSchedules)
            }
    }
}

/// A simplified "today" view.
/// - Note: This is currently only used by the BiAffect app.
public struct TodayWrapperView: View {
    @ObservedObject private var viewModel: TodayTimelineViewModel
    
    public init(viewModel: TodayTimelineViewModel) {
        self.viewModel = viewModel
    }
    
    public var body: some View {
        GenericTodayWrapperView<TodayUpToDateView>(viewModel: viewModel)
    }
}

/// A version of the Today view that can handle a generic view for the header when there are no assessments *currently* available.
public struct GenericTodayWrapperView<TodayFinishedContent : TodayFinishedViewProtocol>: View {
    @ObservedObject private var viewModel: AbstractTodayTimelineViewModel
    
    public init(viewModel: AbstractTodayTimelineViewModel) {
        self.viewModel = viewModel
    }
    
    public var body: some View {
        ScreenBackground {
            VStack {
                dateHeader()
                CustomScrollView {
                    VStack(spacing: 16) {
                        ForEach(TodayTimelineSession.SessionState.allCases, id: \.rawValue) { state in
                            let sessions = viewModel.filterSchedules(for: state)
                            if sessions.count > 0 {
                                Section(header: availabilityHeader(state)) {
                                    ForEach(sessions) { session in
                                        Section(header: sectionHeader(session)) {
                                            ForEach(session.assessments) { assessment in
                                                singleCardView(session, assessment)
                                            }
                                        }// Section session
                                    }
                                }// Section state
                            }
                            else if state == .availableNow, !viewModel.isLoading {
                                TodayFinishedContent()
                            }
                        }// end ForEach state
                        Spacer()
                            .frame(height: 4)
                    }
                }// end scrollview
            }
        }
    }
    
    @ViewBuilder
    private func dateHeader() -> some View {
        Text(viewModel.today, style: .date)
            .font(DesignSystem.fontRules.headerFont(at: 7))
            .foregroundColor(Color.hex727272)
            .padding(.top, 16)
    }
    
    @ViewBuilder
    private func availabilityHeader(_ state: TodayTimelineSession.SessionState) -> some View {
        availabilityText(state)
            .font(DesignSystem.fontRules.headerFont(at: 2))
            .foregroundColor(.textForeground)
    }
    
    private func availabilityText(_ state: TodayTimelineSession.SessionState) -> Text {
        switch state {
        case .availableNow:
            return Text("CURRENT_ACTIVITIES", bundle: .module)
        case .upNext:
            return Text("Up next", bundle: .module)
        case .completed:
            return Text("Completed", bundle: .module)
        case .expired:
            return Text("Expired", bundle: .module)
        }
    }
    
    @ViewBuilder
    private func singleCardView(_ session: TodayTimelineSession, _ assessment: TodayTimelineAssessment) -> some View {
        if (session.persistent || !(assessment.isDeclined || assessment.isCompleted)) {
            Button(action: {
                guard assessment.isEnabled else { return }
                self.viewModel.selectedAssessment = assessment.assessmentScheduleInfo
                self.viewModel.isPresentingAssessment = true
            }) {
                AssessmentTimelineCardView(assessment)
            }
            .transition(.exitStageLeft)
            .animation(.easeOut(duration: 1))
            .accessibilityLabel(assessment.assessmentInfo.label)
            .accessibilityIdentifier(assessment.assessmentInfo.identifier)
        }
    }

    @ViewBuilder
    private func sectionHeader(_ session: TodayTimelineSession) -> some View {
        HStack {
            LineView()
            if !session.dateString.isEmpty {
                switch session.state {
                case .expired:
                    sectionTitle(format: NSLocalizedString("Expired: %@", bundle: .module, comment: ""),
                                 session.dateString, "locked_icon")
                case .upNext:
                    sectionTitle(format: NSLocalizedString("Opens: %@", bundle: .module, comment: ""),
                                 session.dateString, "locked_icon")
                default:
                    sectionTitle(format: NSLocalizedString("Due: %@", bundle: .module, comment: ""),
                                 session.dateString, "timer_icon")
                }
            }
        }
        .padding(.horizontal)
    }
    
    @ViewBuilder
    private func sectionTitle(format: String, _ dateString: String, _ imageName: String) -> some View {
        Image(decorative: imageName, bundle: .module)
        Text(String(format: format, dateString))
            .font(DesignSystem.fontRules.headerFont(at: 7))
            .foregroundColor(.sageBlack)
            .fixedSize()
        LineView()
    }
}

extension AnyTransition {
    static var exitStageLeft: AnyTransition {
        let insertion = AnyTransition.identity
        let removal = AnyTransition.move(edge: .leading)
        return .asymmetric(insertion: insertion, removal: removal)
    }
}

// Used to allow previewing the `TodayView`
fileprivate struct PreviewTodayView : View {
    @StateObject var bridgeManager = SingleStudyAppManager(appId: kPreviewStudyId)
    @StateObject var viewModel = TodayTimelineViewModel()
    
    var body: some View {
        TodayView(previewSchedulesB)
            .environmentObject(bridgeManager)
            .environmentObject(viewModel)
    }
}

struct TodayScheduleView_Previews: PreviewProvider {
    static var previews: some View {
        PreviewTodayView()
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

let previewStartB = previewStart.endOfPeriod(60)
let previewEndB = previewStartB.endOfPeriod(7)

let previewSchedulesB = [
    NativeScheduledSessionWindow(guid: "upNext_SessionC",
                                 index: 0,
                                 startDateTime: previewStartB,
                                 endDateTime: previewEndB,
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
                  sessionInfo: SessionInfo(guid: guid, performanceOrder: performanceOrder),
                  startEventId: nil)
    }
}

extension SessionInfo {
    convenience init(guid: String, performanceOrder: PerformanceOrder) {
        self.init(guid: guid, label: "Some Activities", symbol: nil, performanceOrder: performanceOrder, timeWindowGuids: nil, minutesToComplete: nil, notifications: nil, type: "SessionInfo")
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
        self.init(key: identifier, guid: UUID().uuidString, appId: kPreviewStudyId, identifier: identifier, revision: nil, label: identifier, minutesToComplete: 3, colorScheme: assessmentColors[identifier], configUrl: "nil", imageResource: nil, type: "AssessmentInfo")
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


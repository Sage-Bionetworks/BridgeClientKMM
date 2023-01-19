//
//  TodayScheduleView.swift
//

import SwiftUI
import BridgeClient
import SharedMobileUI

public struct TodayView: View {
    @EnvironmentObject private var bridgeManager: SingleStudyAppManager
    @EnvironmentObject private var viewModel: TodayTimelineViewModel
    
    private let previewSchedules: [NativeScheduledSessionWindow]
    public init(_ previewSchedules: [NativeScheduledSessionWindow] = []) {
        self.previewSchedules = previewSchedules
    }
    
    public var body: some View {
        TodayWrapperView(viewModel: viewModel)
            .onAppear {
                viewModel.onAppear(bridgeManager: bridgeManager, previewSchedules: previewSchedules)
            }
    }
}

public struct TodayWrapperView: View {
    @ObservedObject private var viewModel: TodayTimelineViewModel
    
    public init(viewModel: TodayTimelineViewModel) {
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
                                ZStack {
                                    Image(decorative: "available_complete", bundle: .module)
                                    Text("Nice, you’re all up to date!", bundle: .module)
                                        // TODO: syoung 09/23/2021 Cut the image so that I can make this text dynamic.
                                        .font(.playfairDisplayFont(fixedSize: 18))
                                }
                                .padding(.vertical, 24)
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
            return Text("Current activities", bundle: .module)
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
            AssessmentTimelineCardView(assessment)
                .onTapGesture {
                    guard assessment.isEnabled else { return }
                    self.viewModel.selectedAssessment = assessment.assessmentScheduleInfo
                    self.viewModel.isPresentingAssessment = true
                }
                .transition(.exitStageLeft)
                .animation(.easeOut(duration: 1))
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

// syoung 08/16/2021 SwiftUI fails to build complex UI in a shared framework. Therefore, the preview
// for this element is in iosApp.
struct TodayScheduleView_Previews: PreviewProvider {
    static var previews: some View {
        Text("Hello, World!")
    }
}


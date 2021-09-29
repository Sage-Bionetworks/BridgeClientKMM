//
//  TodayScheduleView.swift
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
import SharedMobileUI

public struct TodayView: View {
    @EnvironmentObject private var bridgeManager: SingleStudyAppManager
    @EnvironmentObject private var viewModel: TodayTimelineViewModel
    
    private let previewSchedules: [NativeScheduledSessionWindow]
    public init(_ previewSchedules: [NativeScheduledSessionWindow] = []) {
        self.previewSchedules = previewSchedules
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
                            else if state == .availableNow {
                                ZStack {
                                    Image(decorative: "available_complete", bundle: .module)
                                    Text("nice, you’re all up to date!", bundle: .module)
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
        .onAppear {
            viewModel.onAppear(bridgeManager: bridgeManager, previewSchedules: previewSchedules)
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
                    sectionTitle("Expired:  \(session.dateString)", "locked_icon")
                case .upNext:
                    sectionTitle("Opens:  \(session.dateString)", "locked_icon")
                default:
                    sectionTitle("Due:  \(session.dateString)", "timer_icon")
                }
            }
        }
        .padding(.horizontal)
    }
    
    @ViewBuilder
    private func sectionTitle(_ textValue: LocalizedStringKey, _ imageName: String) -> some View {
        Image(decorative: imageName, bundle: .module)
        Text(textValue, bundle: .module)
            .font(DesignSystem.fontRules.headerFont(at: 7))
            .foregroundColor(.sageBlack)
            .fixedSize()
        LineView()
    }
}

struct AssessmentTimelineCardView : View {
    @ObservedObject var viewModel: TodayTimelineAssessment
    @SwiftUI.Environment(\.sizeCategory) var sizeCategory
    @SwiftUI.Environment(\.assessmentInfoMap) var assessmentInfoMap: AssessmentInfoMap
    
    init(_ viewModel: TodayTimelineAssessment) {
        self.viewModel = viewModel
    }
    
    private var assessment: AssessmentInfo {
        viewModel.assessmentInfo
    }
    
    private let horizontalPadding: CGFloat = 24
    private let cornerRadius: CGFloat = 5
    
    var body: some View {
        ZStack(alignment: .topTrailing) {
            card()
            CompletedDotView(color: assessmentInfoMap.color(for: assessment))
                .opacity(viewModel.isCompleted ? 1 : 0)
                .padding(.trailing, horizontalPadding - 8)
                .padding(.top, 12)
        }
        .fixedSize(horizontal: false, vertical: true)
    }
    
    @ViewBuilder
    private func card() -> some View {
        ZStack(alignment: Alignment(horizontal: .leading, vertical: .top)) {
            HStack(spacing: 0) {
                rightSide()
                leftSide()
            }
            .opacity((viewModel.isEnabled || viewModel.isCompleted) ? 1.0 : 0.3)
        }
        .background(Color.sageWhite)
        .cornerRadius(cornerRadius)
        .overlay(
                RoundedRectangle(cornerRadius: cornerRadius)
                    .stroke(Color.hexDFDFDF, lineWidth: 0.5)
            )
        .shadow(color: .black.opacity(0.05), radius: 4, x: 0, y: 3)
        .padding(.horizontal, horizontalPadding)
        .padding(.vertical, 0)
    }
    
    @ViewBuilder
    private func rightSide() -> some View {
        assessmentInfoMap.color(for: assessment)
            .overlay(assessmentInfoMap.icon(for: assessment))
            .frame(width: 113)
            .frame(minHeight: 112)
    }
    
    @ViewBuilder
    private func leftSide() -> some View {
        VStack(alignment: .leading) {
            assessmentInfoMap.title(for: assessment)
                .font(DesignSystem.fontRules.headerFont(at: 4))
                .foregroundColor(.textForeground)
                .padding(10)
            
            Spacer()
            
            HStack {
                Spacer()
                assessmentInfoMap.estimatedTime(for: assessment)
                    .foregroundColor(.textForeground)
                    .font(DesignSystem.fontRules.headerFont(at: 6))
            }
            .padding()
        }
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
        Text("Hello, World")
    }
}


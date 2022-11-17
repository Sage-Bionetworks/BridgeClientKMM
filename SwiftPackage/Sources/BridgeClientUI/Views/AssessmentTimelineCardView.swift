// Created 11/16/22
// swift-version:5.0

import SwiftUI
import BridgeClient
import SharedMobileUI

public struct AssessmentTimelineCardView : View {
    @ObservedObject var viewModel: TodayTimelineAssessment
    @SwiftUI.Environment(\.sizeCategory) var sizeCategory
    @SwiftUI.Environment(\.assessmentInfoMap) var assessmentInfoMap: AssessmentInfoMap
    
    public init(_ viewModel: TodayTimelineAssessment) {
        self.viewModel = viewModel
    }
    
    private var assessment: AssessmentInfo {
        viewModel.assessmentInfo
    }
    
    private let horizontalPadding: CGFloat = 24
    private let cornerRadius: CGFloat = 5
    
    public var body: some View {
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

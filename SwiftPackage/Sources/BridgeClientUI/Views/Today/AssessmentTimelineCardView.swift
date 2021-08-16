//
//  AssessmentTimelineCardView.swift
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

struct AssessmentTimelineCardView : View {
    @ObservedObject var viewModel: TodayTimelineAssessment
    @SwiftUI.Environment(\.sizeCategory) var sizeCategory
    @SwiftUI.Environment(\.assessmentInfoMap) var assessmentInfoMap: AssessmentInfoMap
    
    init(_ viewModel: TodayTimelineAssessment) {
        self.viewModel = viewModel
    }
    
    private var assessment: AssessmentInfo {
        viewModel.assessment.assessmentInfo
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
                .font(.latoFont(16, relativeTo: .title, weight: .regular))
                .foregroundColor(.textForeground)
                .padding(10)
            
            Spacer()
            
            HStack {
                Spacer()
                assessmentInfoMap.estimatedTime(for: assessment)
                    .foregroundColor(.textForeground)
                    .font(.poppinsFont(10, relativeTo: .caption, weight: .regular))
            }
            .padding()
        }
    }
}

// syoung 08/16/2021 SwiftUI fails to build complex UI in a shared framework. Therefore, the preview
// for this element is in iosApp.
struct AssessmentSingleCardView_Previews: PreviewProvider {
    static var previews: some View {
        Text("Hello, World")
    }
}


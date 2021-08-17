//
//  PreviewHistoryView.swift
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
import BridgeClientUI


struct PreviewHistoryView_Previews: PreviewProvider {
    static var previews: some View {
        HistoryView(historyPreviews)
            .assessmentInfoMap(.init(extensions: MTBIdentifier.allCases))
            .environmentObject(SingleStudyAppManager(appId: kPreviewStudyId))
    }
}

let historyPreviews: [AssessmentRecord] = [
    .init(assessmentInfo: .init(identifier: .numberMatch),
          instanceGuid: "record1", startedOn: Date().addingTimeInterval(-360), finishedOn: Date()),
    .init(assessmentInfo: .init(identifier: .mfs),
          instanceGuid: "record2", startedOn: Date().addingTimeInterval(-480), finishedOn: Date()),
    .init(assessmentInfo: .init(identifier: .spelling),
          instanceGuid: "record3", startedOn: Date().addingTimeInterval(-120), finishedOn: Date()),
    .init(assessmentInfo: .init(identifier: .vocabulary),
          instanceGuid: "record4", startedOn: Date().addingTimeInterval(-420), finishedOn: Date())
]


extension AssessmentInfo {
    convenience init(identifier: MTBIdentifier) {
        self.init(key: identifier.rawValue, guid: UUID().uuidString, appId: kPreviewStudyId, identifier: identifier.rawValue, revision: nil, label: identifier.label(), minutesToComplete: 3, colorScheme: nil, type: "AssessmentInfo")
    }
}

extension BridgeClient.ColorScheme {
    fileprivate convenience init(foreground: String) {
        self.init(foreground: foreground, background: nil, activated: nil, inactivated: nil, type: nil)
    }
}

enum MTBIdentifier : String, CaseIterable, AssessmentInfoExtension {
    case numberMatch="number-match",
    mfs="memory-for-sequences",
    dccs="dccs",
    fnamea="fnamea",
    flanker="flanker",
    fnameb="fnameb",
    psm="psm",
    spelling="spelling",
    vocabulary="vocabulary"
    
    var assessmentIdentifier: String { self.rawValue }
    
    func label() -> String {
        switch self {
        case .numberMatch:
            return "Number-Symbol Match"
        case .mfs:
            return "Sequences"
        case .dccs:
            return "Shape-Color Sorting"
        case .fnamea:
            return "Faces & Names A"
        case .fnameb:
            return "Faces & Names B"
        case .flanker:
            return "Arrow Matching"
        case .psm:
            return "Arranging Pictures"
        case .spelling:
            return "Spelling"
        case .vocabulary:
            return "Word Meaning"
        }
    }
    
    func title() -> Text {
        Text(label())
    }
    
    func icon() -> Image {
        Image(label())
    }
    
    func color() -> Color {
        switch self {
        case .numberMatch:
            return .appLavender
        case .mfs:
            return .appPeriwinkle
        case .dccs:
            return .appOrange
        case .fnamea:
            return .appGreen
        case .fnameb:
            return .appGreen
        case .flanker:
            return .appOrange
        case .psm:
            return .appGreen
        case .spelling:
            return .appBlue
        case .vocabulary:
            return .appBlue
        }
    }
}

extension Color {
    static let appGreen: Color = .init("app.green")
    static let appBlue: Color = .init("app.blue")
    static let appOrange: Color = .init("app.orange")
    static let appPeriwinkle: Color = .init("app.periwinkle")
    static let appLavender: Color = .init("app.lavender")
}

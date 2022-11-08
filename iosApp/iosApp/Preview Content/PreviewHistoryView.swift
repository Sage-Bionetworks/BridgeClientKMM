//
//  PreviewHistoryView.swift
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
        self.init(key: identifier.rawValue, guid: UUID().uuidString, appId: kPreviewStudyId, identifier: identifier.rawValue, revision: nil, label: identifier.label(), minutesToComplete: 3, colorScheme: nil, configUrl: nil, type: "AssessmentInfo")
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

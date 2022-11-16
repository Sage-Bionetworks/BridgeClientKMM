//
//  HistoryView.swift
//

import SwiftUI
import BridgeClient
import SharedMobileUI

public struct HistoryView: View {
    @EnvironmentObject private var bridgeManager: SingleStudyAppManager
    @StateObject private var viewModel: HistoryViewModel = .init()
    @SwiftUI.Environment(\.assessmentInfoMap) private var assessmentInfoMap: AssessmentInfoMap

    private let previewRecords: [AssessmentRecord]
    
    public init(_ previewRecords: [AssessmentRecord] = []) {
        self.previewRecords = previewRecords
    }
    
    public var body: some View {
        ScreenBackground {
            VStack(spacing: 21) {
                if viewModel.minutes == 0 {
                    heroImage()
                    Text("Your completed activities will be shown here.", bundle: .module)
                        .font(DesignSystem.fontRules.headerFont(at: 2))
                        .multilineTextAlignment(.center)
                        .foregroundColor(.textForeground)
                        .padding(.horizontal, 24)
                }
                else {
                    header()
                    CustomScrollView {
                        LazyVStack(spacing: 16) {
                            ForEach(viewModel.records) { record in
                                HistoryCardView(record)
                            }
                        }
                        .padding(.bottom, 20)
                    }// end scrollview
                }
            }
        }
        .onAppear {
            viewModel.onAppear(studyId: bridgeManager.studyId!, previewRecords: previewRecords)
        }
    }
    
    @ViewBuilder
    private func header() -> some View {
        VStack(spacing: 10) {
            ZStack(alignment: .top) {
                heroImage()
                    .padding(.top, 12)
                VStack(spacing: -6) {
                    Text("\(viewModel.minutes)")
                        // Use fixed size b/c otherwise real-estate will not fit with image.
                        .font(.latoFont(fixedSize: 24, weight: .bold))
                        .foregroundColor(.textForeground)
                    Text("minutes", bundle: .module)
                        // Use fixed size b/c otherwise real-estate will not fit with image.
                        .font(.poppinsFont(fixedSize: 12))
                        .foregroundColor(.textForeground)
                }
            }
            Text("Thank you for your contributions!", bundle: .module)
                .font(DesignSystem.fontRules.headerFont(at: 2))
                .foregroundColor(.textForeground)
        }
        .padding(.top, 16)
    }
    
    @ViewBuilder
    private func heroImage() -> some View {
        CompositeTintedImage("History.tinted", background: "History", bundle: .module)
    }
    

}

extension DateFormatter {
    static func string(from date: Date, timeZone: TimeZone, dateStyle: Style, timeStyle: Style) -> String {
        let formatter = DateFormatter()
        formatter.timeStyle = timeStyle
        formatter.dateStyle = dateStyle
        formatter.timeZone = timeZone
        return formatter.string(from: date)
    }
}

// syoung 08/16/2021 SwiftUI fails to build complex UI in a shared framework. Therefore, the preview
// for this element is in iosApp.
struct HistoryView_Previews: PreviewProvider {
    static var previews: some View {
        Text("Hello, World!")
    }
}
 


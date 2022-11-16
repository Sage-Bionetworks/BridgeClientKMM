// Created 11/16/22
// swift-version:5.0

import SwiftUI
import SharedMobileUI

public struct HistoryCardView: View {
    @SwiftUI.Environment(\.assessmentInfoMap) private var assessmentInfoMap: AssessmentInfoMap
    
    let record: AssessmentRecord
    public init(_ record: AssessmentRecord) {
        self.record = record
    }
    
    public var body: some View {
        HStack(alignment: .top, spacing: 0) {
            rightSide(record)
            leftSide(record)
        }
        .padding(.horizontal, 31)
    }
    
    @ViewBuilder
    private func rightSide(_ record: AssessmentRecord) -> some View {
        assessmentInfoMap.color(for: record.info)
            .overlay(assessmentInfoMap.icon(for: record.info))
            .frame(width: 114)
            .frame(minHeight: 112)
    }
    
    let detailHeaderFont = DesignSystem.fontRules.headerFont(at: 7)
    let titleHeaderFont = DesignSystem.fontRules.headerFont(at: 5)
    
    @ViewBuilder
    private func leftSide(_ record: AssessmentRecord) -> some View {
        VStack(alignment: .leading, spacing: 2) {
            CompletedDotView(color: assessmentInfoMap.color(for: record.info))
                .padding(.bottom, 2)
            Text(DateFormatter.string(from: record.finishedOn, timeZone: record.timeZone, dateStyle: .medium, timeStyle: .none))
                .foregroundColor(.textForeground)
                .font(detailHeaderFont)
            assessmentInfoMap.title(for: record.info)
                .font(titleHeaderFont)
                .foregroundColor(.textForeground)
                .frame(maxWidth: .infinity, alignment: .leading)
            Text(durationFormatter.string(from: Double(record.minutes * 60)) ?? "")
                .foregroundColor(.textForeground)
                .font(detailHeaderFont)
        }
        .padding(.leading, 16)
        .padding(.top, 8)
    }
    
    private let durationFormatter: DateComponentsFormatter = {
        let formatter = DateComponentsFormatter()
        formatter.unitsStyle = .short
        formatter.allowedUnits = .minute
        return formatter
    }()
}

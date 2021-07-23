//
//  HistoryViewModel.swift
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
import JsonModel

open class HistoryViewModel : NSObject, ObservableObject {
    
    /// The sum of all the minutes spent on the performed assessments.
    @Published open var minutes: Int = 0
    
    /// The list of all finished assessment records.
    @Published open var records: [AssessmentRecord] = [] {
        didSet {
            self.minutes = self.records.reduce(0, { $0 + $1.minutes })
        }
    }
            
    private var studyId: String!
        
    private var historyManager: NativeHistoryManager! {
        willSet {
            try? historyManager?.onCleared()
        }
    }
    
    deinit {
        try? historyManager?.onCleared()
    }
    
    /// Called by the view that owns this view model so that it can set up the view on appearance.
    ///
    /// This allows the `View` that uses this model to pass the `studyId` after
    /// initialization.
    ///
    /// - Parameters
    ///     - studyId: The identifier for this study.
    ///     - previewRecords: The records to use to create the View preview.
    open func onAppear(studyId: String, previewRecords: [AssessmentRecord] = []) {
        guard self.studyId == nil else { return }
        
        self.studyId = studyId
        if (studyId == kPreviewStudyId) {
            self.records = previewRecords
        }
        else {
            self.historyManager = NativeHistoryManager(studyId: studyId) { timelineSlice in
                self.records = timelineSlice.scheduledSessionWindows
                    .flatMap { $0.history() }
                    .sorted(by: { $0.finishedOn > $1.finishedOn })
            }
            self.historyManager.observeHistory()
        }
    }
}

extension NativeScheduledSessionWindow {
    fileprivate func history() -> [AssessmentRecord] {
        self.assessments.flatMap { $0.history() }
    }
}

extension NativeScheduledAssessment {
    fileprivate func history() -> [AssessmentRecord] {
        self.adherenceRecords?.compactMap { record in
            guard let startedOn = record.startedOn, let finishedOn = record.finishedOn else { return nil }
            return AssessmentRecord(assessmentInfo: self.assessmentInfo,
                                     instanceGuid: self.instanceGuid,
                                     startedOn: startedOn,
                                     finishedOn: finishedOn,
                                     timeZone: record.timezoneIdentifier.map { TimeZone(identifier: $0) ?? .current },
                                     clientData: record.clientDataJson())
        } ?? []
    }
}

/// The `AssessmentRecord` is an `Identifiable` object that wraps a Kotlin Native
/// ``AdherenceRecord`` for use in showing completed assessments.
public struct AssessmentRecord : Identifiable {
    public let id: String
    
    public let info: AssessmentInfo
    public let instanceGuid: String
    public let startedOn: Date
    public let finishedOn: Date
    public let timeZone: TimeZone
    public let clientData: Data?
    public let minutes: Int
    
    public init(assessmentInfo: AssessmentInfo, instanceGuid: String, startedOn: Date, finishedOn: Date, timeZone: TimeZone? = nil, clientData: Data? = nil) {
        self.id = "\(instanceGuid)|\(finishedOn)"
        self.info = assessmentInfo
        self.instanceGuid = instanceGuid
        self.startedOn = startedOn
        self.finishedOn = finishedOn
        self.timeZone = timeZone ?? TimeZone.current
        self.clientData = clientData
        self.minutes = Calendar.current.dateComponents([.minute], from: startedOn, to: finishedOn).minute ?? 1
    }
}

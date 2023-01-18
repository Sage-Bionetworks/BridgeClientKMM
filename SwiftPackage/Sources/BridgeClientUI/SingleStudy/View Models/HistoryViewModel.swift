//
//  HistoryViewModel.swift
//

import SwiftUI
import BridgeClient
import BridgeClientExtension
import JsonModel

/// The view model that backs a `HistoryView` and wraps `BridgeClient.NativeAdherenceRecord`
/// objects to create threadsafe objects that can be used to build views.
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
            self.historyManager = NativeHistoryManager(studyId: studyId) { historyList in
                self.records = historyList
                    .flatMap { $0.history() }
                    .sorted(by: { $0.finishedOn > $1.finishedOn })
            }
            self.historyManager.observeHistory()
        }
    }
}

extension AssessmentHistoryRecord {
    fileprivate func history() -> AssessmentRecord {
            return AssessmentRecord(assessmentInfo: self.assessmentInfo,
                                     instanceGuid: self.instanceGuid,
                                    startedOn: self.startedOn.dateValue,
                                    finishedOn: self.finishedOn.dateValue,
                                    timeZone: self.clientTimeZone.map { TimeZone(identifier: $0) ?? .current },
                                    clientData: self.clientDataJson())
    }
}


/// The `AssessmentRecord` is an `Identifiable` object that wraps a Kotlin Native
/// ``AssessmentHistoryRecord`` for use in showing completed assessments.
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
        self.minutes = max(1, Calendar.current.dateComponents([.minute], from: startedOn, to: finishedOn).minute ?? 1)
    }
}

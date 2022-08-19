//
//  ScheduledAssessmentHandler.swift
//
//  Copyright © 2021-2022 Sage Bionetworks. All rights reserved.
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

import Foundation
import BridgeClient
import JsonModel

/// Light-weight protocol for handling state of a displayed assessment.
/// - Note: All the methods within this protocol are marked as `@MainActor` which means that they are
///         required to launch from the main thread.
public protocol ScheduledAssessmentHandler : AnyObject {
    
    /// An async method for fetching the config for a given scheduled assessment.
    @MainActor func fetchAssessmentConfig(for scheduleInfo: AssessmentScheduleInfo) async throws -> ScheduledAssessmentConfig
    
    /// Hand off updating the adherence record, any published objects, uploading, etc.
    @MainActor func updateAssessmentStatus(_ scheduleInfo: AssessmentScheduleInfo, status: ScheduledAssessmentStatus)
}

/// The  status of a scheduled assessment when it is finished
public enum ScheduledAssessmentStatus {
    case declined(Date)
    case saveForLater(AssessmentResult)
    case restartLater
    case error(Error)
    case readyToSave(ResultArchiveBuilder)
    case finished
    case saveAndFinish(ResultArchiveBuilder)
}

/// Thread-safe result of fetching the config and restored result for a given scheduled assessment.
public struct ScheduledAssessmentConfig : Identifiable {
    public var id: String { scheduleInfo.instanceGuid }
    public let scheduleInfo: AssessmentScheduleInfo
    public let config: Data?
    public let restoreResult: Data?
    
    public init(scheduleInfo: AssessmentScheduleInfo, config: Data?, restoreResult: Data?) {
        self.scheduleInfo = scheduleInfo
        self.config = config
        self.restoreResult = restoreResult
    }
}

/// Thread-safe assessment schedule info. Kotlin objects can only be accessed from the main thread or it causes
/// a crash so this must be initialized on the main thread.
public struct AssessmentScheduleInfo : Identifiable, Hashable, Codable {
    public var id: String { instanceGuid }
    
    /// The ``BridgeClient.ScheduledAssessment/instanceGuid`` for this scheduled assessment.
    public let instanceGuid: String
    
    /// Information about the session.
    public let session: Session
    
    /// Information about the assessment.
    public let assessmentInfo: Info
    
    public var assessmentIdentifier : String {
        assessmentInfo.identifier
    }
    
    public init(session: NativeScheduledSessionWindow, assessment: NativeScheduledAssessment) {
        self.instanceGuid = assessment.instanceGuid
        self.session = Session(instanceGuid: session.instanceGuid,
                               eventTimestamp: session.eventTimestamp,
                               scheduledOn: session.startDateTime)
        self.assessmentInfo = Info(identifier: assessment.assessmentInfo.identifier,
                                   key: assessment.assessmentInfo.key,
                                   guid: assessment.assessmentInfo.guid,
                                   label: assessment.assessmentInfo.label)
    }
    
    /// A thread-safe struct with information required to load and save the results from an assessment.
    public struct Info : Hashable, Codable {
        /// The ``BridgeClient.AssessmentInfo/identifier``.
        public let identifier: String
        /// The ``BridgeClient.AssessmentInfo/key``.
        public let key: String?
        /// The ``BridgeClient.AssessmentInfo/guid``.
        public let guid: String?
        /// The ``BridgeClient.AssessmentInfo/label``.
        public let label: String?
    }
    
    /// A thread-safe struct with information needed to find and update the Kotlin ``BridgeClient.NativeScheduledSessionWindow``
    /// for the session to which this assessment belongs.
    public struct Session : Hashable, Codable {
        /// The ``BridgeClient.ScheduledSession/instanceGuid`` for this scheduled assessment.
        public let instanceGuid: String
        /// The ``BridgeClient.StudyActivityEvent/timestamp`` for the event used as the reference
        /// when *this* schedule was built. This value is mutable on the server so the timestamp is used rather
        /// than the event id.
        public let eventTimestamp: String
        /// The calculated start time for when this session opens.
        public let scheduledOn: Date
    }
}


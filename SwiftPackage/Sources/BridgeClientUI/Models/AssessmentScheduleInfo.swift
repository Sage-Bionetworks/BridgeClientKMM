//
//  AssessmentScheduleInfo.swift
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

import Foundation
import BridgeClient

public struct AssessmentScheduleInfo {
    public let instanceGuid: String
    public let session: Session
    public let assessmentInfo: Info
    
    public init(session: NativeScheduledSessionWindow, assessment: NativeScheduledAssessment) {
        self.instanceGuid = assessment.instanceGuid
        self.session = Session(instanceGuid: session.instanceGuid,
                               eventTimestamp: session.eventTimestamp,
                               scheduledOn: session.startDateTime)
        self.assessmentInfo = Info(identifier: assessment.assessmentInfo.identifier!,
                                   key: assessment.assessmentInfo.key,
                                   guid: assessment.assessmentInfo.identifier,
                                   label: assessment.assessmentInfo.label)
    }
    
    /// Thread-safe assessment info. Kotlin objects can only be accessed from the main thread or it causes a crash.
    public struct Info : Hashable, Codable {
        let identifier: String
        let key: String?
        let guid: String?
        let label: String?
    }
    
    public struct Session : Hashable, Codable {
        public let instanceGuid: String
        public let eventTimestamp: String
        public let scheduledOn: Date
    }
}

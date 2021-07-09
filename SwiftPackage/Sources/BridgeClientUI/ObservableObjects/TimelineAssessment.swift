//
//  TimelineAssessment.swift
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

/// The `TimelineAssessment` is an `ObservableObject` that wraps a Kotlin Native
/// ``NativeScheduledAssessment``.
public final class TimelineAssessment : ObservableObject, Identifiable {
    public var id: String {
        self.assessment.instanceGuid
    }
    
    public var instanceGuid: String {
        self.assessment.instanceGuid
    }
    
    /// The Kotlin Native assessment information that backs this object.
    public var assessment: NativeScheduledAssessment {
        didSet {
            self.isCompleted = assessment.isCompleted
            self.isDeclined = assessment.isDeclined
        }
    }
    
    /// Is the assessment enabled?
    @Published public var isEnabled: Bool
    
    /// Is the assessment completed?
    @Published public var isCompleted: Bool {
        didSet {
            self.finishedOn = finishedOn ?? Date()
        }
    }
    
    // Has the assessment been declined (participant asked *not* to finish).
    @Published public var isDeclined: Bool
            
    /// When was it finished?
    @Published public var finishedOn: Date?
    
    public init(_ assessment: NativeScheduledAssessment, isEnabled: Bool = true) {
        self.assessment = assessment
        self.isCompleted = assessment.isCompleted
        self.isDeclined = assessment.isDeclined
        self.isEnabled = isEnabled
        self.finishedOn = assessment.adherenceRecords?
            .filter({ $0.finishedOn != nil })
            .sorted(by: { $0.finishedOn! < $1.finishedOn! })
            .last?.finishedOn
    }
}

//
//  TimelineSession.swift
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

public class TimelineSession : ObservableObject, Identifiable {
    public var id: String {
        self.window.instanceGuid
    }
    
    public var instanceGuid: String {
        self.window.instanceGuid
    }
    
    public var window: NativeScheduledSessionWindow {
        didSet {
            let newAssessments: [TimelineAssessment] = window.assessments.map { nativeAssessment in
                guard let existingAssessment = self.assessments.first(where: { $0.instanceGuid == nativeAssessment.instanceGuid })
                else {
                    return TimelineAssessment(nativeAssessment)
                }
                existingAssessment.assessment = nativeAssessment
                return existingAssessment
            }
            self.assessments = newAssessments
            updateState()
        }
    }
    
    @Published public var assessments: [TimelineAssessment]
    @Published public var availableNow: Bool = false
    @Published public var isExpired: Bool = false
    @Published public var isCompleted: Bool = false
    
    public init(_ window: NativeScheduledSessionWindow) {
        self.window = window
        self.assessments = window.assessments.map { TimelineAssessment($0) }
        self.updateState()
    }
    
    public func updateState(_ now: Date = Date()) {
        self.availableNow = window.availableNow()
        self.isExpired = window.isExpired()
        let performInOrder = window.performInOrder
        var found = false
        self.isCompleted = self.assessments.reduce(true) { (initial, assessment) in
            let isNext = !found && !assessment.isCompleted
            assessment.isLocked = !window.persistent && (!availableNow || (performInOrder && !isNext))
            if isNext { found = true }
            return initial && assessment.isCompleted
        }
    }
}

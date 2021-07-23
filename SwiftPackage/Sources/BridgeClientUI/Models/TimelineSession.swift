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

/// The `TimelineSession` is an `ObservableObject` that wraps a Kotlin Native
/// ``NativeScheduledSessionWindow``.
public final class TimelineSession : ObservableObject, Identifiable {
    public final var id: String {
        self.window.instanceGuid
    }
    
    public final var instanceGuid: String {
        self.window.instanceGuid
    }
    
    /// The Kotlin Native session window information that backs this object.
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
    
    /// The assessments included in this session.
    @Published public var assessments: [TimelineAssessment]

    /// The ``state`` is used allow SwiftUI to respond in a performant way to what is essentially a
    /// cascading if statement about the state of the session.
    @Published public var state: SessionState = .upNext
    
    /// A simple, `Identifiable` enum for describing the session state.
    public enum SessionState : Int, CaseIterable {
        case completed, expired, availableNow, upNext
    }
    
    /// The current text to display for the section header based on the ``state``.
    ///
    /// - Note: This is *not* published b/c this should only ever change in association with a change
    ///         to the ``state`` of the session window.
    public var dateString: String = ""
    
    /// A timer that is fired when this session is going to change state based on the current time.
    private var updateTimer: Timer?
    
    public init(_ window: NativeScheduledSessionWindow) {
        self.window = window
        self.assessments = window.assessments.map { TimelineAssessment($0) }
        self.updateState()
    }
    
    /// Update the session ``state``.
    public func updateState(_ now: Date = Date()) {
        
        // Determine availability.
        let availableNow = window.availableNow(now)
        let isExpired = window.isExpired(now)
        let performInOrder = window.performInOrder
        var found = false
        var finishedOn: Date?
        let isCompleted = self.assessments.reduce(true) { (initial, assessment) in
            let isNext = !found && !assessment.isCompleted
            assessment.isEnabled = availableNow && (!performInOrder || isNext)
            if isNext { found = true }
            if let newFinishedOn = assessment.finishedOn,
               (finishedOn == nil || finishedOn! < newFinishedOn) {
                finishedOn = newFinishedOn
            }
            return initial && assessment.isCompleted
        }
        
        // Set up the session state and timer.
        setupSessionState(availableNow: availableNow, isExpired: isExpired, isCompleted: isCompleted, finishedOn: finishedOn)
        setupTimer(now)
    }
    
    private func setupSessionState(availableNow: Bool, isExpired: Bool, isCompleted: Bool, finishedOn: Date?) {
        if window.persistent && availableNow {
            self.dateString = window.dueDateString
            self.state = .availableNow
        }
        else if isCompleted {
            self.dateString = (finishedOn ?? Date()).localizeDate(hasTimeOfDay: true)
            self.state = .completed
        }
        else if isExpired {
            self.dateString = window.dueDateString
            self.state = .expired
        }
        else if !availableNow {
            self.dateString = window.availableDateString
            self.state = .upNext
        }
        else {
            self.dateString = window.dueDateString
            self.state = .availableNow
        }
    }
    
    /// The timer is used to update the session state when it's going to change due to a date-time trigger.
    private func setupTimer(_ now: Date) {
        // Set up a timer to update the
        updateTimer?.invalidate()
        if self.state == .availableNow, window.endDateTime != .distantFuture {
            let timeInterval = window.endDateTime.timeIntervalSince(now) + 1
            updateTimer = Timer.scheduledTimer(withTimeInterval: timeInterval, repeats: false) { [weak self] _ in
                self?.state = .expired
            }
        }
        else if self.state == .upNext {
            let timeInterval = window.startDateTime.timeIntervalSince(now) + 1
            updateTimer = Timer.scheduledTimer(withTimeInterval: timeInterval, repeats: false) { [weak self] _ in
                guard let strongSelf = self else { return }
                strongSelf.dateString = strongSelf.window.dueDateString
                strongSelf.state = .availableNow
            }
        }
        else {
            updateTimer = nil
        }
    }
}


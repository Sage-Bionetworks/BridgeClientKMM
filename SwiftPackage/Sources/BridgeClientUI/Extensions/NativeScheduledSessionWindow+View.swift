//
//  NativeScheduledSessionWindow+View.swift
//
//

import SwiftUI
import BridgeClient

extension NativeScheduledSessionWindow {
    
    /// Is the schedule available?
    public func availableNow(_ now: Date = Date()) -> Bool {
        startDateTime < now && now < endDateTime
    }
    
    /// Is the schedule expired?
    public func isExpired(_ now: Date = Date()) -> Bool {
        now > endDateTime
    }
    
    /// Should the assessments in the session be performed in order?
    public var performInOrder: Bool {
        sessionInfo.performanceOrder != .participantChoice
    }
    
    /// Localized date string for when the schedule will be available.
    public var availableDateString: String {
        startDateTime.localizeDate(hasTimeOfDay: hasStartTimeOfDay)
    }
    
    /// Localized date string for when the schedule is due.
    public var dueDateString: String {
        endDateTime == .distantFuture ? "" : endDateTime.localizeDate(hasTimeOfDay: hasEndTimeOfDay)
    }
}


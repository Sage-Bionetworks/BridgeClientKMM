//
//  Date+Utils.swift
//
//

import Foundation
import BridgeClient

extension Date {
    
    /// Convenience method for returning the "start" of the day (i.e., midnight).
    ///
    /// - Returns: The start of the day using the current calendar.
    public func startOfDay() -> Date {
        Calendar.current.startOfDay(for: self)
    }
    
    /// Is this date "today"?
    public var isToday: Bool {
        Calendar.current.isDateInToday(self)
    }
    
    /// Is this date "tomorrow"?
    public var isTomorrow: Bool {
        Calendar.current.isDateInTomorrow(self)
    }
    
    public func isWithinDays(_ numDays: Int) -> Bool {
        Calendar.current.dateComponents([.day], from: self, to: Date()).day.map { abs($0) <= numDays } ?? false
    }
    
    /// This date localized using the participant's preferred locale.
    ///
    /// - Parameter hasTimeOfDay: Whether or not the time of day should be included.
    /// - Returns: Localized formatted string for the date.
    public func localizeDate(hasTimeOfDay: Bool) -> String {
        if !hasTimeOfDay {
            return DateFormatter.localizedString(from: self, dateStyle: .medium, timeStyle: .none)
        }
        else if self.isToday {
            return String(format: NSLocalizedString("today at %@", bundle: .module, comment: ""),
                          DateFormatter.localizedString(from: self, dateStyle: .none, timeStyle: .short))
        }
        else {
            return DateFormatter.localizedString(from: self, dateStyle: .medium, timeStyle: .short)
        }
    }
}

extension Kotlinx_datetimeInstant {
    public var dateValue: Date {
        Date(timeIntervalSince1970: Double(self.toEpochMilliseconds()) * 0.001)
    }
}

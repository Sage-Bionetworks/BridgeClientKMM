//
//  Date+Utils.swift
//
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

extension Date {
    
    public func startOfDay() -> Date {
        Calendar.current.startOfDay(for: self)
    }
    
    public var isToday: Bool {
        Calendar.current.isDateInToday(self)
    }
    
    public var isTomorrow: Bool {
        Calendar.current.isDateInTomorrow(self)
    }
    
    public func localizeDate(hasTimeOfDay: Bool) -> String {
        if !hasTimeOfDay {
            if self.isTomorrow {
                return NSLocalizedString("tomorrow", comment: "")
            }
            else {
                return String.localizedStringWithFormat(NSLocalizedString("on %@", comment: ""),
                                                        DateFormatter.localizedString(from: self, dateStyle: .medium, timeStyle: .none))
            }
        }
        else if self.isToday {
            return String.localizedStringWithFormat(NSLocalizedString("today at %@", comment: ""),
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

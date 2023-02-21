//
//  LocalNotificationManagerTests.swift
//

import XCTest
import UserNotifications
import BridgeClient
@testable import BridgeClientUI

fileprivate let dateTime: Set<Calendar.Component> = [.day, .month, .year, .hour, .minute]
fileprivate let timeOnly: Set<Calendar.Component> = [.hour, .minute]

extension Date {
    fileprivate func addingDays(_ days: Int) -> Date {
        let calendar = Calendar.init(identifier: .iso8601)
        return calendar.date(byAdding: .day, value: days, to: self, wrappingComponents: false)!
    }
}

final class LocalNotificationManagerTests: XCTestCase {
    
    let calendar = Calendar(identifier: .iso8601)
    var scheduleOnA: Date!
    var scheduleOnB: Date!
    var scheduleA: NativeScheduledNotification!
    var scheduleB: NativeScheduledNotification!
    
    override func setUp() {
        super.setUp()
        
        let now = Date()

        // Schedule A started an hour ago. Repeats every day for 90 days.
        self.scheduleOnA = now.addingTimeInterval(-60*60)
        let repeatUntilA = scheduleOnA.addingDays(90)
        var repeatIntervalA = DateComponents()
        repeatIntervalA.day = 1
        self.scheduleA = NativeScheduledNotification(instanceGuid: "scheduleA",
                                                     scheduleOn: calendar.dateComponents(dateTime, from: scheduleOnA),
                                                     repeatInterval: repeatIntervalA,
                                                     repeatUntil: calendar.dateComponents(dateTime, from: repeatUntilA),
                                                     allowSnooze: false,
                                                     message: .init(subject: "Schedule A", message: "Do schedule A", lang: nil, type: nil),
                                                     isTimeSensitive: false)
        
        // Schedule B starts in an hour. Repeats once a week for ~2 years.
        self.scheduleOnB = now.addingTimeInterval(60*60)
        let repeatUntilB = scheduleOnB.addingDays(2*52*7)
        var repeatIntervalB = DateComponents()
        repeatIntervalB.day = 7
        self.scheduleB = NativeScheduledNotification(instanceGuid: "scheduleB",
                                                     scheduleOn: calendar.dateComponents(dateTime, from: scheduleOnB),
                                                     repeatInterval: repeatIntervalB,
                                                     repeatUntil: calendar.dateComponents(dateTime, from: repeatUntilB),
                                                     allowSnooze: true,
                                                     message: .init(subject: "Schedule B", message: "Do schedule B", lang: nil, type: nil),
                                                     isTimeSensitive: false)
    }
    
    func testBuildRequests_ScheduleB() {
        let manager = LocalNotificationManager()

        let builders = manager.buildRequests(for: scheduleB)
        XCTAssertEqual(builders.count, 60)
        let sorted = builders.sorted()
        XCTAssertEqual(builders, sorted)
        let expectedScheduledOn = calendar.date(from: calendar.dateComponents(dateTime, from: scheduleOnB))
        XCTAssertEqual(expectedScheduledOn, builders.first?.scheduleInstant)
        
        builders.enumerated().forEach { (index, builder) in
            let expectedDate = expectedScheduledOn!.addingDays(7*index)
            let expectedComponents = calendar.dateComponents(dateTime, from: expectedDate)
            XCTAssertEqual(expectedDate, builder.scheduleInstant)
            XCTAssertEqual(expectedComponents, builder.trigger.dateComponents)
            XCTAssertEqual(expectedDate, builder.trigger.nextTriggerDate())
        }
    }
    
    func testCreateBuilders() {
        let manager = LocalNotificationManager()
        manager.notifications = [scheduleA, scheduleB]
        let builders = manager.createBuilders()
        
        XCTAssertEqual(builders.count, 60)
        let sorted = builders.sorted()
        XCTAssertEqual(builders, sorted)
        
        let buildersB = builders.filter { $0.instanceGuid == "scheduleB" }
        let expectedScheduledOn = calendar.date(from: calendar.dateComponents(dateTime, from: scheduleOnB))
        XCTAssertEqual(expectedScheduledOn, buildersB.first?.scheduleInstant)
        
        buildersB.enumerated().forEach { (index, builder) in
            let expectedDate = expectedScheduledOn!.addingDays(7*index)
            let expectedComponents = calendar.dateComponents(dateTime, from: expectedDate)
            XCTAssertEqual(expectedDate, builder.scheduleInstant)
            XCTAssertEqual(expectedComponents, builder.trigger.dateComponents)
            XCTAssertEqual(expectedDate, builder.trigger.nextTriggerDate())
        }
    }
    
    func testCreateRequests() {
        let manager = LocalNotificationManager()
        manager.notifications = [scheduleA, scheduleB]
        let requests = manager.createRequests()
        
        XCTAssertEqual(requests.count, 60)
        
        if let requestA = requests.first(where: { $0.content.threadIdentifier == "scheduleA" }) {
            XCTAssertEqual(requestA.content.title, "Schedule A")
            XCTAssertEqual(requestA.content.body, "Do schedule A")
            XCTAssertEqual(requestA.content.categoryIdentifier, "org.sagebionetworks.ScheduledSession")
            XCTAssertEqual(requestA.content.threadIdentifier, "scheduleA")
            XCTAssertEqual(requestA.content.userInfo["allowSnooze"] as? Bool, false)
            if let trigger = requestA.trigger as? UNCalendarNotificationTrigger {
                let expectedComponents = calendar.dateComponents(timeOnly, from: scheduleOnA)
                XCTAssertEqual(expectedComponents, trigger.dateComponents)
                let expectedNextTrigger = calendar.date(from: calendar.dateComponents(dateTime, from: scheduleOnA.addingDays(1)))
                XCTAssertEqual(expectedNextTrigger, trigger.nextTriggerDate())
            }
            else {
                XCTFail("\(String(describing: requestA.trigger)) not `UNCalendarNotificationTrigger`")
            }
        }
        else {
            XCTFail("Missing Schedule A")
        }
        
        // For schedule B, the repeats are manually added up to the max limit of 60.
        // Since Schedule A takes one slot, this can take the other 59.
        let bRequests = requests
            .filter { $0.content.threadIdentifier == "scheduleB" }
        XCTAssertEqual(bRequests.count, requests.count - 1)
        let triggerDates: [Date] = bRequests.compactMap { ($0.trigger as? UNCalendarNotificationTrigger)?.nextTriggerDate() }
        XCTAssertEqual(triggerDates, triggerDates.sorted())
        XCTAssertEqual(triggerDates.count, bRequests.count)
        triggerDates.enumerated().forEach { (index, date) in
            let expected = calendar.date(from: calendar.dateComponents(dateTime, from: scheduleOnB.addingDays(index * 7)))
            XCTAssertEqual(expected, date)
        }
    }
}


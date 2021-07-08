//
//  LocalNotificationManager.swift
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
import UserNotifications
import BridgeClient

fileprivate let kAllowSnoozeKey = "allowSnooze"
fileprivate let maxTotalNotifications = 60

open class LocalNotificationManager : NSObject, UNUserNotificationCenterDelegate {
    
    open private(set) var scheduledNotificationCategory = "org.sagebionetworks.ScheduledSession"
    
    open var notifications: [NativeScheduledNotification] = []
    open var maxScheduledSessionNotifications: Int = .max
    
    open func setupNotifications(_ notifications: [NativeScheduledNotification]) {
        self.notifications = notifications
        UIApplication.shared.applicationIconBadgeNumber = 0
        UNUserNotificationCenter.current().getNotificationSettings { settings in
            // Do nothing if the app did not ask or the participant did not provide
            // permission to send notifications.
            guard settings.authorizationStatus == .authorized else { return }
            UNUserNotificationCenter.current().getPendingNotificationRequests { oldRequests in
                // Use dispatch async to put this work on the next run loop and ensure that
                // we are creating this on the main thread. Has to be the main thread b/c
                // kotlin objects are not thread-safe.
                DispatchQueue.main.async {
                    // Just refresh everything by removing all pending requests.
                    let requestIds: [String] = oldRequests.compactMap {
                        $0.content.categoryIdentifier == self.scheduledNotificationCategory ? $0.identifier : nil
                    }
                    UNUserNotificationCenter.current().removePendingNotificationRequests(withIdentifiers: requestIds)
                    // and then re-adding or adding new.
                    self.createRequests().forEach {
                        UNUserNotificationCenter.current().add($0)
                    }
                }
            }
        }
    }
    
    private var maxRequests: Int {
        min(maxTotalNotifications, maxScheduledSessionNotifications)
    }
    
    private var maxTotalScheduledSessionRequests: Int {
        min(maxRequests, notifications.count)
    }
    
    open func createRequests() -> [UNNotificationRequest] {
        notifications[..<maxTotalScheduledSessionRequests]
            .map { buildRequests(for: $0) }
            .flatMap { $0 }
            .sorted()
    }
    
    open func buildContent(for notification: NativeScheduledNotification) -> UNNotificationContent {
        // Set up the notification
        let content = UNMutableNotificationContent()
        content.sound = UNNotificationSound.default
        content.badge = UIApplication.shared.applicationIconBadgeNumber + 1 as NSNumber;
        content.categoryIdentifier = scheduledNotificationCategory
        content.threadIdentifier = notification.instanceGuid
        if let message = notification.message {
            content.title = message.subject
            content.body = message.message
        }
        content.userInfo = [kAllowSnoozeKey : notification.allowSnooze]
        return content
    }
    
    private func buildRequests(for notification: NativeScheduledNotification) -> [ScheduledSessionNotificationRequest] {
        let content = buildContent(for: notification)
        let calendar = Calendar.current
        
        // If it doesn't repeat then we are done.
        guard let repeatInterval = notification.repeatInterval,
              let repeatUntil = notification.repeatUntil,
              let startInstant = calendar.date(from: notification.scheduleOn),
              let endInstant = calendar.date(from: repeatUntil)
        else {
            return [ScheduledSessionNotificationRequest(content: content,
                                                        scheduleOn: notification.scheduleOn,
                                                        instanceGuid: notification.instanceGuid,
                                                        repeats: false)]
        }
        
        // If it repeats daily and will continue for more that the total number of allowed
        // requests, then schedule it to repeat.
        let maxCount = maxRequests / (notifications.count > 0 ? notifications.count : 1)
        let numDays = calendar.dateComponents([.day], from: notification.scheduleOn, to: repeatUntil).day ?? 0
        if repeatInterval.day == 1, numDays > maxCount {
            var scheduleOn = DateComponents()
            scheduleOn.hour = notification.scheduleOn.hour
            scheduleOn.minute = notification.scheduleOn.minute
            return [ScheduledSessionNotificationRequest(content: content,
                                                        scheduleOn: scheduleOn,
                                                        instanceGuid: notification.instanceGuid,
                                                        repeats: true)]
        }
        
        // Otherwise, we need to advance the date by the repeat interval until we hit the max
        // allowed number of requests for this scheduled session instance.
        var requests = [ScheduledSessionNotificationRequest]()
        var scheduleInstant = startInstant
        repeat {
            let scheduleOn = calendar.dateComponents([.year, .month, .day, .hour, .minute], from: scheduleInstant)
            requests.append(ScheduledSessionNotificationRequest(content: content,
                                                                scheduleOn: scheduleOn,
                                                                instanceGuid: notification.instanceGuid,
                                                                repeats: false))
            scheduleInstant = calendar.date(byAdding: repeatInterval, to: scheduleInstant) ?? .distantFuture
        } while scheduleInstant < endInstant && requests.count < maxCount
        
        return requests
    }
    
    private func removeAllPendingNotifications(_ completionHandler: @escaping (() -> Void)) {
        UNUserNotificationCenter.current().getPendingNotificationRequests { (requests) in
            let requestIds: [String] = requests.compactMap {
                guard $0.content.categoryIdentifier == self.scheduledNotificationCategory else { return nil }
                return $0.identifier
            }
            UNUserNotificationCenter.current().removePendingNotificationRequests(withIdentifiers: requestIds)
            completionHandler()
        }
    }
    
    private class ScheduledSessionNotificationRequest : UNNotificationRequest, Comparable {

        var scheduleInstant: Date!
        var instanceGuid: String!
        
        convenience init(content: UNNotificationContent,
             scheduleOn: DateComponents,
             instanceGuid: String,
             repeats: Bool) {
            var triggerOn = repeats ? DateComponents() : scheduleOn
            triggerOn.hour = scheduleOn.hour
            triggerOn.minute = scheduleOn.minute
            let trigger = UNCalendarNotificationTrigger(dateMatching: triggerOn, repeats: repeats)
            self.init(identifier: "\(instanceGuid)|\(scheduleOn)",
                      content: content,
                      trigger: trigger)
            self.instanceGuid = instanceGuid
            self.scheduleInstant = Calendar.current.date(from: scheduleOn) ?? .distantFuture
        }
        
        static func < (lhs: LocalNotificationManager.ScheduledSessionNotificationRequest, rhs: LocalNotificationManager.ScheduledSessionNotificationRequest) -> Bool {
            lhs.scheduleInstant < rhs.scheduleInstant
        }
    }
}

    
//    func createLocalNotification(_ medication: SBAMedicationAnswer, _ timeOfDay: String, _ inDateComponents: DateComponents, _ reminderTimeInterval: Int) -> UNNotificationRequest {
//        guard Thread.current.isMainThread else {
//            var request: UNNotificationRequest!
//            DispatchQueue.main.sync {
//                request = self.createLocalNotification(medication, timeOfDay, inDateComponents, reminderTimeInterval)
//            }
//            return request
//        }
//
//        // Set up the notification
//        let content = UNMutableNotificationContent()
//        let medTitle = medication.shortText ?? medication.title ?? medication.identifier
//        let reminder = Reminder(itemIdentifier: medication.identifier, timingIdentifier: timeOfDay)
//        // TODO: syoung 08/10/2018 Figure out what the wording of the notification should be and localize.
//        if let date = reminder.timeOfDay(on: now()) {
//            let timeString = DateFormatter.localizedString(from: date, dateStyle: .none, timeStyle: .short)
//            content.body = "Take your \(medTitle) at \(timeString)"
//        }
//        content.sound = UNNotificationSound.default
//        content.badge = UIApplication.shared.applicationIconBadgeNumber + 1 as NSNumber;
//        content.categoryIdentifier = SBAMedicationNotificationCategory
//        content.threadIdentifier = timeOfDay
//
//        do {
//            content.userInfo = try reminder.rsd_jsonEncodedDictionary()
//        } catch let error {
//            assertionFailure("Failed to encode the reminder. \(error)")
//        }
//
//        // Set the reminder
//        var dateComponents = inDateComponents
//        var minute = (dateComponents.minute ?? 0) - reminderTimeInterval
//        var hour = dateComponents.hour ?? 0
//        if minute < 0 {
//            hour -= 1
//            minute += 60
//        }
//        if hour < 0 {
//            hour += 24
//        }
//        dateComponents.hour = hour
//        dateComponents.minute = minute
//        let trigger = UNCalendarNotificationTrigger(dateMatching: dateComponents, repeats: true)
//
//        // Create the request.
//        let identifier = self.getLocalNotificationIdentifier(medication, timeOfDay, dateComponents, reminderTimeInterval)
//        return UNNotificationRequest(identifier: identifier, content: content, trigger: trigger)
//    }
//

//
//    func addNotifications(for medicationResult: SBAMedicationTrackingResult) {
//        UNUserNotificationCenter.current().getPendingNotificationRequests { (pendingRequests) in
//            let filteredRequests = pendingRequests.filter { $0.content.categoryIdentifier == SBAMedicationNotificationCategory }
//            let notifications = self.getLocalNotifications(for: medicationResult, with: filteredRequests)
//            debugPrint("Update notifications: \(notifications)")
//            if notifications.removeIds.count > 0 {
//                UNUserNotificationCenter.current().removePendingNotificationRequests(withIdentifiers: notifications.removeIds)
//            }
//            notifications.add.forEach {
//                UNUserNotificationCenter.current().add($0)
//            }
//        }
//    }



//// MARK: Study burst notification handling
//
//struct NotificationResult : Codable {
//    public enum CodingKeys: String, CodingKey {
//        case reminderTime, noReminder
//    }
//
//    let reminderTime: Date?
//    let noReminder: Bool?
//}
//
//let notificationCategory = "StudyBurst"
//
//func updateNotifications() {
//    guard let reminderTime = self.getReminderTime()
//        else {
//            removeAllPendingNotifications()
//            return
//    }
//
//    // use dispatch async to allow the method to return and put updating reminders on the next run loop
//    UNUserNotificationCenter.current().getNotificationSettings { (settings) in
//        DispatchQueue.main.async {
//            switch settings.authorizationStatus {
//            case .denied:
//                break   // Do nothing. We don't want to pester the user with message.
//            case .notDetermined:
//                // The user has not given authorization, but the app has a record of previously requested
//                // authorization. This means that the app has been re-installed. Unfortunately, there isn't
//                // a great UI/UX for this senario, so just show the authorization request. syoung 07/19/2018
//                UNUserNotificationCenter.current().requestAuthorization(options: [.badge, .alert, .sound]) { (granted, _) in
//                    if granted {
//                        self.updateNotifications(at: reminderTime)
//                    }
//                }
//            default:
//                self.updateNotifications(at: reminderTime)
//            }
//        }
//    }
//}
//
//func getNotificationResult() -> NotificationResult? {
//    guard let report = self.report(with: RSDIdentifier.studyBurstReminder.stringValue)
//        else {
//            return nil
//    }
//    let clientData = report.clientData
//
//    do {
//        if clientData is NSDictionary {
//            return try SBAFactory.shared.createJSONDecoder().decode(NotificationResult.self, from: clientData)
//        }
//        else if let dateString = clientData as? String,
//            let date = SBAFactory.shared.decodeDate(from: dateString) {
//            return NotificationResult(reminderTime: date, noReminder: nil)
//        }
//        else {
//            return NotificationResult(reminderTime: nil, noReminder: nil)
//        }
//    } catch let err {
//        assertionFailure("Failed to decode the reminder result. \(err)")
//        return nil
//    }
//}
//
//func getReminderTime() -> DateComponents? {
//    guard let notificationResult = getNotificationResult(),
//        !(notificationResult.noReminder ?? false),
//        let reminderTime = notificationResult.reminderTime
//        else {
//            return nil
//    }
//    return Calendar(identifier: .iso8601).dateComponents([.hour, .minute], from: reminderTime)
//}
//
//func getLocalNotifications(after reminderTime: DateComponents, with pendingRequests: [UNNotificationRequest]) -> (add: [UNNotificationRequest], removeIds: [String]) {
//
//    let studyBurstMarkerId = self.studyBurst.identifier
//
//    // Get future schedules.
//    let date = self.today()
//    let startOfToday = date.startOfDay()
//    let timeToday = startOfToday.addingDateComponents(reminderTime)
//    let scheduleStart = (date < timeToday) ? startOfToday : startOfToday.addingNumberOfDays(1)
//
//    // Get the schedules for which to set the reminder
//    var futureSchedules = self.scheduledActivities.filter {
//        $0.activityIdentifier == studyBurstMarkerId &&
//        $0.scheduledOn >= scheduleStart &&
//        !$0.isCompleted
//    }.sorted(by: { $0.scheduledOn < $1.scheduledOn })
//
//    // Check if should be scheduling extra days.
//    let extraDays = self.maxDaysCount - self.studyBurst.numberOfDays
//    let completedCount = self.pastDaysCount - self.missedDaysCount
//    if completedCount >= self.studyBurst.minimumRequiredDays {
//        let toCount = futureSchedules.count - extraDays
//        futureSchedules = Array(futureSchedules[..<toCount])
//    }
//
//    // If getting near the end, then add next cycle.
//    if futureSchedules.count <= self.studyBurst.numberOfDays {
//        let taskPredicate = SBBScheduledActivity.activityIdentifierPredicate(with: self.studyBurst.identifier)
//        let start = startOfToday.addingNumberOfDays(self.maxDaysCount)
//        let end = start.addingNumberOfYears(1)
//        let studyMarkerPredicate = NSCompoundPredicate(andPredicateWithSubpredicates: [
//            SBBScheduledActivity.availablePredicate(from: start, to: end),
//            taskPredicate])
//        do {
//            let nextSchedules = try self.activityManager.getCachedSchedules(using: studyMarkerPredicate,
//                                                                        sortDescriptors: [SBBScheduledActivity.scheduledOnSortDescriptor(ascending: true)],
//                                                                        fetchLimit: UInt(self.studyBurst.numberOfDays))
//            futureSchedules.append(contentsOf: nextSchedules)
//        }
//        catch let err {
//            assertionFailure("Failed to get cached schedules. \(err)")
//        }
//    }
//
//    var pendingRequestIds = pendingRequests.map { $0.identifier }
//    let requests: [UNNotificationRequest] = futureSchedules.compactMap {
//        let identifier = getLocalNotificationIdentifier(for: $0, at: reminderTime)
//        if pendingRequestIds.remove(where: { $0 == identifier }).count > 0 {
//            // If there is an unchanged pending request, then remove it from this list
//            // and do not create a new reminder for it.
//            return nil
//        }
//        else {
//            return createLocalNotification(for: $0, at: reminderTime)
//        }
//    }
//
//    return (requests, pendingRequestIds)
//}
//
//func willPresentNotification(_ notification: UNNotification) {
//    let nextDate = notification.date.addingNumberOfDays(90)
//    guard nextDate < SBAParticipantManager.shared.startStudy.addingNumberOfYears(2)
//        else { return }
//    let dateComponents = Calendar.iso8601.dateComponents([.year, .month, .day, .hour, .minute],
//                                                         from: nextDate)
//    let trigger = UNCalendarNotificationTrigger(dateMatching: dateComponents, repeats: false)
//    let nextRequest = UNNotificationRequest(identifier: notification.request.identifier,
//                                            content: notification.request.content,
//                                            trigger: trigger)
//    UNUserNotificationCenter.current().add(nextRequest)
//}
//
//func getLocalNotificationIdentifier(for schedule: SBBScheduledActivity, at time: DateComponents) -> String {
//    let timeIdentifier = time.jsonObject()
//    return "\(schedule.guid) \(timeIdentifier)"
//}
//
//func createLocalNotification(for schedule: SBBScheduledActivity, at time: DateComponents) -> UNNotificationRequest {
//    guard Thread.current.isMainThread else {
//        var request: UNNotificationRequest!
//        DispatchQueue.main.sync {
//            request = self.createLocalNotification(for: schedule, at: time)
//        }
//        return request
//    }
//
//    // Set up the notification
//    let content = UNMutableNotificationContent()
//    // TODO: syoung 07/19/2018 Figure out what the wording of the notification should be.
//    content.body = NSLocalizedString("Time to do your mPower Study Burst activities!", comment: "Notification message")
//    content.sound = UNNotificationSound.default
//    content.badge = UIApplication.shared.applicationIconBadgeNumber + 1 as NSNumber;
//    content.categoryIdentifier = self.notificationCategory
//    content.threadIdentifier = schedule.activity.guid
//
//    // Set up the trigger. Cannot schedule using a repeating notification b/c it doesn't repeat
//    // every day but only every three months.
//    let date = schedule.scheduledOn.startOfDay()
//    var dateComponents = Calendar(identifier: .iso8601).dateComponents([.day, .month, .year], from: date)
//    dateComponents.hour = time.hour
//    dateComponents.minute = time.minute
//    let trigger = UNCalendarNotificationTrigger(dateMatching: dateComponents, repeats: false)
//
//    // Create the request.
//    let identifier = getLocalNotificationIdentifier(for: schedule, at: time)
//    return UNNotificationRequest(identifier: identifier, content: content, trigger: trigger)
//}
//
//func removeAllPendingNotifications() {
//    UNUserNotificationCenter.current().getPendingNotificationRequests { (requests) in
//        let requestIds: [String] = requests.compactMap {
//            guard $0.content.categoryIdentifier == self.notificationCategory else { return nil }
//            return $0.identifier
//        }
//        UNUserNotificationCenter.current().removePendingNotificationRequests(withIdentifiers: requestIds)
//    }
//}
//
//func updateNotifications(at reminderTime: DateComponents) {
//    UNUserNotificationCenter.current().getPendingNotificationRequests { (pendingRequests) in
//        let filteredRequests = pendingRequests.filter { $0.content.categoryIdentifier == self.notificationCategory }
//        let notifications = self.getLocalNotifications(after: reminderTime, with: filteredRequests)
//        if notifications.removeIds.count > 0 {
//            UNUserNotificationCenter.current().removePendingNotificationRequests(withIdentifiers: notifications.removeIds)
//        }
//        notifications.add.forEach {
//            UNUserNotificationCenter.current().add($0)
//        }
//    }
//}

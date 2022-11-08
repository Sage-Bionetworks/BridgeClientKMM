//
//  LocalNotificationManager.swift
//

import SwiftUI
import UserNotifications
import BridgeClient

fileprivate let kAllowSnoozeKey = "allowSnooze"
fileprivate let maxTotalNotifications = 60

/// A manager that is used to set up and respond to local notifications. The base class will set up notifications
/// calculated for the current partipant's timeline. This class must be overridden to add additional custom
/// notifications to the application because there can be only one ``UNUserNotificationCenterDelegate``.
/// In order for this manager to implement features such as "snooze", it must be set during launch as the
/// notification center delegate.
open class LocalNotificationManager : NSObject, UNUserNotificationCenterDelegate {
    
    /// The category identifier used to filter out the notifications that are associated with schedules.
    open private(set) var scheduledNotificationCategory = "org.sagebionetworks.ScheduledSession"
    
    /// The max number of notifications that can be associated with scheduled sessions. This value can be
    /// overridden to allow allocating notifications for a purpose other than schedule adherence.
    open var maxScheduledSessionNotifications: Int = .max
    
    // Do not expose publicly. This class is not threadsafe.
    var notifications: [NativeScheduledNotification] = []
    private var updatingNotifications = false
    
    func setupNotifications(_ notifications: [NativeScheduledNotification]) {
        // Reset the icon badge.
        UIApplication.shared.applicationIconBadgeNumber = 0
        
        // Exit early if nothing has changed.
        guard self.notifications != notifications else { return }
        self.notifications = notifications
        
        UNUserNotificationCenter.current().getPendingNotificationRequests { oldRequests in
            DispatchQueue.main.async {
                // Remove all the old requests
                let requestIds: [String] = oldRequests.compactMap {
                    $0.content.categoryIdentifier == self.scheduledNotificationCategory ? $0.identifier : nil
                }
                UNUserNotificationCenter.current().removePendingNotificationRequests(withIdentifiers: requestIds)
        
                // Do nothing if the app did not ask or the participant did not provide
                // permission to send notifications.
                UNUserNotificationCenter.current().getNotificationSettings { settings in
                    guard settings.authorizationStatus == .authorized else { return }

                    // Use dispatch async to put this work on the next run loop and ensure that
                    // we are creating this on the main thread. Has to be the main thread b/c
                    // kotlin objects are not thread-safe.
                    DispatchQueue.main.async {
                        // and then re-adding or adding new.
                        let requests = self.createRequests()
                        requests[..<min(self.maxRequests, requests.count)].forEach {
                            UNUserNotificationCenter.current().add($0)
                        }
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
    
    func createRequests() -> [UNNotificationRequest] {
        createBuilders().map { $0.buildNotificationRequest()}
    }
    
    func createBuilders() -> [RequestBuilder] {
        let builders = notifications[..<maxTotalScheduledSessionRequests]
            .map { buildRequests(for: $0) }
            .flatMap { $0 }
            .sorted()
        return Array(builders[..<min(maxRequests, builders.count)])
    }
    
    func buildContent(for notification: NativeScheduledNotification) -> UNNotificationContent {
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
        if #available(iOS 15.0, *) {
            content.interruptionLevel = notification.isTimeSensitive ? .timeSensitive : .active
        }
        content.userInfo = [kAllowSnoozeKey : notification.allowSnooze]
        return content
    }
    
    func buildRequests(for notification: NativeScheduledNotification) -> [RequestBuilder] {
        let content = buildContent(for: notification)
        let calendar = Calendar.current
        
        // If it doesn't repeat then we are done.
        guard let repeatInterval = notification.repeatInterval,
              let repeatUntil = notification.repeatUntil,
              let startInstant = calendar.date(from: notification.scheduleOn),
              let endInstant = calendar.date(from: repeatUntil)
        else {
            return [RequestBuilder(content: content,
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
            return [RequestBuilder(content: content,
                                   scheduleOn: scheduleOn,
                                   instanceGuid: notification.instanceGuid,
                                   repeats: true)]
        }
        
        // Otherwise, we need to advance the date by the repeat interval until we hit the max
        // allowed number of requests for this scheduled session instance.
        var requests = [RequestBuilder]()
        var scheduleInstant = startInstant
        repeat {
            let scheduleOn = calendar.dateComponents([.year, .month, .day, .hour, .minute], from: scheduleInstant)
            requests.append(RequestBuilder(content: content,
                                           scheduleOn: scheduleOn,
                                           instanceGuid: notification.instanceGuid,
                                           repeats: false))
            scheduleInstant = calendar.date(byAdding: repeatInterval, to: scheduleInstant) ?? .distantFuture
        } while scheduleInstant < endInstant && requests.count < maxRequests
        
        return requests
    }
    
    public func clearAll() {
        removeAllPendingNotifications() {
        }
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
    
    class RequestBuilder : Comparable {

        let content: UNNotificationContent
        let trigger: UNCalendarNotificationTrigger
        let scheduleInstant: Date
        let instanceGuid: String
        
        init(content: UNNotificationContent,
             scheduleOn: DateComponents,
             instanceGuid: String,
             repeats: Bool) {
            var triggerOn = repeats ? DateComponents() : scheduleOn
            triggerOn.hour = scheduleOn.hour
            triggerOn.minute = scheduleOn.minute
            self.trigger = UNCalendarNotificationTrigger(dateMatching: triggerOn, repeats: repeats)
            self.instanceGuid = instanceGuid
            self.scheduleInstant = Calendar.current.date(from: scheduleOn) ?? .distantFuture
            self.content = content
        }
        
        func buildNotificationRequest() -> UNNotificationRequest {
            UNNotificationRequest(identifier: "\(self.instanceGuid)|\(self.scheduleInstant)", content: content, trigger: trigger)
        }
        
        static func < (lhs: LocalNotificationManager.RequestBuilder, rhs: LocalNotificationManager.RequestBuilder) -> Bool {
            lhs.scheduleInstant < rhs.scheduleInstant
        }
        
        static func == (lhs: LocalNotificationManager.RequestBuilder, rhs: LocalNotificationManager.RequestBuilder) -> Bool {
            lhs.scheduleInstant == rhs.scheduleInstant && lhs.instanceGuid == rhs.instanceGuid
        }
    }
}


// Created 8/28/23
// swift-tools-version:5.0

import Foundation
import BackgroundTasks

/// The delegate is responsible for the actual work that needs to be processed.
protocol BackgroundProcessSyncDelegate : AnyObject {
    
    /// Should a background process be scheduled?
    var shouldScheduleBackgroundProcess: Bool { get }
    
    /// The method to call to process work. The method should be able to handle having the task
    /// cancelled (because of timing out) and exit gracefully.
    ///
    /// - Parameter isBackground: Is the process being called while the app is already in the background?
    func retryBackgroundProcess(isBackground: Bool) async throws
}

#if canImport(UIKit)
import UIKit

/// The `BackgroundProcessSyncManager` is set up to allow syncing a background processing
/// task scheduled with `BGTaskScheduler` while **also** allowing the process to run while
/// the app is active with a timing that is more "chatty".
///
/// - Note: syoung 08/28/2023 The background process sync manager was set up this way
/// to allow testing using this manager in a simplified app. The use of `BGTaskScheduler`
/// is a bit brittle - as of this writing, a background process that runs when the app is
/// backgrounded will stall on tasks that are running on the `MainActor` so only
/// ``onLaunch(backgroundProcessId:)`` is ever called from that thread.
///
actor BackgroundProcessSyncManager {
    
    weak private var delegate: BackgroundProcessSyncDelegate!
    
    init(delegate: BackgroundProcessSyncDelegate) {
        self.delegate = delegate
    }
    
    /// Toggle flag used to check whether or not the app is running in the background.
    var isAppBackground: Bool = false
    
    /// **Required:** This method should be called on app launch to register the background
    /// process id and set up the listeners for app becoming active and entering the
    /// background.
    @MainActor
    func onLaunch(backgroundProcessId: String?) {
        // Register the background process
        if let backgroundProcessId = backgroundProcessId {
            registerBackgroundTasks(backgroundProcessId)
        }
        setupAppListeners()
    }
    
    /// Retry the background process immediately. Calls to this method are ignored if the app
    /// is in the background or the retry is already running.
    func retryBackgroundProcessAsync() {
        guard !isAppBackground else {
            Logger.log(severity: .info, tag: .upload, message: "Attempting to check and retry uploads from the background")
            return
        }
        guard checkRetryTask?.isCancelled ?? true else {
            Logger.log(severity: .info, tag: .upload, message: "Check and retry already running. Ignoring.")
            return
        }
        
        checkRetryTask = Task(priority: .background) {

            // retry all pending uploads
            let task = taskToRetryAllPendingUploads(isBackground: false)
            let _ = await task.result

            // check if we still have pending uploads and schedule a retry
            if !isAppBackground,
               (delegate?.shouldScheduleBackgroundProcess ?? false) {
                enqueueForRetry()
            }

            // nil out the check retry task so it can be restarted
            checkRetryTask = nil
        }
    }
    
    /// Queue up a delay timer for retrying the background process. This will only trigger
    /// if the app is active and there isn't already a retry queued up.
    func enqueueForRetry() {
        guard !isAppBackground else {
            Logger.log(severity: .info, tag: .upload, message: "Attempting to enqueue file for retry in the background. Ignoring.")
            return
        }
        guard waitRetryTask?.isCancelled ?? true else { return }
        waitRetryTask = Task(priority: .background) {
            do {
                try await Task.sleep(nanoseconds: UInt64(delayForRetry * 1_000_000_000))
                retryBackgroundProcessAsync()
            } catch is CancellationError {
                Logger.log(severity: .info, tag: .upload, message: "Wait for check and retry uploads cancelled")
            } catch {
                Logger.log(tag: .upload, error: error, message: "Unexpected failure waiting to retry upload")
            }
            waitRetryTask = nil
        }
    }
    
    // MARK: Private methods and ivars
    
    /// The minimum delay before retrying a failed upload (in seconds). This is a
    /// variable so that unit tests can run without waiting.
    var delayForRetry: TimeInterval = 5 * 60
    
    private var waitRetryTask: Task<Void, Never>?
    private var checkRetryTask: Task<Void, Never>?
    private var retryTask: Task<Void, Never>?
    private var backgroundProcessId: String?
    
    private func taskToRetryAllPendingUploads(isBackground: Bool) -> Task<Void, Never> {
        if retryTask == nil {
            retryTask = Task(priority: .background) {
                
                // if launched from the foreground, then ask for time to finish in the background
                if !isBackground {
                    await beginTimedBackgroundTask()
                }
                
                // run the background process - catching all errors
                do {
                    Logger.log(severity: .info, tag: .upload, message: "Retrying background process. isBackground=\(isBackground)")
                    try await delegate?.retryBackgroundProcess(isBackground: isBackground)
                } catch is CancellationError {
                    Logger.log(severity: .info, tag: .upload, message: "Check and retry uploads cancelled")
                } catch {
                    // TODO: syoung 08/29/2023 Check if the error is b/c of spotty network connectivity
                    Logger.log(tag: .upload, error: error, message: "Failure when checking and retrying uploads")
                }
                
                // finally, let the app know that we are done with our background process
                // (either because it finished or because it timed out)
                if !isBackground {
                    await endTimedBackgroundTask()
                }
                
                // nil out the finished task so it can be restarted
                retryTask = nil
            }
        }
        return retryTask!
    }
    
    private func setBackgroundProcessId(_ backgroundProcessId: String) {
        self.backgroundProcessId = backgroundProcessId
    }
    
    private func didBecomeActive() {
        Logger.log(severity: .info, tag: .upload, message: "App did become active. Check and retry uploads.")
        // when becoming active, we want to retry running the process to clear the queue
        isAppBackground = false
        retryBackgroundProcessAsync()
    }
    
    private func didEnterBackground() {
        Logger.log(severity: .info, tag: .upload, message: "App did enter background. Scheduling background processing if needed.")
        // when entering the background, we want to cancel waiting to retry uploads
        // and then schedule a background process.
        isAppBackground = true
        waitRetryTask?.cancel()
        scheduleBackgroundProcessingIfNeeded()
    }
    
    private func scheduleBackgroundProcessingIfNeeded() {
        // Check that there is a registered background process id, that the
        // app is still in the background, and that the delegate has work
        // to do.
        guard let taskId = self.backgroundProcessId,
              isAppBackground,
              delegate?.shouldScheduleBackgroundProcess ?? false
        else {
            return
        }
        Logger.log(severity: .info, tag: .upload, message: "Pending uploads detected. Scheduling background process: \(taskId)")
        
        let request = BGProcessingTaskRequest(identifier: taskId)
        request.requiresNetworkConnectivity = true                     // Do not attempt processing without network connectivity
        request.earliestBeginDate = Date(timeIntervalSinceNow: 15*60)  // Wait 15 minutes to allow S3 uploads in progress to complete
        
        do {
            try BGTaskScheduler.shared.submit(request)
        } catch {
            Logger.log(tag: .upload, error: error, message: "Error scheduling BG task: \(taskId)")
        }
    }
    
    // MARK: @MainActor methods used to handle set up and continuing a foreground process in the background
    
    @MainActor var timedBackgroundTaskId: UIBackgroundTaskIdentifier?
    
    @MainActor
    private func registerBackgroundTasks(_ backgroundProcessId: String) {
        Task {
            await setBackgroundProcessId(backgroundProcessId)
        }
        BGTaskScheduler.shared.register(forTaskWithIdentifier: backgroundProcessId, using: .main) { task in
            Task {
                let retry = await self.taskToRetryAllPendingUploads(isBackground: true)
                let _ = await retry.result
                task.setTaskCompleted(success: true)
                await self.scheduleBackgroundProcessingIfNeeded()
            }
        }
    }
    
    @MainActor
    private func setupAppListeners() {
        // Set up a listener to retry temporarily-failed uploads whenever the app becomes active
        NotificationCenter.default.addObserver(forName: UIApplication.didBecomeActiveNotification, object: nil, queue: nil) { [weak self] _ in
            guard let strongSelf = self else { return }
            Task {
                await strongSelf.didBecomeActive()
            }
        }
        // Set up a listener to handle entering background
        NotificationCenter.default.addObserver(forName: UIApplication.didEnterBackgroundNotification, object: nil, queue: nil) { [weak self] _ in
            guard let strongSelf = self else { return }
            Task {
                await strongSelf.didEnterBackground()
                let _ = true    // Use this as a breakpoint for simulating a background process
            }
        }
    }
    
    @MainActor
    private func beginTimedBackgroundTask() {
        guard timedBackgroundTaskId == nil else { return }
        timedBackgroundTaskId = UIApplication.shared.beginBackgroundTask {
            Logger.log(severity: .info, tag: .upload, message: "Timed out when checking and retrying uploads.")
            self.endTimedBackgroundTask()
            Task {
                await self.retryTask?.cancel()
            }
        }
    }
    
    @MainActor
    private func endTimedBackgroundTask() {
        guard let taskId = timedBackgroundTaskId else { return }
        timedBackgroundTaskId = nil
        UIApplication.shared.endBackgroundTask(taskId)
    }
    
}

#else

/// This is included b/c a limitation of Swift PM is that you cannot explicitly specify
/// support for only certain platforms. syoung 08/29/2023
actor BackgroundProcessSyncManager {
    init(delegate: BackgroundProcessSyncDelegate) { }
    var isAppBackground: Bool = false
    @MainActor func onLaunch(backgroundProcessId: String?) { }
    func retryBackgroundProcessAsync() { }
    func enqueueForRetry() { }
}

#endif

/** Command for simulating launch of a background task:
 e -l objc -- (void)[[BGTaskScheduler sharedScheduler] _simulateLaunchForTaskWithIdentifier:@"org.sagebase.BackgroundProcessTest"]
 
 */

package org.sagebionetworks.bridge.kmm.shared.managers

import kotlinx.coroutines.MainScope
import kotlinx.coroutines.cancel
import kotlinx.coroutines.launch
import kotlinx.datetime.Clock
import org.koin.core.component.KoinComponent
import org.koin.core.component.inject
import org.sagebionetworks.bridge.kmm.shared.repo.ScheduleTimelineRepo

class NativeScheduledNotificationManager : KoinComponent {

    internal val repo : ScheduleTimelineRepo by inject(mode = LazyThreadSafetyMode.NONE)

    internal val scope = MainScope()

    fun observeNotifications(studyId: String, callBack: (List<NativeScheduledNotification>) -> Unit) {
        scope.launch {
            repo.getCachedPendingNotificationsCollapsed(studyId, Clock.System.now()).collect { notificationList ->
                callBack(notificationList.map { it.toNative() })
            }
        }
    }

    @Throws(Throwable::class)
    fun onCleared() {
        try {
            scope.cancel()
        } catch (err: Exception) {
            throw Throwable(err.message)
        }
    }
}
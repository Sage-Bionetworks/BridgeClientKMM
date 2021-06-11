package org.sagebionetworks.bridge.kmm.shared

import kotlinx.coroutines.MainScope
import kotlinx.coroutines.cancel
import kotlinx.coroutines.flow.collect
import kotlinx.coroutines.launch
import kotlinx.datetime.LocalDateTime
import org.koin.core.component.KoinComponent
import org.koin.core.component.inject
import org.sagebionetworks.bridge.kmm.shared.cache.*
import org.sagebionetworks.bridge.kmm.shared.models.AssessmentInfo
import org.sagebionetworks.bridge.kmm.shared.models.SessionInfo
import org.sagebionetworks.bridge.kmm.shared.repo.*
import platform.Foundation.NSDate
import platform.Foundation.NSDateComponents
import platform.Foundation.distantFuture
import platform.Foundation.distantPast

class NativeTimelineManager(
    val studyId: String,
    private val viewUpdate: (List<NativeScheduledSessionWindow>) -> Unit
) : KoinComponent {

    private val repo : ScheduleTimelineRepo by inject(mode = LazyThreadSafetyMode.NONE)

    private val scope = MainScope()

    fun observeTodaySchedule() {
        scope.launch {
            repo.getSessionsForToday(studyId).collect { timelineResource ->
                (timelineResource as? ResourceResult.Success)?.data?.let { list ->
                    viewUpdate( list.map { it.toNative() } )
                }
            }
        }
    }

    fun refreshTodaySchedule() {
        scope.cancel()
        observeTodaySchedule()
    }

    fun onCleared() {
        scope.cancel()
    }
}

fun LocalDateTime.toNative() : NSDate? {
    val components = NSDateComponents()
    components.year = this.year.toLong()
    components.month = this.month.ordinal.toLong()
    components.day = this.dayOfMonth.toLong()
    components.hour = this.hour.toLong()
    components.minute = this.minute.toLong()
    return components.date
}

fun ScheduledSessionWindow.toNative() : NativeScheduledSessionWindow =
    NativeScheduledSessionWindow(
        instanceGuid,
        startDateTime.toNative() ?: NSDate.distantPast(),
        endDateTime.toNative() ?: NSDate.distantFuture(),
        persistent,
        startTime != null,
        expiration?.let { it.hours > 0 || it.minutes > 0 } ?: false,
        assessments.map { it.toNative() },
        sessionInfo
    )

fun ScheduledAssessmentReference.toNative() : NativeScheduledAssessment =
    NativeScheduledAssessment(instanceGuid, assessmentInfo, isCompleted)

data class NativeScheduledSessionWindow(
    val instanceGuid: String,
    val startDateTime: NSDate,
    val endDateTime: NSDate,
    val persistent: Boolean,
    val hasStartTimeOfDay: Boolean,
    val hasEndTimeOfDay: Boolean,
    val assessments: List<NativeScheduledAssessment>,
    val sessionInfo: SessionInfo
) {
    fun copyWithAssessments(assessments: List<NativeScheduledAssessment>): NativeScheduledSessionWindow {
        return this.copy(assessments = assessments)
    }
}

data class NativeScheduledAssessment(
    val instanceGuid: String,
    val assessmentInfo: AssessmentInfo,
    val isCompleted: Boolean,
)


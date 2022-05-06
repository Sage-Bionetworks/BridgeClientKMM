package org.sagebionetworks.bridge.kmm.shared

import kotlinx.coroutines.MainScope
import kotlinx.coroutines.cancel
import kotlinx.coroutines.flow.collect
import kotlinx.coroutines.launch
import kotlinx.datetime.*
import kotlinx.serialization.json.JsonElement
import org.koin.core.component.KoinComponent
import org.koin.core.component.inject
import org.sagebionetworks.bridge.kmm.shared.cache.*
import org.sagebionetworks.bridge.kmm.shared.models.AdherenceRecord
import org.sagebionetworks.bridge.kmm.shared.models.AssessmentInfo
import org.sagebionetworks.bridge.kmm.shared.models.NotificationMessage
import org.sagebionetworks.bridge.kmm.shared.models.SessionInfo
import org.sagebionetworks.bridge.kmm.shared.repo.*
import platform.Foundation.*

class NativeTimelineManager(
    private val studyId: String,
    private val includeAllNotifications: Boolean,
    private val alwaysIncludeNextDay: Boolean,
    private val viewUpdate: (NativeScheduledSessionTimelineSlice) -> Unit
) : KoinComponent {

    private val repo : ScheduleTimelineRepo by inject(mode = LazyThreadSafetyMode.NONE)
    private val adherenceRecordRepo : AdherenceRecordRepo by inject(mode = LazyThreadSafetyMode.NONE)

    private val scope = MainScope()

    fun observeTodaySchedule(isNewLogin: Boolean) {
        scope.launch {
            if (isNewLogin) {
                adherenceRecordRepo.loadRemoteAdherenceRecords(studyId)
            }
            repo.getSessionsForToday(studyId, includeAllNotifications, alwaysIncludeNextDay).collect { timelineResource ->
                (timelineResource as? ResourceResult.Success)?.data?.let { timelineSlice ->
                    viewUpdate(timelineSlice.toNaive())
                }
            }
        }
    }

    fun refreshTodaySchedule() {
        runCatching { scope.cancel() }
        observeTodaySchedule(false)
    }

    @Throws(Throwable::class)
    fun onCleared() {
        try {
            scope.cancel()
        } catch (err: Exception) {
            throw Throwable(err.message)
        }
    }

    fun updateAdherenceRecord(record: NativeAdherenceRecord) {
        val adherenceRecord = AdherenceRecord(
            instanceGuid = record.instanceGuid,
            eventTimestamp = record.eventTimestamp,
            startedOn = record.startedOn?.toKotlinInstant(),
            finishedOn = record.finishedOn?.toKotlinInstant(),
            clientTimeZone = NSCalendar.currentCalendar.timeZone.name,
            declined = record.declined,
            clientData = record.clientData,
        )
        adherenceRecordRepo.createUpdateAdherenceRecord(adherenceRecord, studyId)
    }
}

internal fun ScheduledSessionTimelineSlice.toNaive() =
    NativeScheduledSessionTimelineSlice(
        instantInDay = instantInDay.toNSDate(),
        timezone = timezone.toNSTimeZone(),
        scheduledSessionWindows = scheduledSessionWindows.map { it.toNative() },
        notifications = notifications.map { it.toNative() }
    )

internal fun ScheduledSessionWindow.toNative() =
    NativeScheduledSessionWindow(
        instanceGuid = instanceGuid,
        eventTimestamp = eventTimestamp.toString(),
        startDateTime = startDateTime.toInstant(TimeZone.currentSystemDefault()).toNSDate(),
        endDateTime = endDateTime.toInstant(TimeZone.currentSystemDefault()).toNSDate(),
        persistent = persistent,
        hasStartTimeOfDay = hasStartTimeOfDay,
        hasEndTimeOfDay = hasEndTimeOfDay,
        assessments = assessments.map { it.toNative() },
        sessionInfo = sessionInfo,
    )

internal fun ScheduledAssessmentReference.toNative()  =
    NativeScheduledAssessment(
        instanceGuid = instanceGuid,
        assessmentInfo = assessmentInfo,
        isCompleted = isCompleted,
        isDeclined = isDeclined,
        adherenceRecords = this.adherenceRecordList.map { it.toNative() },
    )

internal fun AdherenceRecord.toNative()  =
    NativeAdherenceRecord(
        instanceGuid = instanceGuid,
        eventTimestamp = eventTimestamp,
        timezoneIdentifier = clientTimeZone,
        startedOn = startedOn?.toNSDate(),
        finishedOn = finishedOn?.toNSDate(),
        declined = declined,
        clientData = clientData,
    )

internal fun ScheduledNotification.toNative()  =
    NativeScheduledNotification(
        instanceGuid = instanceGuid,
        scheduleOn = scheduleOn.toNSDateComponents(),
        repeatInterval = repeatInterval?.let { period ->
            val components = NSDateComponents()
            components.hour = period.hours.toLong()
            components.minute = period.minutes.toLong()
            components.day = period.days.toLong()
            components.month = period.months.toLong()
            components },
        repeatUntil = repeatUntil?.toNSDateComponents(),
        allowSnooze = allowSnooze,
        message = message,
        isTimeSensitive = isTimeSensitive,
    )

data class NativeScheduledSessionTimelineSlice (
    val instantInDay: NSDate,
    val timezone: NSTimeZone,
    val scheduledSessionWindows: List<NativeScheduledSessionWindow>,
    val notifications: List<NativeScheduledNotification>,
)

data class NativeScheduledSessionWindow(
    val instanceGuid: String,
    val eventTimestamp: String,
    val startDateTime: NSDate,
    val endDateTime: NSDate,
    val persistent: Boolean,
    val hasStartTimeOfDay: Boolean,
    val hasEndTimeOfDay: Boolean,
    val assessments: List<NativeScheduledAssessment>,
    val sessionInfo: SessionInfo,
)

data class NativeScheduledAssessment(
    val instanceGuid: String,
    val assessmentInfo: AssessmentInfo,
    val isCompleted: Boolean,
    val isDeclined: Boolean,
    val adherenceRecords: List<NativeAdherenceRecord>?,
)

data class NativeAdherenceRecord(
    val instanceGuid: String,
    val eventTimestamp: String,
    val timezoneIdentifier: String?,
    val startedOn: NSDate?,
    val finishedOn: NSDate?,
    val declined: Boolean,
    val clientData: JsonElement?,
)

data class NativeScheduledNotification(
    val instanceGuid: String,
    val scheduleOn: NSDateComponents,
    val repeatInterval: NSDateComponents?,
    val repeatUntil: NSDateComponents?,
    val allowSnooze: Boolean,
    val message: NotificationMessage?,
    val isTimeSensitive: Boolean,
)


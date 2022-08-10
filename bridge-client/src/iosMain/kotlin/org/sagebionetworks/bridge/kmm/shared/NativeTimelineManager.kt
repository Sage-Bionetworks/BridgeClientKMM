package org.sagebionetworks.bridge.kmm.shared

import kotlinx.coroutines.MainScope
import kotlinx.coroutines.cancel
import kotlinx.coroutines.flow.collectLatest
import kotlinx.coroutines.launch
import kotlinx.datetime.*
import kotlinx.serialization.json.JsonElement
import kotlinx.serialization.json.JsonObject
import org.koin.core.component.KoinComponent
import org.koin.core.component.inject
import org.sagebionetworks.bridge.kmm.shared.cache.*
import org.sagebionetworks.bridge.kmm.shared.models.*
import org.sagebionetworks.bridge.kmm.shared.repo.*
import platform.Foundation.*

class NativeTimelineManager(
    private val studyId: String,
    private val includeAllNotifications: Boolean,
    private val alwaysIncludeNextDay: Boolean,
    private val viewUpdate: (NativeScheduledSessionTimelineSlice) -> Unit
) : KoinComponent {

    val repo : ScheduleTimelineRepo by inject(mode = LazyThreadSafetyMode.NONE)
    val assessmentConfigRepo : AssessmentConfigRepo by inject(mode = LazyThreadSafetyMode.NONE)
    val localCache : LocalJsonDataCache by inject(mode = LazyThreadSafetyMode.NONE)
    val adherenceRecordRepo : AdherenceRecordRepo by inject(mode = LazyThreadSafetyMode.NONE)
    val activityEventsRepo : ActivityEventsRepo by inject(mode = LazyThreadSafetyMode.NONE)

    private val scope = MainScope()

    fun observeTodaySchedule(isNewLogin: Boolean) = observeTodaySchedule(isNewLogin, null)

    fun observeTodaySchedule(isNewLogin: Boolean, scheduleMutator: ParticipantScheduleMutator?) {
        scope.launch {
            if (isNewLogin) {
                adherenceRecordRepo.loadRemoteAdherenceRecords(studyId)
            }
            repo.scheduleMutator = scheduleMutator
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

    fun fetchAssessmentConfig(instanceGuid: String, assessmentInfo: AssessmentInfo, callBack: (NativeAssessmentConfig) -> Unit) {
        scope.launch {
            assessmentConfigRepo.getAssessmentConfig(assessmentInfo).collectLatest { resource ->
                val restoredResultData = localCache.loadData(instanceGuid, "AssessmentResult")
                val restoredJson = (restoredResultData?.json as? JsonObject)?.toString()?.toNSData()
                callBack(
                    NativeAssessmentConfig(
                        instanceGuid = instanceGuid,
                        identifier = assessmentInfo.identifier,
                        config = (resource as? ResourceResult.Success)?.data?.config.toString().toNSData(),
                        restoredResult = restoredJson
                    )
                )
            }
        }
    }

    fun saveAssessmentResult(instanceGuid: String, json: JsonElement, expiresOn: NSDate?) {
        localCache.storeData(
            id = instanceGuid,
            dataType = "AssessmentResult",
            data = json,
            expire = expiresOn?.toKotlinInstant()?.toLocalDateTime(TimeZone.currentSystemDefault())
        )
    }

    fun clearAssessmentResult(instanceGuid: String) {
        localCache.removeData(instanceGuid, "AssessmentResult")
    }

    fun createActivityEvent(studyId: String, eventId: String, timeStamp: Instant, callBack: (Boolean) -> Unit) {
        scope.launch {
            callBack(activityEventsRepo.createActivityEvent(studyId, eventId, timeStamp))
        }
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

data class NativeAssessmentConfig(
    val instanceGuid: String,
    val identifier: String,
    val config: NSData?,
    val restoredResult: NSData?
)
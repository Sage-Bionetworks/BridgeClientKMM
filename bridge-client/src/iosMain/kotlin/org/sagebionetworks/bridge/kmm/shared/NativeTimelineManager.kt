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
import org.sagebionetworks.bridge.kmm.shared.models.SessionInfo
import org.sagebionetworks.bridge.kmm.shared.repo.*
import platform.Foundation.*

class NativeTimelineManager(
    val studyId: String,
    private val viewUpdate: (List<NativeScheduledSessionWindow>) -> Unit
) : KoinComponent {

    private val repo : ScheduleTimelineRepo by inject(mode = LazyThreadSafetyMode.NONE)
    private val adherenceRecordRepo : AdherenceRecordRepo by inject(mode = LazyThreadSafetyMode.NONE)

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

internal fun ScheduledSessionWindow.toNative() : NativeScheduledSessionWindow =
    NativeScheduledSessionWindow(
        instanceGuid = instanceGuid,
        eventTimestamp = eventTimeStamp.toString(),
        startDateTime = startDateTime.toNSDateComponents().date ?: NSDate.distantPast(),
        endDateTime = endDateTime.toNSDateComponents().date ?: NSDate.distantFuture(),
        persistent = persistent,
        hasStartTimeOfDay = hasStartTimeOfDay,
        hasEndTimeOfDay = hasEndTimeOfDay,
        assessments = assessments.map { it.toNative() },
        sessionInfo = sessionInfo,
    )

internal fun ScheduledAssessmentReference.toNative() : NativeScheduledAssessment =
    NativeScheduledAssessment(
        instanceGuid = instanceGuid,
        assessmentInfo = assessmentInfo,
        isCompleted = isCompleted,
        isDeclined = isDeclined,
        adherenceRecords = this.adherenceRecordList?.map { it.toNative() },
    )

internal fun AdherenceRecord.toNative() : NativeAdherenceRecord =
    NativeAdherenceRecord(
        instanceGuid = instanceGuid,
        eventTimestamp = eventTimestamp,
        startedOn = startedOn?.toNSDate(),
        finishedOn = finishedOn?.toNSDate(),
        declined = declined,
        clientData = clientData,
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
    val sessionInfo: SessionInfo
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
    val startedOn: NSDate?,
    val finishedOn: NSDate?,
    val declined: Boolean?,
    val clientData: JsonElement?,
)


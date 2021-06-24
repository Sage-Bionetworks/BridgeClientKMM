package org.sagebionetworks.bridge.kmm.shared.repo

import co.touchlab.stately.ensureNeverFrozen
import io.ktor.client.*
import kotlinx.coroutines.CoroutineScope
import kotlinx.coroutines.flow.Flow
import kotlinx.coroutines.flow.combine
import kotlinx.datetime.*
import kotlinx.serialization.encodeToString
import kotlinx.serialization.json.Json
import org.sagebionetworks.bridge.kmm.shared.apis.SchedulesV2Api
import org.sagebionetworks.bridge.kmm.shared.cache.ResourceDatabaseHelper
import org.sagebionetworks.bridge.kmm.shared.cache.ResourceResult
import org.sagebionetworks.bridge.kmm.shared.cache.ResourceType
import org.sagebionetworks.bridge.kmm.shared.models.*
import kotlin.time.ExperimentalTime

class ScheduleTimelineRepo(internal val adherenceRecordRepo: AdherenceRecordRepo,
                           internal val activityEventsRepo: ActivityEventsRepo,
                           httpClient: HttpClient,
                           databaseHelper: ResourceDatabaseHelper,
                           backgroundScope: CoroutineScope) :
    AbstractResourceRepo(databaseHelper, resourceType = ResourceType.TIMELINE, backgroundScope) {

    companion object {
        const val SCHEDULE_TIMELINE_ID = "ScheduleTimelineId"
    }

    init {
        ensureNeverFrozen()
    }

    private var scheduleApi = SchedulesV2Api(
        httpClient = httpClient
    )

    private fun getTimeline(studyId: String): Flow<ResourceResult<Timeline>> {
        return getResourceById(
            SCHEDULE_TIMELINE_ID + studyId,
            remoteLoad = { loadRemoteTimeline(studyId) },
            studyId = studyId
        )
    }

    private suspend fun loadRemoteTimeline(studyId: String): String {
        return Json.encodeToString(scheduleApi.getTimelineForUser(studyId))
    }

    /**
     * Get all the scheduled sessions for today that have not expired.
     */
    fun getSessionsForToday(studyId: String): Flow<ResourceResult<List<ScheduledSessionWindow>>> {
        return getSessionsForDay(studyId, Clock.System.now())
    }

    /**
     * Used for testing so that we can specify a consistent point in time.
     */
    internal fun getSessionsForDay(
        studyId: String,
        instantInDay: Instant
    ): Flow<ResourceResult<List<ScheduledSessionWindow>>> {
        return combine(
            getTimeline(studyId),
            activityEventsRepo.getActivityEvents(studyId)
        ) { timeLineResource, eventsResource ->
            extractSessionsForDay(
                timeLineResource,
                eventsResource,
                studyId,
                instantInDay
            )
        }
    }

    private fun extractSessionsForDay(
        timelineResult: ResourceResult<Timeline>,
        eventsResult: ResourceResult<StudyActivityEventList>,
        studyId: String,
        instantInDay: Instant
    ): ResourceResult<List<ScheduledSessionWindow>> {
        return when (eventsResult) {
            is ResourceResult.Success -> {
                return extractSessions(eventsResult.data, timelineResult, instantInDay, studyId)
            }
            is ResourceResult.InProgress -> eventsResult
            is ResourceResult.Failed -> eventsResult
        }
    }

    private fun extractSessions(
        eventList: StudyActivityEventList,
        resource: ResourceResult<Timeline>,
        instantInDay: Instant,
        studyId: String
    ): ResourceResult<List<ScheduledSessionWindow>> {
        return when (resource) {
            is ResourceResult.Success -> {
                val timeline = resource.data
                ResourceResult.Success(
                    extractSessionsForDay(
                        eventList,
                        timeline,
                        instantInDay,
                        studyId
                    ), resource.status
                )
            }
            is ResourceResult.InProgress -> resource
            is ResourceResult.Failed -> resource
        }
    }

    /**
     * Extract the scheduled sessions from the [Timeline] for the day specified by [instantInDay].
     * The returned list of [ScheduledSessionWindow]s will include all sessions that are active on the
     * day specified by [instantInDay]. Sessions that expire before [instantInDay] will be excluded.
     */
    @OptIn(ExperimentalTime::class)
    private fun extractSessionsForDay(
        eventList: StudyActivityEventList,
        timeline: Timeline,
        instantInDay: Instant,
        studyId: String,
        includeExpired: Boolean = false,
        timezone: TimeZone = TimeZone.currentSystemDefault(),
    ): List<ScheduledSessionWindow> {
        return extractSessionWindows(
            eventList,
            timeline,
            instantInDay,
            studyId,
            false,
            includeExpired,
            timezone
        )
    }

    @OptIn(ExperimentalTime::class)
    private fun extractSessionWindows(
        eventList: StudyActivityEventList,
        timeline: Timeline,
        instantInDay: Instant,
        studyId: String,
        future: Boolean,
        includeExpired: Boolean,
        timezone: TimeZone,
    ): List<ScheduledSessionWindow> {

        // Map of eventID to SessionInfo
        val sessionInfoMap = timeline.sessions?.groupBy { it.startEventId } ?: return emptyList()
        // Map of key to AssessmentInfo
        val assessmentInfoMap =
            timeline.assessments?.associateBy({ it.key }, { it }) ?: return emptyList()
        // Map of Session Guid to ScheduledSessionList
        val scheduleSessionMap = timeline.schedule?.groupBy { it.refGuid } ?: return emptyList()
        // Get date portion of instantInDay
        val day: LocalDate = instantInDay.toLocalDateTime(timezone).date

        val events = eventList.items ?: return emptyList()
        return events.map { event ->
            // Convert the event timestamp to a LocalDate
            val eventLocalDate = event.timestamp.toLocalDateTime(timezone).date
            // Get number of days since the event date
            val daysSince = eventLocalDate.daysUntil(day)

            val sessions = sessionInfoMap[event.eventId] ?: emptyList()
            sessions.map { session ->
                //Find the list of scheduled sessions for the given session
                val scheduledSessionList = scheduleSessionMap[session.guid] ?: emptyList()
                //Filter the list to today's sessions (start on or before and end on or after today)
                scheduledSessionList.filterByDaysSince(daysSince, future)
                    .mapNotNull { scheduledSession ->
                        createScheduledSessionWindow(
                            scheduledSession,
                            daysSince,
                            day,
                            instantInDay,
                            studyId,
                            assessmentInfoMap,
                            session,
                            event,
                            includeExpired,
                            timezone
                        )
                }
            }.flatten()
        }.flatten()
        .sortedBy { it.startDateTime }
    }

    private fun List<ScheduledSession>.filterByDaysSince(daysSince: Int, future: Boolean): List<ScheduledSession> {
        return if (future) filter { it.startDay > daysSince }
        else filter { it.startDay <= daysSince && it.endDay >= daysSince }
    }

    private fun createScheduledSessionWindow(
        scheduledSession: ScheduledSession,
        daysSince: Int,
        day: LocalDate,
        instantInDay: Instant,
        studyId: String,
        assessmentInfoMap: Map<String?, AssessmentInfo>,
        session: SessionInfo,
        event: StudyActivityEvent,
        includeExpired: Boolean,
        timezone: TimeZone,
    ): ScheduledSessionWindow? {
        // For sessions with an expiration we need to check if it is passed

        //Used for sorting when sessions span multiple days
        val startDaysFromToday = scheduledSession.startDay - daysSince
        val startDate = day.plus(startDaysFromToday.toLong(), DateTimeUnit.DateBased.DayBased(1))

        // LocalTime support is hopefully coming: https://github.com/Kotlin/kotlinx-datetime/issues/57#issuecomment-800287971
        // Construct a startDateTime from today and startTime
        val startDateTimeString =
            startDate.toString() + "T" + scheduledSession.startTime
        val startDateTime = LocalDateTime.parse(startDateTimeString)

        val startInstant = startDateTime.toInstant(timezone)
        val expirationInstant = startInstant.plus(scheduledSession.expiration, timezone)

        val endDateTime = expirationInstant.toLocalDateTime(timezone)
        val isExpired = (expirationInstant < instantInDay)

        // Expiration is in the past so don't include it
        return if (includeExpired || !isExpired)
            ScheduledSessionWindow(
                scheduledSession = scheduledSession,
                sessionInfo = session,
                assessments = mapAssessments(scheduledSession, studyId, assessmentInfoMap),
                event = event,
                isExpired = isExpired,
                startDateTime = startDateTime,
                endDateTime = endDateTime
            ) else null
    }

    private fun mapAssessments(
        scheduledSession: ScheduledSession,
        studyId: String,
        assessmentInfoMap: Map<String?, AssessmentInfo>
    ): List<ScheduledAssessmentReference> {

        val adherenceRecords = adherenceRecordRepo.getCachedAdherenceRecords(
            scheduledSession.assessments.map { it.instanceGuid },
            studyId
        )

        return scheduledSession.assessments.map { assessment ->
            val recordsList = adherenceRecords[assessment.instanceGuid]
            ScheduledAssessmentReference(
                instanceGuid = assessment.instanceGuid,
                assessmentInfo = assessmentInfoMap[assessment.refKey]!!,
                adherenceRecordList = recordsList
            )
        }
    }
}

data class ScheduledSessionWindow (
    val scheduledSession: ScheduledSession,
    val event: StudyActivityEvent,
    val startDateTime: LocalDateTime,
    val endDateTime: LocalDateTime,
    val isExpired: Boolean,
    val assessments: List<ScheduledAssessmentReference>,
    val sessionInfo: SessionInfo
) {
    val instanceGuid = scheduledSession.instanceGuid
    val eventTimeStamp = event.timestamp
    val hasStartTimeOfDay = startDateTime.hour == 0 && startDateTime.minute == 0
    val hasEndTimeOfDay = scheduledSession.expiration.let { it.hours > 0 || it.minutes > 0 }
    val isCompleted = assessments.all { it.isCompleted || it.isDeclined }
    val persistent = scheduledSession.persistent
}

data class ScheduledAssessmentReference (
    val instanceGuid: String,
    val assessmentInfo: AssessmentInfo,
    val adherenceRecordList: List<AdherenceRecord>?,
) {
    val isCompleted = adherenceRecordList?.let { records -> records.any { it.finishedOn != null }} ?: false
    val isDeclined = !isCompleted && adherenceRecordList?.let { records -> records.any { it.declined == true }} ?: false
}
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
        return getResourceById(SCHEDULE_TIMELINE_ID+studyId, remoteLoad =  { loadRemoteTimeline(studyId) }, studyId = studyId)
    }

    private suspend fun loadRemoteTimeline(studyId: String) : String {
        return Json.encodeToString(scheduleApi.getTimelineForUser(studyId))
    }

    /**
     * Get all the scheduled sessions for today that have not expired.
     */
    fun getSessionsForToday(studyId: String) : Flow<ResourceResult<List<ScheduledSessionWindow>>> {
        return getSessionsForDay(studyId, Clock.System.now())
    }

    /**
     * Used for testing so that we can specify a consistent point in time.
     */
    internal fun getSessionsForDay(studyId: String, instantInDay: Instant) : Flow<ResourceResult<List<ScheduledSessionWindow>>> {
        return combine(getTimeline(studyId), activityEventsRepo.getActivityEvents(studyId), adherenceRecordRepo.getAllCachedAdherenceRecords(studyId)) { timeLineResource, eventsResource, adherence ->
            extractSessionsForDay(timeLineResource, eventsResource, adherence, studyId, instantInDay)
        }
    }

    private fun extractSessionsForDay(timelineResult: ResourceResult<Timeline>,
                                        eventsResult: ResourceResult<StudyActivityEventList>,
                                        adherenceRecords: Map<String, List<AdherenceRecord>>,
                                        studyId: String,
                                        instantInDay: Instant
                                        ) : ResourceResult<List<ScheduledSessionWindow>> {
        return when (eventsResult) {
            is ResourceResult.Success -> {
                return extractSessions(eventsResult.data, timelineResult, instantInDay, studyId)
            }
            is ResourceResult.InProgress -> eventsResult
            is ResourceResult.Failed -> eventsResult
        }
    }

    private fun extractSessions(eventList: StudyActivityEventList, resource: ResourceResult<Timeline>, instantInDay: Instant, studyId: String): ResourceResult<List<ScheduledSessionWindow>> {
        return when (resource) {
            is ResourceResult.Success -> {
                val timeline = resource.data
                ResourceResult.Success(extractSessionsForDay(eventList, timeline, instantInDay, studyId), resource.status)
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
    private fun extractSessionsForDay(eventList: StudyActivityEventList, timeline: Timeline, instantInDay: Instant, studyId: String) : List<ScheduledSessionWindow> {
        // Map of eventID to SessionInfo
        val sessionInfoMap = timeline.sessions?.groupBy({it.startEventId})
        // Map of key to AssessmentInfo
        val assessmentInfoMap = timeline.assessments?.associateBy({it.key}, {it})
        // Map of Session Guid to ScheduledSessionList
        val scheduleSessionMap = timeline.schedule?.groupBy({it.refGuid})

        if (sessionInfoMap == null || assessmentInfoMap == null || scheduleSessionMap == null) {
            return emptyList()
        }

        // Get date portion of instantInDay
        val day: LocalDate = instantInDay.toLocalDateTime(TimeZone.currentSystemDefault()).date

        val scheduledSessionWindowList = mutableListOf<ScheduledSessionWindow>()
        eventList.items?.let {
            for (event in eventList.items) {
                // Convert the event timestamp to a LocalDate
                val eventLocalDate = event.timestamp.toLocalDateTime(TimeZone.currentSystemDefault()).date
                // Get number of days since the event date
                val daysSince = eventLocalDate.daysUntil(day)

                sessionInfoMap.get(event.eventId)?.let { sessionInfoList ->
                    for (session in sessionInfoList) {
                        //Find the list of scheduled sessions for the given session
                        val scheduledSessionList = scheduleSessionMap[session.guid]
                        //Filter the list to today's sessions (start on or before and end on or after today)
                        scheduledSessionList?.filter { it.startDay <= daysSince && it.endDay >= daysSince }
                            ?.let { todaySessionList ->
                                for (scheduledSession in todaySessionList) {
                                    var includeSession = true
                                    // For sessions with an expiration we need to check if it is passed

                                    //Used for sorting when sessions span multiple days
                                    val startDaysFromToday = scheduledSession.startDay - daysSince
                                    val startDate = day.plus(startDaysFromToday.toLong(), DateTimeUnit.DateBased.DayBased(1))

                                    // LocalTime support is hopefully coming: https://github.com/Kotlin/kotlinx-datetime/issues/57#issuecomment-800287971
                                    // Construct a startDateTime from today and startTime
                                    val startDateTimeString =
                                        startDate.toString() + "T" + scheduledSession.startTime
                                    val startDateTime = LocalDateTime.parse(startDateTimeString)

                                    val startInstant =
                                        startDateTime.toInstant(TimeZone.currentSystemDefault())
                                    val expirationInstant = startInstant.plus(
                                        scheduledSession.expiration,
                                        TimeZone.currentSystemDefault()
                                    )
                                    if ((expirationInstant.toEpochMilliseconds() - instantInDay.toEpochMilliseconds()) < 0) {
                                        // Expiration is in the past so don't include it
                                        includeSession = false
                                    }
                                    val endDateTime = expirationInstant.toLocalDateTime(TimeZone.currentSystemDefault())


                                    if (includeSession) {
                                        val adherenceRecords = adherenceRecordRepo.getCachedAdherenceRecords(scheduledSession.assessments.map { it.instanceGuid }, studyId)
                                        val assessmentList = scheduledSession.assessments.map {assessment ->
                                            val recordsList = adherenceRecords.get(assessment.instanceGuid)
                                            ScheduledAssessmentReference(
                                                instanceGuid = assessment.instanceGuid,
                                                assessmentInfo = assessmentInfoMap[assessment.refKey]!!,
                                                adherenceRecordList = recordsList
                                            )
                                        }


                                        val sessionWindow =
                                            ScheduledSessionWindow.createScheduledSessionWindow(
                                                scheduledSession = scheduledSession,
                                                sessionInfo = session,
                                                assessments = assessmentList,
                                                startDaysFromToday = startDaysFromToday,
                                                eventTimeStamp = event.timestamp,
                                                startDateTime = startDateTime,
                                                endDateTime = endDateTime
                                            )
                                        scheduledSessionWindowList.add(sessionWindow)
                                    }
                                }
                            }
                    }
                }
            }
        }
        // Order session windows first by startDaysFromToday, then by startTime
        scheduledSessionWindowList.sortWith(compareBy({ it.startDaysFromToday}, {it.startTime}))
        return scheduledSessionWindowList
    }
}


data class ScheduledSessionWindow (

    val refGuid: String? = null,
    val instanceGuid: String,
    val eventTimeStamp: Instant,
    val startDaysFromToday: Int,
    val startDateTime: LocalDateTime,
    val endDateTime: LocalDateTime,

    val startDay: Int,
    val endDay: Int,
    val startTime: String? = null,
    val delayTime: String? = null,
    val expiration: DateTimePeriod? = null,
    val persistent: Boolean = false,
    val assessments: List<ScheduledAssessmentReference>,
    val sessionInfo: SessionInfo
) {

    /**
     * Session is completed if all assessments are completed and it is not persistent
     */
    val isCompleted = assessments.find { !it.isCompleted } == null && !persistent

    companion object {

        fun createScheduledSessionWindow(
            scheduledSession: ScheduledSession,
            sessionInfo: SessionInfo,
            assessments: List<ScheduledAssessmentReference>,
            startDaysFromToday: Int,
            eventTimeStamp: Instant,
            startDateTime: LocalDateTime,
            endDateTime: LocalDateTime,
            ): ScheduledSessionWindow {

            return ScheduledSessionWindow(
                refGuid = scheduledSession.refGuid,
                instanceGuid = scheduledSession.instanceGuid,
                eventTimeStamp = eventTimeStamp,
                startDay = scheduledSession.startDay,
                endDay = scheduledSession.endDay,
                startTime = scheduledSession.startTime,
                delayTime = scheduledSession.delayTime,
                expiration = scheduledSession.expiration,
                persistent = scheduledSession.persistent,
                sessionInfo = sessionInfo,
                assessments = assessments,
                startDaysFromToday = startDaysFromToday,
                startDateTime = startDateTime,
                endDateTime = endDateTime
            )
        }

    }
}

data class ScheduledAssessmentReference (
    val instanceGuid: kotlin.String,
    val assessmentInfo: AssessmentInfo,
    val adherenceRecordList: List<AdherenceRecord>?,
) {
    val isCompleted = adherenceRecordList?.let { records -> records.any { it.finishedOn != null }} ?: false
    val isDeclined = adherenceRecordList?.let { records -> records.any { it.declined == true }} ?: false
}
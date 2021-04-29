package org.sagebionetworks.bridge.kmm.shared.repo

import co.touchlab.stately.ensureNeverFrozen
import io.ktor.client.*
import kotlinx.coroutines.CoroutineScope
import kotlinx.coroutines.flow.Flow
import kotlinx.coroutines.flow.firstOrNull
import kotlinx.coroutines.flow.map
import kotlinx.datetime.*
import kotlinx.serialization.SerialName
import kotlinx.serialization.Serializable
import kotlinx.serialization.encodeToString
import kotlinx.serialization.json.Json
import org.sagebionetworks.bridge.kmm.shared.apis.AssessmentsApi
import org.sagebionetworks.bridge.kmm.shared.apis.SchedulesV2Api
import org.sagebionetworks.bridge.kmm.shared.cache.ResourceDatabaseHelper
import org.sagebionetworks.bridge.kmm.shared.cache.ResourceResult
import org.sagebionetworks.bridge.kmm.shared.cache.ResourceStatus
import org.sagebionetworks.bridge.kmm.shared.cache.ResourceType
import org.sagebionetworks.bridge.kmm.shared.models.*
import kotlin.time.Duration
import kotlin.time.ExperimentalTime

class ScheduleTimelineRepo(httpClient: HttpClient, databaseHelper: ResourceDatabaseHelper, backgroundScope: CoroutineScope) :
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

    fun getTimeline(studyId: String): Flow<ResourceResult<Timeline>> {
        return getResourceById(SCHEDULE_TIMELINE_ID+studyId, remoteLoad =  { loadRemoteTimeline(studyId) })
    }

    private suspend fun loadRemoteTimeline(studyId: String) : String {
        return Json.encodeToString(scheduleApi.getTimelineForUser(studyId))
    }

    /**
     * Get all the scheduled sessions for today that have not expired.
     */
    fun getSessionsForToday(studyId: String, eventList: ActivityEventList) : Flow<ResourceResult<List<ScheduledSessionWindow>>> {
        return getTimeline(studyId).map {
            extractSessions(eventList, it, Clock.System.now())
        }
    }

    /**
     * Used for testing so that we can specify a consistent point in time.
     */
    internal fun getSessionsForDay(studyId: String, eventList: ActivityEventList, instantInDay: Instant) : Flow<ResourceResult<List<ScheduledSessionWindow>>> {
        return getTimeline(studyId).map {
            extractSessions(eventList, it, instantInDay)
        }
    }

    private fun extractSessions(eventList: ActivityEventList, resource: ResourceResult<Timeline>, instantInDay: Instant): ResourceResult<List<ScheduledSessionWindow>> {
        return when (resource) {
            is ResourceResult.Success -> {
                val timeline = resource.data
                ResourceResult.Success(extractSessionsForDay(eventList, timeline, instantInDay), resource.status)
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
    private fun extractSessionsForDay(eventList: ActivityEventList, timeline: Timeline, instantInDay: Instant) : List<ScheduledSessionWindow> {
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
                                    scheduledSession.expiration?.let { expirationPeriod ->

                                        // LocalTime support is hopefully coming: https://github.com/Kotlin/kotlinx-datetime/issues/57#issuecomment-800287971
                                        // Construct a startDateTime from today and startTime
                                        val startDateTimeString =
                                            day.toString() + "T" + scheduledSession.startTime!!
                                        val startDateTime = LocalDateTime.parse(startDateTimeString)

                                        val startInstant =
                                            startDateTime.toInstant(TimeZone.currentSystemDefault())
                                        val expirationInstant = startInstant.plus(
                                            expirationPeriod,
                                            TimeZone.currentSystemDefault()
                                        )
                                        if (expirationInstant.minus(instantInDay).isNegative()) {
                                            // Expiration is in the past so don't include it
                                            includeSession = false
                                        }
                                    }
                                    if (includeSession) {

                                        val assessmentList = scheduledSession.assessments?.map {
                                            ScheduledAssessmentReference(
                                                it.instanceGuid!!,
                                                assessmentInfoMap[it.refKey]!!
                                            )
                                        }

                                        //Used for sorting when sessions span multiple days
                                        val startDaysFromToday = scheduledSession.startDay - daysSince
                                        val sessionWindow =
                                            ScheduledSessionWindow.createScheduledSessionWindow(
                                                scheduledSession,
                                                session,
                                                assessmentList!!,
                                                startDaysFromToday
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
    val instanceGuid: String? = null,
    val startDaysFromToday: Int,
    val startDay: Int,
    val endDay: Int,
    val startTime: String? = null,
    val delayTime: String? = null,
    val expiration: DateTimePeriod? = null,
    val persistent: Boolean? = null,
    val assessments: List<ScheduledAssessmentReference>? = null,
    val sessionInfo: SessionInfo
) {
    companion object {

        fun createScheduledSessionWindow(scheduledSession: ScheduledSession, sessionInfo: SessionInfo, assessments: List<ScheduledAssessmentReference>, startDaysFromToday: Int): ScheduledSessionWindow {
            return ScheduledSessionWindow(
                refGuid = scheduledSession.refGuid,
                instanceGuid = scheduledSession.instanceGuid,
                startDay = scheduledSession.startDay,
                endDay = scheduledSession.endDay,
                startTime = scheduledSession.startTime,
                delayTime = scheduledSession.delayTime,
                expiration = scheduledSession.expiration,
                persistent = scheduledSession.persistent,
                sessionInfo = sessionInfo,
                assessments = assessments,
                startDaysFromToday = startDaysFromToday
            )
        }

    }
}

data class ScheduledAssessmentReference (
    val instanceGuid: kotlin.String,
    val assessmentInfo: AssessmentInfo
)
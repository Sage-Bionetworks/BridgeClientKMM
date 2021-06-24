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
    fun getSessionsForToday(studyId: String,
                            includeFutureNotifications: Boolean = false): Flow<ResourceResult<List<ScheduledSessionWindow>>> {
        return getSessionsForDay(
            studyId = studyId,
            instantInDay = Clock.System.now(),
            filterType = if (includeFutureNotifications) WindowFilterType.TodayAndNotifications else WindowFilterType.Today
        )
    }

    /**
     * Used for testing so that we can specify a consistent point in time.
     */
    internal fun getSessionsForDay(
        studyId: String,
        instantInDay: Instant,
        filterType: WindowFilterType = WindowFilterType.Today
    ): Flow<ResourceResult<List<ScheduledSessionWindow>>> {
        return combine(
            getTimeline(studyId),
            activityEventsRepo.getActivityEvents(studyId),
            adherenceRecordRepo.getAllCachedAdherenceRecords(studyId)
        ) { timeLineResource, eventsResource, _ ->
            extractSessionsForDay(
                timeLineResource,
                eventsResource,
                studyId,
                instantInDay,
                filterType
            )
        }
    }

    private fun extractSessionsForDay(
        timelineResult: ResourceResult<Timeline>,
        eventsResult: ResourceResult<StudyActivityEventList>,
        studyId: String,
        instantInDay: Instant,
        filterType: WindowFilterType
    ): ResourceResult<List<ScheduledSessionWindow>> {
        return when (eventsResult) {
            is ResourceResult.Success -> {
                return extractSessions(eventsResult.data, timelineResult, instantInDay, studyId, filterType)
            }
            is ResourceResult.InProgress -> eventsResult
            is ResourceResult.Failed -> eventsResult
        }
    }

    private fun extractSessions(
        eventList: StudyActivityEventList,
        resource: ResourceResult<Timeline>,
        instantInDay: Instant,
        studyId: String,
        filterType: WindowFilterType
    ): ResourceResult<List<ScheduledSessionWindow>> {
        return when (resource) {
            is ResourceResult.Success -> {
                val timeline = resource.data
                ResourceResult.Success(
                    extractSessionsForDay(
                        eventList,
                        timeline,
                        instantInDay,
                        studyId,
                        filterType
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
        filterType: WindowFilterType,
        timezone: TimeZone = TimeZone.currentSystemDefault(),
    ): List<ScheduledSessionWindow> {
        val sessions = extractSessionWindows(
            eventList,
            timeline,
            instantInDay,
            studyId,
            filterType,
            timezone
        )
        // If getting sessions for today, need to further filter them based on what is in this set
        if (!filterType.isToday() || sessions.isEmpty()) {
            return sessions
        }

        var upNext: LocalDate? = null
        val today = instantInDay.toLocalDateTime(timezone)
        return sessions.filter {
            when {
                // Include if window already started
                it.startDateTime < today -> true
                // Include first found future date
                upNext == null -> {
                    upNext = it.startDateTime.date
                    true
                }
                // Include on same upNext date
                upNext == it.startDateTime.date -> true
                // Include notifications if requested
                filterType.isNotifications() && !it.notifications.isNullOrEmpty() -> true
                else -> false
            }
        }
    }

    @OptIn(ExperimentalTime::class)
    private fun extractSessionWindows(
        eventList: StudyActivityEventList,
        timeline: Timeline,
        instantInDay: Instant,
        studyId: String,
        filterType: WindowFilterType,
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

        val foundState = FoundWindowState()
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
                //Map the schedules to windows
                scheduledSessionList.mapNotNull { scheduledSession ->
                    createScheduledSessionWindow(
                        scheduledSession,
                        filterType,
                        daysSince,
                        day,
                        instantInDay,
                        studyId,
                        assessmentInfoMap,
                        session,
                        event,
                        timezone,
                        foundState
                    )
                }
            }.flatten()
        }.flatten()
        .sortedBy { it.startDateTime }
    }

    // Work-around for Kotlin not having inout variables. syoung 06/25/2021
    private class FoundWindowState(var found: Boolean = false)

    internal enum class WindowFilterType {
        Future, Past, Today, Notifications, TodayAndNotifications;

        fun isToday() = listOf(Today, TodayAndNotifications).contains(this)
        fun includeCompleted() = listOf(Today, TodayAndNotifications, Past).contains(this)
        fun isNotifications() = listOf(Notifications, TodayAndNotifications).contains(this)
        fun includeExpired() = listOf(Past).contains(this)
    }

    /**
     * This is pulled out into a function to make it a little easier to read and to
     * allow for using explicit returns in the `mapNotNull` method. I find mapping
     * functions in Kotlin with early exits difficult to grok. syoung 06/24/2021
     */
    @ExperimentalTime
    private fun createScheduledSessionWindow(
        scheduledSession: ScheduledSession,
        filterType: WindowFilterType,
        daysSince: Int,
        day: LocalDate,
        instantInDay: Instant,
        studyId: String,
        assessmentInfoMap: Map<String?, AssessmentInfo>,
        session: SessionInfo,
        event: StudyActivityEvent,
        timezone: TimeZone,
        foundState: FoundWindowState,
    ): ScheduledSessionWindow? {

        fun rulesForNotifications() =
            scheduledSession.startDay >= daysSince && !session.notifications.isNullOrEmpty()
        fun rulesForAvailableToday() =
            (daysSince in scheduledSession.startDay..scheduledSession.endDay)
        fun rulesForToday() =
            if (foundState.found) rulesForAvailableToday() else { scheduledSession.endDay >= daysSince }

        // Exit early if this schedule is not in the range that we are looking for
        if (!when (filterType) {
            WindowFilterType.Notifications -> rulesForNotifications()
            WindowFilterType.Future -> scheduledSession.startDay > daysSince
            WindowFilterType.Past -> scheduledSession.startDay <= daysSince
            WindowFilterType.Today -> rulesForToday()
            WindowFilterType.TodayAndNotifications -> rulesForToday() || rulesForNotifications()
        }) {
            return null
        }

        //Used for sorting when sessions span multiple days
        val startDaysFromDay = scheduledSession.startDay - daysSince
        val startDate = day.plus(startDaysFromDay.toLong(), DateTimeUnit.DateBased.DayBased(1))

        // LocalTime support is hopefully coming: https://github.com/Kotlin/kotlinx-datetime/issues/57#issuecomment-800287971
        // Construct a startDateTime from today and startTime
        val startDateTimeString =
            startDate.toString() + "T" + scheduledSession.startTime
        val startDateTime = LocalDateTime.parse(startDateTimeString)

        val startInstant = startDateTime.toInstant(timezone)
        val expirationInstant = startInstant.plus(scheduledSession.expiration, timezone)

        val endDateTime = expirationInstant.toLocalDateTime(timezone)
        val isExpired = (expirationInstant < instantInDay)

        // Exit early if all the assessments are completed and this filtering does
        // not include them.
        val assessments = mapAssessments(scheduledSession, studyId, assessmentInfoMap)
        val isCompleted = assessments.all { it.isCompleted || it.isDeclined }
        if (!filterType.includeCompleted() && isCompleted) {
            return null
        }

        // Exit early if expired and not completed.
        if (!filterType.includeExpired() && isExpired && !isCompleted) {
            return null
        }

        // If we are filtering for today schedules and one was found that is available today
        // but *not* available NOW then track that and do not include future dates.
        if (rulesForAvailableToday() && startInstant > instantInDay) {
            foundState.found = true
        }

        // Convert notifications
        val notifications = session.notifications?.mapNotNull {
            it.scheduleAt(instantInDay, startDateTime, endDateTime)
        }
        // Exit early if this is only getting future notifications and there aren't any.
        if (notifications.isNullOrEmpty() &&
            filterType.isNotifications() &&
            (!filterType.isToday() || !rulesForToday())) {
            return null
        }

        return ScheduledSessionWindow(
            scheduledSession = scheduledSession,
            sessionInfo = session,
            assessments = assessments,
            event = event,
            isExpired = isExpired,
            isCompleted = isCompleted,
            startDateTime = startDateTime,
            endDateTime = endDateTime,
            notifications = if (notifications.isNullOrEmpty()) null else notifications
        )
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

@ExperimentalTime
internal fun NotificationInfo.scheduleAt(instantInDay: Instant,
                                         startDateTime: LocalDateTime,
                                         endDateTime: LocalDateTime,
): ScheduledNotification? {

    // Get the first notification trigger
    val timeZone = TimeZone.currentSystemDefault()
    val period = this.offset?.let { DateTimePeriod.parse(it) } ?: DateTimePeriod()
    var firstInstant = if (notifyAt == NotificationType.AFTER_WINDOW_START) {
        startDateTime.toInstant(timeZone).plus(period, timeZone)
    } else {
        endDateTime.toInstant(timeZone).minus(period, timeZone)
    }

    // If there is an interval, move the firstInstant forward to after the current time
    val intervalPeriod = this.interval?.let { DateTimePeriod.parse(it) }
    if (intervalPeriod != null && intervalPeriod.days > 0) {
        val endInstant = endDateTime.toInstant(timeZone)
        while(firstInstant < instantInDay && firstInstant < endInstant) {
            firstInstant = firstInstant.plus(intervalPeriod, timeZone)
        }
    }

    // Return null if the first instant isn't in the future
    return if (firstInstant < instantInDay) null
    else ScheduledNotification(
            firstInstant.toLocalDateTime(timeZone),
            intervalPeriod,
            allowSnooze ?: false,
            message
        )
}

data class ScheduledNotification(
    val scheduleOn: LocalDateTime,
    val repeatInterval: DateTimePeriod?,
    val allowSnooze: Boolean,
    val message: NotificationMessage?,
)

data class ScheduledSessionWindow (
    val scheduledSession: ScheduledSession,
    val event: StudyActivityEvent,
    val startDateTime: LocalDateTime,
    val endDateTime: LocalDateTime,
    val isExpired: Boolean,
    val isCompleted: Boolean,
    val assessments: List<ScheduledAssessmentReference>,
    val sessionInfo: SessionInfo,
    val notifications: List<ScheduledNotification>?,
) {
    val instanceGuid = scheduledSession.instanceGuid
    val eventTimeStamp = event.timestamp
    val hasStartTimeOfDay = startDateTime.hour == 0 && startDateTime.minute == 0
    val hasEndTimeOfDay = scheduledSession.expiration.let { it.hours > 0 || it.minutes > 0 }
    val persistent = scheduledSession.persistent
}

data class ScheduledAssessmentReference (
    val instanceGuid: String,
    val assessmentInfo: AssessmentInfo,
    val adherenceRecordList: List<AdherenceRecord>?,
) {
    val isCompleted = adherenceRecordList?.any { it.finishedOn != null } ?: false
    val isDeclined = !isCompleted && adherenceRecordList?.any { it.declined == true } ?: false
}
package org.sagebionetworks.bridge.kmm.shared.repo

import co.touchlab.stately.ensureNeverFrozen
import io.ktor.client.*
import kotlinx.coroutines.CoroutineScope
import kotlinx.coroutines.flow.Flow
import kotlinx.coroutines.flow.map
import kotlinx.coroutines.launch
import kotlinx.datetime.*
import kotlinx.serialization.Serializable
import kotlinx.serialization.encodeToString
import kotlinx.serialization.json.Json
import org.sagebionetworks.bridge.kmm.shared.apis.SchedulesV2Api
import org.sagebionetworks.bridge.kmm.shared.cache.*
import org.sagebionetworks.bridge.kmm.shared.models.*
import kotlin.time.ExperimentalTime

class ScheduleTimelineRepo(internal val adherenceRecordRepo: AdherenceRecordRepo,
                           internal val assessmentConfigRepo: AssessmentConfigRepo,
                           httpClient: HttpClient,
                           databaseHelper: ResourceDatabaseHelper,
                           backgroundScope: CoroutineScope,
                           var scheduleMutator: ParticipantScheduleMutator? = null) :
    AbstractResourceRepo(databaseHelper, backgroundScope) {

    internal companion object {
        const val SCHEDULE_TIMELINE_ID = "ScheduleTimelineId"
    }

    init {
        ensureNeverFrozen()
    }

    private var scheduleApi = SchedulesV2Api(
        httpClient = httpClient
    )

    internal val participantScheduleDatabase = ParticipantScheduleDatabase(
        databaseHelper = databaseHelper
    )

    private fun getCachedSchedule(studyId: String): ParticipantSchedule? {
        return database.getResource(SCHEDULE_TIMELINE_ID + studyId, ResourceType.PARTICIPANT_SCHEDULE, studyId )?.loadResource()
    }

    private fun updateCachedSchedule(participantSchedule: ParticipantSchedule, studyId: String) {
        participantScheduleDatabase.cacheParticipantSchedule(studyId, participantSchedule)
        val resource = Resource(
            identifier = SCHEDULE_TIMELINE_ID + studyId,
            secondaryId = ResourceDatabaseHelper.DEFAULT_SECONDARY_ID,
            type = ResourceType.PARTICIPANT_SCHEDULE,
            studyId = studyId,
            json = Json.encodeToString(participantSchedule),
            lastUpdate = Clock.System.now().toEpochMilliseconds(),
            status = ResourceStatus.SUCCESS,
            needSave = false
        )
        database.insertUpdateResource(resource)
    }

    fun runScheduleMutator(studyId: String) {
        if (scheduleMutator != null) {
            getCachedSchedule(studyId)?.let {
                scheduleMutator?.mutateParticipantSchedule(it)?.let { mutatedSchedule ->
                    updateCachedSchedule(mutatedSchedule, studyId)
                }

            }
        }
    }

    private fun getTimeline(studyId: String): Flow<ResourceResult<ParticipantSchedule>> {
        return getResourceByIdAsFlow(
            SCHEDULE_TIMELINE_ID + studyId,
            resourceType = ResourceType.PARTICIPANT_SCHEDULE,
            remoteLoad = { loadRemoteTimeline(studyId) },
            studyId = studyId
        )
    }

    internal suspend fun loadRemoteTimeline(studyId: String): String {
        var schedule = scheduleApi.getParticipantScheduleForSelf(studyId)
        schedule = scheduleMutator?.mutateParticipantSchedule(schedule) ?: schedule
        participantScheduleDatabase.cacheParticipantSchedule(studyId, schedule)
        backgroundScope.launch() {
            schedule.assessments?.let {
                assessmentConfigRepo.loadAndCacheConfigs(it)
            }
        }
        return Json.encodeToString(schedule)
    }

    suspend fun updateScheduleIfNeeded(studyId: String) {
        val resourceIdentifier = SCHEDULE_TIMELINE_ID + studyId
        val curResource = database.getResource(resourceIdentifier, ResourceType.PARTICIPANT_SCHEDULE, studyId )
        if (curResource == null ||
                    (curResource.lastUpdate + defaultUpdateFrequency < Clock.System.now().toEpochMilliseconds())) {
            remoteLoadResource(database, resourceIdentifier, ResourceDatabaseHelper.DEFAULT_SECONDARY_ID,
                resourceType = ResourceType.PARTICIPANT_SCHEDULE,
                studyId = studyId,
                curResource = curResource,
                remoteLoad = { loadRemoteTimeline(studyId) }
                )
        }
    }

    internal fun clearCachedSchedule(studyId: String) {
        database.removeAllResources(ResourceType.PARTICIPANT_SCHEDULE, studyId)
        participantScheduleDatabase.clearCachedSchedule(studyId)
    }

    /**
     * Get all the scheduled sessions for today that have not expired.
     * @param studyId Study identifier
     * @param alwaysIncludeNextDay Include the next day containing a [ScheduledSessionWindow]
     */
    fun getSessionsForToday(studyId: String,
                            alwaysIncludeNextDay: Boolean = true): Flow<ResourceResult<ScheduledSessionTimelineSlice>> {
        return getSessionsForDay(
            studyId = studyId,
            instantInDay = Clock.System.now(),
            alwaysIncludeNextDay,
        )
    }

    fun getCachedPendingNotifications(studyId: String, nowInstant: Instant) : List<ScheduledNotification> {
        return participantScheduleDatabase.getCachedPendingNotifications(studyId, nowInstant)
    }

    fun getCachedPendingNotificationsCollapsed(studyId: String, nowInstant: Instant) : Flow<List<ScheduledNotification>> {
        return participantScheduleDatabase.getCachedPendingNotificationsCollapsed(studyId, nowInstant)
    }


    /**
     * Get all the scheduled sessions for the study, organized by study burst.
     * @param studyId Study identifier
     * @param timezone provide a custom timezone if desired, i.e. for testing.
     */
    fun getStudyBurstSchedule(studyId: String,
                              timezone: TimeZone = TimeZone.currentSystemDefault())
            : Flow<ResourceResult<StudyBurstSchedule>> {
        backgroundScope.launch {
            updateScheduleIfNeeded(studyId)
        }
        return participantScheduleDatabase.getStudyBurstSchedule(studyId, timezone)
    }

    internal fun getSessionsForDay(
        studyId: String,
        instantInDay: Instant,
        alwaysIncludeNextDay: Boolean = false
    ): Flow<ResourceResult<ScheduledSessionTimelineSlice>> {
        backgroundScope.launch {
            updateScheduleIfNeeded(studyId)
        }
        return participantScheduleDatabase.getSessionsForDay(studyId, instantInDay, alwaysIncludeNextDay)
            .map {
                if (it.isLoaded) {
                    ResourceResult.Success(it, ResourceStatus.SUCCESS)
                } else {
                    ResourceResult.InProgress
                }
            }
    }

}

@ExperimentalTime
internal fun NotificationInfo.scheduleAt(instanceGuid: String,
                                         instantInDay: Instant,
                                         startDateTime: LocalDateTime,
                                         endDateTime: LocalDateTime,
                                         isTimeSensitive: Boolean,
): ScheduledNotification? {

    // Get the first notification trigger
    val timeZone = TimeZone.currentSystemDefault()
    val period = this.offset?.let { DateTimePeriod.parse(it) } ?: DateTimePeriod()
    val lastInstant = endDateTime.toInstant(timeZone)
    var firstInstant = if (notifyAt == NotificationType.AFTER_WINDOW_START) {
        startDateTime.toInstant(timeZone).plus(period, timeZone)
    } else {
        lastInstant.minus(period, timeZone)
    }

    // If there is an interval, move the firstInstant forward to after the current time
    val intervalPeriod = this.interval?.let { DateTimePeriod.parse(it) }
    if (intervalPeriod != null) {
        val endInstant = endDateTime.toInstant(timeZone)
        while(firstInstant < instantInDay && firstInstant < endInstant) {
            firstInstant = firstInstant.plus(intervalPeriod, timeZone)
        }
    }

    // Return null if the first instant isn't in the future
    return if (firstInstant < instantInDay) null
    else ScheduledNotification(
        instanceGuid,
        firstInstant.toLocalDateTime(timeZone),
        intervalPeriod,
        if (intervalPeriod ==null) null else lastInstant.toLocalDateTime(timeZone),
        allowSnooze ?: false,
        message,
        isTimeSensitive
    )
}

/**
 * A parsed instance of the schedule calculated at a given instant in time and split into
 * which schedules are available now, up next, or require scheduling a notification.
 */
data class ScheduledSessionTimelineSlice (
    val instantInDay: Instant,
    val timezone: TimeZone,
    val isLoaded: Boolean,
    val scheduledSessionWindows: List<ScheduledSessionWindow>,
    val notifications: List<ScheduledNotification>,
)

data class ScheduledSessionWindow (
    val scheduledSession: ScheduledSession,
    val eventTimestamp: Instant,
    val startDateTime: LocalDateTime,
    val endDateTime: LocalDateTime,
    val assessments: List<ScheduledAssessmentReference>,
    val sessionInfo: SessionInfo,
    val notifications: List<ScheduledNotification>?,
) {
    val instanceGuid = scheduledSession.instanceGuid
    val hasStartTimeOfDay = startDateTime.let { it.hour > 0 || it.minute > 0 }
    val hasEndTimeOfDay = scheduledSession.expiration.let { it.hours > 0 || it.minutes > 0 }
    val persistent = scheduledSession.persistent
    val isCompleted = assessments.all { it.isCompleted || it.isDeclined }

    fun isAvailableNow(now: Instant = Clock.System.now()): Boolean {
        val timeZone = TimeZone.currentSystemDefault()
        return startDateTime.toInstant(timeZone) <= now && now < endDateTime.toInstant(timeZone)
    }

    fun isInFuture(now: Instant = Clock.System.now()): Boolean {
        val timeZone = TimeZone.currentSystemDefault()
        return startDateTime.toInstant(timeZone) > now
    }

    fun isInPast(now: Instant = Clock.System.now()): Boolean {
        val timeZone = TimeZone.currentSystemDefault()
        return endDateTime.toInstant(timeZone) < now
    }
}

data class ScheduledAssessmentReference (
    val instanceGuid: String,
    val studyId: String,
    val assessmentInfo: AssessmentInfo,
    val adherenceRecordList: List<AdherenceRecord>,
) {
    val isCompleted = adherenceRecordList.any { it.finishedOn != null }
    val isDeclined = !isCompleted && adherenceRecordList.any { it.declined == true }

    fun history(): List<AssessmentHistoryRecord> {
        return adherenceRecordList.mapNotNull { record ->
            if (record.startedOn != null && record.finishedOn != null && !record.declined)  {
                AssessmentHistoryRecord(instanceGuid, assessmentInfo, record.startedOn, record.finishedOn, record.clientTimeZone, record.clientData)
            } else {
                null
            }
        }
    }
}

@Serializable
data class ScheduledNotification(
    val instanceGuid: String,
    val scheduleOn: LocalDateTime,
    val repeatInterval: DateTimePeriod?,
    val repeatUntil: LocalDateTime?,
    val allowSnooze: Boolean,
    val message: NotificationMessage?,
    val isTimeSensitive: Boolean = false,
)

data class AssessmentHistoryRecord (
    val instanceGuid: String,
    val assessmentInfo: AssessmentInfo,
    val startedOn: Instant,
    val finishedOn: Instant,
    val clientTimeZone: String? = null,
    val clientData: kotlinx.serialization.json.JsonElement? = null) {

    //TODO: Switch to using Instant math once we migrate to Kotlin 1.5 -nbrown 07/27/21
    val minutes: Int = ((finishedOn.epochSeconds - startedOn.epochSeconds) / 60).toInt()
//    @OptIn(ExperimentalTime::class)
//    val minutes = finishedOn.minus(startedOn).inMinutes.roundToInt()
}

interface ParticipantScheduleMutator {

    fun mutateParticipantSchedule(participantSchedule: ParticipantSchedule) : ParticipantSchedule

}

/**
 * A parsed instance of the schedule calculated from the user's joined instant in time onward,
 * and organized in by study burst event ID
 */
data class StudyBurstSchedule (
    val timezone: TimeZone,
    val studyBurstList: List<StudyBurst> = listOf()
) {
    /**
     * Using the full participant schedule, first filter the non-study burst sessions,
     * and then organize the sessions by study burst and the LocalDate startDate.
     * @param studyBurstScheduleSlice full list of schedule sessions containing the study bursts
     * @return the full study burst schedule over their entire timeline
     */
    constructor(studyBurstScheduleSlice: ScheduledSessionTimelineSlice):
        this(studyBurstScheduleSlice.timezone,
             studyBurstScheduleSlice.scheduledSessionWindows.filter {
                 it.scheduledSession.studyBurstId != null && it.scheduledSession.startEventId != null
             }.groupBy {  // Group sessions by study burst ID
                 it.scheduledSession.startEventId
             }.values.sortedBy { // Put sessions lists by burst in chronological order
                 it.first().startDateTime.date
             }.map { sessionsInBurst -> // Sort burst sessions chronologically
                 sessionsInBurst.sortedBy { it.startDateTime.date }
             }.map {
                 StudyBurst(it)
             })
}

data class StudyBurst(
    /** Sessions ordered by session startDate */
    val sessions: List<ScheduledSessionWindow> = listOf())
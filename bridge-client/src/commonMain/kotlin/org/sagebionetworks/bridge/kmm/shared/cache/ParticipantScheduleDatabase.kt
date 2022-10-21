package org.sagebionetworks.bridge.kmm.shared.cache

import app.cash.sqldelight.coroutines.asFlow
import app.cash.sqldelight.coroutines.mapToList
import kotlinx.coroutines.Dispatchers
import kotlinx.coroutines.flow.Flow
import kotlinx.coroutines.flow.map
import kotlinx.datetime.*
import kotlinx.serialization.decodeFromString
import kotlinx.serialization.encodeToString
import kotlinx.serialization.json.Json
import org.sagebionetworks.bridge.kmm.shared.models.*
import org.sagebionetworks.bridge.kmm.shared.repo.*
import kotlin.time.ExperimentalTime

class ParticipantScheduleDatabase(val databaseHelper: ResourceDatabaseHelper) {

    private val dbQuery = databaseHelper.database.participantScheduleQueries

    internal fun getSessionsForDay(studyId: String,
                                   day: Instant = Clock.System.now(),
                                   includeNextDay: Boolean = false,
                                   timezone: TimeZone = TimeZone.currentSystemDefault()): Flow<ScheduledSessionTimelineSlice> {
        val nowDateTime = day.toLocalDateTime(timezone)
        val today = nowDateTime.date
        val nowTime = nowDateTime.time

        if (includeNextDay) {
            return dbQuery.dayAndNextDayWithSessions(studyId, today.toString(), nowTime.toString(), expandedSessionMapper).asFlow().mapToList(Dispatchers.Default).map {
                getScheduledSessionTimelineSlice(studyId, day, timezone, it)
            }
        } else {
            return dbQuery.daySessions(studyId, today.toString(), nowTime.toString(), expandedSessionMapper).asFlow().mapToList(Dispatchers.Default).map {
                getScheduledSessionTimelineSlice(studyId, day, timezone, it)
            }
        }
    }

    internal fun clearCachedSchedule(studyId: String) {
        dbQuery.clearSchedule(studyId)
    }

    internal fun getStudyBurstSchedule(studyId: String,
                              timezone: TimeZone = TimeZone.currentSystemDefault())
            : Flow<ResourceResult<StudyBurstSchedule>> {
        return dbQuery.studyBurstSessions(studyId, expandedSessionMapper).asFlow().mapToList(Dispatchers.Default).map {
            getScheduledSessionTimelineSlice(studyId, Clock.System.now(), timezone, it)
        }.map {
            if (it.isLoaded) {
                ResourceResult.Success(StudyBurstSchedule(it), ResourceStatus.SUCCESS)
            } else {
                ResourceResult.InProgress
            }
        }
    }

    fun getCachedPendingNotifications(studyId: String, nowInstant: Instant) : List<ScheduledNotificationV2> {
        val nowString = nowInstant.toLocalDateTime(TimeZone.currentSystemDefault()).toString()
        val notificationList = dbQuery.futurePendingNotifications(studyId, nowString).executeAsList().toSet().toList()
        return notificationList.map {
            val notifInfo: NotificationInfo = Json.decodeFromString(it.notificationInfoJson)
            ScheduledNotificationV2(
                instanceGuid = it.sessionInstanceGuid,
                scheduleOn = it.scheduleOn.toLocalDateTime(),
                allowSnooze = notifInfo.allowSnooze?: false,
                message = notifInfo.message
            )
        }
    }

    fun getCachedPendingNotificationsCollapsed(studyId: String, nowInstant: Instant) : List<ScheduledNotificationV2> {
        val nowString = nowInstant.toLocalDateTime(TimeZone.currentSystemDefault()).toString()
        val notificationList = dbQuery.groupedFuturePendingNotifications(studyId, nowString).executeAsList().toSet().toList()
        return notificationList.map {
            val notifInfo: NotificationInfo = Json.decodeFromString(it.notificationInfoJson)
            ScheduledNotificationV2(
                instanceGuid = it.sessionInstanceGuid,
                scheduleOn = it.scheduleOn!!.toLocalDateTime(),
                allowSnooze = notifInfo.allowSnooze?: false,
                message = notifInfo.message
            )
        }
    }

    private fun getScheduledSessionTimelineSlice(studyId: String, instantInDay: Instant, timeZone: TimeZone, fullSessionsList: List<ExpandedScheduledSession>) : ScheduledSessionTimelineSlice {
        // fullSessionsList has an entry for every assessment and adherence record every session
        val sessionWindows = fullSessionsList.groupBy { it.sessionInstanceGuid }
            .mapNotNull { (sessionInstanceGuid, assessments) ->
                // assessments has an entry for every assessment and adherence record for a given session
                extractScheduledSessionWindow(instantInDay, timeZone, assessments)
            }
        val createdOn = dbQuery.selectScheduleMetadata(studyId).executeAsOneOrNull()?.createdOn
        return ScheduledSessionTimelineSlice(
            instantInDay = instantInDay,
            timezone = timeZone,
            isLoaded = createdOn != null,
            scheduledSessionWindows = sessionWindows.sortedBy { it.startDateTime },
            notifications = listOf()
        )
    }

    @OptIn(ExperimentalTime::class)
    private fun extractScheduledSessionWindow(instantInDay: Instant, timezone: TimeZone, session: List<ExpandedScheduledSession>) : ScheduledSessionWindow? {
        if (session.isEmpty() || session[0].startEventTimestamp == null) {
            return null
        }
        val scheduleAssessmentList = session.groupBy { it.assessmentInstanceGuid }
            .map {(instanceGuid, assessments) ->
                // For persistent sessions we could have multiple adherence records per assessment
                ScheduledAssessmentReference(
                    instanceGuid = instanceGuid,
                    studyId = assessments[0].studyId,
                    assessmentInfo = Json.decodeFromString(assessments[0].assessmentInfoJson),
                    adherenceRecordList = assessments.filter { it.adherenceJson != null }.map {
                        Json.decodeFromString(it.adherenceJson!!)
                    }
                )
            }
        val scheduledSession = Json.decodeFromString<ScheduledSession>(session[0].scheduledSessionJson)
        val startDateTime = LocalDateTime(scheduledSession.startDate, scheduledSession.startTime)
        val startInstant = startDateTime.toInstant(timezone)
        val expirationInstant = startInstant.plus(scheduledSession.expiration, timezone)
        val endDateTime = expirationInstant.toLocalDateTime(timezone)

        // TODO: Remove adding notifications which would allow removal instantInDay method argument -nbrown 10/12/22
        // Convert notifications, including for backwards compatibility
        val isCompleted = scheduleAssessmentList.all { it.isCompleted || it.isDeclined }
        val sessionInfo: SessionInfo = Json.decodeFromString(session[0].sessionInfoJson)
        val notifications = sessionInfo.notifications?.mapNotNull {
            it.scheduleAt(scheduledSession.instanceGuid, instantInDay, startDateTime, endDateTime, scheduledSession.expiration.days == 0)
        }

        return ScheduledSessionWindow(
            scheduledSession = scheduledSession,
            sessionInfo = sessionInfo,
            assessments = scheduleAssessmentList,
            eventTimestamp = session[0].startEventTimestamp!!.toInstant(),
            startDateTime = startDateTime,
            endDateTime = endDateTime,
            notifications = if (notifications.isNullOrEmpty() || isCompleted) null else notifications.sortedBy { it.scheduleOn }
        )
    }

    // Our own data class and mapper so we can reuse extraction code for getStudyBursts method
    data class ExpandedScheduledSession(
        public val studyId: String,
        public val instanceGuid: String,
        public val startDate: String,
        public val endDate: String,
        public val startTime: String,
        public val endTime: String,
        public val studyBurstID: String?,
        public val startEventId: String?,
        public val startEventTimestamp: String?,
        public val persistent: Boolean,
        public val scheduledSessionJson: String,
        public val sessionInfoJson: String,
        public val sessionInstanceGuid: String,
        public val assessmentInstanceGuid: String,
        public val assessmentInfoJson: String,
        public val startedOn: String?,
        public val finishedOn: String?,
        public val declined: Boolean?,
        public val adherenceJson: String?,
    )

    val expandedSessionMapper: ((
        studyId: String,
        instanceGuid: String,
        startDate: String,
        endDate: String,
        startTime: String,
        endTime: String,
        studyBurstID: String?,
        startEventId: String?,
        startEventTimestamp: String?,
        persistent: Boolean,
        scheduledSessionJson: String,
        sessionInfoJson: String,
        sessionInstanceGuid: String,
        assessmentInstanceGuid: String,
        assessmentInfoJson: String,
        startedOn: String?,
        finishedOn: String?,
        declined: Boolean?,
        adherenceJson: String?,
    ) -> ExpandedScheduledSession) = { studyId,
                                       instanceGuid,
                                       startDate,
                                       endDate,
                                       startTime,
                                       endTime,
                                       studyBurstID,
                                       startEventId,
                                       startEventTimestamp,
                                       persistent,
                                       scheduledSessionJson,
                                       sessionInfoJson,
                                       sessionInstanceGuid,
                                       assessmentInstanceGuid,
                                       assessmentInfoJson,
                                       startedOn,
                                       finishedOn,
                                       declined,
                                       adherenceJson ->
        ExpandedScheduledSession(
            studyId,
            instanceGuid,
            startDate,
            endDate,
            startTime,
            endTime,
            studyBurstID,
            startEventId,
            startEventTimestamp,
            persistent,
            scheduledSessionJson,
            sessionInfoJson,
            sessionInstanceGuid,
            assessmentInstanceGuid,
            assessmentInfoJson,
            startedOn,
            finishedOn,
            declined,
            adherenceJson
        )
    }




    internal fun cacheParticipantSchedule(studyId: String, schedule: ParticipantSchedule) {
        // Check the createdOn date to see if we need to update the cached schedule
        val createdOn = schedule.createdOn
        val cachedCreatedOn = dbQuery.selectScheduleMetadata(studyId).executeAsOneOrNull()?.createdOn
        if (createdOn == cachedCreatedOn) {
            return
        }

        val assessmentInfoMap = schedule.assessments?.associateBy({ it.key }, { it }) ?: return
        val scheduleSessionMap = schedule.schedule?.groupBy { it.refGuid } ?: return
        val eventMap = schedule.eventTimestamps
        val sessions = schedule.sessions ?: emptyList()

        val sessionWindowsList = sessions.mapNotNull { session ->
            scheduleSessionMap[session.guid]?.mapNotNull { scheduledSession ->
                createScheduledSessionWindow(
                    studyId = studyId,
                    scheduledSession = scheduledSession,
                    session = session,
                    assessmentInfoMap = assessmentInfoMap,
                    eventMap = eventMap
                )
            }
        }.flatten()

        databaseHelper.database.transaction {
            dbQuery.clearSchedule(studyId)
            dbQuery.insertUpdateScheduleMetadata(studyId, createdOn)
            sessionWindowsList.forEach {
                val timezone = TimeZone.currentSystemDefault()
                val startInstant = it.scheduledSession.startDateTime.toInstant(timezone)
                val expirationInstant = startInstant.plus(it.scheduledSession.expiration, timezone)

                val endDateTime = expirationInstant.toLocalDateTime(timezone)
                dbQuery.insertUpdateSession(
                    studyId = studyId,
                    instanceGuid = it.scheduledSession.instanceGuid ,
                    startDate = it.scheduledSession.startDate.toString(),
                    // Use computed endDate instead of one from services, which seems wrong for full day sessions -nbrown 10/11/22
                    endDate = endDateTime.date.toString(),
                    startTime = it.scheduledSession.startTime.toString(),
                    endTime = endDateTime.time.toString(),
                    studyBurstID = it.scheduledSession.studyBurstId,
                    startEventId = it.scheduledSession.startEventId,
                    startEventTimestamp = it.eventTimestamp.toString(),
                    persistent = it.scheduledSession.persistent,
                    scheduledSessionJson = Json.encodeToString(it.scheduledSession),
                    sessionInfoJson = Json.encodeToString(it.sessionInfo),
                )
                it.assessments.forEach { assessment ->
                    dbQuery.insertUpdateScheduledAssessments(
                        studyId = studyId,
                        sessionInstanceGuid = it.scheduledSession.instanceGuid,
                        assessmentInstanceGuid = assessment.instanceGuid,
                        guid = assessment.assessmentInfo.guid,
                        identifier = assessment.assessmentInfo.identifier,
                        assessmentInfoJson = Json.encodeToString(assessment.assessmentInfo),
                    )
                }
                // Store all potential notifications for a session
                it.sessionInfo.notifications?.forEach { notificationInfo ->
                    // Get the first notification trigger
                    val period = notificationInfo.offset?.let { DateTimePeriod.parse(it) } ?: DateTimePeriod()
                    var firstInstant = if (notificationInfo.notifyAt == NotificationType.AFTER_WINDOW_START) {
                        startInstant.plus(period, timezone)
                    } else {
                        expirationInstant.minus(period, timezone)
                    }
                    dbQuery.insertUpdateNotifications(
                        studyId = studyId,
                        sessionInstanceGuid = it.scheduledSession.instanceGuid,
                        scheduleOn = firstInstant.toLocalDateTime(timezone).toString(),
                        repeatInterval = notificationInfo.interval,
                        repeatUntil = endDateTime.toString(),
                        notificationInfoJson = Json.encodeToString(notificationInfo)
                    )
                    val intervalPeriod = notificationInfo.interval?.let { DateTimePeriod.parse(it) }
                    if (intervalPeriod != null) {
                        firstInstant = firstInstant.plus(intervalPeriod, timezone)
                        while (firstInstant < expirationInstant) {
                            dbQuery.insertUpdateNotifications(
                                studyId = studyId,
                                sessionInstanceGuid = it.scheduledSession.instanceGuid,
                                scheduleOn = firstInstant.toLocalDateTime(timezone).toString(),
                                repeatInterval = notificationInfo.interval,
                                repeatUntil = endDateTime.toString(),
                                notificationInfoJson = Json.encodeToString(notificationInfo)
                            )
                            firstInstant = firstInstant.plus(intervalPeriod, timezone)
                        }
                    }
                }
            }
        }

    }
    data class ScheduledSessionHolder (
        val scheduledSession: ScheduledSession,
        val eventTimestamp: Instant,
        val assessments: List<ScheduledAssessment>,
        val sessionInfo: SessionInfo,
    )

    data class ScheduledAssessment (
        val instanceGuid: String,
        val studyId: String,
        val assessmentInfo: AssessmentInfo
    )

    private fun createScheduledSessionWindow(
        studyId: String,
        scheduledSession: ScheduledSession,
        session: SessionInfo,
        assessmentInfoMap: Map<String, AssessmentInfo>,
        eventMap: Map<String,Instant>?,
    ) : ScheduledSessionHolder? {
        val eventTimestamp = eventMap?.get(scheduledSession.startEventId) ?: return null
        val assessments = scheduledSession.assessments.map { assessment ->
            ScheduledAssessment(
                instanceGuid = assessment.instanceGuid,
                studyId = studyId,
                assessmentInfo = assessmentInfoMap[assessment.refKey]!!,
            )
        }
        return ScheduledSessionHolder(
            scheduledSession = scheduledSession,
            eventTimestamp = eventTimestamp,
            assessments = assessments,
            sessionInfo = session
        )
    }

}
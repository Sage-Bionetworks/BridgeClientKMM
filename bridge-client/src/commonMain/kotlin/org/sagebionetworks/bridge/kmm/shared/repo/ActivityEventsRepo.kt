package org.sagebionetworks.bridge.kmm.shared.repo

import co.touchlab.kermit.Logger
import co.touchlab.stately.ensureNeverFrozen
import io.ktor.client.*
import kotlinx.coroutines.CoroutineScope
import kotlinx.coroutines.flow.Flow
import kotlinx.datetime.Instant
import kotlinx.serialization.encodeToString
import kotlinx.serialization.json.Json
import org.sagebionetworks.bridge.kmm.shared.apis.ActivityEventsApi
import org.sagebionetworks.bridge.kmm.shared.cache.ResourceDatabaseHelper
import org.sagebionetworks.bridge.kmm.shared.cache.ResourceResult
import org.sagebionetworks.bridge.kmm.shared.cache.ResourceType
import org.sagebionetworks.bridge.kmm.shared.models.StudyActivityEventList
import org.sagebionetworks.bridge.kmm.shared.models.StudyActivityEventRequest

class ActivityEventsRepo(httpClient: HttpClient, databaseHelper: ResourceDatabaseHelper, backgroundScope: CoroutineScope, val scheduleTimelineRepo: ScheduleTimelineRepo) :
    AbstractResourceRepo(databaseHelper, backgroundScope) {

    internal companion object {
        const val ACTIVITY_EVENTS_LIST_ID = "ActivityEventsListId"
    }

    init {
        ensureNeverFrozen()
    }


    internal var activityEventsApi = ActivityEventsApi(
        httpClient = httpClient
    )

    /**
     * Get the activity events for this study (for the caller).
     *
     * @param studyId Study identifier
     * @return StudyActivityEventList
     */
    fun getActivityEvents(studyId: String): Flow<ResourceResult<StudyActivityEventList>> {
        return getResourceByIdAsFlow(ACTIVITY_EVENTS_LIST_ID+studyId, resourceType = ResourceType.ACTIVITY_EVENTS_LIST, remoteLoad =  { loadRemoteEvents(studyId) }, studyId = studyId)
    }

    private suspend fun loadRemoteEvents(studyId: String) : String {
        return Json.encodeToString(activityEventsApi.getActivityEventsForSelf(studyId))
    }

    /**
     * Create a new activity event for the caller in this study. The creation or update of an event
     * that triggers a study burst will update the study burst events as well, even to the point of
     * recreating study burst events that have been deleted (depending on the update type of the bursts).
     */
    suspend fun createActivityEvent(studyId: String, eventId: String, timeStamp: Instant) : Boolean {
        try {
            val eventRequest = StudyActivityEventRequest(eventId = eventId, timestamp = timeStamp)
            activityEventsApi.createActivityEvent(studyId, eventRequest)
        } catch (throwable: Throwable) {
            Logger.e("Unable to create ActivityEvent", throwable)
            return false
        }
        scheduleTimelineRepo.clearCachedSchedule(studyId)
        return true
    }

}
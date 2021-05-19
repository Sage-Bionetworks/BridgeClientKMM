package org.sagebionetworks.bridge.kmm.shared.repo

import co.touchlab.stately.ensureNeverFrozen
import io.ktor.client.*
import kotlinx.coroutines.CoroutineScope
import kotlinx.coroutines.flow.Flow
import kotlinx.serialization.encodeToString
import kotlinx.serialization.json.Json
import org.sagebionetworks.bridge.kmm.shared.apis.ActivityEventsApi
import org.sagebionetworks.bridge.kmm.shared.cache.ResourceDatabaseHelper
import org.sagebionetworks.bridge.kmm.shared.cache.ResourceResult
import org.sagebionetworks.bridge.kmm.shared.cache.ResourceType
import org.sagebionetworks.bridge.kmm.shared.cache.loadResource
import org.sagebionetworks.bridge.kmm.shared.models.StudyActivityEventList

class ActivityEventsRepo(httpClient: HttpClient, databaseHelper: ResourceDatabaseHelper, backgroundScope: CoroutineScope) :
    AbstractResourceRepo(databaseHelper, resourceType = ResourceType.ACTIVITY_EVENTS_LIST, backgroundScope) {

    companion object {
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
        return getResourceById(ACTIVITY_EVENTS_LIST_ID+studyId, remoteLoad =  { loadRemoteEvents(studyId) }, studyId = studyId)
    }

    private suspend fun loadRemoteEvents(studyId: String) : String {
        return Json.encodeToString(activityEventsApi.getActivityEventsForSelf(studyId))
    }

}
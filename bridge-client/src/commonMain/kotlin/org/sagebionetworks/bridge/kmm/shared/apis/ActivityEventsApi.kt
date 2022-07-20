/**
* Bridge Server Assessments API
*/
package org.sagebionetworks.bridge.kmm.shared.apis


import io.ktor.client.*
import org.sagebionetworks.bridge.kmm.shared.models.Message
import org.sagebionetworks.bridge.kmm.shared.models.StudyActivityEventList
import org.sagebionetworks.bridge.kmm.shared.models.StudyActivityEventRequest

internal class ActivityEventsApi(basePath: String = BASE_PATH, httpClient: HttpClient) : AbstractApi(basePath, httpClient) {

    /**
     * Get the activity events for this study (for the caller).
     *
     * @param studyId Study identifier
     * @return StudyActivityEventList
     */
    suspend fun getActivityEventsForSelf(studyId: String) : StudyActivityEventList {
        return getData("v5/studies/$studyId/participants/self/activityevents")
    }

    /**
     * Create a new activity event for the caller in this study. This call returns 201 whether the event updates or not,
     * to support concurrent and out-of-order POSTs from the client. To return 400 if an event fails to publish,
     * set the showError parameter to true. The creation or update of an event that triggers a study burst will update
     * the study burst events as well, even to the point of recreating study burst events that have been deleted
     * (depending on the update type of the bursts). To decouple these events and update the origin event without
     * changing the study burst events, set the updateBursts parameter to false.
     * Client is using server defaults:
     * showError = false
     * updateBursts = true
     */
    suspend fun createActivityEvent(studyId: String, eventRequest: StudyActivityEventRequest) : Message {
        return postData(eventRequest, "/v5/studies/$studyId/participants/self/activityevents")
    }

}

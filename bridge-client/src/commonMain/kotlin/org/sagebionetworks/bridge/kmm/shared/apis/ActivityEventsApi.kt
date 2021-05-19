/**
* Bridge Server Assessments API
*/
package org.sagebionetworks.bridge.kmm.shared.apis


import io.ktor.client.*
import org.sagebionetworks.bridge.kmm.shared.models.StudyActivityEventList

internal class ActivityEventsApi(basePath: kotlin.String = BASE_PATH, httpClient: HttpClient) : AbstractApi(basePath, httpClient) {

    /**
     * Get the activity events for this study (for the caller).
     *
     * @param studyId Study identifier
     * @return StudyActivityEventList
     */
    suspend fun getActivityEventsForSelf(studyId: kotlin.String) : StudyActivityEventList {
        return getData("v5/studies/$studyId/participants/self/activityevents")
    }

}

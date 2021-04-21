/**
* Bridge Server Assessments API
*/
package org.sagebionetworks.bridge.kmm.shared.apis


import io.ktor.client.*
import io.ktor.client.call.*
import io.ktor.client.request.*
import io.ktor.http.*
import org.sagebionetworks.bridge.kmm.shared.models.ActivityEventList
import org.sagebionetworks.bridge.kmm.shared.models.AssessmentConfig
import org.sagebionetworks.bridge.kmm.shared.models.Timeline

internal class ActivityEventsApi(basePath: kotlin.String = BASE_PATH, httpClient: HttpClient) : AbstractApi(basePath, httpClient) {

    /**
     * Get the activity events for this study (for the caller).
     *
     * @param studyId Study identifier
     * @return ActivityEventList
     */
    suspend fun getActivityEventsForSelf(studyId: kotlin.String) : ActivityEventList {
        return getData("v5/studies/$studyId/participants/self/activityEvents")
    }

}

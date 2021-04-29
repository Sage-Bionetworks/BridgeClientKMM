/**
* Bridge Server Assessments API
*/
package org.sagebionetworks.bridge.kmm.shared.apis


import io.ktor.client.*
import org.sagebionetworks.bridge.kmm.shared.models.AssessmentConfig
import org.sagebionetworks.bridge.kmm.shared.models.Timeline

internal class SchedulesV2Api(basePath: kotlin.String = BASE_PATH, httpClient: HttpClient) : AbstractApi(basePath, httpClient) {

    /**
     * Get the caller’s timeline of scheduled assessments in this study.
     * Timelines rarely change and can be large, though they are sent compressed by the server and usually compress well for transfer.
     * This method supports long-term caching by accepting an optional timestamp.
     * It will return a 304 `Not Modified` response if the schedule has not been updated after the given timestamp.
     * @param studyId Study identifier
     * @return Timeline
     */
    suspend fun getTimelineForUser(studyId: String) : Timeline {
        return getData("/v5/studies/$studyId/participants/self/timeline")
    }

}

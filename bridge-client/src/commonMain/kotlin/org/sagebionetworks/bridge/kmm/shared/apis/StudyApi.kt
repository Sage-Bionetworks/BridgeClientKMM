/**
* Bridge Server Assessments API
*/
package org.sagebionetworks.bridge.kmm.shared.apis


import io.ktor.client.*
import org.sagebionetworks.bridge.kmm.shared.models.Study
import org.sagebionetworks.bridge.kmm.shared.models.StudyInfo

internal class StudyApi(basePath: String = BASE_PATH, httpClient: HttpClient) : AbstractApi(basePath, httpClient) {

    /**
     * Get the information on a study that is useful for displaying, selecting, and signing into the study.
     *
     * @param appId App ID
     * @param studyId Study identifier
     * @return StudyInfo
     */
    suspend fun getStudyInfo(appId: String, studyId: String) : StudyInfo {
        return getData("v1/apps/$appId/studies/$studyId")
    }

    /**
     * Get a study
     * Get a study for this app.
     * @param studyId Study identifier
     * @return Study
     */
    @Suppress("UNCHECKED_CAST")
    suspend fun getStudy(studyId: String) : Study {
        return getData("v5/studies/$studyId")

    }

}

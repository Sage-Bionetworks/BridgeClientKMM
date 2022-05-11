/**
* Bridge Server Assessments API
*/
package org.sagebionetworks.bridge.kmm.shared.apis


import io.ktor.client.*
import org.sagebionetworks.bridge.kmm.shared.models.AssessmentConfig
import org.sagebionetworks.bridge.kmm.shared.models.AssessmentInfo

internal class AssessmentsApi(basePath: String = BASE_PATH, httpClient: HttpClient) : AbstractApi(basePath, httpClient) {

    /**
    * Get the JSON config for this assessment
    * 
    * @param guid A guid 
    * @return AssessmentConfig
    */
    suspend fun getAssessmentConfig(guid: String) : AssessmentConfig {
        return getData("v1/assessments/$guid/config")
    }

    /**
     * Get the JSON config for this assessment
     *
     * @param guid A guid
     * @return AssessmentConfig
     */
    suspend fun getAssessmentConfig(assessmentInfo: AssessmentInfo) : AssessmentConfig {
        return getData(assessmentInfo.configPath)
    }

}

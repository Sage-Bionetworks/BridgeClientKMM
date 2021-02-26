/**
* Bridge Server Assessments API
*/
package org.sagebionetworks.bridge.kmm.shared.apis


import io.ktor.client.*
import org.sagebionetworks.bridge.kmm.shared.models.AssessmentConfig

internal class AssessmentsApi(basePath: kotlin.String = BASE_PATH, httpClient: HttpClient) : AbstractApi(basePath, httpClient) {

    /**
    * Get the JSON config for this assessment
    * 
    * @param guid A guid 
    * @return AssessmentConfig
    */
    suspend fun getAssessmentConfig(guid: kotlin.String) : AssessmentConfig {
        return getData("v1/assessments/$guid/config")
    }

}

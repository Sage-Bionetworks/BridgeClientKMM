/**
* Bridge Server Assessments API
*/
package org.sagebionetworks.bridge.kmm.shared.apis


import io.ktor.client.*
import org.sagebionetworks.bridge.kmm.shared.models.AssessmentConfig

// TODO: syoung 11/25/2020 Should the endpoint be a global constant?

internal class AssessmentsApi(basePath: kotlin.String = "https://webservices.sagebridge.org", httpClient: HttpClient) : AbstractApi() {
    override val _basePath = basePath
    override val _httpClient = httpClient


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

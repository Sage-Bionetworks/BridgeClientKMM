/**
* Bridge Server Assessments API
*/
package org.sagebionetworks.bridge.kmm.shared.apis


import io.ktor.client.*
import org.sagebionetworks.bridge.kmm.shared.models.Assessment
import org.sagebionetworks.bridge.kmm.shared.models.AssessmentConfig
import org.sagebionetworks.bridge.kmm.shared.models.AssessmentInfo
import org.sagebionetworks.bridge.kmm.shared.models.AssessmentList

class AssessmentsApi(basePath: String = BASE_PATH, httpClient: HttpClient) : AbstractApi(basePath, httpClient) {

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

    /**
     * Get a specific assessment revision.
     * A GUID uniquely identifies a specific assessment revision.
     * @param guid A guid
     * @return Assessment
     */
    suspend fun getAssessmentByGUID(guid: String) : Assessment {
        return getData("v1/assessments/$guid")
    }

    /**
     * Get assessments in the app context.
     * This is a paged API that can be filtered by the categories and tags assigned to assessments. The most recent (highest) revision of each assessment is returned in the API.
     * @param offsetBy next page start offset for pagination (optional, default to 0)
     * @param pageSize maximum number of records in each returned page (optional, default to 50)
     * @param tag One or more tags. Every resource that has at least one of the tags will be returned (resources do not need to match all tags). (optional)
     * @param includeDeleted Should deleted items be returned in results? (optional, default to false)
     * @return AssessmentListComposed
     */
    suspend fun getAssessments(offsetBy: Int? = 0, pageSize: Int? = 100, tag:String? = null, includeDeleted: Boolean? = false) : AssessmentList {
        val parameters = mutableMapOf<String, String>()
        with(parameters) {
            offsetBy?.let { put("offsetBy", it.toString()) }
            pageSize?.let { put("pageSize", it.toString()) }
            tag?.let { put("tag", it) }
            includeDeleted?.let { put("includeDeleted", it.toString()) }
        }
        return getData("v1/assessments", queryParams = parameters)
    }

    /**
     * Update an assessment revision.
     * A GUID uniquely identifies a specific assessment revision. Only members of the organization that own this assessment can update it. This operation returns the updated assessment revision.
     * @param guid A guid
     * @param assessment Updated assessment
     * @return Assessment
     */
    suspend fun updateAssessment(guid: String, assessment: Assessment) : Assessment {
        return postData(assessment, "v1/assessments/$guid" )
    }

}

/**
* Bridge Server Assessments API
*/
package org.sagebionetworks.bridge.kmm.shared.apis


import io.ktor.client.*
import io.ktor.client.call.*
import io.ktor.client.request.*
import io.ktor.http.*
import kotlinx.datetime.TimeZone
import org.sagebionetworks.bridge.kmm.shared.models.*

internal class AdminApis(basePath: String = BASE_PATH, httpClient: HttpClient) : AbstractApi(basePath, httpClient) {


    suspend fun getStudyParticipantTimeline(studyId: String, userId: String) : ParticipantSchedule {
        return getData("v5/studies/$studyId/participants/$userId/schedule")
    }

    /**
     * Get information about the last request made by this participant
     *
     * @param studyId Study identifier
     * @param userId User ID
     * @return RequestInfo
     */
    suspend fun getStudyParticipantRequestInfo(studyId: String, userId: String) : RequestInfo {
        return getData("v5/studies/$studyId/participants/$userId/requestInfo")
    }


    /**
     * Search for adherence records.
     *
     * @param studyId Study identifier
     * @param userId User identifier
     * @param adherenceRecordsSearch The search criteria.
     * @return AdherenceRecordList
     */
    suspend fun searchForAdherenceRecords(studyId: String, userId: String, adherenceRecordsSearch: AdherenceRecordsSearch) : AdherenceRecordList {
        return postData(adherenceRecordsSearch, "v5/studies/$studyId/participants/$userId/adherence/search")

    }

    /**
     * Get a study participant’s upload history
     * Retrieve information about the uploads from a user. This is particularly useful during development to verify the mobile application is sending valid data back to the Bridge server. The API can retrieve any number of days worth of upload records, defined by the startTime and endTime timestamps (ISO 8601 format), and paginated using a pageSize and offsetKey value (null for the first page, but returned with subsequent requests to retrieve further pages in the time range). If the endTime is not provided, it will be one day after the startTime. If the startTime is not provided, it will be one day before the endTime.
     * @param studyId Study identifier
     * @param userId User ID
     * @param startTime
     * @param endTime
     * @param pageSize maximum number of records in each returned page (optional, default to 50)
     * @param offsetKey next page start key for pagination (optional)
     * @return UploadListComposed
     */
    @Suppress("UNCHECKED_CAST")
    suspend fun getStudyParticipantUploads(studyId: String, userId: String, startTime: String, endTime: String, pageSize: Int?, offsetKey: String?) : UploadList {
        val parametersMap = mutableMapOf<String, String>()
        with(parametersMap) {
            put("startTime", startTime.toString())
            put("endTime", endTime.toString())
            pageSize?.let { put("pageSize", it.toString()) }
            offsetKey?.let { put("offsetKey", it.toString()) }
        }
        return getData("v5/studies/$studyId/participants/$userId/uploads", queryParams = parametersMap)
    }

    /**
     * Get the enrollments in this study. These include participants who have been withdrawn from the study (as we continue to document their historic participation).
     *
     * @param studyId Study identifier
     * @param enrollmentFilter Filter enrollees (optional)
     * @param includeTesters Include accounts with &#39;test_user&#39; data group (optional, default to false)
     * @param offsetBy next page start offset for pagination (optional, default to 0)
     * @param pageSize maximum number of records in each returned page (optional, default to 50)
     * @return EnrollmentDetailListComposed
     */
    @Suppress("UNCHECKED_CAST")
    suspend fun getEnrollments(studyId: String, enrollmentFilter: String?, includeTesters: Boolean?, offsetBy: Int?, pageSize: Int?) : EnrollmentDetailList {
        val parametersMap = mutableMapOf<String, String>()
        with(parametersMap) {
            enrollmentFilter?.let { put("enrollmentFilter", it.toString()) }
            includeTesters?.let { put("includeTesters", it.toString()) }
            offsetBy?.let { put("offsetBy", it.toString()) }
            pageSize?.let { put("pageSize", it.toString()) }
        }
        return getData("v5/studies/$studyId/enrollments", queryParams = parametersMap)
    }

}

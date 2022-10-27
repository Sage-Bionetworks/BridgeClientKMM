/**
* Bridge Server Assessments API
*/
package org.sagebionetworks.bridge.kmm.shared.apis


import io.ktor.client.*
import io.ktor.client.request.*
import io.ktor.http.*
import kotlinx.datetime.Instant
import org.sagebionetworks.bridge.kmm.shared.models.*
import org.sagebionetworks.bridge.kmm.shared.models.Message

internal class ParticipantApi(basePath: String = BASE_PATH, httpClient: HttpClient) : AbstractApi(basePath, httpClient) {


    /**
     * Save a participant data record
     * Save a participant record. If a record exists with the given identifier, it will be replaced with this record. Note that this call requires consent and authentication.
     * @param identifier identifier
     * @param participantData
     * @return Message
     */
    suspend fun saveDataForSelf(identifier: String, participantData: ParticipantData) : Message {
        return postData(participantData, "v3/users/self/data/$identifier")
    }

    /**
     * Get user's data based on the given identifier
     * Get the participant data record based on the given identifier. Participants can get reports for their own account. Note that this call does require consent and authentication.
     * @param identifier identifier
     * @return ParticipantData
     */
    suspend fun getDataByIdentifierForSelf(identifier: String) : ParticipantData {
        return getData("v3/users/self/data/$identifier")
    }

    //This endpoint is probably not needed as the UserSessionInfo object returned as part of sign-in
    //has almost all the data found in a StudyParticipant
    /**
     * Get user's participant record
     * Get the current user's participant record. Any authenticated user may call this endpoint. **The user does not need to have consented a study in the app in order to access their participant record.**
     * @param consents Should consent histories be included with this participant record? (optional)
     * @return StudyParticipant
     */
    suspend fun getUsersParticipantRecord(consents: Boolean = false) : StudyParticipant {
        val params = mapOf("consents" to consents.toString())
        return getData("v3/participants/self", queryParams = params)
    }

    /**
     * Update user's participant record
     * Update the current user's participant record. **Unlike most other calls in this API, you can send partically complete JSON to this endpoint,** and it will selectively update the participant&#39;s record (rather than treating missing properties as an instruction to delete those fields in the record). This means that many existing APIs that sent a single update value, can direct those payloads to this endpoint and they will still work fine. For this reason most &#x60;/v3/users/_*&#x60; endpoints are now deprecated, though there is no plan to remove them. Any authenticated user may call this endpoint. **The user does not need to have consented to a study in the app in order to update their participant
     * @param studyParticipant Study participant
     * @return UserSessionInfo
     */
    suspend fun updateUsersParticipantRecord(studyParticipant: StudyParticipant) : UserSessionInfo {
        return postData(studyParticipant, "v3/participants/self")
    }

    /**
     * Get a series of report records for a specific date and time range for the caller (this API uses dates and times and not just dates; use a standard time of day portion like “T00:00:00.000Z” if a time portion is unnecessary, being sure to create and retrieve records with the same set time).
     *
     * @param studyId Study identifier
     * @param identifier identifier
     * @param startTime
     * @param endTime
     * @param offsetKey next page start key for pagination (optional)
     * @param pageSize maximum number of records in each returned page (optional, default to 50)
     * @return ForwardCursorReportDataListComposed
     */
    suspend fun getUsersStudyParticipantReport(studyId: String, identifier: String, startTime: Instant, endTime: Instant, offsetKey: String?, pageSize: Int?) : ForwardCursorReportDataList {
        val parameters = mutableMapOf<String, String>()
        with(parameters) {
            put("startTime", startTime.toString())
            put("endTime", endTime.toString())
            offsetKey?.let { put("offsetKey", it) }
            pageSize?.let { put("pageSize", it.toString()) }
        }
        return getData("v5/studies/$studyId/participants/self/reports/$identifier", queryParams = parameters)
    }

    /**
     * Add a participant report for a single date and time for the caller (this API uses dates and times and not just dates; use a standard time of day portion like “T00:00:00.000Z” if a time portion is unnecessary, being sure to create and retrieve records with the same set time).
     *
     * @param studyId Study identifier
     * @param identifier identifier
     * @param reportData
     * @return Message
     */
    suspend fun saveUsersStudyParticipantReportRecord(studyId: String, identifier: String, reportData: ReportData) : Message {
        return postData( reportData,"v5/studies/$studyId/participants/self/reports/$identifier")
    }



}


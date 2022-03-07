/**
* Bridge Server Assessments API
*/
package org.sagebionetworks.bridge.kmm.shared.apis


import io.ktor.client.*
import org.sagebionetworks.bridge.kmm.shared.models.Message
import org.sagebionetworks.bridge.kmm.shared.models.ParticipantData
import org.sagebionetworks.bridge.kmm.shared.models.StudyParticipant
import org.sagebionetworks.bridge.kmm.shared.models.UserSessionInfo

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

}


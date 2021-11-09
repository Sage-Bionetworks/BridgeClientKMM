/**
* Bridge Server Assessments API
*/
package org.sagebionetworks.bridge.kmm.shared.apis


import io.ktor.client.*
import io.ktor.client.call.*
import io.ktor.client.request.*
import io.ktor.http.*
import org.sagebionetworks.bridge.kmm.shared.models.*
import org.sagebionetworks.bridge.kmm.shared.models.AdherenceRecordList
import org.sagebionetworks.bridge.kmm.shared.models.AdherenceRecordUpdates
import org.sagebionetworks.bridge.kmm.shared.models.Message

internal class SchedulesV2Api(basePath: String = BASE_PATH, httpClient: HttpClient) : AbstractApi(basePath, httpClient) {

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

    /**
     * Search for adherence records.
     *
     * @param studyId Study identifier
     * @param adherenceRecordsSearch The search criteria.
     * @return AdherenceRecordList
     */
    suspend fun searchForAdherenceRecords(studyId: String, adherenceRecordsSearch: AdherenceRecordsSearch) : AdherenceRecordList {
        return postData(adherenceRecordsSearch, "v5/studies/$studyId/participants/self/adherence/search")

    }

    /**
     * Create or update one or more adherence records.
     *
     * @param studyId Study identifier
     * @param adherenceRecord One ore more adherence records
     * @return Message
     */
    suspend fun updateAdherenceRecords(studyId: String, records: List<AdherenceRecord>) : Message {
        val adherenceRecord = AdherenceRecordUpdates(records)
        return postData(adherenceRecord,"v5/studies/$studyId/participants/self/adherence")
    }


}

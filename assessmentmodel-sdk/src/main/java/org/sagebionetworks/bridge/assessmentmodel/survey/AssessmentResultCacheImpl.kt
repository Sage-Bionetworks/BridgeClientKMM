package org.sagebionetworks.bridge.assessmentmodel.survey

import kotlinx.datetime.Instant
import kotlinx.datetime.TimeZone
import kotlinx.datetime.toLocalDateTime
import kotlinx.serialization.json.Json
import kotlinx.serialization.json.decodeFromJsonElement
import kotlinx.serialization.json.encodeToJsonElement
import org.sagebionetworks.assessmentmodel.AssessmentResult
import org.sagebionetworks.bridge.kmm.shared.cache.LocalJsonDataCache

//TODO: Implement AssessmentResultCache interface once AssessmentModel is ready -nbrown 05/18/2022
class AssessmentResultCacheImpl (private val jsonDataCache: LocalJsonDataCache) { // : AssessmentResultCache {

    fun loadAssessmentResult(instanceGuid: String, jsonCoder: Json) : AssessmentResult? {
        val data = jsonDataCache.loadData(instanceGuid, TYPE_ASSESSMENT_RESULT)
        data?.let {
            return jsonCoder.decodeFromJsonElement(it.json)
        }
        return null
    }

    fun storeAssessmentResult(instanceGuid: String, result: AssessmentResult, jsonCoder: Json, expire: Instant?) {
        jsonDataCache.storeData(
            id = instanceGuid,
            dataType = TYPE_ASSESSMENT_RESULT,
            data = jsonCoder.encodeToJsonElement(result),
            expire = expire?.toLocalDateTime(TimeZone.currentSystemDefault())
        )
    }

    fun clearExpiredAssessmentResults() {
        jsonDataCache.removeExpiredData()
    }

    companion object {
        private const val TYPE_ASSESSMENT_RESULT = "TypeAssessmentResult"
    }

}
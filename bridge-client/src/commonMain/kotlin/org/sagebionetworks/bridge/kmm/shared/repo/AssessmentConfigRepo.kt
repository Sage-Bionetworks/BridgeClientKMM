package org.sagebionetworks.bridge.kmm.shared.repo

import co.touchlab.stately.ensureNeverFrozen
import io.ktor.client.*
import kotlinx.coroutines.CoroutineScope
import kotlinx.coroutines.flow.Flow
import kotlinx.coroutines.flow.map
import kotlinx.serialization.encodeToString
import kotlinx.serialization.json.Json
import org.sagebionetworks.bridge.kmm.shared.apis.AssessmentsApi
import org.sagebionetworks.bridge.kmm.shared.cache.*
import org.sagebionetworks.bridge.kmm.shared.cache.ResourceDatabaseHelper.Companion.APP_WIDE_STUDY_ID
import org.sagebionetworks.bridge.kmm.shared.models.AssessmentConfig
import org.sagebionetworks.bridge.kmm.shared.models.AssessmentInfo

class AssessmentConfigRepo(httpClient: HttpClient, databaseHelper: ResourceDatabaseHelper, backgroundScope: CoroutineScope) :
    AbstractResourceRepo(databaseHelper, backgroundScope) {

    init {
        ensureNeverFrozen()
    }


    internal var assessmentsApi = AssessmentsApi(
        httpClient = httpClient
    )

    /**
     * Load [AssessmentConfig] from local cache using Assessment GUID.
     * Using [ScheduleTimelineRepo] to load participant's schedule will trigger a call to [loadAndCacheConfigs]
     * with all [AssessmentInfo]s that are part of the schedule.
     */
    fun getCachedAssessmentConfigByGuidAsFlow(guid: String) : Flow<ResourceResult<AssessmentConfig>> {
        return database.getResourceAsFlow(guid, ResourceType.ASSESSMENT_CONFIG, APP_WIDE_STUDY_ID).map { processResult(it)}
    }

    fun getCachedAssessmentConfigByGuid(guid: String) : AssessmentConfig? {
        return database.getResource(guid, ResourceType.ASSESSMENT_CONFIG, APP_WIDE_STUDY_ID)?.loadResource()
    }

    fun hasCachedAssessmentConfigByGuid(guid: String) : Boolean {
        return database.getResource(guid, ResourceType.ASSESSMENT_CONFIG, APP_WIDE_STUDY_ID) != null
    }

    /**
     * Load [AssessmentConfig] using [AssessmentInfo]. This will trigger a remote call to load from
     * Bridge server when necessary.
     */
    fun getAssessmentConfig(assessmentInfo: AssessmentInfo): Flow<ResourceResult<AssessmentConfig>> {
        return getResourceById(
            identifier = assessmentInfo.guid,
            secondaryId = assessmentInfo.identifier,
            resourceType = ResourceType.ASSESSMENT_CONFIG,
            remoteLoad = { loadRemoteAssessmentConfig(assessmentInfo) },
            studyId = APP_WIDE_STUDY_ID
        )
    }

    private suspend fun loadRemoteAssessmentConfig(assessmentInfo: AssessmentInfo) : String {
        return Json.encodeToString(assessmentsApi.getAssessmentConfig(assessmentInfo))
    }

    suspend fun loadAndCacheConfigs(assessmentInfos: List<AssessmentInfo>) {
        for (assessment in assessmentInfos) {
            val curResource = database.getResource(assessment.guid, ResourceType.ASSESSMENT_CONFIG, APP_WIDE_STUDY_ID)
            remoteLoadResource(
                database = database,
                identifier = assessment.guid,
                secondaryId = assessment.identifier,
                resourceType = ResourceType.ASSESSMENT_CONFIG,
                studyId = APP_WIDE_STUDY_ID,
                curResource = curResource,
                remoteLoad = {loadRemoteAssessmentConfig(assessment)}
                )
        }
    }

}
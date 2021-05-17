package org.sagebionetworks.bridge.kmm.shared.repo

import co.touchlab.stately.ensureNeverFrozen
import io.ktor.client.*
import kotlinx.coroutines.CoroutineScope
import kotlinx.coroutines.flow.Flow
import kotlinx.serialization.encodeToString
import kotlinx.serialization.json.Json
import org.sagebionetworks.bridge.kmm.shared.apis.AssessmentsApi
import org.sagebionetworks.bridge.kmm.shared.cache.ResourceDatabaseHelper
import org.sagebionetworks.bridge.kmm.shared.cache.ResourceDatabaseHelper.Companion.APP_WIDE_STUDY_ID
import org.sagebionetworks.bridge.kmm.shared.cache.ResourceResult
import org.sagebionetworks.bridge.kmm.shared.cache.ResourceType
import org.sagebionetworks.bridge.kmm.shared.models.AssessmentConfig

class AssessmentConfigRepo(httpClient: HttpClient, databaseHelper: ResourceDatabaseHelper, backgroundScope: CoroutineScope) :
    AbstractResourceRepo(databaseHelper, resourceType = ResourceType.ASSESSMENT_CONFIG, backgroundScope) {

    init {
        ensureNeverFrozen()
    }


    internal var assessmentsApi = AssessmentsApi(
        httpClient = httpClient
    )

    fun getAssessmentById(identifier: String): Flow<ResourceResult<AssessmentConfig>> {
        return getResourceById(identifier, remoteLoad =  { loadRemoteAssessmentConfig(identifier) },
            studyId = APP_WIDE_STUDY_ID
        )
    }

    private suspend fun loadRemoteAssessmentConfig(identifier: String) : String {
        return Json.encodeToString(assessmentsApi.getAssessmentConfig(identifier))
    }

}
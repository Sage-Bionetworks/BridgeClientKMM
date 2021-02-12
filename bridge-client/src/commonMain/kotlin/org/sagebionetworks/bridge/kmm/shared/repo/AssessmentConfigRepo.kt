package org.sagebionetworks.bridge.kmm.shared.repo

import co.touchlab.stately.ensureNeverFrozen
import io.ktor.client.features.*
import io.ktor.http.*
import io.ktor.util.network.*
import kotlinx.coroutines.CoroutineScope
import kotlinx.coroutines.flow.Flow
import kotlinx.coroutines.flow.filter
import kotlinx.coroutines.flow.map
import kotlinx.coroutines.launch
import kotlinx.datetime.Clock
import kotlinx.serialization.encodeToString
import kotlinx.serialization.json.Json
import org.sagebionetworks.bridge.kmm.shared.apis.AssessmentsApi
import org.sagebionetworks.bridge.kmm.shared.apis.DefaultHttpClient
import org.sagebionetworks.bridge.kmm.shared.cache.*
import org.sagebionetworks.bridge.kmm.shared.cache.ResourceDatabaseHelper
import org.sagebionetworks.bridge.kmm.shared.models.AssessmentConfig

class AssessmentConfigRepo(databaseDriverFactory: DbDriverFactory, backgroundScope: CoroutineScope) :
    AbstractResourceRepo(databaseDriverFactory, resourceType = ResourceType.ASSESSMENT_CONFIG, backgroundScope) {

    init {
        ensureNeverFrozen()
    }


    internal var assessmentsApi = AssessmentsApi(
        httpClient = DefaultHttpClient.httpClient
    )

    fun getAssessmentById(identifier: String): Flow<ResourceResult<AssessmentConfig>> {
        return getResourceById(identifier, remoteLoad =  { loadRemoteAssessmentConfig(identifier) })
    }

    private suspend fun loadRemoteAssessmentConfig(identifier: String) : String {
        return Json.encodeToString(assessmentsApi.getAssessmentConfig(identifier))
    }

}
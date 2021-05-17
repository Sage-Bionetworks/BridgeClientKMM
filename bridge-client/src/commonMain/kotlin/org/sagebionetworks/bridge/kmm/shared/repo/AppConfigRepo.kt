package org.sagebionetworks.bridge.kmm.shared.repo

import co.touchlab.stately.ensureNeverFrozen
import io.ktor.client.*
import kotlinx.coroutines.CoroutineScope
import kotlinx.coroutines.flow.Flow
import kotlinx.serialization.encodeToString
import kotlinx.serialization.json.Json
import org.sagebionetworks.bridge.kmm.shared.apis.PublicApi
import org.sagebionetworks.bridge.kmm.shared.cache.ResourceDatabaseHelper
import org.sagebionetworks.bridge.kmm.shared.cache.ResourceResult
import org.sagebionetworks.bridge.kmm.shared.cache.ResourceType
import org.sagebionetworks.bridge.mpp.network.generated.models.AppConfig

class AppConfigRepo(httpClient: HttpClient, databaseHelper: ResourceDatabaseHelper, backgroundScope: CoroutineScope) :
    AbstractResourceRepo(databaseHelper, resourceType = ResourceType.APP_CONFIG, backgroundScope) {

    init {
        ensureNeverFrozen()
    }


    internal var publicApi = PublicApi(
        httpClient = httpClient
    )

    fun getAppConfig(appId: String): Flow<ResourceResult<AppConfig>> {
        return getResourceById(identifier = appId, remoteLoad = { loadRemoteAppConfig(appId) }, studyId =  ResourceDatabaseHelper.APP_WIDE_STUDY_ID)
    }

    private suspend fun loadRemoteAppConfig(appId: String) : String {
        return Json.encodeToString(publicApi.getConfigForApp(appId))
    }

}
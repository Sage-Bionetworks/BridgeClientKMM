package org.sagebionetworks.bridge.kmm.shared.repo

import co.touchlab.stately.ensureNeverFrozen
import kotlinx.coroutines.CoroutineScope
import kotlinx.coroutines.flow.Flow
import kotlinx.serialization.encodeToString
import kotlinx.serialization.json.Json
import org.sagebionetworks.bridge.kmm.shared.apis.DefaultHttpClient
import org.sagebionetworks.bridge.kmm.shared.apis.PublicApi
import org.sagebionetworks.bridge.kmm.shared.cache.DbDriverFactory
import org.sagebionetworks.bridge.kmm.shared.cache.ResourceResult
import org.sagebionetworks.bridge.kmm.shared.cache.ResourceType
import org.sagebionetworks.bridge.mpp.network.generated.models.AppConfig

class AppConfigRepo(databaseDriverFactory: DbDriverFactory, backgroundScope: CoroutineScope) :
    AbstractResourceRepo(databaseDriverFactory, resourceType = ResourceType.APP_CONFIG, backgroundScope) {

    init {
        ensureNeverFrozen()
    }


    internal var publicApi = PublicApi(
        httpClient = DefaultHttpClient.httpClient
    )

    fun getAppConfig(appId: String): Flow<ResourceResult<AppConfig>> {
        return getResourceById(appId, { loadRemoteAppConfig(appId) })
    }

    private suspend fun loadRemoteAppConfig(appId: String) : String {
        return Json.encodeToString(publicApi.getConfigForApp(appId))
    }

}
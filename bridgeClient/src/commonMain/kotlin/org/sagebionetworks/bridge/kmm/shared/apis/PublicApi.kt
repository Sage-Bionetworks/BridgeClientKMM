/**
* Bridge Server Public API
*/
package org.sagebionetworks.bridge.kmm.shared.apis


import io.ktor.client.*
import io.ktor.client.call.*
import io.ktor.client.request.*
import io.ktor.http.*
import org.sagebionetworks.bridge.kmm.shared.models.AssessmentConfig
import org.sagebionetworks.bridge.mpp.network.generated.models.AppConfig

internal class PublicApi(basePath: kotlin.String = BASE_PATH, httpClient: HttpClient) : AbstractApi(basePath, httpClient) {

    /**
     * Get the config for the current version of the app making the request.
     * Although this call uses Bridge&#39;s common filtering framework (see https://developer.sagebridge.org/articles/study_design.html#filtering), the request does not require authentication, so only User-Agent and Accept-Language filtering criteria are used.
     * @param appId App ID
     * @return AppConfig
     */
    @Suppress("UNCHECKED_CAST")
    suspend fun getConfigForApp(appId: String) : AppConfig {
        return getData("v1/apps/$appId/appconfig")
    }

}

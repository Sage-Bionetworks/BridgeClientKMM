package org.sagebionetworks.bridge.kmm.shared.repo

import io.ktor.client.*
import org.sagebionetworks.bridge.kmm.shared.apis.ConsentApi
import org.sagebionetworks.bridge.kmm.shared.models.ConsentSignature
import org.sagebionetworks.bridge.kmm.shared.models.SharingScope
import org.sagebionetworks.bridge.kmm.shared.models.UserSessionInfo

class ConsentRepo(httpClient: HttpClient) {

    private val consentApi = ConsentApi(
        httpClient = httpClient
    )

    suspend fun createConsentSignature(
        subpopulationGuid: String,
        scope: SharingScope = SharingScope.ALL_QUALIFIED_RESEARCHERS
    ): UserSessionInfo {

        val consentSignature = ConsentSignature("Name", scope = scope)

        return consentApi.createConsentSignature(subpopulationGuid, consentSignature)
    }

}
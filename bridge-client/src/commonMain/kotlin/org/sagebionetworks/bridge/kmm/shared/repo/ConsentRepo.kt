package org.sagebionetworks.bridge.kmm.shared.repo

import org.sagebionetworks.bridge.kmm.shared.apis.ConsentApi
import org.sagebionetworks.bridge.kmm.shared.apis.DefaultHttpClient
import org.sagebionetworks.bridge.kmm.shared.models.ConsentSignature
import org.sagebionetworks.bridge.kmm.shared.models.SharingScope
import org.sagebionetworks.bridge.kmm.shared.models.UserSessionInfo

class ConsentRepo {

    private val consentApi = ConsentApi(
        httpClient = DefaultHttpClient.httpClient
    )

    suspend fun createConsentSignature(subpopulationGuid: String, scope: SharingScope = SharingScope.ALL_QUALIFIED_RESEARCHERS) : UserSessionInfo {

        val consentSignature = ConsentSignature("Name", scope = scope)

        val userSession = consentApi.createConsentSignature(subpopulationGuid, consentSignature)
        return userSession
    }

}
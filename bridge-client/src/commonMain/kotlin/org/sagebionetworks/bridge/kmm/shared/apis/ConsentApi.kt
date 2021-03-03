package org.sagebionetworks.bridge.kmm.shared.apis

import io.ktor.client.*
import org.sagebionetworks.bridge.kmm.shared.models.ConsentSignature
import org.sagebionetworks.bridge.kmm.shared.models.UserSessionInfo

internal class ConsentApi(basePath: kotlin.String = BASE_PATH, httpClient: HttpClient): AbstractApi(basePath, httpClient) {

    /**
     * Consent to this subpopulation by submitting a signature
     * Agree to the terms of participant represented by this subpopulation, by submitting a  signature to the Bridge server.
     * @param subpopulationGuid Subpopulation GUID
     * @param consentSignature A consent signature
     * @return UserSessionInfo
     */
    suspend fun createConsentSignature(subpopulationGuid: kotlin.String, consentSignature: ConsentSignature) : UserSessionInfo {
        val path = "v3/subpopulations/$subpopulationGuid/consents/signature"
        return postData(consentSignature, path)
    }


}
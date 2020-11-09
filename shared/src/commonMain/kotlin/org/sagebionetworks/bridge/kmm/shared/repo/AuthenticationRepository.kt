package org.sagebionetworks.bridge.kmm.shared.repo

import org.sagebionetworks.bridge.kmm.shared.apis.AuthenticationApi
import org.sagebionetworks.bridge.kmm.shared.cache.AccountDAO
import org.sagebionetworks.bridge.kmm.shared.models.SignIn
import org.sagebionetworks.bridge.kmm.shared.models.UserSessionInfo

class AuthenticationRepository {

    val accountDAO = AccountDAO()

    suspend fun signIn(email: String, password: String) : UserSessionInfo {
        val authApi = AuthenticationApi()
        val signIn = SignIn(
            accountDAO.appId,
            email,
            password = password,
        )
        val userSession = authApi.signIn(signIn)
        accountDAO.email = userSession.email
        accountDAO.sessionToken = userSession.sessionToken
        accountDAO.reauthToken = userSession.reauthToken

        if (!userSession.consented) {
            ConsentRepo().createConsentSignature("sage-assessment-test")
        }

        return userSession
    }

}
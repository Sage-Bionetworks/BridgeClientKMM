package org.sagebionetworks.bridge.kmm.shared.repo

import org.sagebionetworks.bridge.kmm.shared.BridgeConfig
import org.sagebionetworks.bridge.kmm.shared.apis.AuthenticationApi
import org.sagebionetworks.bridge.kmm.shared.cache.AccountDAO
import org.sagebionetworks.bridge.kmm.shared.models.SignIn
import org.sagebionetworks.bridge.kmm.shared.models.UserSessionInfo

class AuthenticationRepository(val bridgeConfig: BridgeConfig) {

    val accountDAO = AccountDAO()

    suspend fun signIn(email: String, password: String) : UserSessionInfo {
        val authApi = AuthenticationApi()
        val signIn = SignIn(
            bridgeConfig.appId,
            email,
            password = password,
        )
        val userSession = authApi.signIn(signIn)
        accountDAO.email = userSession.email
        accountDAO.sessionToken = userSession.sessionToken
        accountDAO.reauthToken = userSession.reauthToken

        // TODO: syoung 11/25/2020 Is this test code to get around consenting the user? Should it be here? And if so, please add a comment. Thanks!
//        if (!userSession.consented) {
//            ConsentRepo().createConsentSignature("sage-assessment-test")
//        }

        return userSession
    }

    suspend fun reAuth() : Boolean {
        val accountDAO = AccountDAO()
        return accountDAO.reauthToken?.let {
            val signIn = SignIn(
                bridgeConfig.appId,
                accountDAO.email,
                reauthToken = accountDAO.reauthToken
            )
            val authApi = AuthenticationApi()
            val userSession = authApi.reauthenticate(signIn)
            authApi.close()
            accountDAO.sessionToken = userSession.sessionToken
            accountDAO.reauthToken = userSession.reauthToken
            true
        } ?: false
    }

}
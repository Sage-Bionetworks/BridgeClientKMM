package org.sagebionetworks.bridge.kmm.shared.repo

import kotlinx.coroutines.flow.Flow
import kotlinx.coroutines.flow.map
import kotlinx.datetime.Clock
import kotlinx.serialization.encodeToString
import kotlinx.serialization.json.Json
import org.sagebionetworks.bridge.kmm.shared.BridgeConfig
import org.sagebionetworks.bridge.kmm.shared.apis.AuthenticationApi
import org.sagebionetworks.bridge.kmm.shared.cache.*
import org.sagebionetworks.bridge.kmm.shared.models.SignIn
import org.sagebionetworks.bridge.kmm.shared.models.UserSessionInfo

class AuthenticationRepository(val bridgeConfig: BridgeConfig, val database: ResourceDatabaseHelper) {

    companion object {
        const val USER_SESSION_ID = "UserSessionId"
    }

    /**
     * Get the current [UserSessionInfo] object as a Flow. The flow will emit a new value whenever
     * the session is updated. This allows observers to watch for changes to authentication or
     * consent status.
     */
    fun sessionAsFlow() : Flow<UserSessionInfo?> {
        return database.getResourceAsFlow(USER_SESSION_ID).map { curResource -> curResource?.loadResource() }
    }

    /**
     * Get the current [UserSessionInfo] object.
     */
    fun session() : UserSessionInfo? {
        return database.getResource(USER_SESSION_ID)?.loadResource()
    }

    fun isAuthenticated() : Boolean {
        return session()?.authenticated ?: false
    }

    suspend fun signInExternalId(externalId: String, password: String) : UserSessionInfo {
        val signIn = SignIn(
            bridgeConfig.appId,
            externalId = externalId,
            password = password,
        )
        return signIn(signIn)
    }

    suspend fun signInEmail(email: String, password: String) : UserSessionInfo {
        val signIn = SignIn(
            appId = bridgeConfig.appId,
            email = email,
            password = password,
        )
        return signIn(signIn)
    }

    private suspend fun signIn(signIn: SignIn) : UserSessionInfo {
        val authApi = AuthenticationApi()
        val userSession = authApi.signIn(signIn)
        updateCachedSession(null, userSession)
        return userSession
    }

    suspend fun reAuth() : Boolean {
        val sessionInfo = session()
        //val accountDAO = AccountDAO()
        return sessionInfo?.reauthToken?.let {
            val signIn = SignIn(
                appId = bridgeConfig.appId,
                email = sessionInfo.email,
                externalId = sessionInfo.externalId,
                reauthToken = it
            )
            val authApi = AuthenticationApi()
            val userSession = authApi.reauthenticate(signIn)
            authApi.close()
            //TODO: Handle failure cases, currently errors result in an empty UserSessionInfo -nbrown 02/23/2021
            updateCachedSession(sessionInfo, userSession)
            true
        } ?: false
    }

    private fun updateCachedSession(oldUserSessionInfo: UserSessionInfo?, newUserSession: UserSessionInfo) {
        var toCacheSession = newUserSession
        if (newUserSession.reauthToken == null && oldUserSessionInfo?.reauthToken != null) {
            toCacheSession = newUserSession.copy(reauthToken = oldUserSessionInfo.reauthToken)
        }
        var resource = Resource(
            USER_SESSION_ID,
            ResourceType.USER_SESSION_INFO,
            Json.encodeToString(toCacheSession),
            Clock.System.now().toEpochMilliseconds(),
            ResourceStatus.SUCCESS
        )
        database.insertUpdateResource(resource)
    }

}
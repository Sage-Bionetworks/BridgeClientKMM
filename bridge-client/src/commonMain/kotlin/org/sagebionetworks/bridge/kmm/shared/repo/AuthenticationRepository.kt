package org.sagebionetworks.bridge.kmm.shared.repo

import io.ktor.client.*
import io.ktor.client.features.*
import io.ktor.http.*
import kotlinx.coroutines.flow.Flow
import kotlinx.coroutines.flow.map
import kotlinx.datetime.Clock
import kotlinx.serialization.encodeToString
import kotlinx.serialization.json.Json
import org.sagebionetworks.bridge.kmm.shared.BridgeConfig
import org.sagebionetworks.bridge.kmm.shared.apis.AuthenticationApi
import org.sagebionetworks.bridge.kmm.shared.cache.*
import org.sagebionetworks.bridge.kmm.shared.cache.ResourceDatabaseHelper.Companion.APP_WIDE_STUDY_ID
import org.sagebionetworks.bridge.kmm.shared.models.SignIn
import org.sagebionetworks.bridge.kmm.shared.models.UserSessionInfo

class AuthenticationRepository(httpClient: HttpClient, val bridgeConfig: BridgeConfig, val database: ResourceDatabaseHelper) {

    internal companion object {
        const val USER_SESSION_ID = "UserSessionId"
    }

    private val authenticationApi = AuthenticationApi(httpClient = httpClient)

    /**
     * Get the current [UserSessionInfo] object as a Flow. The flow will emit a new value whenever
     * the session is updated. This allows observers to watch for changes to authentication or
     * consent status.
     */
    fun sessionAsFlow() : Flow<UserSessionInfo?> {
        return database.getResourceAsFlow(USER_SESSION_ID, ResourceType.USER_SESSION_INFO, APP_WIDE_STUDY_ID).map { curResource -> curResource?.loadResource() }
    }

    /**
     * Get the current [UserSessionInfo] object.
     */
    fun session() : UserSessionInfo? {
        return database.getResource(USER_SESSION_ID, ResourceType.USER_SESSION_INFO, APP_WIDE_STUDY_ID)?.loadResource()
    }

    fun currentStudyId() : String? {
        return session()?.studyIds?.get(0)
    }

    fun isAuthenticated() : Boolean {
        return session()?.authenticated ?: false
    }

    suspend fun signOut() {
        session()?.let {
            try {
                authenticationApi.signOut(it)
            } catch (error: Throwable) {
                println(error)
            }
            database.clearDatabase()
        }
    }

    suspend fun signInExternalId(externalId: String, password: String) : ResourceResult<UserSessionInfo> {
        val signIn = SignIn(
            bridgeConfig.appId,
            externalId = externalId,
            password = password,
        )
        return signIn(signIn)
    }

    suspend fun signInEmail(email: String, password: String) : ResourceResult<UserSessionInfo> {
        val signIn = SignIn(
            appId = bridgeConfig.appId,
            email = email,
            password = password,
        )
        return signIn(signIn)
    }

    private suspend fun signIn(signIn: SignIn) : ResourceResult<UserSessionInfo> {
        try {
            val userSession = authenticationApi.signIn(signIn)
            updateCachedSession(null, userSession)
            return ResourceResult.Success(userSession, ResourceStatus.SUCCESS)
        } catch (err: Throwable) {
            database.removeResource(USER_SESSION_ID, ResourceType.USER_SESSION_INFO, APP_WIDE_STUDY_ID)
            println(err)
        }
        return ResourceResult.Failed(ResourceStatus.FAILED)
    }

    suspend fun reAuth() : Boolean {
        val sessionInfo = session()
        return sessionInfo?.reauthToken?.let {
            val signIn = SignIn(
                appId = bridgeConfig.appId,
                email = sessionInfo.email,
                externalId = sessionInfo.externalId,
                reauthToken = it
            )
            var success = false
            try {
                val userSession = authenticationApi.reauthenticate(signIn)
                updateCachedSession(sessionInfo, userSession)
                success = true
            } catch (err: Throwable) {
                println(err)
                if (err is ResponseException) {
                    // We got a response from Bridge and it was an error.
                    // Clear the cached session
                    database.removeResource(USER_SESSION_ID, ResourceType.USER_SESSION_INFO, APP_WIDE_STUDY_ID)
                } else {
                    // Some sort of network error leave the session alone so we can try again
                }
            }
            success
        } ?: false
    }

    fun notifyUIOfBridgeError(statusCode: HttpStatusCode) {
        // TODO: emm 2021-08-17 pass 410 (app version not supported) and 412 (not consented) Bridge errors along to the UI to deal with.
    }

    private fun updateCachedSession(oldUserSessionInfo: UserSessionInfo?, newUserSession: UserSessionInfo) {
        var toCacheSession = newUserSession
        if (newUserSession.reauthToken == null && oldUserSessionInfo?.reauthToken != null) {
            toCacheSession = newUserSession.copy(reauthToken = oldUserSessionInfo.reauthToken)
        }
        var resource = Resource(
            identifier = USER_SESSION_ID,
            secondaryId = ResourceDatabaseHelper.DEFAULT_SECONDARY_ID,
            type = ResourceType.USER_SESSION_INFO,
            studyId = APP_WIDE_STUDY_ID,
            json = Json.encodeToString(toCacheSession),
            lastUpdate = Clock.System.now().toEpochMilliseconds(),
            status = ResourceStatus.SUCCESS,
            needSave = false
        )
        database.insertUpdateResource(resource)
    }

}
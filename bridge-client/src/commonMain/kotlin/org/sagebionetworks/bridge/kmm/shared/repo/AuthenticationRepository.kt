package org.sagebionetworks.bridge.kmm.shared.repo

import co.touchlab.kermit.Logger
import io.ktor.client.*
import io.ktor.client.plugins.*
import io.ktor.http.*
import kotlinx.coroutines.CoroutineScope
import kotlinx.coroutines.flow.Flow
import kotlinx.coroutines.flow.MutableStateFlow
import kotlinx.coroutines.flow.StateFlow
import kotlinx.coroutines.flow.map
import kotlinx.coroutines.launch
import kotlinx.datetime.Clock
import kotlinx.serialization.encodeToString
import kotlinx.serialization.json.Json
import org.koin.core.component.KoinComponent
import org.koin.core.component.inject
import org.sagebionetworks.bridge.kmm.shared.BridgeConfig
import org.sagebionetworks.bridge.kmm.shared.apis.AuthenticationApi
import org.sagebionetworks.bridge.kmm.shared.apis.BridgeErrorStatusNotifier
import org.sagebionetworks.bridge.kmm.shared.cache.*
import org.sagebionetworks.bridge.kmm.shared.cache.ResourceDatabaseHelper.Companion.APP_WIDE_STUDY_ID
import org.sagebionetworks.bridge.kmm.shared.models.*

interface  AuthenticationProvider : BridgeErrorStatusNotifier {
    fun session() : UserSessionInfo?
    suspend fun reAuth() : Boolean
}

class AuthenticationRepository(
    authHttpClient: HttpClient,
    val bridgeConfig: BridgeConfig,
    val database: ResourceDatabaseHelper,
    private val backgroundScope: CoroutineScope
) : KoinComponent, AuthenticationProvider {

    internal companion object {
        const val USER_SESSION_ID = "UserSessionId"
    }

    private val authenticationApi = AuthenticationApi(httpClient = authHttpClient)

    // Lazy inject the ParticipantRepo so we don't have a dependency loop.
    // This is here so we can check for offline updates that need to be saved to bridge.
    private val participantRepo: ParticipantRepo by inject()

    private val _appStatusMutable = MutableStateFlow(AppStatus.SUPPORTED)

    /**
     * A [StateFlow] with the status of whether or not this version of the app is supported by Bridge.
     * When Bridge services return a http status code of 410, this will emit an [AppStatus.UNSUPPORTED].
     */
    val appStatus: StateFlow<AppStatus> = _appStatusMutable

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
    override fun session() : UserSessionInfo? {
        return sessionResource()?.loadResource()
    }

    internal fun sessionResource() : Resource? {
        return database.getResource(USER_SESSION_ID, ResourceType.USER_SESSION_INFO, APP_WIDE_STUDY_ID)
    }

    /**
     * Set the cached [UserSessionInfo]. This should only be used for migrating apps using old
     * Bridge client libraries. This will do nothing if there already is a session.
     */
    fun migrateSession(userSession: UserSessionInfo) {
        if (sessionResource() == null) {
            updateCachedSession(null, userSession)
        }
    }


    /**
     * Get the ID of the current study.
     */
    fun currentStudyId() : String? {
        return session()?.studyIds?.get(0)
    }

    /**
     * Is the current session authenticated.
     */
    fun isAuthenticated() : Boolean {
        return session()?.authenticated ?: false
    }

    /**
     * Calls the sign out api and then clears the local database cache.
     */
    suspend fun signOut() {
        session()?.let {
            try {
                authenticationApi.signOut(it)
            } catch (error: Throwable) {
                Logger.w("Error signing out: $error")
            }
        }
        // Always clear database when signOut is called
        database.clearDatabase()
    }

    /**
     *
     * Will send an SMS message with a code that can be used to call the server and generate a session.
     * @param number The phone number (can be formatted in any way that's useful for end users).
     * @param regionCode CLDR two-letter region code describing the region in which the phone number was issued.
     * @return Boolean
     */
    suspend fun requestPhoneSignIn(number: String, regionCode: String) : ResourceResult<Boolean> {
        try {
            val phone = Phone(number, regionCode)
            val phoneSignInRequest = PhoneSignInRequest(bridgeConfig.appId, phone)
            authenticationApi.requestPhoneSignIn(phoneSignInRequest)
            return ResourceResult.Success(true, ResourceStatus.SUCCESS)
        } catch (err: Throwable) {
            Logger.w("Error requesting phone sign-in: $err")
            return ResourceResult.Failed(ResourceStatus.FAILED, getHttpStatusCode(err))
        }
    }

    /**
     *
     * Resend an SMS message to the provided phone number asking the recipient to verify their  phone number.
     * Whether the phone has been registered or not through sign up, this method will return 200 in order to prevent \&quot;account enumeration\&quot; security breaches.
     * @param number The phone number (can be formatted in any way that's useful for end users).
     * @param regionCode CLDR two-letter region code describing the region in which the phone number was issued.
     * @return Message
     */
    suspend fun resendPhoneVerification(number: String, regionCode: String) : ResourceResult<Boolean> {
        try {
            val phone = Phone(number, regionCode)
            val identifier = Identifier(bridgeConfig.appId, phone=phone)
            authenticationApi.resendPhoneVerification(identifier)
            return ResourceResult.Success(true, ResourceStatus.SUCCESS)
        } catch (err: Throwable) {
            Logger.w("Error calling resendPhoneVerification: $err")
            return ResourceResult.Failed(ResourceStatus.FAILED, getHttpStatusCode(err))
        }
    }

    /**
     *
     * Using the token supplied via an SMS message sent to the user, request a session from the server.
     * @param token The token that was sent to the user via SMS, that needs to be entered into the application so it can be sent back to authenticate.
     * @param number The phone number (can be formatted in any way that's useful for end users).
     * @param regionCode CLDR two-letter region code describing the region in which the phone number was issued.
     * @return ResourceResult<UserSessionInfo>
     */
    suspend fun signInPhone(token: String, number: String, regionCode: String) : ResourceResult<UserSessionInfo> {
        try {
            val phone = Phone(number, regionCode)
            val phoneSignin = PhoneSignin(bridgeConfig.appId, phone, token)
            val userSession = authenticationApi.signInViaPhone(phoneSignin)
            updateCachedSession(null, userSession)
            return ResourceResult.Success(userSession, ResourceStatus.SUCCESS)
        } catch (err: Throwable) {
            database.removeResource(USER_SESSION_ID, ResourceType.USER_SESSION_INFO, APP_WIDE_STUDY_ID)
            Logger.w("Error signInPhone: $err")
            return ResourceResult.Failed(ResourceStatus.FAILED, getHttpStatusCode(err))
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

    suspend fun reauthWithCredentials(password: String) : ResourceResult<UserSessionInfo> {
        val sessionInfo = session() ?: return ResourceResult.Failed(ResourceStatus.FAILED)
        val signIn = SignIn(
            appId = bridgeConfig.appId,
            email = sessionInfo.email,
            externalId = sessionInfo.externalId,
            password = password
        )
        return try {
            val userSession = authenticationApi.signIn(signIn)
            updateCachedSession(null, userSession)
            ResourceResult.Success(userSession, ResourceStatus.SUCCESS)
        } catch (err: Throwable) {
            Logger.w("Error requesting reAuth with stored password: $err")
            if (err is ResponseException && err.response.status == HttpStatusCode.NotFound) {
                ResourceResult.Failed(ResourceStatus.FAILED)
            } else {
                ResourceResult.Failed(ResourceStatus.RETRY)
            }
        }
    }

    private suspend fun signIn(signIn: SignIn) : ResourceResult<UserSessionInfo> {
        try {
            val userSession = authenticationApi.signIn(signIn)
            updateCachedSession(null, userSession)
            return ResourceResult.Success(userSession, ResourceStatus.SUCCESS)
        } catch (err: Throwable) {
            database.removeResource(USER_SESSION_ID, ResourceType.USER_SESSION_INFO, APP_WIDE_STUDY_ID)
            Logger.w("Error signIn: $err")
            return ResourceResult.Failed(ResourceStatus.FAILED, getHttpStatusCode(err))
        }
    }

    private fun getHttpStatusCode(error: Throwable) : HttpStatusCode? {
        var httpStatusCode: HttpStatusCode? = null
        (error as? ResponseException)?.let {
            httpStatusCode = it.response.status
            notifyUIOfBridgeError(it.response.status)
        }
        return httpStatusCode
    }

    suspend fun signUpEmail(email: String,
                            password: String,
                            testUser: Boolean = false,
                            name: String? = null,
                            sharingScope: SharingScope? = null,
                            dataGroups: List<String>? = null) : Boolean {
        val signUp = SignUp(
            appId = bridgeConfig.appId,
            email = email,
            password = password,
            lastName = name,
            sharingScope = sharingScope ?: SharingScope.SPONSORS_AND_PARTNERS,
            dataGroups = if (testUser) ((dataGroups ?: listOf()) + listOf("test_user")).distinct() else dataGroups
        )
        return signUp(signUp)
    }

    private suspend fun signUp(signUp: SignUp) : Boolean {
        try {
            val message = authenticationApi.signUp(signUp)
            return true
        } catch (err: Throwable) {
            Logger.w("Error signUp: $err")
        }
        return false
    }

    override suspend fun reAuth() : Boolean = reAuthWithError().first

    suspend fun reAuthWithError() : Pair<Boolean, Error?> {
        val sessionInfo = session()
        return sessionInfo?.reauthToken?.let { reauthToken ->
            val signIn = SignIn(
                appId = bridgeConfig.appId,
                email = sessionInfo.email,
                externalId = sessionInfo.externalId,
                reauthToken = reauthToken
            )
            var success = false
            var responseError: Error? = null
            try {
                val userSession = authenticationApi.reauthenticate(signIn)
                updateCachedSession(sessionInfo, userSession)
                success = true
            } catch (err: Throwable) {
                responseError = Error(err.message ?: "Error requesting reAuth: $err")
                if (err is ResponseException && (err.response.status == HttpStatusCode.Unauthorized ||
                            err.response.status == HttpStatusCode.Forbidden ||
                            err.response.status == HttpStatusCode.NotFound ||
                            err.response.status == HttpStatusCode.Locked)) {
                    // Should clear session for auth related errors: 401, 403, 404, 423
                    Logger.e("User reauth failed. Removing user session token.", err)
                    val newSession = sessionInfo.copy(
                        reauthToken = null,
                        authenticated = false,
                        sessionToken = ""
                    )
                    updateCachedSession(null, newSession)
                } else {
                    // Some sort of network error leave the session alone so we can try again
                    Logger.i("User reauth failed. Ignoring. $err")
                }
            }
            Pair(success, responseError)
        } ?: Pair(false, Error("reAuth token is null"))
    }

    override fun notifyUIOfBridgeError(statusCode: HttpStatusCode) {
        if (statusCode == HttpStatusCode.Gone) {
            _appStatusMutable.value = AppStatus.UNSUPPORTED
        }
        // TODO: emm 2021-08-17 pass 412 (not consented) Bridge errors along to the UI to deal with.
    }

    internal fun updateCachedSession(oldUserSessionInfo: UserSessionInfo?, newUserSession: UserSessionInfo) {
        val oldSessionResource = sessionResource()
        var toCacheSession = newUserSession
        var needSave = false
        if (oldUserSessionInfo != null && oldSessionResource?.needSave == true && oldSessionResource.status != ResourceStatus.FAILED) {
            //We have local changes that need be saved to bridge that we don't want to overwrite
            toCacheSession = oldUserSessionInfo
            if (newUserSession.reauthToken != null) {
                // Just need to update with the new auth tokens
                toCacheSession = oldUserSessionInfo.copy(
                    sessionToken = newUserSession.sessionToken,
                    reauthToken = newUserSession.reauthToken
                )
            }
            needSave = true
        } else if (newUserSession.reauthToken == null && oldUserSessionInfo?.reauthToken != null) {
            //New session doesn't have re-auth token, so keep old one
            toCacheSession = newUserSession.copy(reauthToken = oldUserSessionInfo.reauthToken)
        }
        // TODO: syoung 02/01/2022 Test this before uncommenting.
//        val previousSession = oldSessionResource?.loadResource<UserSessionInfo>()
//        if (previousSession != null && previousSession.id != newUserSession.id) {
//            database.clearDatabase()
//        }
        val resource = Resource(
            identifier = USER_SESSION_ID,
            secondaryId = ResourceDatabaseHelper.DEFAULT_SECONDARY_ID,
            type = ResourceType.USER_SESSION_INFO,
            studyId = APP_WIDE_STUDY_ID,
            json = Json.encodeToString(toCacheSession),
            lastUpdate = Clock.System.now().toEpochMilliseconds(),
            status = ResourceStatus.SUCCESS,
            needSave = needSave
        )
        database.insertUpdateResource(resource)
        if (needSave) {
            backgroundScope.launch {
                participantRepo.processLocalUpdates()
            }
        }
    }

}

enum class AppStatus {
    SUPPORTED,
    UNSUPPORTED,
}




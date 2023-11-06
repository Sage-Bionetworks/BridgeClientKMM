package org.sagebionetworks.bridge.kmm.shared

import app.cash.sqldelight.db.SqlDriver
import io.ktor.client.*
import io.ktor.client.engine.*
import io.ktor.client.engine.mock.*
import io.ktor.client.plugins.*
import io.ktor.client.plugins.contentnegotiation.*
import io.ktor.client.plugins.logging.*
import io.ktor.client.request.*
import io.ktor.http.*
import io.ktor.serialization.kotlinx.json.*
import kotlinx.coroutines.flow.MutableStateFlow
import kotlinx.serialization.json.Json
import org.sagebionetworks.bridge.kmm.shared.apis.RefreshTokenFeature
import org.sagebionetworks.bridge.kmm.shared.apis.SessionTokenFeature
import org.sagebionetworks.bridge.kmm.shared.apis.HttpUtil
import org.sagebionetworks.bridge.kmm.shared.cache.EncryptedSharedSettings
import org.sagebionetworks.bridge.kmm.shared.cache.ResourceDatabaseHelper
import org.sagebionetworks.bridge.kmm.shared.di.appendAuthConfig
import org.sagebionetworks.bridge.kmm.shared.di.appendDefaultConfig
import org.sagebionetworks.bridge.kmm.shared.models.UserSessionInfo
import org.sagebionetworks.bridge.kmm.shared.repo.AppStatus
import org.sagebionetworks.bridge.kmm.shared.repo.AuthenticationProvider
import org.sagebionetworks.bridge.kmm.shared.repo.TestBridgeConfig

internal expect fun testDatabaseDriver() : SqlDriver

internal expect fun randomUUID(): String

data class MockAuthenticationProvider(
    var userSessionInfo: UserSessionInfo? = createUserSessionInfo(),
    val reauthSessionToken: String = "newTestSessionToken",
    val reauthToken: String = "newReauthToken"
) : AuthenticationProvider {

    var reauthCalled: Boolean = false
    var sessionCallCount: Int = 0

    override fun session(): UserSessionInfo? {
        sessionCallCount++
        return userSessionInfo
    }

    override suspend fun reAuth(): Boolean {
        reauthCalled = true
        userSessionInfo = userSessionInfo?.copy(sessionToken = reauthSessionToken, reauthToken = reauthToken)
        return userSessionInfo != null
    }

    val appStatusMutable = MutableStateFlow(AppStatus.SUPPORTED)
    override fun notifyUIOfBridgeError(statusCode: HttpStatusCode) {
        if (statusCode == HttpStatusCode.Gone) {
            appStatusMutable.value = AppStatus.UNSUPPORTED
        }
    }
}

fun createUserSessionInfo(sessionToken: String = "testSessionToken", reauthToken: String? = "reauthToken") : UserSessionInfo = UserSessionInfo(
    id = "uniqueId",
    authenticated = true,
    studyIds = listOf("testStudyId"),
    sessionToken = sessionToken,
    reauthToken = reauthToken
)

data class TestHttpClientConfig(
    val bridgeConfig: BridgeConfig = TestBridgeConfig(),
    val authProvider: AuthenticationProvider? = MockAuthenticationProvider(),
    val db: ResourceDatabaseHelper = ResourceDatabaseHelper(testDatabaseDriver()),
    val langCode: String = "en-US,en"
) : HttpUtil {
    override fun acceptLanguage(): String {
        return langCode
    }
}

fun getTestClient(json: String,
                  responseCode: HttpStatusCode = HttpStatusCode.OK,
                  config: TestHttpClientConfig = TestHttpClientConfig()): HttpClient {
    val mockEngine = MockEngine.config {
        addHandler (
            getJsonReponseHandler(json, responseCode)
        )
    }
    return getTestClient(mockEngine, config)
}

fun getTestClient(mockEngine: HttpClientEngineFactory<MockEngineConfig>,
                  config: TestHttpClientConfig = TestHttpClientConfig()) =
    if (config.authProvider != null) {
        HttpClient(mockEngine).appendDefaultConfig(true, config.bridgeConfig, config.authProvider, config.db, config)
    } else {
        HttpClient(mockEngine).appendAuthConfig(true, config.bridgeConfig, config)
    }

fun getJsonReponseHandler(json: String, responseCode: HttpStatusCode = HttpStatusCode.OK) : suspend MockRequestHandleScope.(io.ktor.client.request.HttpRequestData) -> io.ktor.client.request.HttpResponseData {
    return {request ->
        respond(json, responseCode, headersOf("Content-Type" to listOf(ContentType.Application.Json.toString())))
    }
}

class TestEncryptedSharedSettings : EncryptedSharedSettings {

    override var pwd: String? = null

}

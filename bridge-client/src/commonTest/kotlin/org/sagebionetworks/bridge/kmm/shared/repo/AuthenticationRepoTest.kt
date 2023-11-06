package org.sagebionetworks.bridge.kmm.shared.repo

import io.ktor.client.engine.*
import io.ktor.client.engine.mock.*
import io.ktor.client.request.*
import io.ktor.client.statement.*
import io.ktor.http.*
import kotlinx.coroutines.MainScope
import kotlinx.serialization.encodeToString
import kotlinx.serialization.json.Json
import org.sagebionetworks.bridge.kmm.shared.*
import org.sagebionetworks.bridge.kmm.shared.apis.AbstractApi
import org.sagebionetworks.bridge.kmm.shared.cache.ResourceDatabaseHelper
import org.sagebionetworks.bridge.kmm.shared.cache.ResourceResult
import org.sagebionetworks.bridge.kmm.shared.models.UserSessionInfo
import org.sagebionetworks.bridge.kmm.shared.testDatabaseDriver
import kotlin.test.Test
import kotlin.test.assertEquals
import kotlin.test.assertTrue

class AuthenticationRepoTest : BaseTest() {

    @Test
    fun testSignIn_404_NotFound() {
        runTest {

            val json = "{\"statusCode\":404,\"entityClass\":\"Account\",\"message\":\"Study not found.\",\"type\":\"EntityNotFoundException\"}"
            val testConfig = TestHttpClientConfig(authProvider = null)

            val authRepo = AuthenticationRepository(
                getTestClient(json, HttpStatusCode.NotFound, testConfig),
                testConfig.bridgeConfig,
                testConfig.db,
                MainScope(),
                TestEncryptedSharedSettings())

            val response = authRepo.signInExternalId("typo:test_study", "typo:test_study")
            assertTrue(response is ResourceResult.Failed)
            assertEquals(HttpStatusCode.NotFound, response.httpStatusCode)
        }
    }

    @Test
    fun testSignIn_410() {
        runTest {

            val json = "{\"statusCode\":410}"
            val testConfig = TestHttpClientConfig()

            val authRepo = AuthenticationRepository(
                getTestClient(json, HttpStatusCode.Gone, testConfig),
                testConfig.bridgeConfig,
                testConfig.db,
                MainScope(),
                TestEncryptedSharedSettings())

            val response = authRepo.signInExternalId("typo:test_study", "typo:test_study")
            assertTrue(response is ResourceResult.Failed)
            assertEquals(HttpStatusCode.Gone, response.httpStatusCode)
            assertEquals(AppStatus.UNSUPPORTED, authRepo.appStatus.value)
        }
    }

    val userSessionInfo = UserSessionInfo(
        id = "uniqueId",
        authenticated = true,
        studyIds = listOf("testStudyId"),
        sessionToken = "testSessionToken",
        reauthToken = "testReauthToken"
    )

    @Test
    fun testReauthWithCredentials() {
        runTest {
            val mockEngine = MockEngine.config {
                // 1 - Sign-in call
                addHandler(
                    getJsonReponseHandler(Json.encodeToString(userSessionInfo))
                )
                // 2 - Re-auth call
                addHandler { respondError(HttpStatusCode.Unauthorized) }
                // 3 - Re-auth with credentials
                addHandler (
                    getJsonReponseHandler(Json.encodeToString(userSessionInfo))
                )
                reuseHandlers = false
            }
            // AuthProvider needs to be null so RefreshTokenFeature doesn't get installed
            val testConfig = TestHttpClientConfig(authProvider = null)
            (testConfig.bridgeConfig as TestBridgeConfig).cacheCredentials = true
            val testClient = getTestClient(mockEngine, testConfig)

            val authRepo = AuthenticationRepository(
                testClient,
                testConfig.bridgeConfig,
                testConfig.db,
                MainScope(),
                TestEncryptedSharedSettings()
            )

            val result = authRepo.signInExternalId("participant:testStudyId", "participant:testStudyId")
            assertTrue(result is ResourceResult.Success)
            assertTrue(authRepo.reAuth())
            assertTrue(authRepo.isAuthenticated())

        }

    }
}
package org.sagebionetworks.bridge.kmm.shared.repo

import io.ktor.client.engine.*
import io.ktor.client.engine.mock.*
import io.ktor.client.request.*
import io.ktor.client.statement.*
import io.ktor.http.*
import kotlinx.coroutines.MainScope
import org.sagebionetworks.bridge.kmm.shared.*
import org.sagebionetworks.bridge.kmm.shared.apis.AbstractApi
import org.sagebionetworks.bridge.kmm.shared.cache.ResourceDatabaseHelper
import org.sagebionetworks.bridge.kmm.shared.cache.ResourceResult
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
                MainScope())

            val response = authRepo.signInExternalId("typo:test_study", "typo:test_study")
            assertTrue(response is ResourceResult.Failed)
            assertEquals(HttpStatusCode.NotFound, response.httpStatusCode)
        }
    }

    @Test
    fun testSignIn_410() {
        runTest {

            val json = "{\"statusCode\":410}"
            val testConfig = TestHttpClientConfig(authProvider = null)

            val authRepo = AuthenticationRepository(
                getTestClient(json, HttpStatusCode.Gone, testConfig),
                testConfig.bridgeConfig,
                testConfig.db,
                MainScope())

            val response = authRepo.signInExternalId("typo:test_study", "typo:test_study")
            assertTrue(response is ResourceResult.Failed)
            assertEquals(HttpStatusCode.Gone, response.httpStatusCode)
            assertEquals(AppStatus.UNSUPPORTED, authRepo.appStatus.value)
        }
    }
}
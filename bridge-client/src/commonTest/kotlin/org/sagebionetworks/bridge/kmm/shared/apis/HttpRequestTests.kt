package org.sagebionetworks.bridge.kmm.shared.apis

import io.ktor.client.*
import io.ktor.client.engine.*
import io.ktor.client.engine.mock.*
import io.ktor.client.request.*
import io.ktor.client.statement.*
import io.ktor.http.*
import org.sagebionetworks.bridge.kmm.shared.*
import org.sagebionetworks.bridge.kmm.shared.models.UserSessionInfo
import org.sagebionetworks.bridge.kmm.shared.repo.AuthenticationProvider
import kotlin.test.*

class HttpRequestTests: BaseTest() {

    @Test
    fun testRefreshToken_UserAgent() {
        runTest {
            val mockEngine = MockEngine.config {
                // 1 - Fail first call to simulate expired token
                addHandler { respondError(HttpStatusCode.Unauthorized) }
                // 2 successful call
                addHandler(
                    getJsonReponseHandler("")
                )
                reuseHandlers = false
            }
            val testClient = getTestClient(mockEngine)

            val response: HttpResponse = testClient.get(AbstractApi.BASE_PATH)
            val agentList = response.request.headers.getAll(HttpHeaders.UserAgent)
            assertEquals(HttpStatusCode.OK, response.status)
            // Verify that we only had one User-Agent added
            assertEquals(1, agentList?.size)
            assertEquals("bridge-client-kmm-test/1 (Test; Test/Test)", agentList?.get(0))
        }
    }

    @Test
    fun testRefreshToken_NullSessionToken() {
        runTest {

            var request1Headers: Headers? = null
            var request2Headers: Headers? = null

            val mockEngine = MockEngine.config {
                // 1 - Fail first call due to missing session token
                addHandler {
                    request1Headers = it.headers
                    respondError(HttpStatusCode.Unauthorized)
                }
                // 2 successful call
                addHandler {
                    request2Headers = it.headers
                    respond("{}", HttpStatusCode.OK, headersOf("Content-Type" to listOf(ContentType.Application.Json.toString())))
                }
                reuseHandlers = false
            }
            val authProvider = MockBrokenAuthenticationProvider(minCount = 1)
            val testClient = getTestClient(mockEngine, TestHttpClientConfig(authProvider = authProvider))

            val response: HttpResponse = testClient.get(AbstractApi.BASE_PATH)

            assertNotNull(request1Headers)
            assertNull(request1Headers!!.get("Bridge-Session"))

            assertNotNull(request2Headers)
            assertNotNull(request2Headers!!.get("Bridge-Session"))

            assertFalse(authProvider.reauthCalled)
            assertEquals(3, authProvider.sessionCallCount)
        }
    }

    @Test
    fun testRefreshToken_OldSessionToken() {
        runTest {

            var request1Headers: Headers? = null
            var request2Headers: Headers? = null

            val mockEngine = MockEngine.config {
                // 1 - Fail first call to simulate expired token
                addHandler {
                    request1Headers = it.headers
                    respondError(HttpStatusCode.Unauthorized)
                }
                // 2 successful call
                addHandler {
                    request2Headers = it.headers
                    respond("{}", HttpStatusCode.OK, headersOf("Content-Type" to listOf(ContentType.Application.Json.toString())))
                }
                reuseHandlers = false
            }
            val authProvider = MockAuthenticationProvider()
            val testClient = getTestClient(mockEngine, TestHttpClientConfig(authProvider = authProvider))

            val response: HttpResponse = testClient.get(AbstractApi.BASE_PATH)

            assertNotNull(request1Headers)
            assertEquals("testSessionToken", request1Headers!!.get("Bridge-Session"))

            assertNotNull(request2Headers)
            assertEquals("newTestSessionToken", request2Headers!!.get("Bridge-Session"))

            assertTrue(authProvider.reauthCalled)
            assertEquals(3, authProvider.sessionCallCount)
        }
    }

    @Test
    fun testRequestUrl() {
        runTest {
            val testClient = getTestClient("")
            val testPath =  "v5/test/path"
            val testApi = TestApi(AbstractApi.BASE_PATH, testClient)
            val getResponse = testApi.getDataResponse(testPath)
            assertEquals(AbstractApi.BASE_PATH + "/" + testPath, getResponse.request.url.toString())
            val postResponse = testApi.postDataResponse("", testPath)
            assertEquals(AbstractApi.BASE_PATH + "/" + testPath, postResponse.request.url.toString())
        }
    }


    internal class TestApi(basePath: String, httpClient: HttpClient): AbstractApi(basePath, httpClient) {

    }

    internal data class MockBrokenAuthenticationProvider(
        var userSessionInfo: UserSessionInfo = createUserSessionInfo(),
        val minCount: Int = 1
    ) : AuthenticationProvider {

        var reauthCalled: Boolean = false
        var sessionCallCount: Int = 0

        override fun session(): UserSessionInfo? {
            sessionCallCount++
            return if (sessionCallCount <= minCount) null else userSessionInfo
        }

        override suspend fun reAuth(): Boolean {
            reauthCalled = true
            return true
        }
    }
}

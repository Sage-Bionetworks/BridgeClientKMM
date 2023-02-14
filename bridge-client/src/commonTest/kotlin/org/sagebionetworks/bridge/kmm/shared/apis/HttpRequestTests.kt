package org.sagebionetworks.bridge.kmm.shared.apis

import io.ktor.client.*
import io.ktor.client.engine.*
import io.ktor.client.engine.mock.*
import io.ktor.client.request.*
import io.ktor.client.statement.*
import io.ktor.http.*
import org.sagebionetworks.bridge.kmm.shared.BaseTest
import org.sagebionetworks.bridge.kmm.shared.getJsonReponseHandler
import org.sagebionetworks.bridge.kmm.shared.getMockTestClient
import org.sagebionetworks.bridge.kmm.shared.getTestClient
import kotlin.test.Test
import kotlin.test.assertEquals

class HttpRequestTests: BaseTest() {

    @Test
    fun testRefreshToken() {
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
            // TODO: syoung 02/14/2022 Revisit this and set up to not use the original test client.
            val testClient = getMockTestClient(mockEngine)

            val response: HttpResponse = testClient.get(AbstractApi.BASE_PATH)
            val agentList = response.request.headers.getAll(HttpHeaders.UserAgent)
            // Verify that we only had one User-Agent added
            assertEquals(1, agentList?.size)
            assertEquals("Unit Test agent", agentList?.get(0))
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

}
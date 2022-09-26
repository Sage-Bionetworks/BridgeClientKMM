package org.sagebionetworks.bridge.kmm.shared.apis

import io.ktor.client.engine.*
import io.ktor.client.engine.mock.*
import io.ktor.client.request.*
import io.ktor.client.statement.*
import io.ktor.http.*
import org.sagebionetworks.bridge.kmm.shared.BaseTest
import org.sagebionetworks.bridge.kmm.shared.getJsonReponseHandler
import org.sagebionetworks.bridge.kmm.shared.getTestClient
import kotlin.test.Test
import kotlin.test.assertEquals

class HttpHeadersTest: BaseTest() {

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
            val testClient = getTestClient(mockEngine)

            val response: HttpResponse = testClient.get(AbstractApi.BASE_PATH)
            val agentList = response.request.headers.getAll(HttpHeaders.UserAgent)
            // Verify that we only had one User-Agent added
            assertEquals(1, agentList?.size)
            assertEquals("Unit Test agent", agentList?.get(0))
        }
    }

}
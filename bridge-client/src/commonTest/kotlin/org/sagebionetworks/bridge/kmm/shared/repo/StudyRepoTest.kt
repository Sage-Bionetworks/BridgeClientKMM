package org.sagebionetworks.bridge.kmm.shared.repo

import io.ktor.client.engine.*
import io.ktor.client.engine.mock.*
import io.ktor.http.*
import kotlinx.coroutines.MainScope
import kotlinx.coroutines.flow.filterNot
import kotlinx.coroutines.flow.first
import kotlinx.datetime.Clock
import kotlinx.serialization.encodeToString
import kotlinx.serialization.json.Json
import kotlinx.serialization.json.JsonPrimitive
import org.sagebionetworks.bridge.kmm.shared.*
import org.sagebionetworks.bridge.kmm.shared.cache.*
import org.sagebionetworks.bridge.kmm.shared.models.AssessmentInfo
import org.sagebionetworks.bridge.kmm.shared.models.StudyInfo
import org.sagebionetworks.bridge.kmm.shared.models.UserSessionInfo
import kotlin.test.*

class StudyRepoTest : BaseTest() {

    @Test
    fun testGetStudyInfo_404_NotFound() {
        runTest {
            val json = "{\"statusCode\":404,\"entityClass\":\"Study\",\"message\":\"Study not found.\",\"type\":\"EntityNotFoundException\"}"
            val repo = StudyRepo(
                bridgeConfig = TestBridgeConfig(),
                httpClient = getTestClient(json, HttpStatusCode.NotFound),
                databaseHelper = ResourceDatabaseHelper(testDatabaseDriver()),
                backgroundScope = MainScope()
            )

            val studyInfo = repo.getStudyInfo("missing")
            assertTrue(studyInfo is ResourceResult.Failed)
        }
    }

    @Test
    fun testGetStudyInfo_Success_Then_304() {
        runTest {
            val json = "{\"identifier\": \"test_study\", \"name\": \"Test Study\", \"type\": \"Study\"}"

            val mockEngine = MockEngine.config {
                // 1 - First request returns with 200 and success
                addHandler {
                    respond(json, HttpStatusCode.OK, headersOf("Content-Type" to listOf(ContentType.Application.Json.toString())))
                }
                // 2 - Second request returns with 304 but should return object equal to first
                addHandler {
                    respondError(HttpStatusCode.NotModified)
                }
                reuseHandlers = false
            }

            val repo = StudyRepo(
                bridgeConfig = TestBridgeConfig(),
                httpClient = getTestClient(mockEngine),
                databaseHelper = ResourceDatabaseHelper(testDatabaseDriver()),
                backgroundScope = MainScope()
            )

            val studyInfo = repo.getStudyInfo("test_study")
            assertTrue(studyInfo is ResourceResult.Success<StudyInfo>)
            assertEquals("test_study", studyInfo.data.identifier)
            assertEquals("Test Study", studyInfo.data.name)

            val studyInfo2 = repo.getStudyInfo("test_study")
            assertTrue(studyInfo2 is ResourceResult.Success<StudyInfo>)
            assertEquals("test_study", studyInfo2.data.identifier)
            assertEquals("Test Study", studyInfo2.data.name)
        }
    }
}
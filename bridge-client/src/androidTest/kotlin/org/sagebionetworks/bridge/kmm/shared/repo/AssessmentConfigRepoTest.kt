package org.sagebionetworks.bridge.kmm.shared.repo

import kotlinx.coroutines.CoroutineScope
import kotlinx.coroutines.Dispatchers
import kotlinx.coroutines.flow.filterNotNull
import kotlinx.coroutines.flow.first
import kotlinx.coroutines.runBlocking
import org.sagebionetworks.bridge.kmm.shared.apis.AssessmentsApi
import org.sagebionetworks.bridge.kmm.shared.cache.ResourceType
import org.sagebionetworks.bridge.kmm.shared.getTestClient
import org.sagebionetworks.bridge.kmm.shared.testDatabaseDriverFactory
import kotlin.test.Test
import kotlin.test.assertEquals
import kotlin.test.assertNotNull
import kotlin.test.assertTrue

class AssessmentConfigRepoTest {

    val assessmentJson = "{\"config\":{\"type\":\"assessment\",\"identifier\":\"foo\",\"versionString\":\"1.2.3\",\"resultIdentifier\":\"bar\",\"title\":\"Hello World!\",\"subtitle\":\"Subtitle\",\"detail\":\"Some text. This is a test.\",\"estimatedMinutes\":4,\"icon\":\"fooIcon\",\"footnote\":\"This is a footnote.\",\"shouldHideActions\":[\"goBackward\"],\"progressMarkers\":[\"step1\",\"step2\"],\"steps\":[{\"identifier\":\"step1\",\"type\":\"instruction\",\"title\":\"Instruction Step 1\",\"detail\":\"Here are the details for this instruction.\",\"image\":{\"type\":\"fetchable\",\"identifier\":\"instructionImage\",\"imageName\":\"crf_seated\"}}]},\"createdOn\":\"2020-10-01T17:06:18.434Z\",\"modifiedOn\":\"2020-10-01T17:14:11.262Z\",\"version\":2,\"type\":\"AssessmentConfig\"}"

    @Test
    fun testAssessmentConfig() {
        runBlocking {
            val assessmentConfigId = "testId"
            val repo = AssessmentConfigRepo(testDatabaseDriverFactory(), CoroutineScope(Dispatchers.Default))
            repo.assessmentsApi = AssessmentsApi(httpClient = getTestClient(assessmentJson))

            val resultJson = repo.getAssessmentById(assessmentConfigId).filterNotNull().first() //drop(1).first()
            assertNotNull(resultJson)

            val db = repo.database
            val r1 = db.getResource(assessmentConfigId).first()
            assertNotNull(r1)
            assertEquals(ResourceType.ASSESSMENT_CONFIG, r1.type)
            assertTrue(r1.json?.contains("identifier")?: false)
            db.clearDatabase()
        }
    }

}


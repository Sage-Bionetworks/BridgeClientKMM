package org.sagebionetworks.bridge.kmm.shared.cache

import kotlinx.coroutines.flow.first
import kotlinx.coroutines.runBlocking
import org.sagebionetworks.bridge.kmm.shared.cache.ResourceDatabaseHelper.Companion.APP_WIDE_STUDY_ID
import org.sagebionetworks.bridge.kmm.shared.testDatabaseDriver
import kotlin.test.assertEquals
import kotlin.test.assertNotNull
import kotlin.test.assertNull
import kotlin.test.Test

class ResourceDatabaseTest {

    @Test
    fun testDatabase() {
        runBlocking {
            val db = ResourceDatabaseHelper(testDatabaseDriver())
            val testId = "TestId"
            val resource = Resource(
                identifier = testId,
                type = ResourceType.ASSESSMENT_CONFIG,
                studyId = APP_WIDE_STUDY_ID,
                json = "{}",
                lastUpdate = 0,
                status = ResourceStatus.SUCCESS,
                needSave = false
            )
            db.insertUpdateResource(resource)
            val r1 = db.getResourceAsFlow(testId, ResourceType.ASSESSMENT_CONFIG, APP_WIDE_STUDY_ID).first()
            assertNotNull(r1)
            assertEquals(ResourceType.ASSESSMENT_CONFIG, r1.type)
            assertEquals("{}", r1.json)
            assertEquals(0, r1.lastUpdate)
            db.clearDatabase()
            val r2 = db.getResourceAsFlow(testId, ResourceType.ASSESSMENT_CONFIG, APP_WIDE_STUDY_ID).first()
            assertNull(r2)
        }
    }
}

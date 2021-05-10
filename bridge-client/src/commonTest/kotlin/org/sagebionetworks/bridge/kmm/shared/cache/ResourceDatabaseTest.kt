package org.sagebionetworks.bridge.kmm.shared.cache

import kotlinx.coroutines.flow.first
import kotlinx.coroutines.runBlocking
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
            val resource = Resource(testId, ResourceType.ASSESSMENT_CONFIG, "{}", 0, ResourceStatus.SUCCESS)
            db.insertUpdateResource(resource)
            val r1 = db.getResourceAsFlow(testId, ResourceType.ASSESSMENT_CONFIG).first()
            assertNotNull(r1)
            assertEquals(ResourceType.ASSESSMENT_CONFIG, r1.type)
            assertEquals("{}", r1.json)
            assertEquals(0, r1.lastUpdate)
            db.clearDatabase()
            val r2 = db.getResourceAsFlow(testId, ResourceType.ASSESSMENT_CONFIG).first()
            assertNull(r2)
        }
    }
}

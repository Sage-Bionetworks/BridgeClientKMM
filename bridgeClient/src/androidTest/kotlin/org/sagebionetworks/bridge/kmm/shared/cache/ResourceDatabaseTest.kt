package org.sagebionetworks.bridge.kmm.shared.cache

import com.squareup.sqldelight.db.SqlDriver
import com.squareup.sqldelight.sqlite.driver.JdbcSqliteDriver
import kotlinx.coroutines.flow.first
import kotlinx.coroutines.runBlocking
import org.junit.Test
import org.sagebionetworks.bridge.kmm.shared.TestDatabaseDriverFactory
import kotlin.test.assertEquals
import kotlin.test.assertNotNull
import kotlin.test.assertNull

class ResourceDatabaseTest {

    @Test
    fun testDatabase() {
        runBlocking {
            val db = ResourceDatabaseHelper(TestDatabaseDriverFactory().createDriver())
            val testId = "TestId"
            val resource = Resource(testId, ResourceType.ASSESSMENT_CONFIG, "{}", 0, ResourceStatus.SUCCESS)
            db.insertUpdateResource(resource)
            val r1 = db.getResourceAsFlow(testId).first()
            assertNotNull(r1)
            assertEquals(ResourceType.ASSESSMENT_CONFIG, r1.type)
            assertEquals("{}", r1.json)
            assertEquals(0, r1.lastUpdate)
            db.clearDatabase()
            val r2 = db.getResourceAsFlow(testId).first()
            assertNull(r2)
        }
    }
}

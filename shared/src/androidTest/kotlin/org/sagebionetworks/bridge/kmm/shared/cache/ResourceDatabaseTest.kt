package org.sagebionetworks.bridge.kmm.shared.cache

import com.squareup.sqldelight.db.SqlDriver
import com.squareup.sqldelight.sqlite.driver.JdbcSqliteDriver
import kotlinx.coroutines.flow.first
import kotlinx.coroutines.runBlocking
import org.junit.Test
import kotlin.test.assertEquals
import kotlin.test.assertNotNull
import kotlin.test.assertNull

class ResourceDatabaseTest {

    @Test
    fun testDatabase() {
        runBlocking {
            val db = ResourceDatabaseHelper(TestDatabaseDriverFactory())
            val testId = "TestId"
            val resource = Resource(testId, ResourceType.ASSESSMENT_CONFIG, "{}", 0)
            db.insertUpdateResource(resource)
            val r1 = db.getResource(testId).first()
            assertNotNull(r1)
            assertEquals(ResourceType.ASSESSMENT_CONFIG, r1.type)
            assertEquals("{}", r1.json)
            assertEquals(0, r1.lastUpdate)
            db.clearDatabase()
            val r2 = db.getResource(testId).first()
            assertNull(r2)
        }
    }
}

class TestDatabaseDriverFactory() : DbDriverFactory {
    override fun createDriver(): SqlDriver {
        return JdbcSqliteDriver(JdbcSqliteDriver.IN_MEMORY).apply {
            BridgeResourceDatabase.Schema.create(this)
        }
    }
}
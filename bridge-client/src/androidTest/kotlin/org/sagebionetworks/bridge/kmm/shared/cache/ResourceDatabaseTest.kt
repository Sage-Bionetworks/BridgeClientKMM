package org.sagebionetworks.bridge.kmm.shared.cache

import com.squareup.sqldelight.db.SqlDriver
import com.squareup.sqldelight.sqlite.driver.JdbcSqliteDriver
import kotlinx.coroutines.flow.first
import kotlinx.coroutines.runBlocking
import org.junit.Test
import org.sagebionetworks.bridge.kmm.shared.apis.AuthenticationApi
import org.sagebionetworks.bridge.kmm.shared.models.SignIn
import kotlin.test.assertEquals
import kotlin.test.assertNotNull
import kotlin.test.assertNull

class ResourceDatabaseTest {

    @Test
    fun testDatabase() {
        runBlocking {
            val db = ResourceDatabaseHelper(TestDatabaseDriverFactory())
            val testId = "TestId"
            val resource = Resource(testId, ResourceType.ASSESSMENT_CONFIG, "{}", 0, ResourceStatus.SUCCESS)
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

    @Test
    fun testAuth() {
        runBlocking {
            //val accountDAO = AccountDAO()
            val authApi = AuthenticationApi()
            val signIn = SignIn(
                "sage-assessment-test",
                "nathaniel.brown+test@sagebase.org",
                password = "ngbTest1!",
            )
            val userSession = authApi.signIn(signIn)

            val reAuthToken = userSession.reauthToken!!
            val reAuth = SignIn(
                "sage-assessment-test",
                "Nathaniel.brown+test@sagebase.org",
                reauthToken = reAuthToken
            )
            val session2 = authApi.reauthenticate(reAuth)

            assertNotNull(session2)
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
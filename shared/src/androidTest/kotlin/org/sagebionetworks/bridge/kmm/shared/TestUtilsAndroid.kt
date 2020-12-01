package org.sagebionetworks.bridge.kmm.shared

import com.squareup.sqldelight.db.SqlDriver
import com.squareup.sqldelight.sqlite.driver.JdbcSqliteDriver
import org.sagebionetworks.bridge.kmm.shared.cache.BridgeResourceDatabase
import org.sagebionetworks.bridge.kmm.shared.cache.DbDriverFactory

    internal actual fun testDatabaseDriverFactory(): DbDriverFactory {

        return TestDatabaseDriverFactory()
    }

    class TestDatabaseDriverFactory() : DbDriverFactory {
        override fun createDriver(): SqlDriver {
            return JdbcSqliteDriver(JdbcSqliteDriver.IN_MEMORY).apply {
                BridgeResourceDatabase.Schema.create(this)
            }
        }
    }
package org.sagebionetworks.bridge.kmm.shared

import com.squareup.sqldelight.db.SqlDriver
import com.squareup.sqldelight.sqlite.driver.JdbcSqliteDriver
import org.sagebionetworks.bridge.kmm.shared.cache.BridgeResourceDatabase

internal actual fun testDatabaseDriver(): SqlDriver {
        return JdbcSqliteDriver(JdbcSqliteDriver.IN_MEMORY).apply {
            BridgeResourceDatabase.Schema.create(this)
        }
    }
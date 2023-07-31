package org.sagebionetworks.bridge.kmm.shared

import app.cash.sqldelight.db.SqlDriver
import app.cash.sqldelight.driver.jdbc.sqlite.JdbcSqliteDriver
import org.sagebionetworks.bridge.kmm.shared.cache.BridgeResourceDatabase
import java.util.UUID

internal actual fun testDatabaseDriver(): SqlDriver {
        return JdbcSqliteDriver(JdbcSqliteDriver.IN_MEMORY).apply {
            BridgeResourceDatabase.Schema.create(this)
        }
    }

internal actual fun randomUUID() = UUID.randomUUID().toString()
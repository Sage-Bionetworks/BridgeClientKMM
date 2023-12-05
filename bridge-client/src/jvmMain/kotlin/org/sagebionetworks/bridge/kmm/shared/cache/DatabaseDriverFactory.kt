package org.sagebionetworks.bridge.kmm.shared.cache

import app.cash.sqldelight.db.SqlDriver
import app.cash.sqldelight.driver.jdbc.sqlite.JdbcSqliteDriver

actual class DatabaseDriverFactory : DbDriverFactory {

    actual override fun createDriver(): SqlDriver {
        return JdbcSqliteDriver(JdbcSqliteDriver.IN_MEMORY).apply {
            BridgeResourceDatabase.Schema.create(this)
        }
    }

}
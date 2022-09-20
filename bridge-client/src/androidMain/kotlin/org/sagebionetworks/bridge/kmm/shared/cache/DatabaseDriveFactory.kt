package org.sagebionetworks.bridge.kmm.shared.cache

import android.content.Context
import app.cash.sqldelight.driver.android.AndroidSqliteDriver
import app.cash.sqldelight.db.SqlDriver

actual class DatabaseDriverFactory(private val context: Context) : DbDriverFactory {
    actual override fun createDriver(): SqlDriver {
        return AndroidSqliteDriver(BridgeResourceDatabase.Schema, context, "resource.db")
    }
}
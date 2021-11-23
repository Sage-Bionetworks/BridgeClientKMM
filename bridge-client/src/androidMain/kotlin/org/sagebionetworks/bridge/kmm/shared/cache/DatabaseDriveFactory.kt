package org.sagebionetworks.bridge.kmm.shared.cache

import android.content.Context
import com.squareup.sqldelight.android.AndroidSqliteDriver
import com.squareup.sqldelight.db.SqlDriver

actual class DatabaseDriverFactory(private val context: Context) : DbDriverFactory {
    actual override fun createDriver(): SqlDriver {
        return AndroidSqliteDriver(BridgeResourceDatabase.Schema, context, "resource.db")
    }
}
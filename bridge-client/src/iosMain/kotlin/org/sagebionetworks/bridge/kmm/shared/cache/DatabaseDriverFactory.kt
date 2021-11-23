package org.sagebionetworks.bridge.kmm.shared.cache

import com.squareup.sqldelight.db.SqlDriver
import com.squareup.sqldelight.drivers.native.NativeSqliteDriver

actual class DatabaseDriverFactory: DbDriverFactory {
    actual override fun createDriver(): SqlDriver {
        return NativeSqliteDriver(BridgeResourceDatabase.Schema, "resource.db")
    }
}
package org.sagebionetworks.bridge.kmm.shared

import com.squareup.sqldelight.db.SqlDriver
import com.squareup.sqldelight.drivers.native.NativeSqliteDriver
import org.sagebionetworks.bridge.kmm.shared.cache.BridgeResourceDatabase

    internal actual fun testDatabaseDriver(): SqlDriver {
        return NativeSqliteDriver(BridgeResourceDatabase.Schema, "BridgeResourceDatabase")
    }

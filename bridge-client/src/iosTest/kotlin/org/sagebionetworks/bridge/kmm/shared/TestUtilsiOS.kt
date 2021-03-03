package org.sagebionetworks.bridge.kmm.shared

import com.squareup.sqldelight.db.SqlDriver
import com.squareup.sqldelight.drivers.native.NativeSqliteDriver
import org.sagebionetworks.bridge.kmm.shared.cache.BridgeResourceDatabase
import org.sagebionetworks.bridge.kmm.shared.cache.DbDriverFactory

    internal actual fun testDatabaseDriverFactory(): DbDriverFactory {

        return TestDatabaseDriverFactory()
    }

    class TestDatabaseDriverFactory() : DbDriverFactory {
        override fun createDriver(): SqlDriver {
            return NativeSqliteDriver(BridgeResourceDatabase.Schema, "resource.db")
        }
    }
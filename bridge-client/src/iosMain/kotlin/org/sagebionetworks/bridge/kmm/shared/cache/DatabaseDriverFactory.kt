package org.sagebionetworks.bridge.kmm.shared.cache

import co.touchlab.sqliter.DatabaseConfiguration
import com.squareup.sqldelight.db.SqlDriver
import com.squareup.sqldelight.drivers.native.NativeSqliteDriver
import com.squareup.sqldelight.drivers.native.wrapConnection
import org.sagebionetworks.bridge.kmm.shared.IOSBridgeConfig
import platform.Foundation.NSFileManager

actual class DatabaseDriverFactory: DbDriverFactory {
    actual override fun createDriver(): SqlDriver {

        val schema = BridgeResourceDatabase.Schema
        val name = "resource.db"
        val path = IOSBridgeConfig.appGroupIdentifier?.let {
            NSFileManager.defaultManager.containerURLForSecurityApplicationGroupIdentifier(it)?.absoluteString
        }

        if (path == null) {
            return NativeSqliteDriver(schema, name)
        }
        else {
            // syoung 08/19/2022 This is a copy/paste of the configuration that the above code
            // uses to create the SQL driver. When updating versions of the SQLite code, this
            // constructor should be revisited.
            val configuration = DatabaseConfiguration(
                name = name,
                version = schema.version,
                extendedConfig = DatabaseConfiguration.Extended(
                    basePath = path
                ),
                create = { connection ->
                    wrapConnection(connection) { schema.create(it) }
                },
                upgrade = { connection, oldVersion, newVersion ->
                    wrapConnection(connection) { schema.migrate(it, oldVersion, newVersion) }
                }
            )
            return NativeSqliteDriver(configuration)
        }
    }
}
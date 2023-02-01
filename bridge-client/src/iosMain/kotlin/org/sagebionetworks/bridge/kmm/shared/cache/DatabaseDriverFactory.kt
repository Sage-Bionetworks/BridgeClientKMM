package org.sagebionetworks.bridge.kmm.shared.cache

import co.touchlab.kermit.Logger
import co.touchlab.sqliter.DatabaseConfiguration
import app.cash.sqldelight.db.SqlDriver
import app.cash.sqldelight.db.SqlSchema
import app.cash.sqldelight.driver.native.NativeSqliteDriver
import app.cash.sqldelight.driver.native.wrapConnection
import org.sagebionetworks.bridge.kmm.shared.IOSBridgeConfig
import platform.Foundation.*

actual class DatabaseDriverFactory: DbDriverFactory {
    actual override fun createDriver(): SqlDriver = SqliteDriverFactory.createDriver(BridgeResourceDatabase.Schema, "resource.db")
}

object SqliteDriverFactory {
    fun createDriver(schema: SqlSchema, name: String): NativeSqliteDriver {

        val path = IOSBridgeConfig.appGroupIdentifier?.let { groupId ->
            NSFileManager.defaultManager.containerURLForSecurityApplicationGroupIdentifier(groupId)?.let { baseURL ->
                NSURL.fileURLWithPath("databases", true, baseURL)
            }
        }

        if (path == null) {
            Logger.i("No app group identifier for database. Creating db in app support.")
            return NativeSqliteDriver(schema, name)
        }
        else {
            Logger.i("Creating or opening db at $path")

            try {

                // Create the directory if needed. Ignore the error if this fails.
                NSFileManager.defaultManager.createDirectoryAtURL(path, true, null, null)

                // syoung 08/19/2022 This is a copy/paste of the configuration that the above code
                // uses to create the SQL driver. When updating versions of the SQLite code, this
                // constructor should be revisited.
                val configuration = DatabaseConfiguration(
                    name = name,
                    version = schema.version,
                    extendedConfig = DatabaseConfiguration.Extended(
                        basePath = path.absoluteString
                    ),
                    create = { connection ->
                        wrapConnection(connection) { schema.create(it) }
                    },
                    upgrade = { connection, oldVersion, newVersion ->
                        wrapConnection(connection) { schema.migrate(it, oldVersion, newVersion) }
                    }
                )
                return NativeSqliteDriver(configuration)

            } catch (err: Exception) {
                Logger.e("Failed to create database in shared directory", err)
                return NativeSqliteDriver(schema, name)
            }
        }
    }
}
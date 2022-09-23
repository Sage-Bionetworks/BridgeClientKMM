package org.sagebionetworks.bridge.kmm.shared.di

import co.touchlab.sqliter.DatabaseConfiguration
import com.squareup.sqldelight.db.SqlDriver
import com.squareup.sqldelight.drivers.native.NativeSqliteDriver
import com.squareup.sqldelight.drivers.native.wrapConnection
import kotlinx.coroutines.CoroutineScope
import kotlinx.coroutines.MainScope
import org.koin.core.qualifier.named
import org.koin.dsl.module
import org.sagebionetworks.bridge.kmm.shared.BridgeConfig
import org.sagebionetworks.bridge.kmm.shared.IOSBridgeConfig
import org.sagebionetworks.bridge.kmm.shared.cache.BridgeResourceDatabase
import org.sagebionetworks.bridge.kmm.shared.cache.SqliteDriverFactory
import platform.Foundation.NSFileManager

actual val platformModule = module {
    single<SqlDriver> { SqliteDriverFactory.createDriver(BridgeResourceDatabase.Schema, "resource.db") }

    single<CoroutineScope>(named("background"))  { MainScope() }

    single<BridgeConfig> { IOSBridgeConfig }
}


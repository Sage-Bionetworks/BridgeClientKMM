package org.sagebionetworks.bridge.kmm.shared.di

import app.cash.sqldelight.db.SqlDriver
import kotlinx.coroutines.CoroutineScope
import kotlinx.coroutines.MainScope
import org.koin.core.qualifier.named
import org.koin.dsl.module
import org.sagebionetworks.bridge.kmm.shared.BridgeConfig
import org.sagebionetworks.bridge.kmm.shared.IOSBridgeConfig
import org.sagebionetworks.bridge.kmm.shared.apis.HttpIosUtil
import org.sagebionetworks.bridge.kmm.shared.apis.HttpUtil
import org.sagebionetworks.bridge.kmm.shared.cache.BridgeResourceDatabase
import org.sagebionetworks.bridge.kmm.shared.cache.SqliteDriverFactory

actual val platformModule = module {
    single<SqlDriver> { SqliteDriverFactory.createDriver(BridgeResourceDatabase.Schema, "resource.db") }

    single<CoroutineScope>(named("background"))  { MainScope() }

    single<BridgeConfig> { IOSBridgeConfig }

    single<HttpUtil> {HttpIosUtil()}
}


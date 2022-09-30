package org.sagebionetworks.bridge.kmm.shared.di

import app.cash.sqldelight.driver.android.AndroidSqliteDriver
import app.cash.sqldelight.db.SqlDriver
import kotlinx.coroutines.CoroutineScope
import kotlinx.coroutines.Dispatchers
import kotlinx.coroutines.SupervisorJob
import org.koin.androidx.workmanager.dsl.worker
import org.koin.core.module.Module
import org.koin.core.qualifier.named
import org.koin.dsl.module
import org.sagebionetworks.bridge.kmm.shared.AndroidBridgeConfig
import org.sagebionetworks.bridge.kmm.shared.BridgeConfig
import org.sagebionetworks.bridge.kmm.shared.cache.BridgeResourceDatabase
import org.sagebionetworks.bridge.kmm.shared.upload.CoroutineUploadWorker

actual val platformModule: Module = module {
    single<SqlDriver> {
        AndroidSqliteDriver(BridgeResourceDatabase.Schema, get(), "resource.db")
    }

    single<CoroutineScope>(named("background"))  { CoroutineScope(SupervisorJob() + Dispatchers.IO) }

    single<BridgeConfig> {AndroidBridgeConfig(get())}

    worker { CoroutineUploadWorker(get(), get(), get(), get()) }

}

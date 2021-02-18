package org.sagebionetworks.bridge.kmm.shared.di

import com.russhwolf.settings.AndroidSettings
import com.russhwolf.settings.Settings
import com.squareup.sqldelight.android.AndroidSqliteDriver
import com.squareup.sqldelight.db.SqlDriver
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

    worker { CoroutineUploadWorker(get(), get(), get()) }

}

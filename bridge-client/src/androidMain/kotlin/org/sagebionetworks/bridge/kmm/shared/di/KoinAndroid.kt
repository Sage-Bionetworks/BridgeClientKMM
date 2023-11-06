package org.sagebionetworks.bridge.kmm.shared.di

import androidx.security.crypto.EncryptedSharedPreferences
import androidx.security.crypto.MasterKey
import app.cash.sqldelight.driver.android.AndroidSqliteDriver
import app.cash.sqldelight.db.SqlDriver
import com.russhwolf.settings.Settings
import com.russhwolf.settings.SharedPreferencesSettings
import kotlinx.coroutines.CoroutineScope
import kotlinx.coroutines.Dispatchers
import kotlinx.coroutines.SupervisorJob
import org.koin.androidx.workmanager.dsl.worker
import org.koin.core.module.Module
import org.koin.core.qualifier.named
import org.koin.dsl.module
import org.sagebionetworks.bridge.kmm.shared.AndroidBridgeConfig
import org.sagebionetworks.bridge.kmm.shared.BridgeConfig
import org.sagebionetworks.bridge.kmm.shared.apis.HttpAndroidUtil
import org.sagebionetworks.bridge.kmm.shared.apis.HttpUtil
import org.sagebionetworks.bridge.kmm.shared.cache.BridgeResourceDatabase
import org.sagebionetworks.bridge.kmm.shared.cache.EncryptedSharedSettings
import org.sagebionetworks.bridge.kmm.shared.cache.EncryptedSharedSettingsImpl
import org.sagebionetworks.bridge.kmm.shared.upload.CoroutineUploadWorker

actual val platformModule: Module = module {
    single<SqlDriver> {
        AndroidSqliteDriver(BridgeResourceDatabase.Schema, get(), "resource.db")
    }

    single<CoroutineScope>(named("background"))  { CoroutineScope(SupervisorJob() + Dispatchers.IO) }

    single<BridgeConfig> {AndroidBridgeConfig(get())}

    worker { CoroutineUploadWorker(get(), get(), get(), get(), get(named("background")), get()) }

    single<HttpUtil> {HttpAndroidUtil(get())}

    single<Settings>(named(EncryptedSharedSettingsImpl.encryptedSettingsName)) {
        SharedPreferencesSettings(EncryptedSharedPreferences.create(
            get(),
            EncryptedSharedSettingsImpl.ENCRYPTED_DATABASE_NAME,
            MasterKey.Builder(get())
                .setKeyScheme(MasterKey.KeyScheme.AES256_GCM)
                .build(),
            EncryptedSharedPreferences.PrefKeyEncryptionScheme.AES256_SIV,
            EncryptedSharedPreferences.PrefValueEncryptionScheme.AES256_GCM
        ), false)
    }

}

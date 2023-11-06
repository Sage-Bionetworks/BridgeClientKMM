package org.sagebionetworks.bridge.kmm.shared.di

import app.cash.sqldelight.db.SqlDriver
import com.russhwolf.settings.KeychainSettings
import com.russhwolf.settings.Settings
import kotlinx.coroutines.CoroutineScope
import kotlinx.coroutines.MainScope
import org.koin.core.qualifier.named
import org.koin.dsl.module
import org.sagebionetworks.bridge.kmm.shared.BridgeConfig
import org.sagebionetworks.bridge.kmm.shared.IOSBridgeConfig
import org.sagebionetworks.bridge.kmm.shared.apis.HttpIosUtil
import org.sagebionetworks.bridge.kmm.shared.apis.HttpUtil
import org.sagebionetworks.bridge.kmm.shared.cache.BridgeResourceDatabase
import org.sagebionetworks.bridge.kmm.shared.cache.EncryptedSharedSettings
import org.sagebionetworks.bridge.kmm.shared.cache.EncryptedSharedSettingsImpl
import org.sagebionetworks.bridge.kmm.shared.cache.SqliteDriverFactory
import org.sagebionetworks.bridge.kmm.shared.repo.UploadRepo

actual val platformModule = module {
    single<SqlDriver> { SqliteDriverFactory.createDriver(BridgeResourceDatabase.Schema, "resource.db") }

    single<CoroutineScope>(named("background"))  { MainScope() }

    single<BridgeConfig> { IOSBridgeConfig }

    single<HttpUtil> {HttpIosUtil()}

    single<Settings>(named(EncryptedSharedSettingsImpl.encryptedSettingsName)) {
        KeychainSettings(service = EncryptedSharedSettingsImpl.ENCRYPTED_DATABASE_NAME)
    }
}


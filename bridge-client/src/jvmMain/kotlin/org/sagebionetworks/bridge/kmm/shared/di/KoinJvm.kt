package org.sagebionetworks.bridge.kmm.shared.di

import app.cash.sqldelight.db.SqlDriver
import com.russhwolf.settings.PreferencesSettings
import com.russhwolf.settings.Settings
import kotlinx.coroutines.CoroutineScope
import kotlinx.coroutines.Dispatchers
import kotlinx.coroutines.SupervisorJob
import org.koin.core.module.Module
import org.koin.core.qualifier.named
import org.koin.dsl.module
import org.sagebionetworks.bridge.kmm.shared.BridgeConfig
import org.sagebionetworks.bridge.kmm.shared.JvmBridgeConfig
import org.sagebionetworks.bridge.kmm.shared.apis.HttpJvmUtil
import org.sagebionetworks.bridge.kmm.shared.apis.HttpUtil
import org.sagebionetworks.bridge.kmm.shared.cache.DatabaseDriverFactory
import org.sagebionetworks.bridge.kmm.shared.cache.EncryptedSharedSettingsImpl
import java.util.prefs.Preferences

actual val platformModule: Module = module {
    single<SqlDriver> { DatabaseDriverFactory().createDriver() }

    single<CoroutineScope>(named("background"))  { CoroutineScope(SupervisorJob() + Dispatchers.IO) }

    single<BridgeConfig> {JvmBridgeConfig(appId = "bridge-client-kmm-integration")}

    single<HttpUtil> { HttpJvmUtil() }

    // TODO: Settings when running on JVM are not ecrypted -nbrown 11/30/23
    single<Settings>(named(EncryptedSharedSettingsImpl.encryptedSettingsName)) {
        val preferences = Preferences.userRoot()
        PreferencesSettings(preferences)
    }

}

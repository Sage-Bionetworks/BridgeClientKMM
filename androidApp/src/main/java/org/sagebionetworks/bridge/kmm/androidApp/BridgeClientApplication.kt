package org.sagebionetworks.bridge.kmm.androidApp

import android.app.Application
import org.koin.android.ext.koin.androidContext
import org.koin.android.ext.koin.androidLogger
import org.koin.androidx.workmanager.koin.workManagerFactory
import org.koin.core.component.KoinComponent
import org.sagebionetworks.bridge.kmm.androidApp.di.appModule
import org.sagebionetworks.bridge.kmm.presentation.di.presentationModule
import org.sagebionetworks.bridge.kmm.shared.di.initKoin

class BridgeClientApplication : Application(), KoinComponent {

    override fun onCreate() {
        super.onCreate()

        initKoin (enableNetworkLogs = BuildConfig.DEBUG){
            androidLogger()
            androidContext(this@BridgeClientApplication)
            workManagerFactory()
            modules(appModule)
            modules(presentationModule)
        }

    }

}
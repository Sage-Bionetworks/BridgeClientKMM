package org.sagebionetworks.bridge.kmm.shared.di

import kotlinx.coroutines.CoroutineScope
import org.koin.core.context.startKoin
import org.koin.core.module.Module
import org.koin.core.qualifier.named
import org.koin.dsl.KoinAppDeclaration
import org.koin.dsl.module
import org.sagebionetworks.bridge.kmm.shared.cache.ResourceDatabaseHelper
import org.sagebionetworks.bridge.kmm.shared.repo.AssessmentConfigRepo
import org.sagebionetworks.bridge.kmm.shared.repo.AuthenticationRepository

fun initKoin(enableNetworkLogs: Boolean = true, appDeclaration: KoinAppDeclaration = {}) =
    startKoin {
        appDeclaration()
        modules(platformModule)
        modules(commonModule())
        modules(httpClientModule(enableNetworkLogs = enableNetworkLogs))
    }

// called by iOS etc
fun initKoin() = initKoin(enableNetworkLogs = true) {}

fun commonModule() = module {
    single {ResourceDatabaseHelper(get())}

    single<AssessmentConfigRepo> {AssessmentConfigRepo(get(), get(), get(named("background"))) }
    single<AuthenticationRepository> {AuthenticationRepository(get())}

}

expect val platformModule: Module

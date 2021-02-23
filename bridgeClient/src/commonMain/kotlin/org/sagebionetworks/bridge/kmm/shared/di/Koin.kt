package org.sagebionetworks.bridge.kmm.shared.di

import org.koin.core.context.startKoin
import org.koin.core.module.Module
import org.koin.core.qualifier.named
import org.koin.dsl.KoinAppDeclaration
import org.koin.dsl.module
import org.sagebionetworks.bridge.kmm.shared.cache.ResourceDatabaseHelper
import org.sagebionetworks.bridge.kmm.shared.repo.AssessmentConfigRepo
import org.sagebionetworks.bridge.kmm.shared.repo.AuthenticationRepository

fun initKoin(enableNetworkLogs: Boolean = false, appDeclaration: KoinAppDeclaration = {}) =
    startKoin {
        appDeclaration()
        modules(bridgeClientkoinModules(enableNetworkLogs))
    }

// called by iOS
fun initKoin(enableNetworkLogs: Boolean) = initKoin(enableNetworkLogs) {}

fun bridgeClientkoinModules(enableNetworkLogs: Boolean): List<Module> {
        return listOf(platformModule, commonModule, httpClientModule(enableNetworkLogs))
    }

val commonModule = module {
    single {ResourceDatabaseHelper(get())}

    single<AssessmentConfigRepo> {AssessmentConfigRepo(get(), get(), get(named("background"))) }
    single<AuthenticationRepository> {AuthenticationRepository(get())}

}

expect val platformModule: Module

package org.sagebionetworks.bridge.kmm.shared.di

import org.koin.core.context.startKoin
import org.koin.core.module.Module
import org.koin.core.qualifier.named
import org.koin.dsl.KoinAppDeclaration
import org.koin.dsl.module
import org.sagebionetworks.bridge.kmm.shared.cache.ResourceDatabaseHelper
import org.sagebionetworks.bridge.kmm.shared.repo.*

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
    single<ScheduleTimelineRepo> {ScheduleTimelineRepo(get(), get(), get(), get(), get(named("background"))) }
    single<ActivityEventsRepo> { ActivityEventsRepo(get(), get(), get(named("background"))) }
    single<AdherenceRecordRepo> { AdherenceRecordRepo(get(), get(), get(named("background"))) }
    single<AuthenticationRepository> {AuthenticationRepository(get(named("authHttpClient")), get(), get())}
    single<AppConfigRepo> { AppConfigRepo(get(), get(), get(named("background")), get()) }
    single<StudyRepo> { StudyRepo(get(), get(), get(), get(named("background"))) }

}

expect val platformModule: Module

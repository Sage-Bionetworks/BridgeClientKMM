package org.sagebionetworks.bridge.kmm.shared.integration

import org.koin.core.context.startKoin
import org.koin.dsl.module
import org.koin.test.KoinTest
import org.sagebionetworks.bridge.kmm.shared.BaseTest
import org.sagebionetworks.bridge.kmm.shared.BridgeConfig
import org.sagebionetworks.bridge.kmm.shared.cache.ResourceDatabaseHelper
import org.sagebionetworks.bridge.kmm.shared.di.bridgeClientkoinModules
import org.sagebionetworks.bridge.kmm.shared.testDatabaseDriver
import kotlin.test.*

// Integration tests should be part of commonTest module, but https calls fail due to this bug:
// https://youtrack.jetbrains.com/issue/KT-38317 -nbrown 01/02/21
abstract class AbstractBaseIntegrationTest: BaseTest(), KoinTest {


    @BeforeTest
    fun setUp() {
        startKoin { modules(bridgeClientkoinModules(true).plus(testModule)) }
    }


    val testModule = module {
        single (override=true) { ResourceDatabaseHelper(testDatabaseDriver()) }
        single<BridgeConfig>(override=true) { TestBridgeConfig() }

    }

    class TestBridgeConfig: BridgeConfig {
        override val appId: String
            get() = "bridge-client-kmm-integration"
        override val appName: String
            get() = "BridgeClientKMM Integration Tests"
        override val sdkVersion: Int
            get() = 1
        override val appVersion: Int
            get() = 1
        override val appVersionName: String
            get() = "Android Integration Test"
        override val osName: String
            get() = "Android Integration Test"
        override val osVersion: String
            get() = "Android Integration Test"
        override val deviceName: String
            get() = "Android Integration Test"

    }
}
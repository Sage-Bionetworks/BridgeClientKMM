package org.sagebionetworks.bridge.kmm.shared.integration

import org.koin.core.context.startKoin
import org.koin.core.qualifier.named
import org.koin.dsl.module
import org.koin.test.KoinTest
import org.sagebionetworks.bridge.kmm.shared.BaseTest
import org.sagebionetworks.bridge.kmm.shared.BridgeConfig
import org.sagebionetworks.bridge.kmm.shared.PlatformConfig
import org.sagebionetworks.bridge.kmm.shared.TestEncryptedSharedSettings
import org.sagebionetworks.bridge.kmm.shared.apis.HttpUtil
import org.sagebionetworks.bridge.kmm.shared.cache.EncryptedSharedSettings
import org.sagebionetworks.bridge.kmm.shared.cache.ResourceDatabaseHelper
import org.sagebionetworks.bridge.kmm.shared.di.bridgeClientkoinModules
import org.sagebionetworks.bridge.kmm.shared.repo.AuthenticationRepository
import org.sagebionetworks.bridge.kmm.shared.testDatabaseDriver
import kotlin.test.*

// Integration tests should be part of commonTest module, but https calls fail due to this bug:
// https://youtrack.jetbrains.com/issue/KT-38317 -nbrown 01/02/21
abstract class AbstractBaseIntegrationTest: BaseTest(), KoinTest {

    companion object {
        private val testModule = module {
            single { ResourceDatabaseHelper(testDatabaseDriver()) }
            single<BridgeConfig> { TestBridgeConfig() }
            //Need to override for tests since HttpAndroidUtil requires a Context
            single<HttpUtil> { object: HttpUtil {
                override fun acceptLanguage(): String {
                    return "en-US,en"
                }
            } }
            //Need to override for tests since encryptedSharedSettings requires a Context
            single<AuthenticationRepository> {
                AuthenticationRepository(
                    authHttpClient = get(named("authHttpClient")),
                    bridgeConfig = get(),
                    database = get(),
                    backgroundScope =  get(named("background")),
                    encryptedSharedSettings = TestEncryptedSharedSettings()
                )
            }

        }
        init {
            startKoin { modules(bridgeClientkoinModules(true).plus(testModule)) }
        }
    }

    @BeforeTest
    fun setUp() {

    }

    // To run tests locally, add the external id to your local.properties file: testExternalId01=External_ID_Here -nbrown 9/27/22
    protected fun getBridgeTestUserExternalId(): String? {
        return System.getProperty("testExternalId01")
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
        override val bridgeEnvironment: PlatformConfig.BridgeEnvironment
            get() = PlatformConfig.BridgeEnvironment.PRODUCTION
        override val osName: String
            get() = "Android Integration Test"
        override val cacheCredentials: Boolean
            get() = true
        override val osVersion: String
            get() = "Android Integration Test"
        override val deviceName: String
            get() = "Android Integration Test"

    }
}

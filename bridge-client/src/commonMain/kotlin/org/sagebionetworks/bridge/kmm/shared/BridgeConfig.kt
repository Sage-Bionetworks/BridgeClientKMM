package org.sagebionetworks.bridge.kmm.shared

import org.sagebionetworks.bridge.kmm.shared.models.ClientInfo

interface PlatformConfig {
    enum class BridgeEnvironment {
        PRODUCTION {
            override fun domainSuffix() = ""
        },
        STAGING {
            override fun domainSuffix() = "-staging"
        },
        DEVELOPMENT {
            override fun domainSuffix() = "-develop"
        },
        CUSTOM {
            override fun domainSuffix() = "-custom"
        };

        abstract fun domainSuffix(): String

        fun basePath(): String {
            return "https://webservices${domainSuffix()}.sagebridge.org"
        }
    }

    val appId: String

    val appName: String

    val appVersion: Int

    val appVersionName: String

    val bridgeEnvironment: BridgeEnvironment

    val osVersion: String

    val deviceName: String

    val osName: String
}

interface BridgeConfig : PlatformConfig {

    val sdkVersion: Int

    /**
     * Uses [.getStudyName], [.getAppVersion], [.getDeviceName], [ ][VERSION.RELEASE], and [.getSdkVersion]
     *
     * @return user agent in HTTP header format expected by server
     */
    val userAgent: String
        get() {
            return "$appId/$appVersion ($deviceName; $osName/$osVersion)"
        }
}
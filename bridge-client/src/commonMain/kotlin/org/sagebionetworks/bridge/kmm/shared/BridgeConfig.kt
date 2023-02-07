package org.sagebionetworks.bridge.kmm.shared

import kotlinx.serialization.json.JsonElement
import kotlinx.serialization.json.JsonObject
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

fun PlatformConfig.buildClientData(input: JsonElement? = null, uploadId: String? = null): JsonElement {
    var clientData: JsonObject = input?.let {
        it as? JsonObject ?: JsonObject(mapOf("value" to it))
    } ?: JsonObject(mapOf())
    uploadId?.let {
        clientData.plus("uploadId" to it)
    }
    clientData.plus("osName" to osName)
    clientData.plus("deviceName" to deviceName)
    clientData.plus("osVersion" to osVersion)
    clientData.plus("appVersion" to appVersion)
    return clientData
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
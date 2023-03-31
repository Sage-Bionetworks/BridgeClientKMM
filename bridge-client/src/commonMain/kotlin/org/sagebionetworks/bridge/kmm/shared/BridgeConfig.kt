package org.sagebionetworks.bridge.kmm.shared

import kotlinx.serialization.json.JsonElement
import kotlinx.serialization.json.JsonObject
import kotlinx.serialization.json.JsonPrimitive
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
    val clientData = input?.let {
        (it as? JsonObject)?.toMutableMap() ?: mutableMapOf("value" to it)
    } ?: mutableMapOf()
    return  JsonObject(clientData.apply {
        uploadId?.let {
            this["uploadId"] = JsonPrimitive(it)
        }
        this["osName"] = JsonPrimitive(osName)
        this["deviceName"] = JsonPrimitive(deviceName)
        this["osVersion"] = JsonPrimitive(osVersion)
        this["appVersion"] = JsonPrimitive(appVersion)
    })
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
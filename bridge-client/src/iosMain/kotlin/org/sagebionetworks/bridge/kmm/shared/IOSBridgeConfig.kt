package org.sagebionetworks.bridge.kmm.shared

import kotlin.native.concurrent.AtomicReference
import kotlin.native.concurrent.freeze

interface IOSPlatformConfig : PlatformConfig {
    val appGroupIdentifier: String?
}

object IOSBridgeConfig  : BridgeConfig {

    private val atomicRef: AtomicReference<IOSPlatformConfig?> = AtomicReference(null)

    fun initialize(platformConfig : IOSPlatformConfig) {
        atomicRef.compareAndSet(null, platformConfig.freeze())
    }

    private val platformConfig: IOSPlatformConfig
        get() {
            return atomicRef.value ?: defaultPlatformConfig
        }
    private val defaultPlatformConfig = PlatformConfigImpl()

    override val sdkVersion: Int
        get() = 0   // TODO: syoung 06/07/2021 Figure out how to get the version of the BridgeClient framework.

    // Wrapped values

    val appGroupIdentifier: String?
        get() = platformConfig.appGroupIdentifier
    override val appId: String
        get() = platformConfig.appId
    override val appName: String
        get() = platformConfig.appName
    override val appVersion: Int
        get() = platformConfig.appVersion
    override val appVersionName: String
        get() = platformConfig.appVersionName
    override val bridgeEnvironment: PlatformConfig.BridgeEnvironment
        get() = platformConfig.bridgeEnvironment
    override val osName: String
        get() = platformConfig.osName
    override val osVersion: String
        get() = platformConfig.osVersion
    override val deviceName: String
        get() = platformConfig.deviceName
}

internal data class PlatformConfigImpl(
    override val appGroupIdentifier: String? = null,
    override val appId: String = "sage-assessment-test",
    override val appName: String = "Sage Assessment Test",
    override val appVersion: Int = 99,
    override val appVersionName: String = "Unknown",
    override val bridgeEnvironment: PlatformConfig.BridgeEnvironment = PlatformConfig.BridgeEnvironment.production,
    override val osVersion: String = "Unknown",
    override val deviceName: String = "Unknown",
    override val osName: String = "iOS") : IOSPlatformConfig


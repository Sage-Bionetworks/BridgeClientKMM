package org.sagebionetworks.bridge.kmm.shared

// TODO: Figure out dynamically loading some of these values when running on JVM -nbrown 11/30/23
data class JvmBridgeConfig(
    override val appId: String,
    override val appName: String = "BridgeClientKMM jvm",
    override val appVersion: Int = 1,
    override val appVersionName: String = "BridgeClientKMM jvm",
    override val bridgeEnvironment: PlatformConfig.BridgeEnvironment = PlatformConfig.BridgeEnvironment.PRODUCTION,
    override val osVersion: String = "BridgeClientKMM jvm",
    override val deviceName: String = "BridgeClientKMM jvm",
    override val osName: String = "BridgeClientKMM jvm",
    override val cacheCredentials: Boolean = false,
    override val sdkVersion: Int = 1
) : BridgeConfig
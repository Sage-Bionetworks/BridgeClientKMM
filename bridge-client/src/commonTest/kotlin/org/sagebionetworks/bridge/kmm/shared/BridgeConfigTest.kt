package org.sagebionetworks.bridge.kmm.shared

import kotlinx.serialization.json.JsonObject
import kotlinx.serialization.json.int
import kotlinx.serialization.json.jsonPrimitive
import org.sagebionetworks.bridge.kmm.shared.repo.TestBridgeConfig
import kotlin.test.Test
import kotlin.test.assertEquals

class BridgeConfigTest {

    @Test
    fun testBuildClientData() {
        val config = TestBridgeConfig()
        val clientData = config.buildClientData(null) as JsonObject
        assertEquals(config.osName, clientData["osName"]!!.jsonPrimitive.content)
        assertEquals(config.deviceName, clientData["deviceName"]!!.jsonPrimitive.content)
        assertEquals(config.osVersion, clientData["osVersion"]!!.jsonPrimitive.content)
        assertEquals(config.appVersion, clientData["appVersion"]!!.jsonPrimitive.int)

    }

}
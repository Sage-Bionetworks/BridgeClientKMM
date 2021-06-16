package org.sagebionetworks.bridge.kmm.shared

import kotlinx.serialization.json.Json
import kotlinx.serialization.json.JsonElement

class JsonElementDecoder(private val jsonString: String) {
    private val jsonCoder: Json = Json {}
    @Throws(Throwable::class)
    fun decodeObject(): JsonElement {
        try {
            return jsonCoder.parseToJsonElement(jsonString)
        } catch (err: Exception) {
            throw Throwable(err.message)
        }
    }
}


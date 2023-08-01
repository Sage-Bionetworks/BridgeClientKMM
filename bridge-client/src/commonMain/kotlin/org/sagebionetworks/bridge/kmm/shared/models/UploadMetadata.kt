package org.sagebionetworks.bridge.kmm.shared.models

import kotlinx.serialization.Serializable
import kotlinx.serialization.json.Json
import kotlinx.serialization.json.JsonElement
import kotlinx.serialization.json.jsonObject

@Serializable
data class UploadMetadata(
    val instanceGuid: String? = null,
    val eventTimestamp: String? = null,
    val startedOn: String? = null,
) {

    fun getId(): String? {
        return if (instanceGuid == null) null else "$instanceGuid|$eventTimestamp|$startedOn"
    }

    internal fun toJsonMap(): Map<String, JsonElement> {
        val jsonCoder = Json {
            ignoreUnknownKeys = true
            encodeDefaults = true
            explicitNulls = false
        }
        return jsonCoder.encodeToJsonElement(UploadMetadata.serializer(),this).jsonObject.toMap()
    }
}
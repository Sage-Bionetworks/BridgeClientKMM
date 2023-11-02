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
    internal fun toJsonMap(): Map<String, JsonElement> {
        val jsonCoder = Json {
            ignoreUnknownKeys = true
            encodeDefaults = true
            explicitNulls = false
        }
        return jsonCoder.encodeToJsonElement(UploadMetadata.serializer(),this).jsonObject.toMap()
    }
}

@Serializable
data class UploadRequestMetadata(
    val instanceGuid: String? = null,
    val eventTimestamp: String? = null,
    val startedOn: String? = null,
    val finishedOn: String? = null,
    val declined: Boolean? = null,
    val clientData: JsonElement? = null
) {

    constructor(adherenceRecord: AdherenceRecord) : this(
        instanceGuid = adherenceRecord.instanceGuid,
        eventTimestamp = adherenceRecord.eventTimestamp,
        startedOn = adherenceRecord.startedOn?.toString(),
        finishedOn = adherenceRecord.finishedOn?.toString(),
        declined = adherenceRecord.declined,
        clientData = adherenceRecord.clientData
    )

    internal fun toJsonMap(): Map<String, JsonElement> {
        val jsonCoder = Json {
            ignoreUnknownKeys = true
            encodeDefaults = true
            explicitNulls = false
        }
        return jsonCoder.encodeToJsonElement(UploadRequestMetadata.serializer(),this).jsonObject.toMap()
    }
}
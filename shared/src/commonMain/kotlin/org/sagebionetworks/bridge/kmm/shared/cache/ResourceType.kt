package org.sagebionetworks.bridge.kmm.shared.cache

import kotlinx.serialization.PolymorphicSerializer
import kotlinx.serialization.decodeFromString
import kotlinx.serialization.json.Json
import kotlin.reflect.KClass

// TODO: syoung 11/25/2020 I thought that the all caps with underscores was frowned upon? Shouldn't this be `AssessmentConfig`, etc.?

enum class ResourceType {
    ASSESSMENT_CONFIG()
}

fun <T: Any> Resource.loadResource(classOfT: KClass<T>): T {
    val jsonCoder = Json {  }
    return jsonCoder.decodeFromString(PolymorphicSerializer(classOfT), json)
}
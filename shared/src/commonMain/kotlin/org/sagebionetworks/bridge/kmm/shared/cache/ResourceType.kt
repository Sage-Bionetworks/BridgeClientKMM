package org.sagebionetworks.bridge.kmm.shared.cache

import kotlinx.serialization.PolymorphicSerializer
import kotlinx.serialization.decodeFromString
import kotlinx.serialization.json.Json
import org.sagebionetworks.bridge.kmm.shared.models.AssessmentConfig
import kotlin.reflect.KClass

enum class ResourceType() {
    ASSESSMENT_CONFIG() {
        override fun getClass(): KClass<AssessmentConfig> {
            return AssessmentConfig::class
        }
    };

    abstract fun getClass(): KClass<*>
}

enum class ResourceStatus {
    SUCCESS(),
    PENDING(),
    RETRY(),
    FAILED()
}

sealed class ResourceResult<out T : Any> {
    data class Success<out T : Any>(val data: T, val status: ResourceStatus) : ResourceResult<T>()
    //TODO: Failed reason
    data class Failed(val status: ResourceStatus) : ResourceResult<Nothing>()
    object InProgress : ResourceResult<Nothing>()
}

inline fun <reified T: Any> Resource.loadResource(): T? {
    json?.let {
        val jsonCoder = Json {ignoreUnknownKeys = true }
        return jsonCoder.decodeFromString(it)
    } ?: return null
}
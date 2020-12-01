package org.sagebionetworks.bridge.kmm.shared

import io.ktor.client.*
import io.ktor.client.engine.mock.*
import io.ktor.client.features.json.*
import io.ktor.client.features.json.serializer.*
import io.ktor.client.features.logging.*
import io.ktor.http.*
import kotlinx.serialization.json.Json
import org.sagebionetworks.bridge.kmm.shared.cache.DbDriverFactory

internal expect fun testDatabaseDriverFactory() : DbDriverFactory

fun getTestClient(json: String): HttpClient {
    val client = HttpClient(MockEngine) {
        install(JsonFeature) {
            serializer = KotlinxSerializer(kotlinx.serialization.json.Json {
                ignoreUnknownKeys = true
            })
        }
        install(Logging) {
            level = LogLevel.ALL
            logger = object : Logger {
                override fun log(message: String) {
                    println(message)
                }
            }
        }

        engine {
            addHandler { request ->
                val responseHeaders = headersOf("Content-Type" to listOf(ContentType.Application.Json.toString()))
                respond(json, headers = responseHeaders)
            }
        }
    }
    return client
}
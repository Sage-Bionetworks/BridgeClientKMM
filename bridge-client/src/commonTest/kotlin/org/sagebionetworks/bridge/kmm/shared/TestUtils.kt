package org.sagebionetworks.bridge.kmm.shared

import app.cash.sqldelight.db.SqlDriver
import io.ktor.client.*
import io.ktor.client.engine.*
import io.ktor.client.engine.mock.*
import io.ktor.client.plugins.contentnegotiation.*
import io.ktor.client.plugins.logging.*
import io.ktor.http.*
import io.ktor.serialization.kotlinx.json.*
import kotlinx.serialization.json.Json

internal expect fun testDatabaseDriver() : SqlDriver

fun getTestClient(json: String): HttpClient {
    val mockEngine = MockEngine.config {
        addHandler (
            getJsonReponseHandler(json)
        )
    }
    return getTestClient(mockEngine)
}

fun getTestClient(mockEngine: HttpClientEngineFactory<MockEngineConfig>) : HttpClient {
    return HttpClient(mockEngine) {
        install(ContentNegotiation) {
            json(Json {
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
        expectSuccess = true
    }
}

fun getJsonReponseHandler(json: String) : suspend MockRequestHandleScope.(io.ktor.client.request.HttpRequestData) -> io.ktor.client.request.HttpResponseData {
    return {request ->
        respond(json, headers = headersOf("Content-Type" to listOf(ContentType.Application.Json.toString())))
    }
}
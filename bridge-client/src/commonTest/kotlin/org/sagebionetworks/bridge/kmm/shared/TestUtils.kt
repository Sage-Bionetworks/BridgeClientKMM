package org.sagebionetworks.bridge.kmm.shared

import app.cash.sqldelight.db.SqlDriver
import io.ktor.client.*
import io.ktor.client.engine.*
import io.ktor.client.engine.mock.*
import io.ktor.client.plugins.*
import io.ktor.client.plugins.contentnegotiation.*
import io.ktor.client.plugins.logging.*
import io.ktor.client.request.*
import io.ktor.http.*
import io.ktor.serialization.kotlinx.json.*
import kotlinx.serialization.json.Json
import org.sagebionetworks.bridge.kmm.shared.apis.RefreshTokenFeature
import org.sagebionetworks.bridge.kmm.shared.apis.SessionTokenFeature

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
        install(UserAgent) {
            agent = "Unit Test agent"
        }
        install(SessionTokenFeature) {
            sessionTokenHeaderName = "Bridge-Session"
            sessionTokenProvider = object : SessionTokenFeature.SessionTokenProvider {

                override fun getSessionToken(): String? {
                    return "TestToken"
                }
            }
        }
        install(RefreshTokenFeature) {
            updateTokenHandler = suspend {
                true
            }
            isCredentialsActual = fun(request: HttpRequest): Boolean {
                // By always returning false, test can simulate an expired token by mocking a 401 response.
                // Other tests will not call this code.
                return false
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
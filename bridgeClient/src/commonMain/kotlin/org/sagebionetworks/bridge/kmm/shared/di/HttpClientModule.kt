package org.sagebionetworks.bridge.kmm.shared.di

import io.ktor.client.*
import io.ktor.client.features.*
import io.ktor.client.features.json.*
import io.ktor.client.features.json.serializer.*
import io.ktor.client.features.logging.*
import io.ktor.client.request.*
import org.koin.dsl.module
import org.sagebionetworks.bridge.kmm.shared.BridgeConfig
import org.sagebionetworks.bridge.kmm.shared.apis.RefreshTokenFeature
import org.sagebionetworks.bridge.kmm.shared.apis.SessionTokenFeature
import org.sagebionetworks.bridge.kmm.shared.repo.AuthenticationRepository

fun httpClientModule(enableNetworkLogs: Boolean) = module {
    single { createHttpClient(enableNetworkLogs, get(), get()) }
}

fun createHttpClient(enableNetworkLogs: Boolean, bridgeConfig: BridgeConfig, authenticationRepository: AuthenticationRepository) = HttpClient {
    val sessionTokenHeaderKey = "Bridge-Session"

    defaultRequest {

    }

    install(JsonFeature) {
        serializer = KotlinxSerializer(kotlinx.serialization.json.Json {
            ignoreUnknownKeys = true
        })
    }

    if (enableNetworkLogs) {
        install(Logging) {
            level = LogLevel.ALL
            logger = object : Logger {
                override fun log(message: String) {
                    println(message)
                }
            }
        }
    }
    install(SessionTokenFeature) {
        sessionTokenHeaderName = sessionTokenHeaderKey
        sessionTokenProvider = object: SessionTokenFeature.SessionTokenProvider {

            override fun getSessionToken(): String? {
                return authenticationRepository.session()?.sessionToken
            }
        }
    }
    install(RefreshTokenFeature) {
        updateTokenHandler = suspend {
            authenticationRepository.reAuth()
        }
        isCredentialsActual = fun(request: HttpRequest): Boolean {
            authenticationRepository.session()?.sessionToken?.let {
                return it.equals(request.headers.get(sessionTokenHeaderKey))
            }
            return true
        }

    }
}
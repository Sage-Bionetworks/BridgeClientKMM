package org.sagebionetworks.bridge.kmm.shared.di

import io.ktor.client.*
import io.ktor.client.features.*
import io.ktor.client.features.json.*
import io.ktor.client.features.json.serializer.*
import io.ktor.client.features.logging.*
import io.ktor.client.request.*
import io.ktor.client.statement.*
import org.koin.core.qualifier.named
import org.koin.dsl.module
import org.sagebionetworks.bridge.kmm.shared.BridgeConfig
import org.sagebionetworks.bridge.kmm.shared.apis.EtagFeature
import org.sagebionetworks.bridge.kmm.shared.apis.RefreshTokenFeature
import org.sagebionetworks.bridge.kmm.shared.apis.SessionTokenFeature
import org.sagebionetworks.bridge.kmm.shared.cache.ResourceDatabaseHelper
import org.sagebionetworks.bridge.kmm.shared.repo.AuthenticationRepository

fun httpClientModule(enableNetworkLogs: Boolean) = module {
    //HttpClient configured with session token and refresh token features for Bridge calls
    single { createBridgeHttpClient(enableNetworkLogs, get(), get(), get()) }

    //HttpClient configured for use with AuthenticationAPI, it needs its own HttpClient so as not to
    // include the re-authentication feature found in DefaultHttpClient, which would cause a dependency loop
    single<HttpClient>(named("authHttpClient")) { createHttpClient(enableNetworkLogs, get()) }

}

/**
 * Creates an HttpClient configured with session token and refresh token features for authenticated
 * Bridge calls.
 */
private fun createBridgeHttpClient(
    enableNetworkLogs: Boolean,
    bridgeConfig: BridgeConfig,
    authenticationRepository: AuthenticationRepository,
    etagStorageCache: ResourceDatabaseHelper
) = HttpClient {
    val sessionTokenHeaderKey = "Bridge-Session"

    install(UserAgent) {
        agent = bridgeConfig.userAgent
    }

    install(JsonFeature) {
        serializer = KotlinxSerializer(kotlinx.serialization.json.Json {
            ignoreUnknownKeys = true
        })
    }
    install(EtagFeature) {
        storageCache = etagStorageCache
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

    defaultRequest {
        // temporarily hard code to avoid a 404 when retrieving AppConfig - liujoshua 2021-09-21
        // TODO: Set Accept-Language based on device setting - liujoshua 2021-09-21
        // A Feature is likely needed. For example, on Android we may need to respond to
        // https://developer.android.com/reference/android/content/Intent.html#ACTION_LOCALE_CHANGED
        header("Accept-Language", "en-US,en")
    }

    install(SessionTokenFeature) {
        sessionTokenHeaderName = sessionTokenHeaderKey
        sessionTokenProvider = object : SessionTokenFeature.SessionTokenProvider {

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

private fun createHttpClient(enableNetworkLogs: Boolean, bridgeConfig: BridgeConfig) = HttpClient {

    install(UserAgent) {
        agent = bridgeConfig.userAgent
    }

    install(JsonFeature) {
        serializer = KotlinxSerializer(kotlinx.serialization.json.Json {
            ignoreUnknownKeys = true
        })
    }

    if (enableNetworkLogs) {
        install(Logging) {
            level = LogLevel.HEADERS //Don't log body since that could include password
            logger = object : Logger {
                override fun log(message: String) {
                    println(message)
                }
            }
        }
    }

    expectSuccess = false //Turns off automatic response code validation

    HttpResponseValidator {

        validateResponse { response ->

            val statusCode = response.status.value
            val originCall = response.call
            //Authentication calls return 412 when a user isn't consented
            if (statusCode < 300 || statusCode == 412) {
                return@validateResponse
            }

            val exceptionResponse = originCall.response
            val exceptionResponseText = exceptionResponse.readText()
            when (statusCode) {
                in 300..399 -> throw RedirectResponseException(exceptionResponse, exceptionResponseText)
                in 400..499 -> throw ClientRequestException(exceptionResponse, exceptionResponseText)
                in 500..599 -> throw ServerResponseException(exceptionResponse, exceptionResponseText)
                else -> throw ResponseException(exceptionResponse, exceptionResponseText)
            }
        }
    }

}



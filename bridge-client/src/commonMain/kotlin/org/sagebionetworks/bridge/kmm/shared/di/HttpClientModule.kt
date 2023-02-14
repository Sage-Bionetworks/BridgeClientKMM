package org.sagebionetworks.bridge.kmm.shared.di

import io.ktor.client.*
import io.ktor.client.engine.*
import io.ktor.client.plugins.*
import io.ktor.client.plugins.contentnegotiation.*
import io.ktor.client.plugins.logging.*
import io.ktor.client.request.*
import io.ktor.client.statement.*
import io.ktor.serialization.kotlinx.json.*
import kotlinx.serialization.json.Json
import org.koin.core.qualifier.named
import org.koin.dsl.module
import org.sagebionetworks.bridge.kmm.shared.BridgeConfig
import org.sagebionetworks.bridge.kmm.shared.apis.EtagFeature
import org.sagebionetworks.bridge.kmm.shared.apis.HttpUtil
import org.sagebionetworks.bridge.kmm.shared.apis.RefreshTokenFeature
import org.sagebionetworks.bridge.kmm.shared.apis.SessionTokenFeature
import org.sagebionetworks.bridge.kmm.shared.cache.ResourceDatabaseHelper
import org.sagebionetworks.bridge.kmm.shared.repo.AuthenticationProvider
import org.sagebionetworks.bridge.kmm.shared.repo.AuthenticationRepository

fun httpClientModule(enableNetworkLogs: Boolean) = module {
    //HttpClient configured with session token and refresh token features for Bridge calls
    single { createBridgeHttpClient(enableNetworkLogs, get(), get(), get(), get()) }

    //HttpClient configured for use with AuthenticationAPI, it needs its own HttpClient so as not to
    // include the re-authentication feature found in DefaultHttpClient, which would cause a dependency loop
    single<HttpClient>(named("authHttpClient")) { createAuthHttpClient(enableNetworkLogs, get(), get()) }

}

/**
 * Create a base HttpClient with any config that is shared between the authentication services
 * and the other services (which typically includes a session token).
 */
private fun HttpClient.appendBaseConfig(bridgeConfig: BridgeConfig, httpUtil: HttpUtil, logLevel: LogLevel?) =
    this.config {

    install(UserAgent) {
        agent = bridgeConfig.userAgent
    }

    install(ContentNegotiation) {
        json(Json {
            ignoreUnknownKeys = true
        })
    }

    if (logLevel != null) {
        install(Logging) {
            level = logLevel
            logger = object : Logger {
                override fun log(message: String) {
                    println(message)
                }
            }
        }
    }

    defaultRequest {
        header("Accept-Language", httpUtil.acceptLanguage())
    }
}

private fun createBridgeHttpClient(
    enableNetworkLogs: Boolean,
    bridgeConfig: BridgeConfig,
    authenticationRepository: AuthenticationRepository,
    etagStorageCache: ResourceDatabaseHelper,
    httpUtil: HttpUtil
) = HttpClient().appendDefaultConfig(enableNetworkLogs, bridgeConfig, authenticationRepository, etagStorageCache, httpUtil)

/**
 * Creates an HttpClient configured with session token and refresh token features for authenticated
 * Bridge calls.
 */
internal fun HttpClient.appendDefaultConfig(
    enableNetworkLogs: Boolean,
    bridgeConfig: BridgeConfig,
    authenticationRepository: AuthenticationProvider,
    etagStorageCache: ResourceDatabaseHelper,
    httpUtil: HttpUtil
) = this.appendBaseConfig(bridgeConfig, httpUtil, if (enableNetworkLogs) LogLevel.ALL else null).config {

    expectSuccess = true    // Turn on default of throwing exception for status code > 300

    val sessionTokenHeaderKey = "Bridge-Session"

    install(EtagFeature) {
        storageCache = etagStorageCache
    }

    install(SessionTokenFeature) {
        sessionTokenHeaderName = sessionTokenHeaderKey
        sessionTokenProvider = object : SessionTokenFeature.SessionTokenProvider {

            override fun getSessionToken(): String? {
                return authenticationRepository.session()?.sessionToken?.ifEmpty { null }
            }
        }
    }

    install(RefreshTokenFeature) {
        updateTokenHandler = suspend {
            authenticationRepository.reAuth()
        }
        isCredentialsActual = fun(request: HttpRequest): Boolean {
            authenticationRepository.session()?.sessionToken?.let {
                return it.isNotEmpty() && it.equals(request.headers.get(sessionTokenHeaderKey))
            }
            return true
        }
    }
}

private fun createAuthHttpClient(
    enableNetworkLogs: Boolean,
    bridgeConfig: BridgeConfig,
    httpUtil: HttpUtil
) = HttpClient().appendAuthConfig(enableNetworkLogs, bridgeConfig, httpUtil)

internal fun HttpClient.appendAuthConfig(
    enableNetworkLogs: Boolean,
    bridgeConfig: BridgeConfig,
    httpUtil: HttpUtil
) = this.appendBaseConfig(bridgeConfig, httpUtil, if (enableNetworkLogs) LogLevel.HEADERS else null).config {

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
            val exceptionResponseText = exceptionResponse.bodyAsText()
            when (statusCode) {
                in 300..399 -> throw RedirectResponseException(exceptionResponse, exceptionResponseText)
                in 400..499 -> throw ClientRequestException(exceptionResponse, exceptionResponseText)
                in 500..599 -> throw ServerResponseException(exceptionResponse, exceptionResponseText)
                else -> throw ResponseException(exceptionResponse, exceptionResponseText)
            }
        }
    }
}

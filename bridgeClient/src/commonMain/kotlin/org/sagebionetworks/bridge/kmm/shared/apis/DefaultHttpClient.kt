package org.sagebionetworks.bridge.kmm.shared.apis

import io.ktor.client.*
import io.ktor.client.features.*
import io.ktor.client.features.json.*
import io.ktor.client.features.json.serializer.*
import io.ktor.client.features.logging.*
import io.ktor.client.request.*
import org.sagebionetworks.bridge.kmm.shared.cache.AccountDAO
import org.sagebionetworks.bridge.kmm.shared.models.SignIn

object DefaultHttpClient {

    val httpClient = HttpClient {

        defaultRequest {
            
        }

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
        install(SessionTokenFeature) {
            // TODO: syoung 11/25/2020 Should this be a global key? I notice that it is also used below.
            sessionTokenHeaderName = "Bridge-Session"
            sessionTokenProvider = object: SessionTokenFeature.SessionTokenProvider {

                override fun getSessionToken(): String? {
                    return AccountDAO().sessionToken
                }
            }
        }
        install(RefreshTokenFeature) {
            updateTokenHandler = suspend {
                val accountDAO = AccountDAO()
                accountDAO.reauthToken?.let {
                    val signIn = SignIn(
                        accountDAO.appId,
                        accountDAO.email,
                        reauthToken = accountDAO.reauthToken
                    )
                    val authApi = AuthenticationApi()
                    val userSession = authApi.reauthenticate(signIn)
                    authApi.close()
                    accountDAO.sessionToken = userSession.sessionToken
                    accountDAO.reauthToken = userSession.reauthToken
                    true
                } ?: false
            }
            isCredentialsActual = fun(request: HttpRequest): Boolean {
                AccountDAO().sessionToken?.let {
                    return it.equals(request.headers.get("Bridge-Session"))
                }
                return true
            }

        }
    }
}

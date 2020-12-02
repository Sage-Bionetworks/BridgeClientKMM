/**
* Bridge Server Authentication API
*/
package org.sagebionetworks.bridge.kmm.shared.apis

import io.ktor.client.*
import io.ktor.client.features.json.*
import io.ktor.client.features.json.serializer.*
import io.ktor.client.features.logging.*
import org.sagebionetworks.bridge.kmm.shared.models.SignIn
import org.sagebionetworks.bridge.kmm.shared.models.UserSessionInfo

internal class AuthenticationApi(basePath: kotlin.String = "https://webservices.sagebridge.org") : AbstractApi(basePath) {

    // Authentication uses its own HttpClient so as not to include the re-authentication feature found in DefaultHttpClient,
    // which would cause a dependency loop
    override val httpClient = HttpClient {

        install(JsonFeature) {
            serializer = KotlinxSerializer(kotlinx.serialization.json.Json {
                ignoreUnknownKeys = true
            })
        }

        install(Logging) {
            level = LogLevel.ALL
            logger = object : Logger {
                override fun log(message: String) {
                    // TODO: syoung 11/25/2020 Given that this is an authentication service, is there a risk that the message will include PII?
                    println(message)
                }
            }
        }
        expectSuccess = false //Turns off automatic response code validation
    }

    /**
     * Close the httpclient used by this api
     */
    fun close() {
        httpClient.close()
    }

    /**
    * 
    * Using the reauthentication token supplied with a new session, request a new session from  the server. Updates the session&#39;s timeout value, and issues a new reauthentication token.  Reauthentication tokens can only be used one time.  
    * @param signIn Information to authenticate with the server 
    * @return UserSessionInfo
    */
    suspend fun reauthenticate(signIn: SignIn) : UserSessionInfo {
        return postData(signIn, "v3/auth/reauth")
    }


    /**
    * 
    * Send user credentials to authenticate with the Bridge server. Whether the server returns  200 (user successfully authenticated) or 412 (user has authenticated but has not yet  consented to participate in research), the response will contain a user session.   The session contains the \&quot;sessionToken\&quot; property with the token that must be used to interact  with other endpoints of the service. That value should be sent via the request header  \&quot;Bridge-Session\&quot; to any endpoint requiring authentication. The Bridge session token is  currently valid for 12 hours. However, your client application should be prepared to  re-authenticate on any call if it returns 401 (\&quot;Not authenticated\&quot;), as the session may  expire before this period for unforeseen reasons, like a server failure.  If the user has not yet consented, the session also contains detailed information about the  consent (or consents) the user must submit a signature for, before they will be allowed to  make further calls to Bridge. You can also implement logic to re-consent to updated consents,  if desired.  Note that a 412 response will not be sent for any account that has an administrative role. 
    * @param signIn Sign in information 
    * @return UserSessionInfo
    */
    suspend fun signIn(signIn: SignIn) : UserSessionInfo {
        return postData(signIn, "v3/auth/signIn")
    }

}

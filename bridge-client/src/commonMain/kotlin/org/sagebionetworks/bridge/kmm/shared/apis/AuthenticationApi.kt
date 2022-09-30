/**
* Bridge Server Authentication API
*/
package org.sagebionetworks.bridge.kmm.shared.apis

import io.ktor.client.*
import io.ktor.client.call.*
import io.ktor.client.request.*
import io.ktor.http.*
import org.sagebionetworks.bridge.kmm.shared.models.*

internal class AuthenticationApi(basePath: String = BASE_PATH, httpClient: HttpClient) : AbstractApi(basePath, httpClient) {

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
     * Does not require authentication. Will send an SMS message with a code that can be used to  call the server and generate a session.
     * @param phoneSignInRequest Information to trigger an SMS message for sign in.
     * @return Message
     */
    suspend fun requestPhoneSignIn(phoneSignInRequest: PhoneSignInRequest) : Message {
        return postData(phoneSignInRequest, "v3/auth/phone")
    }

    /**
     *
     * Resend an SMS message to the provided phone number asking the recipient to verify their  phone number. Whether the phone has been registered or not through sign up, this method will return 200 in order to prevent \&quot;account enumeration\&quot; security breaches.
     * @param identifier Phone number of participant (email address is ignored).
     * @return Message
     */
    suspend fun resendPhoneVerification(identifier: Identifier) : Message {
        return postData(identifier, "v3/auth/resendPhoneVerification")
    }

    /**
     *
     * Does not require authentication. Using the token supplied via an SMS message sent to the user, request a session from the server.
     * @param phoneSignIn
     * @return UserSessionInfoComposed
     */
    suspend fun signInViaPhone(phoneSignIn: PhoneSignin) : UserSessionInfo {
        return postData(phoneSignIn, "v3/auth/phone/signIn")
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

    suspend fun signOut(sessionInfo: UserSessionInfo) : Message {
        val builder = HttpRequestBuilder()

        builder.method = HttpMethod.Post
        builder.url {
            takeFrom(basePath)
            encodedPath = encodedPath.let { startingPath ->
                path("v4/auth/signOut")
                return@let startingPath + encodedPath.substring(1)
            }
        }

        with(builder.headers) {
            append("Accept", "application/json")
            append("Content-Type", "application/json; charset=UTF-8")
            append("Bridge-Session", sessionInfo.sessionToken)
        }

        try {
            return httpClient.post(builder).body()
        } catch (pipeline: ReceivePipelineException) {
            throw pipeline.cause
        }
    }

}

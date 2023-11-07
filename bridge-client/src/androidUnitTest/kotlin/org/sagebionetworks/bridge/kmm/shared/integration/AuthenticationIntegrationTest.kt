package org.sagebionetworks.bridge.kmm.shared.integration

import org.koin.core.component.inject
import org.sagebionetworks.bridge.kmm.shared.cache.ResourceResult
import org.sagebionetworks.bridge.kmm.shared.models.UserSessionInfo
import org.sagebionetworks.bridge.kmm.shared.repo.AuthenticationRepository
import kotlin.test.Test
import kotlin.test.assertFalse
import kotlin.test.assertNotEquals
import kotlin.test.assertNotNull
import kotlin.test.assertTrue

class AuthenticationIntegrationTest: AbstractBaseIntegrationTest() {

    private val authRepo by inject<AuthenticationRepository>()

    @Test
    fun testExternalIdSignIn() {
        runTest {
            authRepo.signOut()
            //Test signIn
            assertFalse(authRepo.isAuthenticated())
            val externalId = getBridgeTestUserExternalId()
            assertNotNull(externalId)
            val signInResult = authRepo.signInExternalId(externalId, externalId)
            assertTrue(signInResult is ResourceResult.Success<*>)
            val sessionInfo = signInResult.data as UserSessionInfo
            assertNotNull(sessionInfo.sessionToken)
            assertNotNull(sessionInfo.reauthToken)
            assertTrue(sessionInfo.authenticated == true)
            assertTrue(authRepo.isAuthenticated())
            //Test reauth
            assertTrue(authRepo.reAuth())
            assertTrue(authRepo.isAuthenticated())
            val updatedSession = authRepo.session()
            assertNotNull(updatedSession)
            assertNotEquals(updatedSession.reauthToken, sessionInfo.reauthToken)
            // Clear session token and reauth token
            authRepo.updateCachedSession(null, updatedSession.copy(reauthToken = "invalid-token", sessionToken = "", authenticated = false))
            //Test reauth using cached credentials
            assertTrue(authRepo.reAuth())
            assertTrue(authRepo.isAuthenticated())

            //Test signout
            authRepo.signOut()
            assertFalse(authRepo.isAuthenticated())

        }
    }


}
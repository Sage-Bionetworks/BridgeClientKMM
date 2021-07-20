package org.sagebionetworks.bridge.kmm.shared

import kotlinx.coroutines.MainScope
import kotlinx.coroutines.cancel
import kotlinx.coroutines.flow.collect
import kotlinx.coroutines.launch
import org.koin.core.component.KoinComponent
import org.koin.core.component.inject
import org.sagebionetworks.bridge.kmm.shared.cache.ResourceResult
import org.sagebionetworks.bridge.kmm.shared.cache.ResourceStatus
import org.sagebionetworks.bridge.kmm.shared.models.UserSessionInfo
import org.sagebionetworks.bridge.kmm.shared.repo.AuthenticationRepository

class NativeAuthenticationManager(
    private val viewUpdate: (UserSessionInfo?) -> Unit
) : KoinComponent {

    private val authManager : AuthenticationRepository by inject(mode = LazyThreadSafetyMode.NONE)

    private val scope = MainScope()

    fun observeUserSessionInfo() {
        scope.launch {
            authManager.sessionAsFlow().collect { resourceResult ->
                viewUpdate(resourceResult)
            }
        }
    }

    fun isAuthenticated() : Boolean {
        return authManager.isAuthenticated()
    }

    fun session() : UserSessionInfo? {
        return authManager.session()
    }

    fun signInEmail(userName: String, password: String, callBack: (UserSessionInfo?, ResourceStatus) -> Unit) {
        scope.launch {
            when(val userSessionResult = authManager.signInEmail(email = userName, password = password)) {
                is ResourceResult.Success -> callBack(userSessionResult.data, userSessionResult.status)
                is ResourceResult.Failed -> callBack(null, userSessionResult.status)
            }
        }
    }

    fun signInExternalId(externalId: String, password: String?, callBack: (UserSessionInfo?, ResourceStatus) -> Unit) {
        scope.launch {
            when(val userSessionResult = authManager.signInExternalId(externalId, password ?: externalId)) {
                is ResourceResult.Success -> callBack(userSessionResult.data, userSessionResult.status)
                is ResourceResult.Failed -> callBack(null, userSessionResult.status)
            }
        }
    }

    fun signOut() {
        scope.launch {
            authManager.signOut()
        }
    }

    fun onCleared() {
        scope.cancel()
    }
}
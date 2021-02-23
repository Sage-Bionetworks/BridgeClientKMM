package org.sagebionetworks.bridge.kmm.shared

import kotlinx.coroutines.MainScope
import kotlinx.coroutines.cancel
import kotlinx.coroutines.flow.collect
import kotlinx.coroutines.launch
import org.koin.core.component.KoinComponent
import org.koin.core.component.inject
import org.sagebionetworks.bridge.kmm.shared.cache.ResourceResult
import org.sagebionetworks.bridge.kmm.shared.models.UserSessionInfo
import org.sagebionetworks.bridge.kmm.shared.repo.AssessmentConfigRepo
import org.sagebionetworks.bridge.kmm.shared.repo.AuthenticationRepository

class NativeAssessmentViewModel (
    private val viewUpdate: (String?) -> Unit
) : KoinComponent {

    private val repo : AssessmentConfigRepo by inject(mode = LazyThreadSafetyMode.NONE)
    private val authManager: AuthenticationRepository by inject(mode = LazyThreadSafetyMode.NONE)

    private val scope = MainScope()

    fun observeAssessmentConfig(identifier: String) {
        scope.launch {
            repo.getAssessmentById(identifier).collect { resourceResult ->
                when (resourceResult) {
                    is ResourceResult.Success -> {viewUpdate(resourceResult.data.config.toString())}
                    is ResourceResult.InProgress -> {viewUpdate("loading...")}
                    is ResourceResult.Failed -> {viewUpdate("failed to load")}
                }
            }
        }
    }

    fun isAuthenticated() : Boolean {
        return authManager.isAuthenticated()
    }

    fun signIn(userName: String, password: String, callBack: (UserSessionInfo?) -> Unit) {
        scope.launch {
            val userSession = authManager.signIn(email = userName, password = password)
            callBack(userSession)
        }
    }

    fun onCleared() {
        scope.cancel()
    }


}
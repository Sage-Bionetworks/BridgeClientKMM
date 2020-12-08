package org.sagebionetworks.bridge.kmm.shared

import kotlinx.coroutines.MainScope
import kotlinx.coroutines.cancel
import kotlinx.coroutines.flow.collect
import kotlinx.coroutines.launch
import org.sagebionetworks.bridge.kmm.shared.cache.DbDriverFactory
import org.sagebionetworks.bridge.kmm.shared.cache.ResourceResult
import org.sagebionetworks.bridge.kmm.shared.models.UserSessionInfo
import org.sagebionetworks.bridge.kmm.shared.repo.AssessmentConfigRepo
import org.sagebionetworks.bridge.kmm.shared.repo.AuthenticationRepository

class NativeAssessmentViewModel (
    databaseDriverFactory: DbDriverFactory,
    private val viewUpdate: (String?) -> Unit
) {

    private val scope = MainScope()
    private val repo = AssessmentConfigRepo(databaseDriverFactory, scope)

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

    fun signIn(userName: String, password: String, callBack: (UserSessionInfo?) -> Unit) {
        scope.launch {
            val userSession = AuthenticationRepository().signIn(email = userName, password = password)
            callBack(userSession)
        }
    }

    fun onCleared() {
        scope.cancel()
    }


}
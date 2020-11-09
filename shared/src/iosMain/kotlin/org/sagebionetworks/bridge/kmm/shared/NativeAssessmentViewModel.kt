package org.sagebionetworks.bridge.kmm.shared

import kotlinx.coroutines.MainScope
import kotlinx.coroutines.cancel
import kotlinx.coroutines.flow.collect
import kotlinx.coroutines.launch
import org.sagebionetworks.bridge.kmm.shared.models.UserSessionInfo
import org.sagebionetworks.bridge.kmm.shared.repo.AssessmentConfigRepo
import org.sagebionetworks.bridge.kmm.shared.repo.AuthenticationRepository

class NativeAssessmentViewModel (
    private val repo: AssessmentConfigRepo,
    private val viewUpdate: (String?) -> Unit
) {

    fun observeAssessmentConfig(identifier: String) {
        MainScope().launch {
            repo.getAssessmentById(identifier).collect { config ->
                viewUpdate(config)
            }
        }
    }

    fun signIn(userName: String, password: String, callBack: (UserSessionInfo?) -> Unit) {
        MainScope().launch {
            val userSession = AuthenticationRepository().signIn(email = userName, password = password)
            callBack(userSession)
        }
    }


}
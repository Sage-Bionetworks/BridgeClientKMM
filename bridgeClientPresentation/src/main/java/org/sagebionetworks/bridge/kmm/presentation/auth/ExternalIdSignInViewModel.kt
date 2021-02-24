package org.sagebionetworks.bridge.kmm.presentation.auth

import androidx.lifecycle.LiveData
import androidx.lifecycle.MutableLiveData
import androidx.lifecycle.ViewModel
import androidx.lifecycle.viewModelScope
import kotlinx.coroutines.launch
import org.sagebionetworks.bridge.kmm.shared.repo.AuthenticationRepository

class ExternalIdSignInViewModel(private val authenticationRepository: AuthenticationRepository) : ViewModel() {

    private val _signInResult = MutableLiveData<SignInResult>()
    val signInResult: LiveData<SignInResult> = _signInResult

    fun login(externalId: String) {

        viewModelScope.launch {

            val userSession = authenticationRepository.signInExternalId(externalId, externalId)
            if (userSession.authenticated == true) {
                _signInResult.value = SignInResult.Success
            } else {
                _signInResult.value = SignInResult.Failed
            }
        }
    }

}

sealed class SignInResult {
    object Success : SignInResult()
    //TODO: figure out what additional info we need to pass -nbrown 02/23/2021
    object Failed : SignInResult()
}

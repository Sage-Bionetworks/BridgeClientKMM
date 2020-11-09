package org.sagebionetworks.bridge.kmm.shared.cache

import com.russhwolf.settings.Settings
import com.russhwolf.settings.invoke
import org.sagebionetworks.bridge.kmm.shared.models.UserSessionInfo


class AccountDAO() {

    private val settings = Settings()

    /*
     * Removes all saved data
     */
    fun clear() {
        for (key in KEYS) {
            settings.remove(key)
        }
    }

    val hasSignedIn = reauthToken != null

    val appId = "sage-assessment-test"

    var email: String?
        get() = settings.getStringOrNull(KEY_EMAIL)
        set(email) {
            email?.let {
                settings.putString(KEY_EMAIL, email)
            }?: settings.remove(KEY_EMAIL)
        }

    var sessionToken: String?
        get() = settings.getStringOrNull(KEY_SESSION_TOKEN)
        set(sessionToken) {
            sessionToken?.let {
                settings.putString(KEY_SESSION_TOKEN, sessionToken)
            }?: settings.remove(KEY_SESSION_TOKEN)
        }

    var reauthToken: String?
        get() = settings.getStringOrNull(KEY_REAUTH_TOKEN)
        set(reauthToken) {
            reauthToken?.let {
                settings.putString(KEY_REAUTH_TOKEN, reauthToken)
            }?: settings.remove(KEY_REAUTH_TOKEN)
        }


    companion object {
        private const val KEY_EMAIL = "email"
        private const val KEY_SESSION_TOKEN = "sessionToken"
        private const val KEY_REAUTH_TOKEN = "reauthToken"

        private val KEYS = listOf(KEY_EMAIL, KEY_SESSION_TOKEN, KEY_REAUTH_TOKEN)
    }
}
package org.sagebionetworks.bridge.kmm.shared.cache

import com.russhwolf.settings.Settings
import com.russhwolf.settings.get
import com.russhwolf.settings.set

interface EncryptedSharedSettings {
    var pwd: String?
}

class EncryptedSharedSettingsImpl (
    private val encryptedSettings: Settings,
) : EncryptedSharedSettings {

    override var pwd: String?
        get() {
            return encryptedSettings[PWD_KEY]
        }
        set(value) {
            encryptedSettings[PWD_KEY] = value
        }

    companion object {
        const val ENCRYPTED_DATABASE_NAME = "ENCRYPTED_SETTINGS"
        const val encryptedSettingsName = "encryptedSettings"
        // Keys of values stored in settings
        private const val PWD_KEY = "PWD_KEY"
    }
}
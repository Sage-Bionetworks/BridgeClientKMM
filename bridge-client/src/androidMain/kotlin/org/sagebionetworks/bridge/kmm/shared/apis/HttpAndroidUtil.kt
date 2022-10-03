package org.sagebionetworks.bridge.kmm.shared.apis

import android.content.Context
import android.os.Build

class HttpAndroidUtil(private val applicationContext: Context): HttpUtil {

    override fun acceptLanguage(): String {
        return if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.N) {
            applicationContext.resources.configuration.locales.toLanguageTags()
        } else {
            applicationContext.resources.configuration.locale.toLanguageTag()
        }
    }

}
package org.sagebionetworks.bridge.kmm.shared.apis

import platform.Foundation.NSLocale
import platform.Foundation.preferredLanguages

class HttpIosUtil : HttpUtil {

    override fun acceptLanguage(): String {
        return NSLocale.preferredLanguages.joinToString(", ")
    }

}
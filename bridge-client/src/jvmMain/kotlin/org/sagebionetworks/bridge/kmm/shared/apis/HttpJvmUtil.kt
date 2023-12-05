package org.sagebionetworks.bridge.kmm.shared.apis

class HttpJvmUtil : HttpUtil {

    override fun acceptLanguage(): String {
        return "en-US"
    }
}
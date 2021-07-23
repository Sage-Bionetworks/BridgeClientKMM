package org.sagebionetworks.bridge.kmm.shared

import kotlinx.serialization.json.Json
import kotlinx.serialization.json.JsonElement
import platform.Foundation.*
import org.sagebionetworks.bridge.kmm.shared.models.AdherenceRecord
import org.sagebionetworks.bridge.kmm.shared.models.Study
import org.sagebionetworks.bridge.kmm.shared.models.UserSessionInfo
import org.sagebionetworks.bridge.mpp.network.generated.models.AppConfig

class JsonElementDecoder(private val jsonData: NSData) {
    private val jsonCoder: Json = Json {}
    @Throws(Throwable::class)
    fun decodeObject(): JsonElement {
        try {
            val jsonString = jsonData.toUTF8String()
            return jsonCoder.parseToJsonElement(jsonString!!)
        } catch (err: Exception) {
            throw Throwable(err.message)
        }
    }
}

// syoung 07/23/2021 from https://github.com/JetBrains/kotlin-native/issues/2146

fun String.toNSData(): NSData? =
    NSString.create(string = this).dataUsingEncoding(NSUTF8StringEncoding)

fun NSData.toUTF8String(): String? =
    NSString.create(data = this, encoding = NSUTF8StringEncoding)?.toString()

// syoung 07/23/2021 There is a bug in the Kotlin KMM serialization where the
// clientData object is **not** a JsonElement, but is instead an NSDictionary
// subclass. As such, it does not respond to the selector if `encodeObject()` is
// called which causes a crash. The following code is an attempt to work-around
// this issue.
//
//@Throws(Throwable::class)
//fun JsonElement.encodeObject(): NSData {
//    val jsonCoder: Json = Json {}
//    try {
//        val jsonString = this.toString()
//        return jsonString.toNSData()!!
//    } catch (err: Exception) {
//        throw Throwable(err.message)
//    }
//}

fun AppConfig.configElementJson(identifier: String) : NSData? {
    return this.configElements?.get(identifier)?.toString()?.toNSData()
}

fun AppConfig.clientDataJson() : NSData? {
    return this.clientData?.toString()?.toNSData()
}

fun Study.clientDataJson() : NSData? {
    return this.clientData?.toString()?.toNSData()
}

fun UserSessionInfo.clientDataJson() : NSData? {
    return this.clientData?.toString()?.toNSData()
}

fun AdherenceRecord.clientDataJson() : NSData? {
    return this.clientData?.toString()?.toNSData()
}

fun NativeAdherenceRecord.clientDataJson() : NSData? {
    return this.clientData?.toString()?.toNSData()
}


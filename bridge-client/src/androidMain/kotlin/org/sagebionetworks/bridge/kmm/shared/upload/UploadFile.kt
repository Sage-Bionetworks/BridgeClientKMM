package org.sagebionetworks.bridge.kmm.shared.upload

import kotlinx.datetime.Instant
import kotlinx.serialization.Serializable
import org.sagebionetworks.bridge.mpp.network.generated.models.UploadRequest

@Serializable
data class UploadFile (
    val filePath: String,
    val contentType: String,
    val fileLength: Long,
    val md5Hash: String,
    val encrypted: Boolean = true,
    val metadata: Map<kotlin.String, kotlinx.serialization.json.JsonElement>? = null,
    val sessionExpires: Instant? = null // Delay doing upload until after session expires
) {

    internal fun getUploadFileResourceId(): String {
        return "uploadFile-$filePath"
    }

    internal fun getUploadSessionResourceId(): String {
        return "uploadSession--$filePath"
    }

    internal fun getUploadRequest(): UploadRequest {
        return UploadRequest(
            name = filePath.subSequence(filePath.lastIndexOf("/")+1, filePath.length).toString(),
            contentLength = fileLength,
            contentMd5 = md5Hash,
            contentType = contentType,
            encrypted = encrypted,
            metadata = metadata,
            type = "UploadRequest"
        )
    }

}
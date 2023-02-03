package org.sagebionetworks.bridge.kmm.shared.upload

import kotlinx.datetime.Instant
import kotlinx.serialization.Serializable
import org.sagebionetworks.bridge.kmm.shared.models.UploadRequest

@Serializable
data class UploadFile (
    val filePath: String,
    val contentType: String,
    val fileLength: Long,
    val md5Hash: String,
    val encrypted: Boolean = true,
    val metadata: Map<String, kotlinx.serialization.json.JsonElement>? = null,
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
            contentMd5 = md5Hash.trim(), //Old md5 algorithm was sometimes including newline character at end, trim() is to fix old stuck uploads -nbrown 1/20/23
            contentType = contentType,
            encrypted = encrypted,
            metadata = metadata,
            type = "UploadRequest"
        )
    }

}
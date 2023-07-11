package org.sagebionetworks.bridge.kmm.shared.models

import kotlinx.datetime.Instant
import kotlinx.serialization.Serializable

@Serializable
data class UploadFile (
    val filePath: String,
    val contentType: String,
    val fileLength: Long,
    val md5Hash: String,
    val encrypted: Boolean = true,
    val metadata: UploadMetadata? = null,

    // TODO: Deprecate on Android. This is not supported on iOS. - syoung 07/10/2023
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
            metadata = metadata?.toJsonMap(),
            type = "UploadRequest"
        )
    }

}
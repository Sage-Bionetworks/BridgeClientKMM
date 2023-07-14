package org.sagebionetworks.bridge.kmm.shared.models

import kotlinx.datetime.Instant
import kotlinx.serialization.Serializable

@Serializable
data class UploadFile (
    override val filePath: String,
    val contentType: String,
    val fileLength: Long,
    val md5Hash: String,
    val encrypted: Boolean = true,
    val metadata: UploadMetadata? = null,

    // TODO: Deprecate on Android. This is not supported on iOS. - syoung 07/10/2023
    val sessionExpires: Instant? = null // Delay doing upload until after session expires
) : UploadFileIdentifiable {

    internal fun getSecondaryId(): String {
        // TODO: syoung 07/14/2023 Refactor use of secondaryId on Android to use adherence record unique id (instanceGuid|eventTimestamp|startedOn)
        return metadata?.instanceGuid ?: filename()
    }

    internal fun filename(): String {
        return filePath.subSequence(filePath.lastIndexOf("/")+1, filePath.length).toString()
    }

    internal fun getUploadRequest(): UploadRequest {
        return UploadRequest(
            name = filename(),
            contentLength = fileLength,
            contentMd5 = md5Hash.trim(), //Old md5 algorithm was sometimes including newline character at end, trim() is to fix old stuck uploads -nbrown 1/20/23
            contentType = contentType,
            encrypted = encrypted,
            metadata = metadata?.toJsonMap(),
            type = "UploadRequest"
        )
    }

}

interface UploadFileIdentifiable {
    val filePath: String
}

internal fun UploadFileIdentifiable.getUploadFileResourceId(): String {
    return "uploadFile-$filePath"
}

internal fun UploadFileIdentifiable.getUploadSessionResourceId(): String {
    return "uploadSession--$filePath"
}
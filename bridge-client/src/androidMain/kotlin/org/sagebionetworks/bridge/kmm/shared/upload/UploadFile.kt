package org.sagebionetworks.bridge.kmm.shared.upload

import kotlinx.serialization.Serializable
import org.sagebionetworks.bridge.mpp.network.generated.models.UploadRequest

@Serializable
data class UploadFile (
    val filename: String,
    val contentType: String,
    val fileLength: Long,
    val md5Hash: String,
    val encrypted: Boolean = true
) {

    internal fun getUploadFileResourceId(): String {
        return "uploadFile-$filename"
    }

    internal fun getUploadSessionResourceId(): String {
        return "uploadSession--$filename"
    }

    internal fun getUploadRequest(): UploadRequest {
        return UploadRequest(
            name = filename,
            contentLength = fileLength,
            contentMd5 = md5Hash,
            contentType = contentType,
            encrypted = encrypted,
            type = "UploadRequest"
        )
    }

}
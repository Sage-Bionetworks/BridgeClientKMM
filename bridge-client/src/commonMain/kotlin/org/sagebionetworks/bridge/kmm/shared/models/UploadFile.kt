package org.sagebionetworks.bridge.kmm.shared.models

import kotlinx.serialization.Serializable
import org.sagebionetworks.bridge.kmm.shared.repo.AdherenceRecordRepo

@Serializable
data class UploadFile (
    override val filePath: String,
    val contentType: String,
    val fileLength: Long,
    val md5Hash: String?,
    val encrypted: Boolean = true,
    val metadata: UploadMetadata? = null,
    val s3UploadType: S3UploadType = S3UploadType.STUDY_DATA,
) : UploadFileIdentifiable {

    internal fun getSecondaryId(): String {
        // TODO: syoung 07/14/2023 Refactor use of secondaryId on Android to use adherence record unique id (instanceGuid|eventTimestamp|startedOn)
        return metadata?.instanceGuid ?: filename()
    }

    internal fun filename(): String {
        return filePath.subSequence(filePath.lastIndexOf("/")+1, filePath.length).toString()
    }

    internal fun getUploadRequest(adherenceRepo: AdherenceRecordRepo?): UploadRequest {
        val adherenceRecord = if (metadata?.instanceGuid != null && metadata?.startedOn != null) {
            adherenceRepo?.getCachedAdherenceRecord(metadata.instanceGuid, metadata.startedOn)
        } else {
            null
        }
        val requestMetadata = adherenceRecord?.let { UploadRequestMetadata(adherenceRecord).toJsonMap() } ?: metadata?.toJsonMap()

        return UploadRequest(
            name = filename(),
            contentLength = fileLength,
            contentMd5 = md5Hash?.trim() ?: "", //Old md5 algorithm was sometimes including newline character at end, trim() is to fix old stuck uploads -nbrown 1/20/23
            contentType = contentType,
            encrypted = encrypted,
            metadata = requestMetadata,
            type = "UploadRequest"
        )
    }

    internal fun getS3RequestHeaders(): Map<String, String> {
        var headers = mapOf(
            "Content-Length" to "$fileLength",
            "Content-Type" to contentType,
        )
        if (md5Hash != null) {
            headers = headers.plus(
                "Content-MD5" to md5Hash.trim(), //Old md5 algorithm was sometimes including newline character at end, trim() is to fix old stuck uploads -nbrown 1/20/23
            )
        }
        return headers
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

internal fun UploadFileIdentifiable.getUploadedFileRecordResourceId(): String {
    return "uploadedFileRecord--$filePath"
}

internal class UploadFileId(override val filePath: String) : UploadFileIdentifiable

enum class S3UploadType {
    STUDY_DATA,
    PARTICIPANT_DATA    // TODO: syoung 07/202023 Support uploading participant data.
}
package org.sagebionetworks.bridge.kmm.shared.models

import kotlinx.datetime.Instant

data class UploadedFileRecord(
    override val filePath: String,
    val uploadTimestamp: Instant,
    val uploadSessionId: String? = null,
    val metadata: UploadMetadata? = null,
) : UploadFileIdentifiable


package org.sagebionetworks.bridge.kmm.shared.models

import kotlinx.serialization.Serializable

data class S3UploadSession (
    /* The file path for the file. */
    override val filePath: String,
    /* The content type of the file. */
    val contentType: String,
    /* The upload ID. The client needs to use this ID to call Bridge when the upload is complete. */
    val uploadSessionId: String,
    /* A pre-signed URL for doing a PUT upload of the data. The URL will remain valid for 24 hours once created on the Bridge side.  */
    val url: String,
    /* The headers to add to the S3 request. */
    val requestHeaders: Map<String, String>,
) : UploadFileIdentifiable

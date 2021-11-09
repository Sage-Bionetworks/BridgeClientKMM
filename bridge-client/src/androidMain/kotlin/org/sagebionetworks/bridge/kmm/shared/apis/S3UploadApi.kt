package org.sagebionetworks.bridge.kmm.shared.apis

import io.ktor.client.*
import io.ktor.client.call.*
import io.ktor.client.content.*
import io.ktor.client.request.*
import io.ktor.http.*
import org.sagebionetworks.bridge.kmm.shared.upload.UploadFile
import java.io.File

class S3UploadApi(private val httpClient: HttpClient) {

    suspend fun uploadFile(url: String, uploadFile: UploadFile) {
        // LocalFileContent is jvm only, we could probably write our own using Okio if we need
        // this on iOS before it is available in Ktor -nbrown 1/5/21
        val fileRequest =
            LocalFileContent(File(uploadFile.filePath), ContentType.parse(uploadFile.contentType))

        try {
            return httpClient.put(url) {
                body = fileRequest
                method = HttpMethod.Put
                with(headers) {
                    append("Content-MD5", uploadFile.md5Hash)
                }
            }
        } catch (pipeline: ReceivePipelineException) {
            throw pipeline.cause
        }
    }
}


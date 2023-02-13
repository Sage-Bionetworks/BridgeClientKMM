package org.sagebionetworks.bridge.kmm.shared.apis

import io.ktor.client.*
import io.ktor.client.call.*
import io.ktor.client.content.*
import io.ktor.client.request.*
import io.ktor.client.statement.*
import io.ktor.http.*
import org.sagebionetworks.bridge.kmm.shared.upload.UploadFile
import java.io.File

internal class S3UploadApi(private val httpClient: HttpClient) {

    suspend fun uploadFile(url: String, uploadFile: UploadFile) : HttpResponse {
        // LocalFileContent is jvm only, we could probably write our own using Okio if we need
        // this on iOS before it is available in Ktor -nbrown 1/5/21
        val fileRequest =
            LocalFileContent(File(uploadFile.filePath), ContentType.parse(uploadFile.contentType))

        try {
            return httpClient.put(url) {
                setBody(fileRequest)
                method = HttpMethod.Put
                with(headers) {
                    //Old md5 algorithm was sometimes including newline character at end, trim() is to fix old stuck uploads -nbrown 1/20/23
                    append("Content-MD5", uploadFile.md5Hash.trim())
                }
            }
        } catch (pipeline: ReceivePipelineException) {
            throw pipeline.cause
        }
    }
}


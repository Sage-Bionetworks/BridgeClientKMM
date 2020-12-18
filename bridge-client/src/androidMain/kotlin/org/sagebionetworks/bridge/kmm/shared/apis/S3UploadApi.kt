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
        //LocalFileContent is jvm only
        val fileRequest = LocalFileContent(File(uploadFile.filename))

        try {
            return httpClient.put<Unit>(url) {
                body = fileRequest
                method = HttpMethod.Post
                with(headers) {
                    append("Content-MD5", uploadFile.md5Hash)
                }
            }
        } catch (pipeline: ReceivePipelineException) {
            throw pipeline.cause
        }

    }

}


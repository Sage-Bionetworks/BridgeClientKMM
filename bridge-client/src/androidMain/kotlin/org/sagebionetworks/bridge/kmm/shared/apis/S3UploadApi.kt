package org.sagebionetworks.bridge.kmm.shared.apis

import android.os.Build
import androidx.annotation.RequiresApi
import io.ktor.client.HttpClient
import io.ktor.client.call.ReceivePipelineException
import io.ktor.client.content.LocalFileContent
import io.ktor.client.request.put
import io.ktor.http.ContentType
import io.ktor.http.HttpMethod
import org.sagebionetworks.bridge.kmm.shared.upload.UploadFile
import java.io.File

class S3UploadApi(private val httpClient: HttpClient) {

    suspend fun uploadFile(url: String, uploadFile: UploadFile) {
        // LocalFileContent is jvm only, we could probably write our own using Okio if we need
        // this on iOS before it is available in Ktor -nbrown 1/5/21
        val fileRequest =
            LocalFileContent(File(uploadFile.filePath), ContentType.parse(uploadFile.contentType))

        try {
            return httpClient.put<Unit>(url) {
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


package org.sagebionetworks.bridge.kmm.shared.upload

import co.touchlab.kermit.Logger
import io.ktor.client.*
import kotlinx.coroutines.CoroutineScope
import kotlinx.datetime.*
import okio.FileSystem
import okio.Path.Companion.toPath
import org.sagebionetworks.bridge.kmm.shared.apis.S3UploadApi
import org.sagebionetworks.bridge.kmm.shared.cache.ResourceDatabaseHelper
import org.sagebionetworks.bridge.kmm.shared.models.UploadFile
import org.sagebionetworks.bridge.kmm.shared.models.UploadSession
import org.sagebionetworks.bridge.kmm.shared.repo.UploadRepo

internal class UploadManager(
    httpClient: HttpClient,
    databaseHelper: ResourceDatabaseHelper,
    backgroundScope: CoroutineScope,
) : UploadRepo(httpClient, databaseHelper, backgroundScope) {

    private val s3UploadApi = S3UploadApi(httpClient = httpClient)

    suspend fun processUploads(): Boolean {
        getUploadFiles().forEach {
            try {
                processUploadFile(it)
            } catch (error: Throwable) {
                Logger.e("Failed to process upload", error)
            }
        }
        return processFinishedUploads()
    }

    private suspend fun processUploadFile(uploadFile: UploadFile) {
        if (uploadFile.sessionExpires != null && Clock.System.now().toEpochMilliseconds() < uploadFile.sessionExpires.toEpochMilliseconds()) {
            // If we have a sessionExpires value, we need to wait to upload
            return
        }
        //Does upload order matter to Bridge? -nbrown 01/11/21
        val uploadSession = getUploadSession(uploadFile)
        uploadSession?.let {
            uploadToS3(uploadFile, uploadSession)
            completeUploadSession(uploadSession, uploadFile.getUploadSessionResourceId())
        }
    }

    private suspend fun uploadToS3(uploadFile: UploadFile, uploadSession: UploadSession) {
        //Make call to S3 using url from UploadSession
        try {
            Logger.d("uploadingToS3 $uploadFile")
            s3UploadApi.uploadFile(uploadSession.url, uploadFile) //TODO: Handle network exceptions -nbrown 4/26/21
            FileSystem.SYSTEM.delete(uploadFile.filePath.toPath()) //TODO: Handle delete failure -nbrown 12/16/20
            removeUploadFile(uploadFile)
        } catch (error: Throwable) {
            Logger.e("Error uploadingToS3 $uploadFile", error)

            //TODO: Handle failure cases -nbrown 12/16/20
            throw error
        }
    }

}
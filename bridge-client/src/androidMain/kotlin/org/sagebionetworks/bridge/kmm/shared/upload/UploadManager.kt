package org.sagebionetworks.bridge.kmm.shared.upload

import co.touchlab.kermit.Logger
import io.ktor.client.*
import kotlinx.coroutines.CoroutineScope
import okio.FileSystem
import okio.Path.Companion.toPath
import org.sagebionetworks.bridge.kmm.shared.apis.S3UploadApi
import org.sagebionetworks.bridge.kmm.shared.cache.ResourceDatabaseHelper
import org.sagebionetworks.bridge.kmm.shared.cache.ResourceType
import org.sagebionetworks.bridge.kmm.shared.cache.loadResource
import org.sagebionetworks.bridge.kmm.shared.models.UploadFile
import org.sagebionetworks.bridge.kmm.shared.models.UploadSession
import org.sagebionetworks.bridge.kmm.shared.models.getUploadSessionResourceId
import org.sagebionetworks.bridge.kmm.shared.repo.AdherenceRecordRepo
import org.sagebionetworks.bridge.kmm.shared.repo.UploadRepo

internal class UploadManager(
    httpClient: HttpClient,
    databaseHelper: ResourceDatabaseHelper,
    backgroundScope: CoroutineScope,
    adherenceRecordRepo: AdherenceRecordRepo?,
) : UploadRepo(httpClient, databaseHelper, backgroundScope, adherenceRecordRepo) {

    private val s3UploadApi = S3UploadApi(httpClient = httpClient)

    suspend fun processUploads(): Boolean {
        getUploadFiles().forEach {
            try {
                processUploadFile(it)
            } catch (error: Throwable) {
                Logger.e("Failed to process upload", error)
            }
        }
        processFinishedUploads()
        processFinishedUploadsV1()
        return database.getResourcesCount(listOf(ResourceType.FILE_UPLOAD)) == 0L
    }

    private suspend fun processFinishedUploadsV1() {
        // Check if all the UploadFiles have been uploaded to S3 and the UploadFile has been
        // removed.
        if (database.getResourcesCount(listOf(ResourceType.FILE_UPLOAD)) > 0L) return

        // If so, need to look for UploadSession records that were not marked as needSave
        // so that the call is made to Bridge to mark them as "completed". This is b/c the
        // there may be in-flight uploads that need to be handled from a previous version
        // of the app using this library.
        for (resource in database.getResources(
            ResourceType.UPLOAD_SESSION,
            ResourceDatabaseHelper.APP_WIDE_STUDY_ID
        )) {
            resource.loadResource<UploadSession>()?.let {
                completeUploadSession(it.id, resource.identifier)
            }
        }
    }

    private suspend fun processUploadFile(uploadFile: UploadFile) {
        // Does upload order matter to Bridge? -nbrown 01/11/21
        val uploadSession = getUploadSession(uploadFile)
        uploadSession?.let {
            uploadToS3(uploadFile, uploadSession)
            completeUploadSession(uploadSession.id, uploadFile.getUploadSessionResourceId())
        }
    }

    private suspend fun uploadToS3(uploadFile: UploadFile, uploadSession: UploadSession) {
        //Make call to S3 using url from UploadSession
        try {
            Logger.d("uploadingToS3 $uploadFile")
            s3UploadApi.uploadFile(uploadSession.url, uploadFile) //TODO: Handle network exceptions -nbrown 4/26/21
            FileSystem.SYSTEM.delete(uploadFile.filePath.toPath()) //TODO: Handle delete failure -nbrown 12/16/20
            markUploadFileFinished(uploadFile, uploadSession.id)
        } catch (error: Throwable) {
            Logger.e("Error uploadingToS3 $uploadFile", error)

            //TODO: Handle failure cases -nbrown 12/16/20
            throw error
        }
    }

}
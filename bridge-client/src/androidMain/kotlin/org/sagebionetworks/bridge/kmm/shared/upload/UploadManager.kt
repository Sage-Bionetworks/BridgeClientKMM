package org.sagebionetworks.bridge.kmm.shared.upload

import io.ktor.client.*
import kotlinx.datetime.*
import kotlinx.serialization.encodeToString
import kotlinx.serialization.json.Json
import okio.ExperimentalFileSystem
import okio.FileSystem
import okio.Path
import okio.Path.Companion.toPath
import org.sagebionetworks.bridge.kmm.shared.apis.S3UploadApi
import org.sagebionetworks.bridge.kmm.shared.apis.UploadsApi
import org.sagebionetworks.bridge.kmm.shared.cache.DbDriverFactory
import org.sagebionetworks.bridge.kmm.shared.cache.ResourceDatabaseHelper
import org.sagebionetworks.bridge.kmm.shared.cache.ResourceType
import org.sagebionetworks.bridge.kmm.shared.cache.loadResource
import org.sagebionetworks.bridge.kmm.shared.repo.AbstractResourceRepo
import org.sagebionetworks.bridge.mpp.network.generated.models.UploadRequest
import org.sagebionetworks.bridge.mpp.network.generated.models.UploadSession

class UploadManager(
    httpClient: HttpClient,
    databaseDriverFactory: DbDriverFactory
) {

    companion object {
        // minimum number of minutes from now an expiration should be
        private const val UPLOAD_EXPIRY_WINDOW_MINUTES = 30
    }

    private val uploadsApi = UploadsApi(httpClient = httpClient)
    private val s3UploadApi = S3UploadApi(httpClient = httpClient)
    internal val database = ResourceDatabaseHelper(databaseDriverFactory)


    /**
     * Clears all queued uploads.
     */
    fun clearUploads() {
        database.removeAllResources(ResourceType.FILE_UPLOAD)
        database.removeAllResources(ResourceType.UPLOAD_SESSION)
    }

    suspend fun processUploads(): Boolean {
        for (resource in database.getResources(ResourceType.FILE_UPLOAD)) {
            resource.loadResource<UploadFile>()?.let {
                processUploadFile(it)
            }
        }
        //Check that all uploads succeeded and have been removed
        return database.getResources(ResourceType.FILE_UPLOAD).isEmpty()
    }

    private suspend fun processUploadFile(uploadFile: UploadFile) {
        //Does upload order matter to Bridge? -nbrown 01/11/21
        val uploadSession = getUploadSession(uploadFile)
        uploadSession?.let {
            uploadToS3(uploadFile, uploadSession)
        }
    }

    /**
     * Retrieves cached UploadSession (if one exists), else requests one from Bridge and caches session
     * before returning it. This method is responsible for ensuring that upload session has not expired and is valid.
     */
    private suspend fun getUploadSession(uploadFile: UploadFile): UploadSession? {
        val identifier = uploadFile.getUploadSessionResourceId()
        val resource = database.getResource(identifier)
        resource?.let {
            val uploadSession = resource.loadResource<UploadSession>()
            uploadSession?.expires?.let {
                val desiredMinimumExpiration = Clock.System.now().plus(
                    UPLOAD_EXPIRY_WINDOW_MINUTES,
                    DateTimeUnit.MINUTE,
                    TimeZone.currentSystemDefault()
                )
                val expires = Instant.parse(uploadSession.expires)
                if (expires.compareTo(desiredMinimumExpiration) < 0) {
                    //return cached upload session
                    return uploadSession
                }
            }
        }
        val updatedResource = AbstractResourceRepo.remoteLoadResource(
            database = database,
            identifier = identifier,
            resourceType = ResourceType.UPLOAD_SESSION,
            curResource = null,
            remoteLoad = {loadRemoteUploadSession(uploadFile.getUploadRequest())}
        )
        //TODO: Need to think through error handling if we are unable to get an UploadSession -nbrown 12/16/20
        return updatedResource.loadResource<UploadSession>()
    }

    private suspend fun loadRemoteUploadSession(uploadRequest: UploadRequest): String {
        return Json.encodeToString(uploadsApi.requestUploadSession(uploadRequest))
    }

    @OptIn(ExperimentalFileSystem::class)
    private suspend fun uploadToS3(uploadFile: UploadFile, uploadSession: UploadSession) {
        //Make call to S3 using url from UploadSession
        try {
            s3UploadApi.uploadFile(uploadSession.url, uploadFile)
            FileSystem.SYSTEM.delete(uploadFile.filePath.toPath(Path.DIRECTORY_SEPARATOR)) //TODO: Handle delete failure -nbrown 12/16/20
            //Remove UploadFile unless we want to keep a history of successful uploads?
            database.removeResource(uploadFile.getUploadFileResourceId())
            database.removeResource(uploadFile.getUploadSessionResourceId())
        } catch (error: Throwable) {
            //TODO: Handle failure cases -nbrown 12/16/20
            throw error
        }
    }




}
package org.sagebionetworks.bridge.kmm.shared.repo

import co.touchlab.kermit.Logger
import co.touchlab.stately.ensureNeverFrozen
import io.ktor.client.HttpClient
import kotlinx.coroutines.CoroutineScope
import kotlinx.coroutines.flow.Flow
import kotlinx.datetime.Clock
import kotlinx.datetime.DateTimeUnit
import kotlinx.datetime.Instant
import kotlinx.datetime.TimeZone
import kotlinx.datetime.plus
import kotlinx.serialization.encodeToString
import kotlinx.serialization.json.Json
import org.sagebionetworks.bridge.kmm.shared.apis.UploadsApi
import org.sagebionetworks.bridge.kmm.shared.cache.Resource
import org.sagebionetworks.bridge.kmm.shared.cache.ResourceDatabaseHelper
import org.sagebionetworks.bridge.kmm.shared.cache.ResourceStatus
import org.sagebionetworks.bridge.kmm.shared.cache.ResourceType
import org.sagebionetworks.bridge.kmm.shared.cache.loadResource
import org.sagebionetworks.bridge.kmm.shared.models.UploadFile
import org.sagebionetworks.bridge.kmm.shared.models.UploadFileIdentifiable
import org.sagebionetworks.bridge.kmm.shared.models.UploadRequest
import org.sagebionetworks.bridge.kmm.shared.models.UploadSession
import org.sagebionetworks.bridge.kmm.shared.models.getUploadFileResourceId
import org.sagebionetworks.bridge.kmm.shared.models.getUploadSessionResourceId

internal open class UploadRepo(
    httpClient: HttpClient,
    databaseHelper: ResourceDatabaseHelper,
    backgroundScope: CoroutineScope,
) : AbstractResourceRepo(databaseHelper, backgroundScope) {

    companion object {
        // minimum number of minutes from now an expiration should be
        private const val UPLOAD_EXPIRY_WINDOW_MINUTES = 30
    }

    init {
        ensureNeverFrozen()
    }

    private var uploadsApi = UploadsApi(
        httpClient = httpClient
    )

    /**
     * Clears all queued uploads.
     */
    fun clearUploads() {
        database.removeAllResources(
            ResourceType.FILE_UPLOAD,
            ResourceDatabaseHelper.APP_WIDE_STUDY_ID
        )
        database.removeAllResources(
            ResourceType.UPLOAD_SESSION,
            ResourceDatabaseHelper.APP_WIDE_STUDY_ID
        )
    }

    /**
     * Get all the [UploadFile] records from the local cache. This will include files with an
     * outstanding S3 upload in progress.
     */
    fun getUploadFiles(): List<UploadFile> {
        val resources = database.getResources(
            ResourceType.FILE_UPLOAD,
            ResourceDatabaseHelper.APP_WIDE_STUDY_ID
        )
        return resources.mapNotNull { it.loadResource() }
    }

    /**
     * Remove the [UploadFile] from the local cache and send "upload complete" message to Bridge.
     * This is called after successfully uploading to S3.
     *
     * Note: Deleting the file must be handled natively as a part of S3 upload rather than using
     * expect/actually. This is done b/c on iOS, the file path can change with OS version changes
     * and the [UploadFile] only keeps a pointer to the invariant file path. syoung 07/14/2023
     */
    suspend fun didFinishUploadFile(uploadFile: UploadFileIdentifiable, uploadSessionId: String?) {
        val resourceId = uploadFile.getUploadSessionResourceId()
        val resource = database.getResource(resourceId, ResourceType.UPLOAD_SESSION,
            ResourceDatabaseHelper.APP_WIDE_STUDY_ID
        )?.copy(needSave = true)
        database.database.transaction {
            resource?.let {
                database.insertUpdateResource(it)
            }
            database.removeResource(
                uploadFile.getUploadFileResourceId(),
                ResourceType.FILE_UPLOAD,
                ResourceDatabaseHelper.APP_WIDE_STUDY_ID
            )
        }
        completeUploadSession(uploadSessionId, resourceId)
    }

    /**
     * Retrieves cached UploadSession (if one exists), else requests one from Bridge and caches session
     * before returning it. This method is responsible for ensuring that upload session has not expired and is valid.
     */
    suspend fun getUploadSession(uploadFile: UploadFile): UploadSession? {
        val identifier = uploadFile.getUploadSessionResourceId()
        val resource = database.getResource(identifier, ResourceType.UPLOAD_SESSION,
            ResourceDatabaseHelper.APP_WIDE_STUDY_ID
        )
        resource?.let {
            val uploadSession = resource.loadResource<UploadSession>()
            uploadSession?.expires?.let {
                val desiredMinimumExpiration = Clock.System.now().plus(
                    UPLOAD_EXPIRY_WINDOW_MINUTES,
                    DateTimeUnit.MINUTE,
                    TimeZone.currentSystemDefault()
                )
                val expires = Instant.parse(uploadSession.expires)
                if (expires < desiredMinimumExpiration) {
                    //return cached upload session
                    return uploadSession
                }
            }
        }
        val updatedResource = remoteLoadResource(
            database = database,
            identifier = identifier,
            resourceType = ResourceType.UPLOAD_SESSION,
            studyId = ResourceDatabaseHelper.APP_WIDE_STUDY_ID,
            curResource = null,
            remoteLoad = {loadRemoteUploadSession(uploadFile.getUploadRequest())}
        )
        //TODO: Need to think through error handling if we are unable to get an UploadSession -nbrown 12/16/20
        return updatedResource.loadResource()
    }

    private suspend fun loadRemoteUploadSession(uploadRequest: UploadRequest): String {
        try {
            return Json.encodeToString(uploadsApi.requestUploadSession(uploadRequest))
        } catch (throwable: Throwable) {
            Logger.e("Error trying to get upload session", throwable)
            throw throwable
        }
    }

    suspend fun completeUploadSession(uploadSessionId: String?, resourceId: String) {
        uploadSessionId?.let {
            uploadsApi.completeUploadSession(it)
            database.removeResource(
                resourceId,
                ResourceType.UPLOAD_SESSION,
                ResourceDatabaseHelper.APP_WIDE_STUDY_ID
            )
        }
    }

    /**
     * Process any [UploadSession] records where the upload to S3 has been completed, but Bridge
     * has not been notified.
     */
    suspend fun processFinishedUploads() {
        // Check if we have any sessions that have been uploaded and still need completing
        for (resource in database.getResourcesNeedSave(
            ResourceType.UPLOAD_SESSION,
            ResourceDatabaseHelper.APP_WIDE_STUDY_ID
        )) {
            resource.loadResource<UploadSession>()?.let {
                completeUploadSession(it.id, resource.identifier)
            }
        }
    }

}
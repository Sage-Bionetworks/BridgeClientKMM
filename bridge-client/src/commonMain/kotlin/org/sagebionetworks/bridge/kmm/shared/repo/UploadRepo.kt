package org.sagebionetworks.bridge.kmm.shared.repo

import co.touchlab.kermit.Logger
import co.touchlab.stately.ensureNeverFrozen
import io.ktor.client.HttpClient
import kotlinx.coroutines.CoroutineScope
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
import org.sagebionetworks.bridge.kmm.shared.models.UploadRequest
import org.sagebionetworks.bridge.kmm.shared.models.UploadSession

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
     * Get all the [UploadFile]s from the local cache. This will include files with an outstanding
     * S3 upload in progress.
     */
    fun getUploadFiles(): List<UploadFile> {
        val resources = database.getResources(
            ResourceType.FILE_UPLOAD,
            ResourceDatabaseHelper.APP_WIDE_STUDY_ID
        )
        return resources.mapNotNull { it.loadResource() }
    }

    /**
     * Store the [UploadFile] to the local cache. This is called before requesting an S3 upload session.
     */
    fun storeUploadFile(uploadFile: UploadFile) {
        //Store uploadFile in local cache
        val resource = Resource(
            identifier = uploadFile.getUploadFileResourceId(),
            type = ResourceType.FILE_UPLOAD,
            secondaryId = uploadFile.getSecondaryId(),
            studyId = ResourceDatabaseHelper.APP_WIDE_STUDY_ID,
            json = Json.encodeToString(uploadFile),
            lastUpdate = Clock.System.now().toEpochMilliseconds(),
            status = ResourceStatus.SUCCESS,
            needSave = false
        )
        database.insertUpdateResource(resource)
    }

    /**
     * Remove the [UploadFile] from the local cache. This is called after successfully uploading to S3.
     */
    fun removeUploadFile(uploadFile: UploadFile) {
        database.removeResource(
            uploadFile.getUploadFileResourceId(),
            ResourceType.FILE_UPLOAD,
            ResourceDatabaseHelper.APP_WIDE_STUDY_ID
        )
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

    suspend fun completeUploadSession(uploadSession: UploadSession, resourceid: String) {
        uploadSession.id?.let {
            uploadsApi.completeUploadSession(uploadSession.id)
            database.removeResource(
                resourceid,
                ResourceType.UPLOAD_SESSION,
                ResourceDatabaseHelper.APP_WIDE_STUDY_ID
            )
        }
    }

    suspend fun processFinishedUploads() : Boolean {
        //Check that all uploads succeeded and have been removed
        val success = database.getResources(ResourceType.FILE_UPLOAD,
            ResourceDatabaseHelper.APP_WIDE_STUDY_ID
        ).isEmpty()
        if (success) {
            //Check if we have any sessions that have been uploaded and still need completing
            for (resource in database.getResources(ResourceType.UPLOAD_SESSION,
                ResourceDatabaseHelper.APP_WIDE_STUDY_ID
            )) {
                resource.loadResource<UploadSession>()?.let {
                    completeUploadSession(it, resource.identifier)
                }
            }
        }
        return success
    }

}
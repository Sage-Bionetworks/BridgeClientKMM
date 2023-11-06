package org.sagebionetworks.bridge.kmm.shared.repo

import co.touchlab.kermit.Logger
import co.touchlab.stately.ensureNeverFrozen
import io.ktor.client.HttpClient
import kotlinx.coroutines.CoroutineScope
import kotlinx.coroutines.launch
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
import org.sagebionetworks.bridge.kmm.shared.models.S3UploadSession
import org.sagebionetworks.bridge.kmm.shared.models.UploadFile
import org.sagebionetworks.bridge.kmm.shared.models.UploadFileId
import org.sagebionetworks.bridge.kmm.shared.models.UploadFileIdentifiable
import org.sagebionetworks.bridge.kmm.shared.models.UploadRequest
import org.sagebionetworks.bridge.kmm.shared.models.UploadSession
import org.sagebionetworks.bridge.kmm.shared.models.UploadedFileRecord
import org.sagebionetworks.bridge.kmm.shared.models.getUploadFileResourceId
import org.sagebionetworks.bridge.kmm.shared.models.getUploadSessionResourceId
import org.sagebionetworks.bridge.kmm.shared.models.getUploadedFileRecordResourceId

internal open class UploadRepo(
    httpClient: HttpClient,
    databaseHelper: ResourceDatabaseHelper,
    backgroundScope: CoroutineScope,
    val adherenceRecordRepo: AdherenceRecordRepo?
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
     * Get all the completed [UploadSession] records from the local cache. This will include files
     * marked as upload completed.
     */
    fun getCompletedUploadSessions(): List<UploadSession> {
        val resources = database.getResourcesNeedSave(
            ResourceType.UPLOAD_SESSION,
            ResourceDatabaseHelper.APP_WIDE_STUDY_ID
        )
        return resources.mapNotNull { it.loadResource() }
    }

    /**
     * Get a tuple of the filepath and upload session for all pending uploads.
     */
    fun getPendingUploadFiles(): List<PendingUploadFile> {
        return getUploadFiles().map {
            PendingUploadFile(
                it.filePath,
                getCachedUploadSession(it)?.id
            )
        }
    }

    /**
     * Remove the [UploadFile] from the local cache and mark the upload session as "completed"
     * by setting `needSave = true`. This is called after successfully uploading to S3.
     *
     * Note: Deleting the file must be handled natively as a part of S3 upload rather than using
     * expect/actually. This is done b/c on iOS coordinating file read/write is much more
     * complicated - the file location can change with app or OS updates and synchronization is
     * a bit brittle. It's less confusing to handle this in Swift. syoung 07/14/2023
     */
    fun markUploadFileFinished(uploadFile: UploadFileIdentifiable, uploadSessionId: String?) {
        val resourceId = uploadFile.getUploadSessionResourceId()
        val uploadSessionResource = database.getResource(resourceId, ResourceType.UPLOAD_SESSION,
            ResourceDatabaseHelper.APP_WIDE_STUDY_ID
        )?.copy(needSave = true)
        val uploadedFileRecord = UploadedFileRecord(
            filePath = uploadFile.filePath,
            uploadTimestamp = Clock.System.now(),
            uploadSessionId = uploadSessionId,
            metadata = getUploadFile(uploadFile.filePath)?.metadata
        )
        database.database.transaction {
            // Mark the upload session as "completed" by updating with `needSave = true`
            uploadSessionResource?.let {
                database.insertUpdateResource(it)
            }
            // Remove the upload file that is queued for upload to S3
            database.removeResource(
                uploadFile.getUploadFileResourceId(),
                ResourceType.FILE_UPLOAD,
                ResourceDatabaseHelper.APP_WIDE_STUDY_ID
            )
            // Insert a record with the information for the uploaded file record
            database.insertUpdateResource(
                Resource(
                    identifier = uploadedFileRecord.filePath,
                    type = ResourceType.UPLOADED_FILE_RECORD,
                    secondaryId = uploadedFileRecord.metadata?.instanceGuid ?: ResourceDatabaseHelper.DEFAULT_SECONDARY_ID,
                    studyId = ResourceDatabaseHelper.APP_WIDE_STUDY_ID,
                    json = Json.encodeToString(uploadedFileRecord),
                    lastUpdate = uploadedFileRecord.uploadTimestamp.toEpochMilliseconds(),
                    status = ResourceStatus.SUCCESS,
                    needSave = false
                )
            )
        }
    }

    /**
     * Remove the [UploadFile] from the local cache. This is called after an unrecoverable failure
     * to upload to S3.
     *
     * Note: Deleting the file must be handled natively as a part of S3 upload rather than using
     * expect/actually. This is done b/c on iOS coordinating file read/write is much more
     * complicated - the file location can change with app or OS updates and synchronization is
     * a bit brittle. It's less confusing to handle this in Swift. syoung 07/14/2023
     */
    fun removeUploadFile(uploadFile: UploadFileIdentifiable) {
        database.database.transaction {
            database.removeResource(
                uploadFile.getUploadSessionResourceId(),
                ResourceType.UPLOAD_SESSION,
                ResourceDatabaseHelper.APP_WIDE_STUDY_ID
            )
            database.removeResource(
                uploadFile.getUploadFileResourceId(),
                ResourceType.FILE_UPLOAD,
                ResourceDatabaseHelper.APP_WIDE_STUDY_ID
            )
        }
    }

    /**
     * Get the cached [UploadFile] for a given `filePath`.
     */
    private fun getUploadFile(filePath: String): UploadFile? {
        val fileId = UploadFileId(filePath)
        return database.getResourcesById(
            fileId.getUploadFileResourceId(),
            ResourceType.FILE_UPLOAD,
            ResourceDatabaseHelper.APP_WIDE_STUDY_ID
        ).firstOrNull()?.loadResource()
    }

    /**
     * If the file has been uploaded, then this will get the record associated with
     * marking that file as "done".
     */
    fun getUploadedFileRecord(filePath: String): UploadedFileRecord? {
        return database.getResourcesById(
            filePath,
            ResourceType.UPLOADED_FILE_RECORD,
            ResourceDatabaseHelper.APP_WIDE_STUDY_ID
        ).firstOrNull()?.loadResource()
    }

    /**
     * Add the given upload file to the queue and request the S3 upload session.
     */
    suspend fun queueAndRequestUploadSession(uploadFile: UploadFile): S3UploadSession? {
        database.storeUploadFile(uploadFile)
        return getS3UploadSession(uploadFile)
    }

    /**
     * Get the S3 Upload Session for the given file path.
     *
     * Note: Currently, only uploading study data (archives) is supported. syoung 07/20/2023
     */
    suspend fun getS3UploadSessionForFile(filePath: String): S3UploadSession? {
        return getUploadFile(filePath)?.let { getS3UploadSession(it) }
    }

    /**
     * Get the information needed to spawn an S3 upload.
     */
    suspend fun getS3UploadSession(uploadFile: UploadFile): S3UploadSession? {
        val uploadSession = getUploadSession(uploadFile)
        return if (uploadSession?.id == null) null
        else S3UploadSession(
            filePath = uploadFile.filePath,
            contentType = uploadFile.contentType,
            uploadSessionId = uploadSession.id,
            url = uploadSession.url,
            requestHeaders = uploadFile.getS3RequestHeaders(),
        )
    }

    /**
     * Retrieves cached UploadSession (if one exists). This method is responsible for ensuring
     * that upload session has not expired and is valid.
     */
    fun getCachedUploadSession(uploadFile: UploadFileIdentifiable): UploadSession? {
        val uploadSession = database.getResource(
            uploadFile.getUploadSessionResourceId(),
            ResourceType.UPLOAD_SESSION,
            ResourceDatabaseHelper.APP_WIDE_STUDY_ID
        )?.loadResource<UploadSession>()
        return if (isValid(uploadSession)) uploadSession else null
    }

    /**
     * Is the upload session still valid (or has it expired)?
     */
    private fun isValid(uploadSession: UploadSession?): Boolean {
        if (uploadSession?.expires == null) return true
        val desiredMinimumExpiration = Clock.System.now().plus(
            UPLOAD_EXPIRY_WINDOW_MINUTES,
            DateTimeUnit.MINUTE,
            TimeZone.currentSystemDefault()
        )
        val expires = Instant.parse(uploadSession.expires)
        return (desiredMinimumExpiration < expires)
    }

    /**
     * Retrieves cached UploadSession (if one exists), else requests one from Bridge and caches session
     * before returning it. This method is responsible for ensuring that upload session has not expired and is valid.
     */
    suspend fun getUploadSession(uploadFile: UploadFile): UploadSession? {
        return getCachedUploadSession(uploadFile) ?:
        remoteLoadResource(
            database = database,
            identifier = uploadFile.getUploadSessionResourceId(),
            resourceType = ResourceType.UPLOAD_SESSION,
            studyId = ResourceDatabaseHelper.APP_WIDE_STUDY_ID,
            curResource = null,
            remoteLoad = {loadRemoteUploadSession(uploadFile.getUploadRequest(adherenceRecordRepo))}
        ).loadResource()
        //TODO: Need to think through error handling if we are unable to get an UploadSession -nbrown 12/16/20
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
            Logger.i("Processing finished upload: $uploadSessionId")
            uploadsApi.completeUploadSession(it)
            Logger.i("Upload $uploadSessionId marked as completed. Removing resource with identifier: $resourceId.")
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

data class PendingUploadFile(
    val filePath: String,
    val uploadSessionId: String?
)


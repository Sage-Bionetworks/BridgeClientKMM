package org.sagebionetworks.bridge.kmm.shared.upload

import android.content.Context
import androidx.work.*
import co.touchlab.kermit.Logger
import app.cash.sqldelight.db.SqlDriver
import io.ktor.client.*
import kotlinx.coroutines.Dispatchers
import kotlinx.coroutines.flow.Flow
import kotlinx.coroutines.withContext
import kotlinx.datetime.Clock
import kotlinx.serialization.encodeToString
import kotlinx.serialization.json.Json
import okio.*
import okio.Path.Companion.toPath
import org.sagebionetworks.bridge.kmm.shared.cache.*
import org.sagebionetworks.bridge.kmm.shared.cache.ResourceDatabaseHelper.Companion.APP_WIDE_STUDY_ID
import org.sagebionetworks.bridge.kmm.shared.models.UploadFile

class UploadRequester(
    val database: ResourceDatabaseHelper,
    private val context: Context
) {

    /**
     * Persist the file on disk and add it to the queue of pending uploads. Schedule WorkManager to
     * process any pending uploads and save to Bridge.
     *
     * Caller is responsible for zipping, encrypting, and cleaning up any files used
     * to create the UploadFile. Once this method returns, the UploadManager is now responsible
     * for deleting the specified UploadFile after a successful upload.
     */
    fun queueAndRequestUpload(context: Context, uploadFile: UploadFile, assessmentInstanceId: String) {
        val pendingUploads = database.getResourcesBySecondaryId(assessmentInstanceId, ResourceType.FILE_UPLOAD, APP_WIDE_STUDY_ID)
        if (pendingUploads.isNotEmpty()) {
            for (uploadResource in pendingUploads) {
                uploadResource.loadResource<UploadFile>()?.let { pendingUploadFile ->
                    if (pendingUploadFile.sessionExpires != null) {
                        //We already have pending upload for this assessmentInstanceID waiting for
                        //the scheduled session to expire before uploading. It will be replaced
                        //with the new one.
                        FileSystem.SYSTEM.delete(pendingUploadFile.filePath.toPath())
                        database.removeResource(pendingUploadFile.getUploadFileResourceId(), ResourceType.FILE_UPLOAD, APP_WIDE_STUDY_ID)
                    }
                }
            }
        }

        //Store uploadFile in local cache
        val resource = Resource(
            identifier = uploadFile.getUploadFileResourceId(),
            type = ResourceType.FILE_UPLOAD,
            secondaryId = assessmentInstanceId,
            studyId = APP_WIDE_STUDY_ID,
            json = Json.encodeToString(uploadFile),
            lastUpdate = Clock.System.now().toEpochMilliseconds(),
            status = ResourceStatus.SUCCESS,
            needSave = false
        )
        database.insertUpdateResource(resource)

        queueUploadWorker()
    }

    /**
     * Enqueue a WorkManager work request to process uploads.
     */
    fun queueUploadWorker() {
        //Make a WorkManager request to enqueueUniqueWork to processUploads
        val constraints = Constraints.Builder()
            .setRequiredNetworkType(NetworkType.CONNECTED)
            .build()
        val workRequest: OneTimeWorkRequest = OneTimeWorkRequestBuilder<CoroutineUploadWorker>()
            .setConstraints(constraints)
            .build()
        WorkManager.getInstance(context).beginUniqueWork(
            "ResultUpload",
            ExistingWorkPolicy.APPEND_OR_REPLACE, //this will restart a worker chain after a failure
            workRequest
        ).enqueue()
    }

    val pendingUploads get() = database.getResources(ResourceType.FILE_UPLOAD, APP_WIDE_STUDY_ID).isNotEmpty()
            || database.getResources(ResourceType.UPLOAD_SESSION, APP_WIDE_STUDY_ID).isNotEmpty()

    fun getPendingFileUploads() : List<Resource> {
        return database.getResources(ResourceType.FILE_UPLOAD, APP_WIDE_STUDY_ID)
    }

    fun getPendingFileUploadsFlow() : Flow<List<Resource>> {
        return database.getResourcesAsFlow(ResourceType.FILE_UPLOAD, APP_WIDE_STUDY_ID)
    }



    private fun getFile(filename: String): Path {
        val pathString = context.filesDir.absolutePath + Path.DIRECTORY_SEPARATOR + filename
        return pathString.toPath()
    }

}

internal class CoroutineUploadWorker(
    context: Context,
    params: WorkerParameters,
    private val httpClient: HttpClient,
    private val sqlDriver: SqlDriver
) : CoroutineWorker(context, params) {
    private val TAG = "CoroutineUploadWorker"
    
    override suspend fun doWork(): Result {
        return withContext(Dispatchers.IO) {
            Logger.d { "Upload worker started" }
            val uploadManager = UploadManager(
                httpClient, sqlDriver
            )
            return@withContext try {
                if (uploadManager.processUploads()) {
                    Logger.d { "Successfully processed all uploads" }
                    Result.success()
                } else {
                    Logger.d { "uploadManager.processUploads did not finish all uploads" }
                    //TODO: Handle failure and retry scenarios -nbrown 12/21/20
                    Result.retry()
                }
            } catch (t: Throwable) {
                Logger.e("Error calling uploadManager.ProcessUploads", t)
                Result.retry()
            }
        }

    }
}
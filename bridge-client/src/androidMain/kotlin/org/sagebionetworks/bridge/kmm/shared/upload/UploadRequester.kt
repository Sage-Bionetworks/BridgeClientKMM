package org.sagebionetworks.bridge.kmm.shared.upload

import android.content.Context
import android.util.Log
import androidx.work.*
import com.squareup.sqldelight.db.SqlDriver
import io.ktor.client.*
import kotlinx.coroutines.Dispatchers
import kotlinx.coroutines.withContext
import kotlinx.datetime.Clock
import kotlinx.serialization.encodeToString
import kotlinx.serialization.json.Json
import okio.*
import okio.Path.Companion.toPath
import org.sagebionetworks.bridge.kmm.shared.cache.*
import java.io.IOException
import java.io.OutputStream
import java.nio.charset.StandardCharsets
import java.util.zip.ZipEntry
import java.util.zip.ZipOutputStream

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
    fun queueAndRequestUpload(context: Context, uploadFile: UploadFile) {
        //Store uploadFile in local cache
        val resource = Resource(
            identifier = uploadFile.getUploadFileResourceId(),
            type = ResourceType.FILE_UPLOAD,
            studyId = ResourceDatabaseHelper.APP_WIDE_STUDY_ID,
            json = Json.encodeToString(uploadFile),
            lastUpdate = Clock.System.now().toEpochMilliseconds(),
            status = ResourceStatus.SUCCESS,
            needSave = false
        )
        database.insertUpdateResource(resource)

        //Make a WorkManager request to enqueueUniqueWork to processUploads
        val constraints = Constraints.Builder()
            .setRequiredNetworkType(NetworkType.CONNECTED)
            .build()
        val workRequest: OneTimeWorkRequest = OneTimeWorkRequestBuilder<CoroutineUploadWorker>()
            .setConstraints(constraints)
            .build()
        WorkManager.getInstance(context).beginUniqueWork(
            "ResultUpload",
            ExistingWorkPolicy.APPEND,
            workRequest
        ).enqueue()
    }

    // This is a temporary helper method for testing upload with Bridge -nbrown 01/08/21
    @Throws(IOException::class)
    private fun writeTestZipFileTo(os: OutputStream?): ZipOutputStream {
        val zos = ZipOutputStream(os)
        try {
//            for (dataFile in dataFiles) {
//                val entry: ZipEntry = ZipEntry(dataFile.getFilename())
//                zos.putNextEntry(entry)
//                zos.write(dataFile.getByteSource().read())
//                zos.closeEntry()
//            }
            val infoFileEntry: ZipEntry = ZipEntry("testFile")
            zos.putNextEntry(infoFileEntry)
            zos.write("testString".toByteArray(StandardCharsets.UTF_8))
            zos.closeEntry()
        } finally {
            zos.close()
        }
        return zos
    }

    // This is a temporary helper method for testing upload with Bridge -nbrown 01/08/21
    // This utilizes the new multiplatform FileSystem api from Okio
    @OptIn(ExperimentalFileSystem::class)
    fun generateTestUploadFile(filename: String): UploadFile? {
        val filePath = getFile(filename)


        val sink = FileSystem.SYSTEM.sink(filePath)
        val md5Sink = HashingSink.md5(sink);
        val bufferedSink = md5Sink.buffer();

        writeTestZipFileTo(bufferedSink.outputStream())


        val md5Hash: String = md5Sink.hash.base64()
        val uploadFile = UploadFile(
            filePath = filePath.toString(),
            contentType = "application/zip",
            fileLength = FileSystem.SYSTEM.metadata(filePath).size!!,
            md5Hash = md5Hash,
            encrypted = false
        )

        return uploadFile
    }

    @OptIn(ExperimentalFileSystem::class)
    private fun getFile(filename: String): Path {
        val pathString = context.filesDir.absolutePath + Path.DIRECTORY_SEPARATOR + filename
        return pathString.toPath()
    }

}

class CoroutineUploadWorker(
    context: Context,
    params: WorkerParameters,
    private val httpClient: HttpClient,
    private val sqlDriver: SqlDriver
) : CoroutineWorker(context, params) {
    private val TAG = "CoroutineUploadWorker"
    
    override suspend fun doWork(): Result {
        return withContext(Dispatchers.IO) {
            Log.d(TAG, "Upload worker started")
            val uploadManager = UploadManager(
                httpClient, sqlDriver
            )
            return@withContext try {
                if (uploadManager.processUploads()) {
                    Log.d(TAG, "Successfully processed all uploads")
                    Result.success()
                } else {
                    Log.w(TAG, "uploadManager.processUploads did not finish all uploads")
                    //TODO: Handle failure and retry scenarios -nbrown 12/21/20
                    Result.retry()
                }
            } catch (t: Throwable) {
                Log.e(TAG, "Error calling uploadManager.ProcessUploads", t)
                Result.failure()
            }
        }

    }
}
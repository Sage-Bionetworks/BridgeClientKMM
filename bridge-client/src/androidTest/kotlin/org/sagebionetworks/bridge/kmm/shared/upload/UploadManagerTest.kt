package org.sagebionetworks.bridge.kmm.shared.upload

import io.ktor.client.*
import io.ktor.client.engine.*
import io.ktor.client.engine.mock.*
import io.ktor.http.*
import kotlinx.coroutines.runBlocking
import kotlinx.datetime.Clock
import kotlinx.datetime.Instant
import kotlinx.serialization.encodeToString
import kotlinx.serialization.json.Json
import org.junit.Rule
import org.junit.Test
import org.junit.rules.TemporaryFolder
import org.sagebionetworks.bridge.kmm.shared.cache.Resource
import org.sagebionetworks.bridge.kmm.shared.cache.ResourceDatabaseHelper
import org.sagebionetworks.bridge.kmm.shared.cache.ResourceDatabaseHelper.Companion.APP_WIDE_STUDY_ID
import org.sagebionetworks.bridge.kmm.shared.cache.ResourceStatus
import org.sagebionetworks.bridge.kmm.shared.cache.ResourceType
import org.sagebionetworks.bridge.kmm.shared.getJsonReponseHandler
import org.sagebionetworks.bridge.kmm.shared.getTestClient
import org.sagebionetworks.bridge.kmm.shared.models.UploadStatus
import org.sagebionetworks.bridge.kmm.shared.models.UploadValidationStatus
import org.sagebionetworks.bridge.kmm.shared.testDatabaseDriver
import org.sagebionetworks.bridge.mpp.network.generated.models.UploadSession
import java.io.File
import java.io.PrintWriter
import kotlin.test.*


public class UploadManagerTest {

    @get:Rule
    var tempFolder = TemporaryFolder()

    private fun setupUploadManager(testHttpClient: HttpClient, tempFile: File): UploadManager {
        val printWriter = PrintWriter(tempFile)
        printWriter.println("hello world")
        printWriter.close()

        val uploadFile = UploadFile(tempFile.absolutePath, "application/zip", tempFile.length(), "md5Hash")

        val uploadManager = UploadManager(testHttpClient, testDatabaseDriver())
        val database = uploadManager.database
        val resource = Resource(
            uploadFile.getUploadFileResourceId(),
            ResourceType.FILE_UPLOAD,
            APP_WIDE_STUDY_ID,
            Json.encodeToString(uploadFile),
            Clock.System.now().toEpochMilliseconds(),
            ResourceStatus.SUCCESS,
            false
        )
        database.insertUpdateResource(resource)
        return uploadManager
    }

    @Test
    fun testUploadManagerHappyCase() {
        runBlocking {
            val tempFile = tempFolder.newFile("tempFileHappyCase.txt")

            val sessionId = "uploadSessionId"
            val uploadSession = UploadSession(sessionId, "http://testurl", "expires", "UploadSession")
            val uploadValidationStatus = UploadValidationStatus(sessionId, null, UploadStatus.VALIDATION_IN_PROGRESS, null, null)

            val mockEngine = MockEngine.config {
                // 1 - getUploadSession call
                addHandler (
                    getJsonReponseHandler(Json.encodeToString(uploadSession))
                )
                // 2 - s3 call
                addHandler { respondOk() }
                // 3 - completeUploadSession call
                addHandler (
                    getJsonReponseHandler(Json.encodeToString(uploadValidationStatus))
                )
                reuseHandlers = false
            }
            val testClient = getTestClient(mockEngine)
            val uploadManager = setupUploadManager(testClient, tempFile)
            val database = uploadManager.database

            assertFalse(database.getResources(ResourceType.FILE_UPLOAD, APP_WIDE_STUDY_ID).isEmpty())
            uploadManager.processUploads()

            assertTrue(database.getResources(ResourceType.FILE_UPLOAD, APP_WIDE_STUDY_ID).isEmpty())
            assertFalse(tempFile.exists())

            assertTrue(database.getResources(ResourceType.UPLOAD_SESSION, APP_WIDE_STUDY_ID).isEmpty())
        }
    }

    @Test
    fun testNetworkFailAfterGetUploadSession() {
        runBlocking {
            val tempFile = tempFolder.newFile("tempFileFailAfterGetUploadSession.txt")

            val sessionId = "uploadSessionId"
            val uploadSession = UploadSession(sessionId, "http://testurl", Clock.System.now().toString(), "UploadSession")
            val uploadValidationStatus = UploadValidationStatus(sessionId, null, UploadStatus.VALIDATION_IN_PROGRESS, null, null)

            val mockEngine = MockEngine.config {
                // 1 - getUploadSession call
                addHandler (
                    getJsonReponseHandler(Json.encodeToString(uploadSession))
                )
                // 2 - First s3 call
                addHandler { respondError(HttpStatusCode.GatewayTimeout) }
                // 3 - Second s3 call
                addHandler { respondOk() }
                // 4 - completeUploadSession call
                addHandler (
                    getJsonReponseHandler(Json.encodeToString(uploadValidationStatus))
                )
                reuseHandlers = false
            }
            val testClient = getTestClient(mockEngine)
            val uploadManager = setupUploadManager(testClient, tempFile)
            val database = uploadManager.database

            assertFalse(database.getResources(ResourceType.FILE_UPLOAD, APP_WIDE_STUDY_ID).isEmpty())
            try {
                //First try will throw an error with the s3 call
                uploadManager.processUploads()
            } catch (throwable: Throwable) {

            }
            assertFalse(database.getResources(ResourceType.FILE_UPLOAD, APP_WIDE_STUDY_ID).isEmpty())
            assertFalse(database.getResources(ResourceType.UPLOAD_SESSION, APP_WIDE_STUDY_ID).isEmpty())
            //Retry processing uploads, this time should reuse cached uploadSession
            uploadManager.processUploads()
            assertTrue(database.getResources(ResourceType.FILE_UPLOAD, APP_WIDE_STUDY_ID).isEmpty())
            assertFalse(tempFile.exists())
            assertTrue(database.getResources(ResourceType.UPLOAD_SESSION, APP_WIDE_STUDY_ID).isEmpty())
        }
    }

    @Test
    fun testNetworkFailAfterS3Upload() {
        runBlocking {
            val tempFile = tempFolder.newFile("tempFileFailAfterGetUploadSession.txt")

            val sessionId = "uploadSessionId"
            val uploadSession = UploadSession(sessionId, "http://testurl", Clock.System.now().toString(), "UploadSession")
            val uploadValidationStatus = UploadValidationStatus(sessionId, null, UploadStatus.VALIDATION_IN_PROGRESS, null, null)

            val mockEngine = MockEngine.config {
                // 1 - getUploadSession call
                addHandler (
                    getJsonReponseHandler(Json.encodeToString(uploadSession))
                )
                // 2 - s3 call
                addHandler { respondOk() }
                // 3 - First completeUploadSession call
                addHandler { respondError(HttpStatusCode.GatewayTimeout) }
                // 4 - completeUploadSession call
                addHandler (
                    getJsonReponseHandler(Json.encodeToString(uploadValidationStatus))
                )
                reuseHandlers = false
            }
            val testClient = getTestClient(mockEngine)
            val uploadManager = setupUploadManager(testClient, tempFile)
            val database = uploadManager.database

            assertFalse(database.getResources(ResourceType.FILE_UPLOAD, APP_WIDE_STUDY_ID).isEmpty())
            try {
                //First try will throw an error with the completeUploadSession call
                uploadManager.processUploads()
            } catch (throwable: Throwable) {

            }
            //File upload and temp file should be gone
            assertTrue(database.getResources(ResourceType.FILE_UPLOAD, APP_WIDE_STUDY_ID).isEmpty())
            assertFalse(tempFile.exists())
            //Should still have an upload session
            assertFalse(database.getResources(ResourceType.UPLOAD_SESSION, APP_WIDE_STUDY_ID).isEmpty())
            //Retry processing uploads, this time should pass
            uploadManager.processUploads()
            assertTrue(database.getResources(ResourceType.UPLOAD_SESSION, APP_WIDE_STUDY_ID).isEmpty())
        }
    }
}

package org.sagebionetworks.bridge.kmm.shared.upload

import io.ktor.client.*
import io.ktor.client.engine.*
import io.ktor.client.engine.mock.*
import io.ktor.http.*
import kotlinx.coroutines.ExperimentalCoroutinesApi
import kotlinx.coroutines.runBlocking
import kotlinx.coroutines.test.TestScope
import kotlinx.datetime.Clock
import kotlinx.datetime.DateTimeUnit
import kotlinx.datetime.Instant
import kotlinx.datetime.TimeZone
import kotlinx.datetime.plus
import kotlinx.serialization.encodeToString
import kotlinx.serialization.json.Json
import org.junit.Rule
import org.junit.Test
import org.junit.rules.TemporaryFolder
import org.sagebionetworks.bridge.kmm.shared.cache.Resource
import org.sagebionetworks.bridge.kmm.shared.cache.ResourceDatabaseHelper
import org.sagebionetworks.bridge.kmm.shared.cache.ResourceDatabaseHelper.Companion.APP_WIDE_STUDY_ID
import org.sagebionetworks.bridge.kmm.shared.cache.ResourceDatabaseHelper.Companion.DEFAULT_SECONDARY_ID
import org.sagebionetworks.bridge.kmm.shared.cache.ResourceStatus
import org.sagebionetworks.bridge.kmm.shared.cache.ResourceType
import org.sagebionetworks.bridge.kmm.shared.getJsonReponseHandler
import org.sagebionetworks.bridge.kmm.shared.getTestClient
import org.sagebionetworks.bridge.kmm.shared.models.UploadFile
import org.sagebionetworks.bridge.kmm.shared.models.UploadSession
import org.sagebionetworks.bridge.kmm.shared.models.UploadStatus
import org.sagebionetworks.bridge.kmm.shared.models.UploadValidationStatus
import org.sagebionetworks.bridge.kmm.shared.models.getUploadFileResourceId
import org.sagebionetworks.bridge.kmm.shared.randomUUID
import org.sagebionetworks.bridge.kmm.shared.testDatabaseDriver
import java.io.File
import java.io.PrintWriter
import kotlin.test.assertEquals
import kotlin.test.assertFalse
import kotlin.test.assertTrue


class UploadManagerTest {

    @get:Rule
    var tempFolder = TemporaryFolder()

    @OptIn(ExperimentalCoroutinesApi::class)
    private fun setupUploadManager(testHttpClient: HttpClient,
                                   tempFile: File,
                                   assessmentInstanceId: String = DEFAULT_SECONDARY_ID,

    ): UploadManager {
        val printWriter = PrintWriter(tempFile)
        printWriter.println("hello world")
        printWriter.close()

        val uploadFile = UploadFile(tempFile.absolutePath,
            "application/zip",
            tempFile.length(),
            "md5Hash",
        )

        val testDatabaseHelper = ResourceDatabaseHelper(testDatabaseDriver())
        val uploadManager = UploadManager(testHttpClient, testDatabaseHelper, TestScope(), null)
        uploadManager.database.storeUploadFile(uploadFile)
        return uploadManager
    }

    fun mockUploadSession(): UploadSession {
        val expires = Clock.System.now().plus(
            24,
            DateTimeUnit.HOUR,
            TimeZone.currentSystemDefault()
        )
        return UploadSession(
            id = randomUUID(),
            url = "http://testurl/${randomUUID()}",
            expires = expires.toString(),
            type = "UploadSession"
        )
    }

    @Test
    fun testUploadManagerHappyCase() {
        runBlocking {
            val tempFile = tempFolder.newFile("tempFileHappyCase.txt")

            val uploadSession = mockUploadSession()
            val sessionId = uploadSession.id!!
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

            val initialCount = database.getPendingUploadCount()
            assertEquals(1L, initialCount)

            assertFalse(database.getResources(ResourceType.FILE_UPLOAD, APP_WIDE_STUDY_ID).isEmpty())
            uploadManager.processUploads()

            assertTrue(database.getResources(ResourceType.FILE_UPLOAD, APP_WIDE_STUDY_ID).isEmpty())
            assertFalse(tempFile.exists())

            assertTrue(database.getResources(ResourceType.UPLOAD_SESSION, APP_WIDE_STUDY_ID).isEmpty())

            val afterUploadCount = database.getPendingUploadCount()
            assertEquals(0L, afterUploadCount)
        }
    }

    @Test
    fun testNetworkFailAfterGetUploadSession() {
        runBlocking {
            val tempFile = tempFolder.newFile("tempFileFailAfterGetUploadSession.txt")

            val uploadSession = mockUploadSession()
            val sessionId = uploadSession.id!!
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
            } catch (_: Throwable) {

            }

            // Check that after the first call, the file marker and upload session are there.
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

            val uploadSession = mockUploadSession()
            val sessionId = uploadSession.id!!
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
                // 4 - Second completeUploadSession call
                addHandler { respondError(HttpStatusCode.GatewayTimeout) }
                // 5 - completeUploadSession call
                addHandler (
                    getJsonReponseHandler(Json.encodeToString(uploadValidationStatus))
                )
                reuseHandlers = false
            }
            val testClient = getTestClient(mockEngine)
            val uploadManager = setupUploadManager(testClient, tempFile)
            val database = uploadManager.database

            // Check assumptions
            assertFalse(database.getResources(ResourceType.FILE_UPLOAD, APP_WIDE_STUDY_ID).isEmpty())

            // Run process uploads first time. Should fail on completion.
            var didThrow = false
            try {
                //First try will throw an error with the completeUploadSession call
                uploadManager.processUploads()
            } catch (_: Throwable) {
                didThrow = true
            }
            assertTrue(didThrow)

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

    // TODO: syoung 07/17/2023 Delete. Keeping this commented out for now. No longer supported.
//    @Test
//    fun testBeforeSessionExpires() {
//        runBlocking {
//            val tempFile = tempFolder.newFile("tempFileHappyCase.txt")
//
//            val sessionId = "uploadSessionId"
//            val uploadSession = UploadSession(sessionId, "http://testurl", "expires", "UploadSession")
//            val uploadValidationStatus = UploadValidationStatus(sessionId, null, UploadStatus.VALIDATION_IN_PROGRESS, null, null)
//
//            val mockEngine = MockEngine.config {
//                // 1 - getUploadSession call
//                addHandler {
//                    assertTrue(false, "Http call should not have been made")
//                    respondOk()
//                }
//                reuseHandlers = false
//            }
//            val testClient = getTestClient(mockEngine)
//            val expiresFuture = Instant.fromEpochMilliseconds(Clock.System.now().toEpochMilliseconds() + 10000)
//            val uploadManager = setupUploadManager(testClient, tempFile, "BeforeSessionExpiresInstanceID", expiresFuture)
//            val database = uploadManager.database
//
//            assertTrue(database.getResources(ResourceType.FILE_UPLOAD, APP_WIDE_STUDY_ID).isNotEmpty())
//            uploadManager.processUploads()
//            //Verify upload has not been processed
//            assertTrue(database.getResources(ResourceType.FILE_UPLOAD, APP_WIDE_STUDY_ID).isNotEmpty())
//            assertTrue(tempFile.exists())
//
//        }
//    }
//
//
//    @Test
//    fun testAfterSessionExpires() {
//        runBlocking {
//            val tempFile = tempFolder.newFile("tempFileHappyCase.txt")
//
//            val sessionId = "uploadSessionId"
//            val uploadSession = UploadSession(sessionId, "http://testurl", "expires", "UploadSession")
//            val uploadValidationStatus = UploadValidationStatus(sessionId, null, UploadStatus.VALIDATION_IN_PROGRESS, null, null)
//
//            val mockEngine = MockEngine.config {
//                // 1 - getUploadSession call
//                addHandler (
//                    getJsonReponseHandler(Json.encodeToString(uploadSession))
//                )
//                // 2 - s3 call
//                addHandler { respondOk() }
//                // 3 - completeUploadSession call
//                addHandler (
//                    getJsonReponseHandler(Json.encodeToString(uploadValidationStatus))
//                )
//                reuseHandlers = false
//            }
//            val testClient = getTestClient(mockEngine)
//            val expiresFuture = Instant.fromEpochMilliseconds(Clock.System.now().toEpochMilliseconds() - 10000)
//            val uploadManager = setupUploadManager(testClient, tempFile, "AfterSessionExpiresInstanceID", expiresFuture)
//            val database = uploadManager.database
//
//            assertFalse(database.getResources(ResourceType.FILE_UPLOAD, APP_WIDE_STUDY_ID).isEmpty())
//            uploadManager.processUploads()
//
//            assertTrue(database.getResources(ResourceType.FILE_UPLOAD, APP_WIDE_STUDY_ID).isEmpty())
//            assertFalse(tempFile.exists())
//
//            assertTrue(database.getResources(ResourceType.UPLOAD_SESSION, APP_WIDE_STUDY_ID).isEmpty())
//        }
//    }
}

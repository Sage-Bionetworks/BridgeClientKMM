package org.sagebionetworks.bridge.kmm.shared.repo

import io.ktor.client.engine.config
import io.ktor.client.engine.mock.MockEngine
import io.ktor.client.engine.mock.respondError
import io.ktor.http.HttpStatusCode
import kotlinx.coroutines.MainScope
import kotlinx.coroutines.runBlocking
import kotlinx.datetime.Clock
import kotlinx.datetime.DateTimeUnit
import kotlinx.datetime.Instant
import kotlinx.datetime.TimeZone
import kotlinx.datetime.minus
import kotlinx.datetime.plus
import kotlinx.serialization.encodeToString
import kotlinx.serialization.json.Json
import org.sagebionetworks.bridge.kmm.shared.BaseTest
import org.sagebionetworks.bridge.kmm.shared.cache.Resource
import org.sagebionetworks.bridge.kmm.shared.cache.ResourceDatabaseHelper
import org.sagebionetworks.bridge.kmm.shared.cache.ResourceStatus
import org.sagebionetworks.bridge.kmm.shared.cache.ResourceType
import org.sagebionetworks.bridge.kmm.shared.getJsonReponseHandler
import org.sagebionetworks.bridge.kmm.shared.getTestClient
import org.sagebionetworks.bridge.kmm.shared.models.S3UploadSession
import org.sagebionetworks.bridge.kmm.shared.models.UploadFile
import org.sagebionetworks.bridge.kmm.shared.models.UploadFileId
import org.sagebionetworks.bridge.kmm.shared.models.UploadFileIdentifiable
import org.sagebionetworks.bridge.kmm.shared.models.UploadSession
import org.sagebionetworks.bridge.kmm.shared.models.UploadStatus
import org.sagebionetworks.bridge.kmm.shared.models.UploadValidationStatus
import org.sagebionetworks.bridge.kmm.shared.models.getUploadFileResourceId
import org.sagebionetworks.bridge.kmm.shared.models.getUploadSessionResourceId
import org.sagebionetworks.bridge.kmm.shared.randomUUID
import org.sagebionetworks.bridge.kmm.shared.testDatabaseDriver
import kotlin.test.Test
import kotlin.test.assertEquals
import kotlin.test.assertFalse
import kotlin.test.assertNotNull
import kotlin.test.assertNull
import kotlin.test.assertTrue

class UploadRepoTest : BaseTest() {


    fun mockUploadSession(expires: Instant): UploadSession {
        return UploadSession(
            id = randomUUID(),
            url = "http://testurl/${randomUUID()}",
            expires = expires.toString(),
            type = "UploadSession"
        )
    }

    fun mockUploadFile(): UploadFile {
        return UploadFile(
            randomUUID(),
            "application/zip",
            1024,
            randomUUID(),
        )
    }

    @Test
    fun testGetUploadFiles() {
        runBlocking {
            val mockEngine = MockEngine.config {
                // Should never be called
                addHandler { respondError(HttpStatusCode.ExpectationFailed) }
                
                reuseHandlers = false
            }
            val testClient = getTestClient(mockEngine)
            val testDatabaseHelper = ResourceDatabaseHelper(testDatabaseDriver())
            val repo = UploadRepo(testClient, testDatabaseHelper, MainScope())
            val database = repo.database

            val uploadFile1 = mockUploadFile()
            val uploadFile2 = mockUploadFile()
            database.storeUploadFile(uploadFile1)
            database.storeUploadFile(uploadFile2)

            val expected: Set<UploadFile> = setOf(uploadFile1, uploadFile2)
            val uploadFiles: Set<UploadFile> = repo.getUploadFiles().toSet()
            assertEquals(expected, uploadFiles)

        }
    }

    @Test
    fun testS3UploadSession_HappyPath() {
        runBlocking {

            // Run through a "happy path" where everything is online.

            val expires = Clock.System.now().plus(
                24,
                DateTimeUnit.HOUR,
                TimeZone.currentSystemDefault()
            )
            val uploadSession = mockUploadSession(expires)
            val sessionId = uploadSession.id!!
            val uploadValidationStatus = UploadValidationStatus(sessionId, null, UploadStatus.VALIDATION_IN_PROGRESS, null, "UploadValidationStatus")

            val mockEngine = MockEngine.config {
                // 1 - getUploadSession call
                addHandler (
                    getJsonReponseHandler(Json.encodeToString(uploadSession))
                )
                // 3 - completeUploadSession call
                addHandler (
                    getJsonReponseHandler(Json.encodeToString(uploadValidationStatus))
                )
                reuseHandlers = false
            }
            val testClient = getTestClient(mockEngine)
            val testDatabaseHelper = ResourceDatabaseHelper(testDatabaseDriver())
            val repo = UploadRepo(testClient, testDatabaseHelper, MainScope())
            val database = repo.database

            val uploadFile = mockUploadFile()
            val response = repo.queueAndRequestUploadSession(uploadFile)
            assertNotNull(response)

            val expectedS3UploadSession = S3UploadSession(
                filePath = uploadFile.filePath,
                contentType = "application/zip",
                uploadSessionId = sessionId,
                url = uploadSession.url,
                requestHeaders = mapOf(
                    "Content-Length" to "1024",
                    "Content-Type" to "application/zip",
                    "Content-MD5" to uploadFile.md5Hash!!
                )
            )

            assertEquals(expectedS3UploadSession, response)

            val initialCount = database.getPendingUploadCount()
            assertEquals(1L, initialCount)

            // Pretend to upload the S3 file by marking it as finished
            repo.markUploadFileFinished(UploadFileId(uploadFile.filePath))

            val afterUploadCount = database.getPendingUploadCount()
            assertEquals(1L, afterUploadCount)

            // Finally process finished uploads
            repo.processFinishedUploads()

            assertTrue(database.getResources(ResourceType.FILE_UPLOAD, ResourceDatabaseHelper.APP_WIDE_STUDY_ID).isEmpty())
            assertTrue(database.getResources(ResourceType.UPLOAD_SESSION, ResourceDatabaseHelper.APP_WIDE_STUDY_ID).isEmpty())

            val uploadsAllFinishedCount = database.getPendingUploadCount()
            assertEquals(0L, uploadsAllFinishedCount)
        }
    }

    @Test
    fun testQueueS3UploadSession_Offline() {
        runBlocking {

            // Run through the first part of a case where the upload is offline when the file
            // is queued.

            val mockEngine = MockEngine.config {
                // 1 - getUploadSession call timeout
                addHandler { respondError(HttpStatusCode.GatewayTimeout) }

                reuseHandlers = false
            }
            val testClient = getTestClient(mockEngine)
            val testDatabaseHelper = ResourceDatabaseHelper(testDatabaseDriver())
            val repo = UploadRepo(testClient, testDatabaseHelper, MainScope())

            val uploadFile = mockUploadFile()
            val response = repo.queueAndRequestUploadSession(uploadFile)
            assertNull(response)
        }
    }

    @Test
    fun testRetryUploadSession_NotExpired() {
        runBlocking {

            // Run through a case where an upload to S3 fails because the initial upload fails and
            // a retry is attempted after the session expires.

            val uploadFile = mockUploadFile()
            val tempFile = uploadFile.filePath
            val now = Clock.System.now()
            val expires = now.plus(
                20,
                DateTimeUnit.HOUR,
                TimeZone.currentSystemDefault()
            )
            val uploadSession = mockUploadSession(expires)
            val sessionId = uploadSession.id!!

            val mockEngine = MockEngine.config {
                // 1 - getUploadSession call - this should not be called
                addHandler { respondError(HttpStatusCode.ExpectationFailed) }

                reuseHandlers = false
            }
            val testClient = getTestClient(mockEngine)
            val testDatabaseHelper = ResourceDatabaseHelper(testDatabaseDriver())
            val repo = UploadRepo(testClient, testDatabaseHelper, MainScope())
            val database = repo.database

            // Save the upload file and the old (expired) upload session
            database.storeUploadFile(uploadFile)
            val resource = Resource(
                identifier = uploadFile.getUploadSessionResourceId(),
                secondaryId = uploadFile.getSecondaryId(),
                type = ResourceType.UPLOAD_SESSION,
                studyId = ResourceDatabaseHelper.APP_WIDE_STUDY_ID,
                json = Json.encodeToString(uploadSession),
                lastUpdate = now.minus(
                    4, DateTimeUnit.HOUR, TimeZone.currentSystemDefault()
                ).toEpochMilliseconds(),
                status = ResourceStatus.SUCCESS,
                needSave = false
            )
            database.insertUpdateResource(resource)

            val response = repo.getS3UploadSessionForFile(tempFile)
            assertNotNull(response)

            val expectedS3UploadSession = S3UploadSession(
                filePath = tempFile,
                contentType = "application/zip",
                uploadSessionId = sessionId,
                url = uploadSession.url,
                requestHeaders = mapOf(
                    "Content-Length" to "1024",
                    "Content-Type" to "application/zip",
                    "Content-MD5" to uploadFile.md5Hash!!
                )
            )

            assertEquals(expectedS3UploadSession, response)

            val initialCount = database.getPendingUploadCount()
            assertEquals(1L, initialCount)
        }
    }

    @Test
    fun testRetryUploadSession_Expired() {
        runBlocking {

            // Run through a case where an upload to S3 fails because the initial upload fails and
            // a retry is attempted after the session expires.

            val uploadFile = mockUploadFile()
            val tempFile = uploadFile.filePath
            val past = Clock.System.now().minus(
                2,
                DateTimeUnit.DAY,
                TimeZone.currentSystemDefault()
            )
            val oldUploadSession = mockUploadSession(past)


            val expires = Clock.System.now().plus(
                24,
                DateTimeUnit.HOUR,
                TimeZone.currentSystemDefault()
            )
            val uploadSession = mockUploadSession(expires)
            val sessionId = uploadSession.id!!

            val mockEngine = MockEngine.config {
                // 1 - getUploadSession call
                addHandler (
                    getJsonReponseHandler(Json.encodeToString(uploadSession))
                )

                reuseHandlers = false
            }
            val testClient = getTestClient(mockEngine)
            val testDatabaseHelper = ResourceDatabaseHelper(testDatabaseDriver())
            val repo = UploadRepo(testClient, testDatabaseHelper, MainScope())
            val database = repo.database

            // Save the upload file and the old (expired) upload session
            database.storeUploadFile(uploadFile)
            val resource = Resource(
                identifier = uploadFile.getUploadSessionResourceId(),
                secondaryId = uploadFile.getSecondaryId(),
                type = ResourceType.UPLOAD_SESSION,
                studyId = ResourceDatabaseHelper.APP_WIDE_STUDY_ID,
                json = Json.encodeToString(oldUploadSession),
                lastUpdate = past.minus(
                    1, DateTimeUnit.DAY, TimeZone.currentSystemDefault()
                ).toEpochMilliseconds(),
                status = ResourceStatus.SUCCESS,
                needSave = false
            )
            database.insertUpdateResource(resource)

            val response = repo.getS3UploadSessionForFile(tempFile)
            assertNotNull(response)

            val expectedS3UploadSession = S3UploadSession(
                filePath = tempFile,
                contentType = "application/zip",
                uploadSessionId = sessionId,
                url = uploadSession.url,
                requestHeaders = mapOf(
                    "Content-Length" to "1024",
                    "Content-Type" to "application/zip",
                    "Content-MD5" to uploadFile.md5Hash!!
                )
            )

            assertEquals(expectedS3UploadSession, response)

            val initialCount = database.getPendingUploadCount()
            assertEquals(1L, initialCount)
        }
    }

    @Test
    fun testProcessFinishedUploads_Offline() {
        runBlocking {

            // Attempt to process upload completions with the phone offline.

            val tempFile = "tempFile.txt"
            val uploadFile = UploadFileId(tempFile)
            val now = Clock.System.now()
            val expires = now.plus(
                24,
                DateTimeUnit.HOUR,
                TimeZone.currentSystemDefault()
            )
            val uploadSession = mockUploadSession(expires)

            val mockEngine = MockEngine.config {
                // 1 - getUploadSession call timeout
                addHandler { respondError(HttpStatusCode.GatewayTimeout) }

                reuseHandlers = false
            }
            val testClient = getTestClient(mockEngine)
            val testDatabaseHelper = ResourceDatabaseHelper(testDatabaseDriver())
            val repo = UploadRepo(testClient, testDatabaseHelper, MainScope())
            val database = repo.database

            val resource = Resource(
                identifier = uploadFile.getUploadSessionResourceId(),
                secondaryId = randomUUID(),
                type = ResourceType.UPLOAD_SESSION,
                studyId = ResourceDatabaseHelper.APP_WIDE_STUDY_ID,
                json = Json.encodeToString(uploadSession),
                lastUpdate = now.toEpochMilliseconds(),
                status = ResourceStatus.SUCCESS,
                needSave = true
            )
            database.insertUpdateResource(resource)

            var didThrow = false
            try {
                //First try will throw an error with the completeUploadSession call
                repo.processFinishedUploads()
            } catch (_: Throwable) {
                didThrow = true
            }

            // Should have thrown an exception
            assertTrue(didThrow)

            // Should still have an upload session
            assertFalse(database.getResources(ResourceType.UPLOAD_SESSION, ResourceDatabaseHelper.APP_WIDE_STUDY_ID).isEmpty())
        }
    }

}
package org.sagebionetworks.bridge.kmm.shared.upload

import kotlinx.coroutines.runBlocking
import kotlinx.datetime.Clock
import kotlinx.serialization.encodeToString
import kotlinx.serialization.json.Json
import org.junit.Rule
import org.junit.Test
import org.junit.rules.TemporaryFolder
import org.sagebionetworks.bridge.kmm.shared.TestDatabaseDriverFactory
import org.sagebionetworks.bridge.kmm.shared.cache.Resource
import org.sagebionetworks.bridge.kmm.shared.cache.ResourceStatus
import org.sagebionetworks.bridge.kmm.shared.cache.ResourceType
import org.sagebionetworks.bridge.kmm.shared.getTestClient
import org.sagebionetworks.bridge.mpp.network.generated.models.UploadSession
import java.io.PrintWriter
import kotlin.test.*


public class UploadManagerTest {

    @get:Rule
    var tempFolder = TemporaryFolder()

    @Test
    fun testUploadManager() {
        runBlocking {
            val tempFile = tempFolder.newFile("tempFile.txt");
            val printWriter = PrintWriter(tempFile)
            printWriter.println("hello world")
            printWriter.close()

            val uploadFile = UploadFile(tempFile.absolutePath, "application/zip", tempFile.length(), "md5Hash")

            val uploadSession = UploadSession("uploadSessionId", "http://testurl", "expires", "UploadSession")

            val uploadManager = UploadManager(getTestClient(Json.encodeToString(uploadSession)), TestDatabaseDriverFactory().createDriver())
            val database = uploadManager.database
            val resource = Resource(
                uploadFile.getUploadFileResourceId(),
                ResourceType.FILE_UPLOAD,
                Json.encodeToString(uploadFile),
                Clock.System.now().toEpochMilliseconds(),
                ResourceStatus.SUCCESS
            )
            database.insertUpdateResource(resource)
            assertFalse(database.getResources(ResourceType.FILE_UPLOAD).isEmpty())
            uploadManager.processUploads()

            assertTrue(database.getResources(ResourceType.FILE_UPLOAD).isEmpty())
            assertFalse(tempFile.exists())

        }
    }
}

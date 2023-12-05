package org.sagebionetworks.bridge.kmm.shared.repo

import kotlinx.coroutines.CoroutineScope
import kotlinx.coroutines.Dispatchers
import kotlinx.coroutines.IO
import kotlinx.coroutines.SupervisorJob
import kotlinx.datetime.TimeZone
import kotlinx.serialization.json.jsonPrimitive
import org.sagebionetworks.bridge.kmm.shared.BaseTest
import org.sagebionetworks.bridge.kmm.shared.cache.ResourceDatabaseHelper
import org.sagebionetworks.bridge.kmm.shared.cache.ResourceType
import org.sagebionetworks.bridge.kmm.shared.getTestClient
import org.sagebionetworks.bridge.kmm.shared.models.UploadFile
import org.sagebionetworks.bridge.kmm.shared.models.UploadMetadata
import org.sagebionetworks.bridge.kmm.shared.models.UploadRequestMetadata
import org.sagebionetworks.bridge.kmm.shared.randomUUID
import org.sagebionetworks.bridge.kmm.shared.testDatabaseDriver
import kotlin.test.*

class AdherenceRecordRepoTest: BaseTest() {

    val instanceGuid = "JB6aZ_lanz34C5iNF3TZ9Q"
    val startedOn = "2021-05-12T23:44:54.319Z"
    val finishedOn = "2021-05-12T23:44:54.319Z"
    val eventTimestamp = "2021-05-12T23:44:51.872Z"

    val json = "{\n" +
            "   \"items\":[\n" +
            "      {\n" +
            "         \"instanceGuid\":\""+ instanceGuid + "\",\n" +
            "         \"startedOn\":\""+ startedOn + "\",\n" +
            "         \"finishedOn\":\""+ finishedOn + "\",\n" +
            "         \"eventTimestamp\":\""+ eventTimestamp +"\",\n" +
            "         \"clientTimeZone\":\""+ TimeZone.currentSystemDefault().id +"\",\n" +
            "         \"type\":\"AdherenceRecord\"\n" +
            "      }\n" +
            "   ],\n" +
            "   \"total\":1,\n" +
            "   \"type\":\"PagedResourceList\"\n" +
            "}"

    @Test
    fun testAdherenceRepo() {
        runTest {
            val studyId = "testId"
            val scope = CoroutineScope(SupervisorJob() + Dispatchers.IO)
            val repo = AdherenceRecordRepo(getTestClient(json), null, ResourceDatabaseHelper(testDatabaseDriver()), scope)

            assertTrue(repo.loadRemoteAdherenceRecords(studyId))
            val adherenceRecord = repo.getCachedAdherenceRecord(instanceGuid, startedOn)
            assertNotNull(adherenceRecord)

            val recordMap =  repo.getCachedAdherenceRecords(listOf(instanceGuid), studyId)
            assertEquals(1, recordMap.size)
            val recordList = recordMap.get(instanceGuid)
            assertNotNull(recordList)
            val record = recordList.get(0)
            assertNotNull(record)
            assertEquals(instanceGuid, record.instanceGuid)
            val db = repo.database
            val resource = db.getResource(instanceGuid, ResourceType.ADHERENCE_RECORD, studyId)
            assertNotNull(resource)
            assertFalse(resource.needSave)
            db.clearDatabase()
        }
    }

    @Test
    fun testRequestUploadMetadata() {
        runTest {
            val studyId = "testId"
            val scope = CoroutineScope(SupervisorJob() + Dispatchers.IO)
            val repo = AdherenceRecordRepo(
                getTestClient(json),
                null,
                ResourceDatabaseHelper(testDatabaseDriver()),
                scope
            )

            assertTrue(repo.loadRemoteAdherenceRecords(studyId))
            val adherenceRecord =
                repo.getCachedAdherenceRecord(instanceGuid, startedOn)
            assertNotNull(adherenceRecord)
            val metadata = UploadMetadata(
                instanceGuid = instanceGuid,
                eventTimestamp = "eventTimestamp",
                startedOn = startedOn
            )
            val uploadFile = UploadFile(
                filePath = randomUUID(),
                contentType = "application/zip",
                fileLength = 1024,
                md5Hash = randomUUID(),
                metadata = metadata
            );
            val uploadRequest = uploadFile.getUploadRequest(repo)
            val expectedRequestMetadata = UploadRequestMetadata(adherenceRecord).toJsonMap()
            val uploadRequestMetadata = uploadRequest.metadata
            assertEquals(expectedRequestMetadata, uploadRequestMetadata)
            assertEquals(instanceGuid, uploadRequestMetadata?.get("instanceGuid")?.jsonPrimitive?.content)
            assertEquals(startedOn, uploadRequestMetadata?.get("startedOn")?.jsonPrimitive?.content)
            assertEquals(finishedOn, uploadRequestMetadata?.get("finishedOn")?.jsonPrimitive?.content)
            assertEquals(eventTimestamp, uploadRequestMetadata?.get("eventTimestamp")?.jsonPrimitive?.content)
            assertEquals(TimeZone.currentSystemDefault().id, uploadRequestMetadata?.get("clientTimeZone")?.jsonPrimitive?.content)
            assertEquals("false", uploadRequestMetadata?.get("declined").toString())

        }
    }

}


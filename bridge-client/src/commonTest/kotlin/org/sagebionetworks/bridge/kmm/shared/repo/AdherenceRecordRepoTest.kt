package org.sagebionetworks.bridge.kmm.shared.repo

import kotlinx.coroutines.MainScope
import org.sagebionetworks.bridge.kmm.shared.BaseTest
import org.sagebionetworks.bridge.kmm.shared.cache.ResourceDatabaseHelper
import org.sagebionetworks.bridge.kmm.shared.getTestClient
import org.sagebionetworks.bridge.kmm.shared.testDatabaseDriver
import kotlin.test.Test
import kotlin.test.assertEquals
import kotlin.test.assertNotNull
import kotlin.test.assertTrue

class AdherenceRecordRepoTest: BaseTest() {

    val instanceGuid = "JB6aZ_lanz34C5iNF3TZ9Q"

    val json = "{\n" +
            "   \"items\":[\n" +
            "      {\n" +
            "         \"instanceGuid\":\""+ instanceGuid + "\",\n" +
            "         \"startedOn\":\"2021-05-12T23:44:54.319Z\",\n" +
            "         \"finishedOn\":\"2021-05-12T23:44:54.319Z\",\n" +
            "         \"eventTimestamp\":\"2021-05-12T23:44:51.872Z\",\n" +
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
            val repo = AdherenceRecordRepo(getTestClient(json), ResourceDatabaseHelper(testDatabaseDriver()), MainScope())

            assertTrue(repo.loadRemoteAdherenceRecords(studyId))
            val recordMap = repo.getCachedAdherenceRecords(listOf(instanceGuid), studyId)
            assertEquals(1, recordMap.size)
            val recordList = recordMap.get(instanceGuid)
            assertNotNull(recordList)
            val record = recordList.get(0)
            assertNotNull(record)
            assertEquals(instanceGuid, record.instanceGuid)
            val db = repo.database
            db.clearDatabase()
        }
    }

}


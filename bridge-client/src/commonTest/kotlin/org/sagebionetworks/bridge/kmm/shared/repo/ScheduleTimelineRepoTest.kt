package org.sagebionetworks.bridge.kmm.shared.repo

import kotlinx.coroutines.MainScope
import kotlinx.coroutines.flow.firstOrNull
import kotlinx.datetime.*
import org.sagebionetworks.bridge.kmm.shared.BaseTest
import org.sagebionetworks.bridge.kmm.shared.cache.ResourceDatabaseHelper
import org.sagebionetworks.bridge.kmm.shared.cache.ResourceResult
import org.sagebionetworks.bridge.kmm.shared.getTestClient
import org.sagebionetworks.bridge.kmm.shared.models.StudyActivityEvent
import org.sagebionetworks.bridge.kmm.shared.models.StudyActivityEventList
import org.sagebionetworks.bridge.kmm.shared.testDatabaseDriver
import kotlin.test.*

class ScheduleTimelineRepoTest: BaseTest() {

    private val testHour = 12//Clock.System.now().toLocalDateTime(TimeZone.currentSystemDefault()).hour
    private val lastHourString = (testHour - 1).toString().padStart(2,'0')
    private val currentHourString = testHour.toString().padStart(2,'0')
    private val nextHourString = (testHour + 1).toString().padStart(2,'0')

    private val scheduleJson = "{\n" +
            "  \"duration\": \"P4D\",\n" +
            "  \"assessments\": [\n" +
            "    {\n" +
            "      \"key\": \"711cde8b711cde8b\",\n" +
            "      \"guid\": \"6GvgSebKPGM5tGT5t-gw7COj\",\n" +
            "      \"appId\": \"sage-assessment-test\",\n" +
            "      \"identifier\": \"dccs\",\n" +
            "      \"revision\": 5,\n" +
            "      \"label\": \"Shape-Color Sorting\",\n" +
            "      \"minutesToComplete\": 3,\n" +
            "      \"colorScheme\": {\n" +
            "        \"background\": \"#FFFFFF\",\n" +
            "        \"foreground\": \"#F5F5F5\",\n" +
            "        \"activated\": \"#CDCDCD\",\n" +
            "        \"inactivated\": \"#D8D8D8\",\n" +
            "        \"type\": \"ColorScheme\"\n" +
            "      },\n" +
            "      \"configUrl\": \"https://ws.sagebridge.org/v1/assessments/6GvgSebKPGM5tGT5t-gw7COj/config\",\n" +
            "      \"type\": \"AssessmentInfo\"\n" +
            "    },\n" +
            "    {\n" +
            "      \"key\": \"6e06751e6e06751e\",\n" +
            "      \"guid\": \"eGhiQTT2a6SCCmjTod6CDb0t\",\n" +
            "      \"appId\": \"sage-assessment-test\",\n" +
            "      \"identifier\": \"Assessment_Test_1\",\n" +
            "      \"revision\": 1,\n" +
            "      \"label\": \"Assessment Test 1\",\n" +
            "      \"minutesToComplete\": 0,\n" +
            "      \"configUrl\": \"https://ws.sagebridge.org/v1/assessments/eGhiQTT2a6SCCmjTod6CDb0t/config\",\n" +
            "      \"type\": \"AssessmentInfo\"\n" +
            "    }\n" +
            "  ],\n" +
            "  \"sessions\": [\n" +
            "    {\n" +
            "      \"guid\": \"iErUfmT0AzIe7DIiwBzFtxZW\",\n" +
            "      \"label\": \"One time 3 day session\",\n" +
            "      \"startEventId\": \"timeline_retrieved\",\n" +
            "      \"performanceOrder\": \"sequential\",\n" +
            "      \"timeWindowGuids\": [\n" +
            "        \"pFWgzjk-7wOa3GSDbvpy-JDc\"\n" +
            "      ],\n" +
            "      \"notifications\": [],\n" +
            "      \"type\": \"SessionInfo\"\n" +
            "    },\n" +
            "    {\n" +
            "      \"guid\": \"p-oBPW7EDXSEt_ZrXcFd0fAD\",\n" +
            "      \"label\": \"Daily Sessions\",\n" +
            "      \"startEventId\": \"timeline_retrieved\",\n" +
            "      \"performanceOrder\": \"sequential\",\n" +
            "      \"minutesToComplete\": 3,\n" +
            "      \"timeWindowGuids\": [\n" +
            "        \"VbyQ7IElHmGZ-jcelaEy2NCE\",\n" +
            "        \"h2wxlJbf7DRYsBgdcQ3exCh7\",\n" +
            "        \"41j9nQyyeNVcHAJJB0d1vl2j\"\n" +
            "      ],\n" +
            "      \"notifications\": [\n" +
            "        {\n" +
            "          \"notifyAt\": \"after_window_start\",\n" +
            "          \"allowSnooze\": true,\n" +
            "          \"message\": {\n" +
            "            \"lang\": \"en\",\n" +
            "            \"subject\": \"Reminder Title\",\n" +
            "            \"message\": \"Reminder Text\",\n" +
            "            \"type\": \"NotificationMessage\"\n" +
            "          },\n" +
            "          \"type\": \"NotificationInfo\"\n" +
            "        }\n" +
            "      ],\n" +
            "      \"type\": \"SessionInfo\"\n" +
            "    }\n" +
            "  ],\n" +
            "  \"schedule\": [\n" +
            "    {\n" +
            "      \"instanceGuid\": \"mvhyXpjhxHDp7R9fyH02SA\",\n" +
            "      \"startDay\": 0,\n" +
            "      \"endDay\": 0,\n" +
            "      \"startTime\": \"$lastHourString:00\",\n" +
            "      \"expiration\": \"PT30M\",\n" +
            "      \"persistent\": true,\n" +
            "      \"assessments\": [\n" +
            "        {\n" +
            "          \"refKey\": \"711cde8b711cde8b\",\n" +
            "          \"instanceGuid\": \"FowEZJgOmdxO-UKA5-ZqLw\",\n" +
            "          \"type\": \"ScheduledAssessment\"\n" +
            "        }\n" +
            "      ],\n" +
            "      \"timeWindowGuid\": \"VbyQ7IElHmGZ-jcelaEy2NCE\",\n" +
            "      \"refGuid\": \"p-oBPW7EDXSEt_ZrXcFd0fAD\",\n" +
            "      \"type\": \"ScheduledSession\"\n" +
            "    },\n" +
            "    {\n" +
            "      \"instanceGuid\": \"QaqwdxDjRc5FzUIAhBHRwA\",\n" +
            "      \"startDay\": 0,\n" +
            "      \"endDay\": 0,\n" +
            "      \"startTime\": \"$currentHourString:00\",\n" +
            "      \"expiration\": \"PT1H\",\n" +
            "      \"assessments\": [\n" +
            "        {\n" +
            "          \"refKey\": \"711cde8b711cde8b\",\n" +
            "          \"instanceGuid\": \"84cIJmOLnSN4vtAkGfPmQw\",\n" +
            "          \"type\": \"ScheduledAssessment\"\n" +
            "        }\n" +
            "      ],\n" +
            "      \"timeWindowGuid\": \"h2wxlJbf7DRYsBgdcQ3exCh7\",\n" +
            "      \"refGuid\": \"p-oBPW7EDXSEt_ZrXcFd0fAD\",\n" +
            "      \"type\": \"ScheduledSession\"\n" +
            "    },\n" +
            "    {\n" +
            "      \"instanceGuid\": \"SL97UWo1ZQEA1tQKKVFkUA\",\n" +
            "      \"startDay\": 0,\n" +
            "      \"endDay\": 0,\n" +
            "      \"startTime\": \"$nextHourString:00\",\n" +
            "      \"expiration\": \"PT1H\",\n" +
            "      \"assessments\": [\n" +
            "        {\n" +
            "          \"refKey\": \"711cde8b711cde8b\",\n" +
            "          \"instanceGuid\": \"e21215jfezzHCKvIp2TyyA\",\n" +
            "          \"type\": \"ScheduledAssessment\"\n" +
            "        }\n" +
            "      ],\n" +
            "      \"timeWindowGuid\": \"41j9nQyyeNVcHAJJB0d1vl2j\",\n" +
            "      \"refGuid\": \"p-oBPW7EDXSEt_ZrXcFd0fAD\",\n" +
            "      \"type\": \"ScheduledSession\"\n" +
            "    },\n" +
            "    {\n" +
            "      \"instanceGuid\": \"GMJvrk1HuOmw7Uote5J4sw\",\n" +
            "      \"startDay\": 0,\n" +
            "      \"endDay\": 2,\n" +
            "      \"startTime\": \"00:00\",\n" +
            "      \"expiration\": \"P3D\",\n" +
            "      \"assessments\": [\n" +
            "        {\n" +
            "          \"refKey\": \"6e06751e6e06751e\",\n" +
            "          \"instanceGuid\": \"fR4uTueyQSMDEumdMAZdnA\",\n" +
            "          \"type\": \"ScheduledAssessment\"\n" +
            "        }\n" +
            "      ],\n" +
            "      \"timeWindowGuid\": \"pFWgzjk-7wOa3GSDbvpy-JDc\",\n" +
            "      \"refGuid\": \"iErUfmT0AzIe7DIiwBzFtxZW\",\n" +
            "      \"type\": \"ScheduledSession\"\n" +
            "    },\n" +
            "    {\n" +
            "      \"instanceGuid\": \"lVJ-cmbE3cxDWvXcc61tWw\",\n" +
            "      \"startDay\": 1,\n" +
            "      \"endDay\": 1,\n" +
            "      \"startTime\": \"$lastHourString:00\",\n" +
            "      \"expiration\": \"PT30M\",\n" +
            "      \"persistent\": true,\n" +
            "      \"assessments\": [\n" +
            "        {\n" +
            "          \"refKey\": \"711cde8b711cde8b\",\n" +
            "          \"instanceGuid\": \"mv8cxYLK8vrgWQ2F7Um71Q\",\n" +
            "          \"type\": \"ScheduledAssessment\"\n" +
            "        }\n" +
            "      ],\n" +
            "      \"timeWindowGuid\": \"VbyQ7IElHmGZ-jcelaEy2NCE\",\n" +
            "      \"refGuid\": \"p-oBPW7EDXSEt_ZrXcFd0fAD\",\n" +
            "      \"type\": \"ScheduledSession\"\n" +
            "    },\n" +
            "    {\n" +
            "      \"instanceGuid\": \"XlZ3SrLpmEQ2E8PuUUcs7g\",\n" +
            "      \"startDay\": 1,\n" +
            "      \"endDay\": 1,\n" +
            "      \"startTime\": \"$currentHourString:00\",\n" +
            "      \"expiration\": \"PT1H\",\n" +
            "      \"assessments\": [\n" +
            "        {\n" +
            "          \"refKey\": \"711cde8b711cde8b\",\n" +
            "          \"instanceGuid\": \"GgQVjdjyI0uksdnuKpd6SA\",\n" +
            "          \"type\": \"ScheduledAssessment\"\n" +
            "        }\n" +
            "      ],\n" +
            "      \"timeWindowGuid\": \"h2wxlJbf7DRYsBgdcQ3exCh7\",\n" +
            "      \"refGuid\": \"p-oBPW7EDXSEt_ZrXcFd0fAD\",\n" +
            "      \"type\": \"ScheduledSession\"\n" +
            "    },\n" +
            "    {\n" +
            "      \"instanceGuid\": \"-B_yTKp8eTGK7NY_qJ0UTA\",\n" +
            "      \"startDay\": 1,\n" +
            "      \"endDay\": 1,\n" +
            "      \"startTime\": \"$nextHourString:00\",\n" +
            "      \"expiration\": \"PT1H\",\n" +
            "      \"assessments\": [\n" +
            "        {\n" +
            "          \"refKey\": \"711cde8b711cde8b\",\n" +
            "          \"instanceGuid\": \"evLwKAYAD_f0Ecln4QmY_Q\",\n" +
            "          \"type\": \"ScheduledAssessment\"\n" +
            "        }\n" +
            "      ],\n" +
            "      \"timeWindowGuid\": \"41j9nQyyeNVcHAJJB0d1vl2j\",\n" +
            "      \"refGuid\": \"p-oBPW7EDXSEt_ZrXcFd0fAD\",\n" +
            "      \"type\": \"ScheduledSession\"\n" +
            "    },\n" +
            "    {\n" +
            "      \"instanceGuid\": \"6YyBNuEPir0Vkd3a-crQbA\",\n" +
            "      \"startDay\": 2,\n" +
            "      \"endDay\": 2,\n" +
            "      \"startTime\": \"$lastHourString:00\",\n" +
            "      \"expiration\": \"PT30M\",\n" +
            "      \"persistent\": true,\n" +
            "      \"assessments\": [\n" +
            "        {\n" +
            "          \"refKey\": \"711cde8b711cde8b\",\n" +
            "          \"instanceGuid\": \"d5zbbpFUcGeganSy_TJIxg\",\n" +
            "          \"type\": \"ScheduledAssessment\"\n" +
            "        }\n" +
            "      ],\n" +
            "      \"timeWindowGuid\": \"VbyQ7IElHmGZ-jcelaEy2NCE\",\n" +
            "      \"refGuid\": \"p-oBPW7EDXSEt_ZrXcFd0fAD\",\n" +
            "      \"type\": \"ScheduledSession\"\n" +
            "    },\n" +
            "    {\n" +
            "      \"instanceGuid\": \"CDWlxjraDB_yn_jUl0YagA\",\n" +
            "      \"startDay\": 2,\n" +
            "      \"endDay\": 2,\n" +
            "      \"startTime\": \"$currentHourString:00\",\n" +
            "      \"expiration\": \"PT1H\",\n" +
            "      \"assessments\": [\n" +
            "        {\n" +
            "          \"refKey\": \"711cde8b711cde8b\",\n" +
            "          \"instanceGuid\": \"8W35QTL5ph2DAnd1lvnejA\",\n" +
            "          \"type\": \"ScheduledAssessment\"\n" +
            "        }\n" +
            "      ],\n" +
            "      \"timeWindowGuid\": \"h2wxlJbf7DRYsBgdcQ3exCh7\",\n" +
            "      \"refGuid\": \"p-oBPW7EDXSEt_ZrXcFd0fAD\",\n" +
            "      \"type\": \"ScheduledSession\"\n" +
            "    },\n" +
            "    {\n" +
            "      \"instanceGuid\": \"wSFtq35JbCog5s4TXXMNRw\",\n" +
            "      \"startDay\": 2,\n" +
            "      \"endDay\": 2,\n" +
            "      \"startTime\": \"$nextHourString:00\",\n" +
            "      \"expiration\": \"PT1H\",\n" +
            "      \"assessments\": [\n" +
            "        {\n" +
            "          \"refKey\": \"711cde8b711cde8b\",\n" +
            "          \"instanceGuid\": \"GYMXqSOe1JFKifK2XWx2Gg\",\n" +
            "          \"type\": \"ScheduledAssessment\"\n" +
            "        }\n" +
            "      ],\n" +
            "      \"timeWindowGuid\": \"41j9nQyyeNVcHAJJB0d1vl2j\",\n" +
            "      \"refGuid\": \"p-oBPW7EDXSEt_ZrXcFd0fAD\",\n" +
            "      \"type\": \"ScheduledSession\"\n" +
            "    },\n" +
            "    {\n" +
            "      \"instanceGuid\": \"T8X0XUUwUwcr3k6zEh7cBw\",\n" +
            "      \"startDay\": 3,\n" +
            "      \"endDay\": 3,\n" +
            "      \"startTime\": \"$lastHourString:00\",\n" +
            "      \"expiration\": \"PT30M\",\n" +
            "      \"persistent\": true,\n" +
            "      \"assessments\": [\n" +
            "        {\n" +
            "          \"refKey\": \"711cde8b711cde8b\",\n" +
            "          \"instanceGuid\": \"tFtJNUMcUssPezzwKmrB2w\",\n" +
            "          \"type\": \"ScheduledAssessment\"\n" +
            "        }\n" +
            "      ],\n" +
            "      \"timeWindowGuid\": \"VbyQ7IElHmGZ-jcelaEy2NCE\",\n" +
            "      \"refGuid\": \"p-oBPW7EDXSEt_ZrXcFd0fAD\",\n" +
            "      \"type\": \"ScheduledSession\"\n" +
            "    },\n" +
            "    {\n" +
            "      \"instanceGuid\": \"ud-UBuDNBFHDtDrx9YodFA\",\n" +
            "      \"startDay\": 3,\n" +
            "      \"endDay\": 3,\n" +
            "      \"startTime\": \"$currentHourString:00\",\n" +
            "      \"expiration\": \"PT1H\",\n" +
            "      \"assessments\": [\n" +
            "        {\n" +
            "          \"refKey\": \"711cde8b711cde8b\",\n" +
            "          \"instanceGuid\": \"oJp7v2cGXZHVZlLhy1lLuw\",\n" +
            "          \"type\": \"ScheduledAssessment\"\n" +
            "        }\n" +
            "      ],\n" +
            "      \"timeWindowGuid\": \"h2wxlJbf7DRYsBgdcQ3exCh7\",\n" +
            "      \"refGuid\": \"p-oBPW7EDXSEt_ZrXcFd0fAD\",\n" +
            "      \"type\": \"ScheduledSession\"\n" +
            "    },\n" +
            "    {\n" +
            "      \"instanceGuid\": \"CukddPZ9eXREe7lxuL0cXQ\",\n" +
            "      \"startDay\": 3,\n" +
            "      \"endDay\": 3,\n" +
            "      \"startTime\": \"$nextHourString:00\",\n" +
            "      \"expiration\": \"PT1H\",\n" +
            "      \"assessments\": [\n" +
            "        {\n" +
            "          \"refKey\": \"711cde8b711cde8b\",\n" +
            "          \"instanceGuid\": \"Q2QqJtScMENGF23bmizvjQ\",\n" +
            "          \"type\": \"ScheduledAssessment\"\n" +
            "        }\n" +
            "      ],\n" +
            "      \"timeWindowGuid\": \"41j9nQyyeNVcHAJJB0d1vl2j\",\n" +
            "      \"refGuid\": \"p-oBPW7EDXSEt_ZrXcFd0fAD\",\n" +
            "      \"type\": \"ScheduledSession\"\n" +
            "    }\n" +
            "  ],\n" +
            "  \"type\": \"Timeline\"\n" +
            "}"
    
    val assessmentInstanceGuid = "oJp7v2cGXZHVZlLhy1lLuw"

    val adherenceRecordjson = "{\n" +
            "   \"items\":[\n" +
            "      {\n" +
            "         \"instanceGuid\":\""+ assessmentInstanceGuid + "\",\n" +
            "         \"startedOn\":\"2021-05-12T23:44:54.319Z\",\n" +
            "         \"finishedOn\":\"2021-05-12T23:44:54.319Z\",\n" +
            "         \"eventTimestamp\":\"2021-05-12T23:44:51.872Z\",\n" +
            "         \"type\":\"AdherenceRecord\"\n" +
            "      }\n" +
            "   ],\n" +
            "   \"total\":1,\n" +
            "   \"type\":\"PagedResourceList\"\n" +
            "}"


    private fun getActivityEventList(timeStamp: Instant): StudyActivityEventList {
        return StudyActivityEventList(items = listOf(StudyActivityEvent(eventId = "timeline_retrieved", timestamp = timeStamp)))
    }

    private fun getTodayInstant(): Instant {
        val nowDateTime = Clock.System.now().toLocalDateTime(TimeZone.currentSystemDefault())
        val todayNoonDateTime = LocalDateTime(year = nowDateTime.year, month = nowDateTime.month, dayOfMonth = nowDateTime.dayOfMonth, hour = testHour, minute = 0, second = 0)
        return todayNoonDateTime.toInstant(TimeZone.currentSystemDefault())
    }

    private fun getTestScheduleTimelineRepo(adherenceRecordJson: String = "") : ScheduleTimelineRepo {
        val databaseHelper = ResourceDatabaseHelper(testDatabaseDriver())
        val adherenceRecordRepo = AdherenceRecordRepo(getTestClient(adherenceRecordJson), databaseHelper, MainScope())
        return ScheduleTimelineRepo(adherenceRecordRepo, getTestClient(scheduleJson), databaseHelper, MainScope())
    }

    @Test
    fun testScheduledSessionsDay1() {
        runTest {
            val repo = getTestScheduleTimelineRepo()
            val activityEventList = getActivityEventList(Clock.System.now().minus(DateTimeUnit.DAY, TimeZone.currentSystemDefault()))

            val resourceResult = repo.getSessionsForDay("sage-assessment-test", activityEventList, getTodayInstant()).firstOrNull { it is ResourceResult.Success }

            assertTrue(resourceResult is ResourceResult.Success)
            val sessionList = resourceResult.data
            assertNotNull(sessionList)
            assertEquals(3, sessionList.size)

            //First session should be the 3 day session that started yesterday
            val session1 = sessionList.get(0)
            assertEquals("One time 3 day session", session1.sessionInfo.label)

            //Second session should have started in current hour
            val session2 = sessionList.get(1)
            assertEquals("Daily Sessions", session2.sessionInfo.label)
            assertEquals("XlZ3SrLpmEQ2E8PuUUcs7g", session2.instanceGuid)

            //Third session will be starting next hour
            val session3 = sessionList.get(2)
            assertEquals("Daily Sessions", session3.sessionInfo.label)
            assertEquals("-B_yTKp8eTGK7NY_qJ0UTA", session3.instanceGuid)
        }

    }

    @Test
    fun testScheduledSessionsDay3() {
        runTest {
            val repo = getTestScheduleTimelineRepo()
            val activityEventList = getActivityEventList(Clock.System.now().minus(3, DateTimeUnit.DAY, TimeZone.currentSystemDefault()))

            val resourceResult = repo.getSessionsForDay("sage-assessment-test", activityEventList, getTodayInstant()).firstOrNull { it is ResourceResult.Success }

            assertTrue(resourceResult is ResourceResult.Success)
            val sessionList = resourceResult.data
            assertNotNull(sessionList)
            assertEquals(2, sessionList.size)

            //First session should have started in current hour
            val session2 = sessionList.get(0)
            assertEquals("Daily Sessions", session2.sessionInfo.label)
            assertEquals("ud-UBuDNBFHDtDrx9YodFA", session2.instanceGuid)
            assertFalse(session2.isCompleted)

            //Second session will be starting next hour
            val session3 = sessionList.get(1)
            assertEquals("Daily Sessions", session3.sessionInfo.label)
            assertEquals("CukddPZ9eXREe7lxuL0cXQ", session3.instanceGuid)

        }
    }

    @Test
    fun testScheduledSessionsDay3WithCompletion() {
        runTest {
            val studyId = "sage-assessment-test"
            val repo = getTestScheduleTimelineRepo(adherenceRecordjson)
            repo.adherenceRecordRepo.loadRemoteAdherenceRecords(studyId)
            val activityEventList = getActivityEventList(Clock.System.now().minus(3, DateTimeUnit.DAY, TimeZone.currentSystemDefault()))

            val resourceResult = repo.getSessionsForDay(studyId, activityEventList, getTodayInstant()).firstOrNull { it is ResourceResult.Success }

            assertTrue(resourceResult is ResourceResult.Success)
            val sessionList = resourceResult.data
            assertNotNull(sessionList)
            assertEquals(2, sessionList.size)

            //First session should have started in current hour and be completed
            val session2 = sessionList.get(0)
            assertEquals("Daily Sessions", session2.sessionInfo.label)
            assertEquals("ud-UBuDNBFHDtDrx9YodFA", session2.instanceGuid)
            assertTrue(session2.isCompleted)

            //Second session will be starting next hour
            val session3 = sessionList.get(1)
            assertEquals("Daily Sessions", session3.sessionInfo.label)
            assertEquals("CukddPZ9eXREe7lxuL0cXQ", session3.instanceGuid)

        }
    }

    @Test
    fun testScheduledSessionsDay4() {
        runTest {
            val repo = getTestScheduleTimelineRepo()
            val activityEventList = getActivityEventList(Clock.System.now().minus(4, DateTimeUnit.DAY, TimeZone.currentSystemDefault()))

            val resourceResult = repo.getSessionsForDay("sage-assessment-test", activityEventList, getTodayInstant()).firstOrNull { it is ResourceResult.Success }

            assertTrue(resourceResult is ResourceResult.Success)
            val sessionList = resourceResult.data
            assertNotNull(sessionList)
            assertTrue(sessionList.isEmpty())
        }
    }

}


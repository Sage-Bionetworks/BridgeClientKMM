package org.sagebionetworks.bridge.kmm.shared.repo

import kotlinx.coroutines.MainScope
import kotlinx.coroutines.flow.firstOrNull
import kotlinx.datetime.*
import kotlinx.serialization.encodeToString
import kotlinx.serialization.json.Json
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

    private val scheduleJson = """{
  "duration": "P4D",
  "assessments": [
    {
      "key": "711cde8b711cde8b",
      "guid": "6GvgSebKPGM5tGT5t-gw7COj",
      "appId": "sage-assessment-test",
      "identifier": "dccs",
      "revision": 5,
      "label": "Shape-Color Sorting",
      "minutesToComplete": 3,
      "colorScheme": {
        "background": "#FFFFFF",
        "foreground": "#F5F5F5",
        "activated": "#CDCDCD",
        "inactivated": "#D8D8D8",
        "type": "ColorScheme"
      },
      "configUrl": "https://ws.sagebridge.org/v1/assessments/6GvgSebKPGM5tGT5t-gw7COj/config",
      "type": "AssessmentInfo"
    },
    {
      "key": "6e06751e6e06751e",
      "guid": "eGhiQTT2a6SCCmjTod6CDb0t",
      "appId": "sage-assessment-test",
      "identifier": "Assessment_Test_1",
      "revision": 1,
      "label": "Assessment Test 1",
      "minutesToComplete": 0,
      "configUrl": "https://ws.sagebridge.org/v1/assessments/eGhiQTT2a6SCCmjTod6CDb0t/config",
      "type": "AssessmentInfo"
    }
  ],
  "sessions": [
    {
      "guid": "iErUfmT0AzIe7DIiwBzFtxZW",
      "label": "One time 3 day session",
      "startEventId": "timeline_retrieved",
      "performanceOrder": "sequential",
      "timeWindowGuids": [
        "pFWgzjk-7wOa3GSDbvpy-JDc"
      ],
      "notifications": [],
      "type": "SessionInfo"
    },
    {
      "guid": "p-oBPW7EDXSEt_ZrXcFd0fAD",
      "label": "Daily Sessions",
      "startEventId": "timeline_retrieved",
      "performanceOrder": "sequential",
      "minutesToComplete": 3,
      "timeWindowGuids": [
        "VbyQ7IElHmGZ-jcelaEy2NCE",
        "h2wxlJbf7DRYsBgdcQ3exCh7",
        "41j9nQyyeNVcHAJJB0d1vl2j"
      ],
      "notifications": [
        {
          "notifyAt": "after_window_start",
          "allowSnooze": true,
          "message": {
            "lang": "en",
            "subject": "Reminder Title",
            "message": "Reminder Text",
            "type": "NotificationMessage"
          },
          "type": "NotificationInfo"
        }
      ],
      "type": "SessionInfo"
    }
  ],
  "schedule": [
    {
      "instanceGuid": "mvhyXpjhxHDp7R9fyH02SA",
      "startDay": 0,
      "endDay": 0,
      "startTime": "$lastHourString:00",
      "expiration": "PT30M",
      "persistent": true,
      "assessments": [
        {
          "refKey": "711cde8b711cde8b",
          "instanceGuid": "FowEZJgOmdxO-UKA5-ZqLw",
          "type": "ScheduledAssessment"
        }
      ],
      "timeWindowGuid": "VbyQ7IElHmGZ-jcelaEy2NCE",
      "refGuid": "p-oBPW7EDXSEt_ZrXcFd0fAD",
      "type": "ScheduledSession"
    },
    {
      "instanceGuid": "QaqwdxDjRc5FzUIAhBHRwA",
      "startDay": 0,
      "endDay": 0,
      "startTime": "$currentHourString:00",
      "expiration": "PT1H",
      "assessments": [
        {
          "refKey": "711cde8b711cde8b",
          "instanceGuid": "84cIJmOLnSN4vtAkGfPmQw",
          "type": "ScheduledAssessment"
        }
      ],
      "timeWindowGuid": "h2wxlJbf7DRYsBgdcQ3exCh7",
      "refGuid": "p-oBPW7EDXSEt_ZrXcFd0fAD",
      "type": "ScheduledSession"
    },
    {
      "instanceGuid": "SL97UWo1ZQEA1tQKKVFkUA",
      "startDay": 0,
      "endDay": 0,
      "startTime": "$nextHourString:00",
      "expiration": "PT1H",
      "assessments": [
        {
          "refKey": "711cde8b711cde8b",
          "instanceGuid": "e21215jfezzHCKvIp2TyyA",
          "type": "ScheduledAssessment"
        }
      ],
      "timeWindowGuid": "41j9nQyyeNVcHAJJB0d1vl2j",
      "refGuid": "p-oBPW7EDXSEt_ZrXcFd0fAD",
      "type": "ScheduledSession"
    },
    {
      "instanceGuid": "GMJvrk1HuOmw7Uote5J4sw",
      "startDay": 0,
      "endDay": 2,
      "startTime": "00:00",
      "expiration": "P3D",
      "assessments": [
        {
          "refKey": "6e06751e6e06751e",
          "instanceGuid": "fR4uTueyQSMDEumdMAZdnA",
          "type": "ScheduledAssessment"
        }
      ],
      "timeWindowGuid": "pFWgzjk-7wOa3GSDbvpy-JDc",
      "refGuid": "iErUfmT0AzIe7DIiwBzFtxZW",
      "type": "ScheduledSession"
    },
    {
      "instanceGuid": "lVJ-cmbE3cxDWvXcc61tWw",
      "startDay": 1,
      "endDay": 1,
      "startTime": "$lastHourString:00",
      "expiration": "PT30M",
      "persistent": true,
      "assessments": [
        {
          "refKey": "711cde8b711cde8b",
          "instanceGuid": "mv8cxYLK8vrgWQ2F7Um71Q",
          "type": "ScheduledAssessment"
        }
      ],
      "timeWindowGuid": "VbyQ7IElHmGZ-jcelaEy2NCE",
      "refGuid": "p-oBPW7EDXSEt_ZrXcFd0fAD",
      "type": "ScheduledSession"
    },
    {
      "instanceGuid": "XlZ3SrLpmEQ2E8PuUUcs7g",
      "startDay": 1,
      "endDay": 1,
      "startTime": "$currentHourString:00",
      "expiration": "PT1H",
      "assessments": [
        {
          "refKey": "711cde8b711cde8b",
          "instanceGuid": "GgQVjdjyI0uksdnuKpd6SA",
          "type": "ScheduledAssessment"
        }
      ],
      "timeWindowGuid": "h2wxlJbf7DRYsBgdcQ3exCh7",
      "refGuid": "p-oBPW7EDXSEt_ZrXcFd0fAD",
      "type": "ScheduledSession"
    },
    {
      "instanceGuid": "-B_yTKp8eTGK7NY_qJ0UTA",
      "startDay": 1,
      "endDay": 1,
      "startTime": "$nextHourString:00",
      "expiration": "PT1H",
      "assessments": [
        {
          "refKey": "711cde8b711cde8b",
          "instanceGuid": "evLwKAYAD_f0Ecln4QmY_Q",
          "type": "ScheduledAssessment"
        }
      ],
      "timeWindowGuid": "41j9nQyyeNVcHAJJB0d1vl2j",
      "refGuid": "p-oBPW7EDXSEt_ZrXcFd0fAD",
      "type": "ScheduledSession"
    },
    {
      "instanceGuid": "6YyBNuEPir0Vkd3a-crQbA",
      "startDay": 2,
      "endDay": 2,
      "startTime": "$lastHourString:00",
      "expiration": "PT30M",
      "persistent": true,
      "assessments": [
        {
          "refKey": "711cde8b711cde8b",
          "instanceGuid": "d5zbbpFUcGeganSy_TJIxg",
          "type": "ScheduledAssessment"
        }
      ],
      "timeWindowGuid": "VbyQ7IElHmGZ-jcelaEy2NCE",
      "refGuid": "p-oBPW7EDXSEt_ZrXcFd0fAD",
      "type": "ScheduledSession"
    },
    {
      "instanceGuid": "CDWlxjraDB_yn_jUl0YagA",
      "startDay": 2,
      "endDay": 2,
      "startTime": "$currentHourString:00",
      "expiration": "PT1H",
      "assessments": [
        {
          "refKey": "711cde8b711cde8b",
          "instanceGuid": "8W35QTL5ph2DAnd1lvnejA",
          "type": "ScheduledAssessment"
        }
      ],
      "timeWindowGuid": "h2wxlJbf7DRYsBgdcQ3exCh7",
      "refGuid": "p-oBPW7EDXSEt_ZrXcFd0fAD",
      "type": "ScheduledSession"
    },
    {
      "instanceGuid": "wSFtq35JbCog5s4TXXMNRw",
      "startDay": 2,
      "endDay": 2,
      "startTime": "$nextHourString:00",
      "expiration": "PT1H",
      "assessments": [
        {
          "refKey": "711cde8b711cde8b",
          "instanceGuid": "GYMXqSOe1JFKifK2XWx2Gg",
          "type": "ScheduledAssessment"
        }
      ],
      "timeWindowGuid": "41j9nQyyeNVcHAJJB0d1vl2j",
      "refGuid": "p-oBPW7EDXSEt_ZrXcFd0fAD",
      "type": "ScheduledSession"
    },
    {
      "instanceGuid": "T8X0XUUwUwcr3k6zEh7cBw",
      "startDay": 3,
      "endDay": 3,
      "startTime": "$lastHourString:00",
      "expiration": "PT30M",
      "persistent": true,
      "assessments": [
        {
          "refKey": "711cde8b711cde8b",
          "instanceGuid": "tFtJNUMcUssPezzwKmrB2w",
          "type": "ScheduledAssessment"
        }
      ],
      "timeWindowGuid": "VbyQ7IElHmGZ-jcelaEy2NCE",
      "refGuid": "p-oBPW7EDXSEt_ZrXcFd0fAD",
      "type": "ScheduledSession"
    },
    {
      "instanceGuid": "ud-UBuDNBFHDtDrx9YodFA",
      "startDay": 3,
      "endDay": 3,
      "startTime": "$currentHourString:00",
      "expiration": "PT1H",
      "assessments": [
        {
          "refKey": "711cde8b711cde8b",
          "instanceGuid": "oJp7v2cGXZHVZlLhy1lLuw",
          "type": "ScheduledAssessment"
        }
      ],
      "timeWindowGuid": "h2wxlJbf7DRYsBgdcQ3exCh7",
      "refGuid": "p-oBPW7EDXSEt_ZrXcFd0fAD",
      "type": "ScheduledSession"
    },
    {
      "instanceGuid": "CukddPZ9eXREe7lxuL0cXQ",
      "startDay": 3,
      "endDay": 3,
      "startTime": "$nextHourString:00",
      "expiration": "PT1H",
      "assessments": [
        {
          "refKey": "711cde8b711cde8b",
          "instanceGuid": "Q2QqJtScMENGF23bmizvjQ",
          "type": "ScheduledAssessment"
        }
      ],
      "timeWindowGuid": "41j9nQyyeNVcHAJJB0d1vl2j",
      "refGuid": "p-oBPW7EDXSEt_ZrXcFd0fAD",
      "type": "ScheduledSession"
    }
  ],
  "type": "Timeline"
}"""
    
    private val assessmentInstanceGuid = "oJp7v2cGXZHVZlLhy1lLuw"

    private val adherenceRecordjson = "{\n" +
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

    private val adherenceRecordDay2json = "{\n" +
            "   \"items\":[\n" +
            "      {\n" +
            "         \"instanceGuid\":\"fR4uTueyQSMDEumdMAZdnA\",\n" +
            "         \"startedOn\":\"2021-05-12T23:44:54.319Z\",\n" +
            "         \"finishedOn\":\"2021-05-12T23:44:54.319Z\",\n" +
            "         \"eventTimestamp\":\"2021-05-12T23:44:51.872Z\",\n" +
            "         \"type\":\"AdherenceRecord\"\n" +
            "      },\n" +
            "      {\n" +
            "         \"instanceGuid\":\"8W35QTL5ph2DAnd1lvnejA\",\n" +
            "         \"startedOn\":\"2021-05-12T23:44:54.319Z\",\n" +
            "         \"finishedOn\":\"2021-05-12T23:44:54.319Z\",\n" +
            "         \"eventTimestamp\":\"2021-05-12T23:44:51.872Z\",\n" +
            "         \"type\":\"AdherenceRecord\"\n" +
            "      },\n" +
            "      {\n" +
            "         \"instanceGuid\":\"GYMXqSOe1JFKifK2XWx2Gg\",\n" +
            "         \"startedOn\":\"2021-05-12T23:44:54.319Z\",\n" +
            "         \"finishedOn\":\"2021-05-12T23:44:54.319Z\",\n" +
            "         \"eventTimestamp\":\"2021-05-12T23:44:51.872Z\",\n" +
            "         \"type\":\"AdherenceRecord\"\n" +
            "      }\n" +
            "   ],\n" +
            "   \"total\":3,\n" +
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

    private fun getTestScheduleTimelineRepo(adherenceRecordJson: String = "", timeStamp: Instant) : ScheduleTimelineRepo {
        val databaseHelper = ResourceDatabaseHelper(testDatabaseDriver())
        val adherenceRecordRepo = AdherenceRecordRepo(getTestClient(adherenceRecordJson), databaseHelper, MainScope())
        val eventJson = Json.encodeToString(getActivityEventList(timeStamp))
        val activityEventsRepo = ActivityEventsRepo(getTestClient(eventJson), databaseHelper, MainScope())
        return ScheduleTimelineRepo(adherenceRecordRepo, activityEventsRepo, getTestClient(scheduleJson), databaseHelper, MainScope())
    }

    @Test
    fun testScheduledSessionsDay1() {
        runTest {
            val eventTimeStamp = Clock.System.now().minus(DateTimeUnit.DAY, TimeZone.currentSystemDefault())
            val repo = getTestScheduleTimelineRepo(timeStamp = eventTimeStamp)

            val resourceResult = repo.getSessionsForDay("sage-assessment-test", getTodayInstant()).firstOrNull { it is ResourceResult.Success }

            assertTrue(resourceResult is ResourceResult.Success)
            val sessionList = resourceResult.data
            assertNotNull(sessionList)
            assertEquals(3, sessionList.size)

            //First session should be the 3 day session that started yesterday
            val session1 = sessionList[0]
            assertEquals("One time 3 day session", session1.sessionInfo.label)

            //Second session should have started in current hour
            val session2 = sessionList[1]
            assertEquals("Daily Sessions", session2.sessionInfo.label)
            assertEquals("XlZ3SrLpmEQ2E8PuUUcs7g", session2.instanceGuid)

            //Third session will be starting next hour
            val session3 = sessionList[2]
            assertEquals("Daily Sessions", session3.sessionInfo.label)
            assertEquals("-B_yTKp8eTGK7NY_qJ0UTA", session3.instanceGuid)
        }

    }

    @Test
    fun testScheduledSessionsDay2WithCompletion() {
        runTest {
            val studyId = "sage-assessment-test"
            val eventTimeStamp = Clock.System.now().minus(2, DateTimeUnit.DAY, TimeZone.currentSystemDefault())
            val repo = getTestScheduleTimelineRepo(adherenceRecordDay2json, timeStamp = eventTimeStamp)
            repo.adherenceRecordRepo.loadRemoteAdherenceRecords(studyId)
            val resourceResult = repo.getSessionsForDay(studyId, getTodayInstant()).firstOrNull { it is ResourceResult.Success }
            assertTrue(resourceResult is ResourceResult.Success)
            val sessionList = resourceResult.data
            assertNotNull(sessionList)
            assertEquals(6, sessionList.size)

            //First session should be the 3 day session that started yesterday
            val session1 = sessionList[0]
            assertEquals("One time 3 day session", session1.sessionInfo.label)
            assertTrue(session1.isCompleted)

            //Second session should have started in current hour and be completed
            val session2 = sessionList[1]
            assertEquals("Daily Sessions", session2.sessionInfo.label)
            assertEquals("CDWlxjraDB_yn_jUl0YagA", session2.instanceGuid)
            assertTrue(session2.isCompleted)

            //Third session will be starting next hour
            val session3 = sessionList[2]
            assertEquals("Daily Sessions", session3.sessionInfo.label)
            assertEquals("wSFtq35JbCog5s4TXXMNRw", session3.instanceGuid)
            assertTrue(session3.isCompleted)

            // Next day is shown b/c the current day is finished.

            //Fourth session will start tomorrow
            val session4 = sessionList[3]
            assertEquals("Daily Sessions", session4.sessionInfo.label)
            assertEquals("T8X0XUUwUwcr3k6zEh7cBw", session4.instanceGuid)

            //Fifth session will start tomorrow
            val session5 = sessionList[4]
            assertEquals("Daily Sessions", session5.sessionInfo.label)
            assertEquals("ud-UBuDNBFHDtDrx9YodFA", session5.instanceGuid)

            //Sixth session will start tomorrow
            val session6 = sessionList[5]
            assertEquals("Daily Sessions", session6.sessionInfo.label)
            assertEquals("CukddPZ9eXREe7lxuL0cXQ", session6.instanceGuid)
        }
    }

    @Test
    fun testScheduledSessionsDay3() {
        runTest {
            val eventTimeStamp = Clock.System.now().minus(3, DateTimeUnit.DAY, TimeZone.currentSystemDefault())
            val repo = getTestScheduleTimelineRepo(timeStamp = eventTimeStamp)
            val resourceResult = repo.getSessionsForDay("sage-assessment-test", getTodayInstant()).firstOrNull { it is ResourceResult.Success }

            assertTrue(resourceResult is ResourceResult.Success)
            val sessionList = resourceResult.data
            assertNotNull(sessionList)
            assertEquals(2, sessionList.size)

            //First session should have started in current hour
            val session2 = sessionList[0]
            assertEquals("Daily Sessions", session2.sessionInfo.label)
            assertEquals("ud-UBuDNBFHDtDrx9YodFA", session2.instanceGuid)
            assertFalse(session2.isCompleted)

            //Second session will be starting next hour
            val session3 = sessionList[1]
            assertEquals("Daily Sessions", session3.sessionInfo.label)
            assertEquals("CukddPZ9eXREe7lxuL0cXQ", session3.instanceGuid)

        }
    }

    @Test
    fun testScheduledSessionsDay3WithCompletion() {
        runTest {
            val studyId = "sage-assessment-test"
            val eventTimeStamp = Clock.System.now().minus(3, DateTimeUnit.DAY, TimeZone.currentSystemDefault())
            val repo = getTestScheduleTimelineRepo(adherenceRecordjson, timeStamp = eventTimeStamp)
            repo.adherenceRecordRepo.loadRemoteAdherenceRecords(studyId)
            val resourceResult = repo.getSessionsForDay(studyId, getTodayInstant()).firstOrNull { it is ResourceResult.Success }
            assertTrue(resourceResult is ResourceResult.Success)
            val sessionList = resourceResult.data
            assertNotNull(sessionList)
            assertEquals(2, sessionList.size)

            //First session should have started in current hour and be completed
            val session2 = sessionList[0]
            assertEquals("Daily Sessions", session2.sessionInfo.label)
            assertEquals("ud-UBuDNBFHDtDrx9YodFA", session2.instanceGuid)
            assertTrue(session2.isCompleted)

            //Second session will be starting next hour
            val session3 = sessionList[1]
            assertEquals("Daily Sessions", session3.sessionInfo.label)
            assertEquals("CukddPZ9eXREe7lxuL0cXQ", session3.instanceGuid)

        }
    }

    @Test
    fun testScheduledSessionsDay4() {
        runTest {
            val eventTimeStamp = Clock.System.now().minus(4, DateTimeUnit.DAY, TimeZone.currentSystemDefault())
            val repo = getTestScheduleTimelineRepo(timeStamp = eventTimeStamp)
            val resourceResult = repo.getSessionsForDay("sage-assessment-test", getTodayInstant()).firstOrNull { it is ResourceResult.Success }

            assertTrue(resourceResult is ResourceResult.Success)
            val sessionList = resourceResult.data
            assertNotNull(sessionList)
            assertTrue(sessionList.isEmpty())
        }
    }

}


package org.sagebionetworks.bridge.kmm.shared.repo

import kotlinx.coroutines.MainScope
import kotlinx.coroutines.flow.firstOrNull
import kotlinx.datetime.*
import org.sagebionetworks.bridge.kmm.shared.BaseTest
import org.sagebionetworks.bridge.kmm.shared.cache.ResourceDatabaseHelper
import org.sagebionetworks.bridge.kmm.shared.cache.ResourceResult
import org.sagebionetworks.bridge.kmm.shared.getTestClient
import org.sagebionetworks.bridge.kmm.shared.models.ActivityEvent
import org.sagebionetworks.bridge.kmm.shared.models.ActivityEventList
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
            "      \"type\": \"AssessmentInfo\"\n" +
            "    }\n" +
            "  ],\n" +
            "  \"sessions\": [\n" +
            "    {\n" +
            "      \"guid\": \"p-oBPW7EDXSEt_ZrXcFd0fAD\",\n" +
            "      \"label\": \"Daily Sessions\",\n" +
            "      \"startEventId\": \"study_start_date\",\n" +
            "      \"performanceOrder\": \"sequential\",\n" +
            "      \"notifyAt\": \"start_of_window\",\n" +
            "      \"remindAt\": \"after_window_start\",\n" +
            "      \"reminderPeriod\": \"PT15M\",\n" +
            "      \"minutesToComplete\": 3,\n" +
            "      \"message\": {\n" +
            "        \"lang\": \"en\",\n" +
            "        \"subject\": \"Reminder title\",\n" +
            "        \"message\": \"Reminder body text\",\n" +
            "        \"type\": \"NotificationMessage\"\n" +
            "      },\n" +
            "      \"type\": \"SessionInfo\"\n" +
            "    },\n" +
            "    {\n" +
            "      \"guid\": \"iErUfmT0AzIe7DIiwBzFtxZW\",\n" +
            "      \"label\": \"One time 3 day session\",\n" +
            "      \"startEventId\": \"study_start_date\",\n" +
            "      \"performanceOrder\": \"sequential\",\n" +
            "      \"type\": \"SessionInfo\"\n" +
            "    }\n" +
            "  ],\n" +
            "  \"schedule\": [\n" +
            "    {\n" +
            "      \"instanceGuid\": \"G0jPZKoFv461ghfghAam7Q\",\n" +
            "      \"startDay\": 0,\n" +
            "      \"endDay\": 0,\n" +
            "      \"startTime\": \"$lastHourString:00\",\n" +
            "      \"expiration\": \"PT30M\",\n" +
            "      \"assessments\": [\n" +
            "        {\n" +
            "          \"refKey\": \"711cde8b711cde8b\",\n" +
            "          \"instanceGuid\": \"yhirZNT-Fo6K_pwIsQebJA\",\n" +
            "          \"type\": \"ScheduledAssessment\"\n" +
            "        }\n" +
            "      ],\n" +
            "      \"refGuid\": \"p-oBPW7EDXSEt_ZrXcFd0fAD\",\n" +
            "      \"type\": \"ScheduledSession\"\n" +
            "    },\n" +
            "    {\n" +
            "      \"instanceGuid\": \"jNMbaRjxLf8h3QSgS4PrwQ\",\n" +
            "      \"startDay\": 0,\n" +
            "      \"endDay\": 0,\n" +
            "      \"startTime\": \"$currentHourString:00\",\n" +
            "      \"expiration\": \"PT1H\",\n" +
            "      \"assessments\": [\n" +
            "        {\n" +
            "          \"refKey\": \"711cde8b711cde8b\",\n" +
            "          \"instanceGuid\": \"vL9lHpSmf7PloeR_YyScNw\",\n" +
            "          \"type\": \"ScheduledAssessment\"\n" +
            "        }\n" +
            "      ],\n" +
            "      \"refGuid\": \"p-oBPW7EDXSEt_ZrXcFd0fAD\",\n" +
            "      \"type\": \"ScheduledSession\"\n" +
            "    },\n" +
            "    {\n" +
            "      \"instanceGuid\": \"77FZtXgraEhJsuHdqLe_wg\",\n" +
            "      \"startDay\": 0,\n" +
            "      \"endDay\": 0,\n" +
            "      \"startTime\": \"$nextHourString:00\",\n" +
            "      \"expiration\": \"PT1H\",\n" +
            "      \"assessments\": [\n" +
            "        {\n" +
            "          \"refKey\": \"711cde8b711cde8b\",\n" +
            "          \"instanceGuid\": \"MIC9PfZTIyslpKvOkvPVZA\",\n" +
            "          \"type\": \"ScheduledAssessment\"\n" +
            "        }\n" +
            "      ],\n" +
            "      \"refGuid\": \"p-oBPW7EDXSEt_ZrXcFd0fAD\",\n" +
            "      \"type\": \"ScheduledSession\"\n" +
            "    },\n" +
            "    {\n" +
            "      \"instanceGuid\": \"_O7xwt6ASrU3rbiC4Iw-tQ\",\n" +
            "      \"startDay\": 0,\n" +
            "      \"endDay\": 2,\n" +
            "      \"startTime\": \"00:00\",\n" +
            "      \"expiration\": \"P3D\",\n" +
            "      \"assessments\": [\n" +
            "        {\n" +
            "          \"refKey\": \"6e06751e6e06751e\",\n" +
            "          \"instanceGuid\": \"us9pg7qPWwboUhKgBPjmRw\",\n" +
            "          \"type\": \"ScheduledAssessment\"\n" +
            "        }\n" +
            "      ],\n" +
            "      \"refGuid\": \"iErUfmT0AzIe7DIiwBzFtxZW\",\n" +
            "      \"type\": \"ScheduledSession\"\n" +
            "    },\n" +
            "    {\n" +
            "      \"instanceGuid\": \"HUT3b08mnbl11QFickRMjw\",\n" +
            "      \"startDay\": 1,\n" +
            "      \"endDay\": 1,\n" +
            "      \"startTime\": \"$lastHourString:00\",\n" +
            "      \"expiration\": \"PT30M\",\n" +
            "      \"assessments\": [\n" +
            "        {\n" +
            "          \"refKey\": \"711cde8b711cde8b\",\n" +
            "          \"instanceGuid\": \"W8sZfO5aM0r83PCU777Y2g\",\n" +
            "          \"type\": \"ScheduledAssessment\"\n" +
            "        }\n" +
            "      ],\n" +
            "      \"refGuid\": \"p-oBPW7EDXSEt_ZrXcFd0fAD\",\n" +
            "      \"type\": \"ScheduledSession\"\n" +
            "    },\n" +
            "    {\n" +
            "      \"instanceGuid\": \"nH2H5uPOKRZPTwuNk7lrzw\",\n" +
            "      \"startDay\": 1,\n" +
            "      \"endDay\": 1,\n" +
            "      \"startTime\": \"$currentHourString:00\",\n" +
            "      \"expiration\": \"PT1H\",\n" +
            "      \"assessments\": [\n" +
            "        {\n" +
            "          \"refKey\": \"711cde8b711cde8b\",\n" +
            "          \"instanceGuid\": \"loKcdwE7dRKViqk0Lx_DNg\",\n" +
            "          \"type\": \"ScheduledAssessment\"\n" +
            "        }\n" +
            "      ],\n" +
            "      \"refGuid\": \"p-oBPW7EDXSEt_ZrXcFd0fAD\",\n" +
            "      \"type\": \"ScheduledSession\"\n" +
            "    },\n" +
            "    {\n" +
            "      \"instanceGuid\": \"c6fBm4HPKOs3uj76VVbLzg\",\n" +
            "      \"startDay\": 1,\n" +
            "      \"endDay\": 1,\n" +
            "      \"startTime\": \"$nextHourString:00\",\n" +
            "      \"expiration\": \"PT1H\",\n" +
            "      \"assessments\": [\n" +
            "        {\n" +
            "          \"refKey\": \"711cde8b711cde8b\",\n" +
            "          \"instanceGuid\": \"ygZ5Rp1Nd8rhFJ3bV92W4w\",\n" +
            "          \"type\": \"ScheduledAssessment\"\n" +
            "        }\n" +
            "      ],\n" +
            "      \"refGuid\": \"p-oBPW7EDXSEt_ZrXcFd0fAD\",\n" +
            "      \"type\": \"ScheduledSession\"\n" +
            "    },\n" +
            "    {\n" +
            "      \"instanceGuid\": \"DCVV3QTy5LBkeI3Gpo0lZg\",\n" +
            "      \"startDay\": 2,\n" +
            "      \"endDay\": 2,\n" +
            "      \"startTime\": \"$lastHourString:00\",\n" +
            "      \"expiration\": \"PT30M\",\n" +
            "      \"assessments\": [\n" +
            "        {\n" +
            "          \"refKey\": \"711cde8b711cde8b\",\n" +
            "          \"instanceGuid\": \"nCSEJsWIoe9h3tqPSUBvAw\",\n" +
            "          \"type\": \"ScheduledAssessment\"\n" +
            "        }\n" +
            "      ],\n" +
            "      \"refGuid\": \"p-oBPW7EDXSEt_ZrXcFd0fAD\",\n" +
            "      \"type\": \"ScheduledSession\"\n" +
            "    },\n" +
            "    {\n" +
            "      \"instanceGuid\": \"9kuwM30fuRUmDmj0tNL1Ow\",\n" +
            "      \"startDay\": 2,\n" +
            "      \"endDay\": 2,\n" +
            "      \"startTime\": \"$currentHourString:00\",\n" +
            "      \"expiration\": \"PT1H\",\n" +
            "      \"assessments\": [\n" +
            "        {\n" +
            "          \"refKey\": \"711cde8b711cde8b\",\n" +
            "          \"instanceGuid\": \"QKffqrp64LCjItrCBBT7Yg\",\n" +
            "          \"type\": \"ScheduledAssessment\"\n" +
            "        }\n" +
            "      ],\n" +
            "      \"refGuid\": \"p-oBPW7EDXSEt_ZrXcFd0fAD\",\n" +
            "      \"type\": \"ScheduledSession\"\n" +
            "    },\n" +
            "    {\n" +
            "      \"instanceGuid\": \"dTGZQ1tUOK9nLyVziaVeCg\",\n" +
            "      \"startDay\": 2,\n" +
            "      \"endDay\": 2,\n" +
            "      \"startTime\": \"$nextHourString:00\",\n" +
            "      \"expiration\": \"PT1H\",\n" +
            "      \"assessments\": [\n" +
            "        {\n" +
            "          \"refKey\": \"711cde8b711cde8b\",\n" +
            "          \"instanceGuid\": \"RwQrfykYrbYK90gvuCRfww\",\n" +
            "          \"type\": \"ScheduledAssessment\"\n" +
            "        }\n" +
            "      ],\n" +
            "      \"refGuid\": \"p-oBPW7EDXSEt_ZrXcFd0fAD\",\n" +
            "      \"type\": \"ScheduledSession\"\n" +
            "    },\n" +
            "    {\n" +
            "      \"instanceGuid\": \"nfplEx9dwtRsLxSLKI0kWw\",\n" +
            "      \"startDay\": 3,\n" +
            "      \"endDay\": 3,\n" +
            "      \"startTime\": \"$lastHourString:00\",\n" +
            "      \"expiration\": \"PT30M\",\n" +
            "      \"assessments\": [\n" +
            "        {\n" +
            "          \"refKey\": \"711cde8b711cde8b\",\n" +
            "          \"instanceGuid\": \"rzkx5Th_9rDJrb5ezsHCjA\",\n" +
            "          \"type\": \"ScheduledAssessment\"\n" +
            "        }\n" +
            "      ],\n" +
            "      \"refGuid\": \"p-oBPW7EDXSEt_ZrXcFd0fAD\",\n" +
            "      \"type\": \"ScheduledSession\"\n" +
            "    },\n" +
            "    {\n" +
            "      \"instanceGuid\": \"SI3hC2o0hdDTanRwqVVYIQ\",\n" +
            "      \"startDay\": 3,\n" +
            "      \"endDay\": 3,\n" +
            "      \"startTime\": \"$currentHourString:00\",\n" +
            "      \"expiration\": \"PT1H\",\n" +
            "      \"assessments\": [\n" +
            "        {\n" +
            "          \"refKey\": \"711cde8b711cde8b\",\n" +
            "          \"instanceGuid\": \"sGH_BkWl2SVbPxOH0VwVKQ\",\n" +
            "          \"type\": \"ScheduledAssessment\"\n" +
            "        }\n" +
            "      ],\n" +
            "      \"refGuid\": \"p-oBPW7EDXSEt_ZrXcFd0fAD\",\n" +
            "      \"type\": \"ScheduledSession\"\n" +
            "    },\n" +
            "    {\n" +
            "      \"instanceGuid\": \"OjDKErILgVF04xlYktOF0g\",\n" +
            "      \"startDay\": 3,\n" +
            "      \"endDay\": 3,\n" +
            "      \"startTime\": \"$nextHourString:00\",\n" +
            "      \"expiration\": \"PT1H\",\n" +
            "      \"assessments\": [\n" +
            "        {\n" +
            "          \"refKey\": \"711cde8b711cde8b\",\n" +
            "          \"instanceGuid\": \"c00ETA_tI5o_I-HQLc3OeA\",\n" +
            "          \"type\": \"ScheduledAssessment\"\n" +
            "        }\n" +
            "      ],\n" +
            "      \"refGuid\": \"p-oBPW7EDXSEt_ZrXcFd0fAD\",\n" +
            "      \"type\": \"ScheduledSession\"\n" +
            "    }\n" +
            "  ],\n" +
            "  \"type\": \"Timeline\"\n" +
            "}"

    val assessmentInstanceGuid = "sGH_BkWl2SVbPxOH0VwVKQ"

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


    private fun getActivityEventList(timeStamp: Instant): ActivityEventList {
        return ActivityEventList(items = listOf(ActivityEvent(eventId = "study_start_date", timestamp = timeStamp)))
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
            assertEquals("nH2H5uPOKRZPTwuNk7lrzw", session2.instanceGuid)

            //Third session will be starting next hour
            val session3 = sessionList.get(2)
            assertEquals("Daily Sessions", session3.sessionInfo.label)
            assertEquals("c6fBm4HPKOs3uj76VVbLzg", session3.instanceGuid)
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
            assertEquals("SI3hC2o0hdDTanRwqVVYIQ", session2.instanceGuid)
            assertFalse(session2.isCompleted)

            //Second session will be starting next hour
            val session3 = sessionList.get(1)
            assertEquals("Daily Sessions", session3.sessionInfo.label)
            assertEquals("OjDKErILgVF04xlYktOF0g", session3.instanceGuid)

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
            assertEquals("SI3hC2o0hdDTanRwqVVYIQ", session2.instanceGuid)
            assertTrue(session2.isCompleted)

            //Second session will be starting next hour
            val session3 = sessionList.get(1)
            assertEquals("Daily Sessions", session3.sessionInfo.label)
            assertEquals("OjDKErILgVF04xlYktOF0g", session3.instanceGuid)

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


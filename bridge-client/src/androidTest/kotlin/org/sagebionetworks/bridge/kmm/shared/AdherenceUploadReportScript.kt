package org.sagebionetworks.bridge.kmm.shared

import io.ktor.client.*
import io.ktor.client.plugins.contentnegotiation.*
import io.ktor.client.plugins.logging.*
import io.ktor.serialization.kotlinx.json.*
import kotlinx.coroutines.runBlocking
import kotlinx.datetime.DateTimeUnit
import kotlinx.datetime.TimeZone
import kotlinx.datetime.minus
import kotlinx.serialization.json.Json
import kotlinx.serialization.json.jsonPrimitive
import org.sagebionetworks.bridge.kmm.shared.apis.AdminApis
import org.sagebionetworks.bridge.kmm.shared.apis.SessionTokenFeature
import org.sagebionetworks.bridge.kmm.shared.models.*
import java.io.File
import kotlin.test.Test
import kotlin.test.assertFalse

class AdherenceUploadReportScript {

    private val httpClient: HttpClient = HttpClient {
        val sessionTokenHeaderKey = "Bridge-Session"

        install(ContentNegotiation) {
            json(Json {
                ignoreUnknownKeys = true
            })
        }

        install(Logging) {
            level = LogLevel.ALL
            logger = object : Logger {
                override fun log(message: String) {
                    println(message)
                }
            }
        }

        install(SessionTokenFeature) {
            sessionTokenHeaderName = sessionTokenHeaderKey
            sessionTokenProvider = object : SessionTokenFeature.SessionTokenProvider {

                override fun getSessionToken(): String? {
                    return "Insert_Session_Token_Here"
                }
            }
        }
    }

    private val adminApis = AdminApis(httpClient=httpClient)

    private suspend fun checkUploads(studyId: String) {

        val file = File("/adherence_vs_uploads_$studyId.csv")
        file.createNewFile()
        val printWriter = file.printWriter()
        printWriter.println("ExternalID, UserID, Session Guid, Missing Assessment Upload, Have upload, Filesize (bytes), Finished On, declined, User Agent")

        val enrollmentList = mutableListOf<EnrollmentDetail>()
        val pageSize = 100
        var pageOffset = 0
        do {
            val curOffset = pageOffset
            val enrollments = adminApis.getEnrollments(studyId, null, true, pageOffset, pageSize)
            enrollmentList.addAll(enrollments.items)
            pageOffset+= pageSize
        } while (curOffset + pageSize < enrollments.total)

        assertFalse(enrollmentList.isEmpty())
        println("Enrollments in $studyId: ${enrollmentList.size}")
        for (detail in enrollmentList) {
            val participantId = detail.participant.identifier!!
            if (detail.externalId == null) {
                //For Mobile Toolbox App we only support users with external IDS
                continue
            }
            val externalId = detail.externalId

            val requestInfo = adminApis.getStudyParticipantRequestInfo(studyId, participantId)
            val userAgent = requestInfo.userAgent?.replace(",", "")

            val timeline = adminApis.getStudyParticipantTimeline(studyId, participantId)
            val assessmentMap = timeline.assessments!!.associateBy { it.key }
            val scheduledAssessmentMap = mutableMapOf<String, AssessmentInfo>()
            val scheduledSessionMap = mutableMapOf<String, ScheduledSession>()
            for (scheduledSession in timeline.schedule!!) {
                for (assessmentInstance in scheduledSession.assessments) {
                    scheduledAssessmentMap.put(assessmentInstance.instanceGuid, assessmentMap.get(assessmentInstance.refKey)!!)
                    scheduledSessionMap.put(assessmentInstance.instanceGuid, scheduledSession)
                }
            }

            val endTime = kotlinx.datetime.Clock.System.now()
            val startTime = endTime.minus(1, DateTimeUnit.YEAR, TimeZone.currentSystemDefault())
            val uploads = adminApis.getStudyParticipantUploads(studyId, participantId, startTime.toString(), endTime.toString(), 100, null)
            val uploadMap = mutableMapOf<String, Upload>()
            for (upload in uploads.items!!) {
                uploadMap.put(upload.metadata!!.get("instanceGuid")!!.jsonPrimitive.content, upload)
            }

            val adherenceRecordsSearch = AdherenceRecordsSearch(sortOrder = SortOrder.DESC, pageSize = 500, includeRepeats = true, currentTimestampsOnly = true)
            val adherenceList = adminApis.searchForAdherenceRecords(studyId, participantId, adherenceRecordsSearch)
            for (adherenceRecord in adherenceList.items) {
                val upload = uploadMap.get(adherenceRecord.instanceGuid)
                val assessmentInfo = scheduledAssessmentMap.get(adherenceRecord.instanceGuid)
                val scheduledSession = scheduledSessionMap.get(adherenceRecord.instanceGuid)
                if (assessmentInfo != null) {
                    if (upload == null) {
                        //We have an assessment adherence record without an upload
                        printWriter.println("$externalId, $participantId, ${scheduledSession?.refGuid}, ${assessmentInfo.label}, , ,${adherenceRecord.finishedOn?.toString()}, ${adherenceRecord.declined.toString()}, $userAgent")
                    } else {
                        printWriter.println("$externalId, $participantId, ${scheduledSession?.refGuid}, ${assessmentInfo.label}, true, ${upload.contentLength}, ${adherenceRecord.finishedOn?.toString()}, ${adherenceRecord.declined.toString()}, $userAgent")
                    }
                }
            }
        }
        printWriter.close()

    }


    @Test
    fun testUploads() {
        runBlocking {
            checkUploads("StudyID Here")

        }
    }


}
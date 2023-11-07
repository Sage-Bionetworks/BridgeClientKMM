package org.sagebionetworks.bridge.kmm.shared.integration

import kotlinx.coroutines.flow.filter
import kotlinx.coroutines.flow.first
import kotlinx.datetime.Clock
import kotlinx.datetime.TimeZone
import org.koin.core.component.inject
import org.sagebionetworks.bridge.kmm.shared.cache.ResourceResult
import org.sagebionetworks.bridge.kmm.shared.models.UserSessionInfo
import org.sagebionetworks.bridge.kmm.shared.repo.*
import kotlin.test.*

class IntegrationSmokeTest: AbstractBaseIntegrationTest() {

    private val authRepo by inject<AuthenticationRepository>()
    private val timelineRepo by inject<ScheduleTimelineRepo>()
    private val adherenceRecordRepo by inject<AdherenceRecordRepo>()
    private val studyRepo by inject<StudyRepo>()
    private val activityEventsRepo by inject<ActivityEventsRepo>()
    private val assessmentConfigRepo by inject<AssessmentConfigRepo>()


    @Test
    fun testIntegrationSmokeTest() {
        runTest {
            authRepo.signOut()
            // signIn
            assertFalse(authRepo.isAuthenticated())
            val externalId = getBridgeTestUserExternalId()
            assertNotNull(externalId)
            val signInResult = authRepo.signInExternalId(externalId, externalId)
            assertTrue(signInResult is ResourceResult.Success<*>)
            val sessionInfo = signInResult.data as UserSessionInfo
            val studyId = sessionInfo.studyIds.get(0)

            // Load study
            val studyResult = studyRepo.getStudyInfo(studyId)
            assertTrue(studyResult is ResourceResult.Success)
            val studyInfo = studyResult.data
            assertEquals("BridgeClientKMM Integration Tests Study", studyInfo.name)

            // Set activity event that will trigger the schedule
            val success = activityEventsRepo.createActivityEvent(studyId, "custom:integration-start-test", Clock.System.now())
            assertTrue(success)

            // Load adherence records
            assertTrue(adherenceRecordRepo.loadRemoteAdherenceRecords(studyId))

            // Load participant schedule
            val timeLineFlow = timelineRepo.getSessionsForDay(studyId, Clock.System.now())
            val sliceResult = timeLineFlow.filter { it is ResourceResult.Success }.first()
            val slice = (sliceResult as ResourceResult.Success).data
            assertEquals(TimeZone.currentSystemDefault(), slice.timezone)
            assertEquals(1, slice.scheduledSessionWindows.size)
            val session = slice.scheduledSessionWindows[0]
            assertEquals("TestSession1", session.sessionInfo.label)

            // Load an AssessmentConfig
            val assessmentInfo = session.assessments[0].assessmentInfo
            val assessmentResult = assessmentConfigRepo.getAssessmentConfigAsFlow(assessmentInfo).filter { it is ResourceResult.Success }.first()
            val assessmentConfig = (assessmentResult as ResourceResult.Success).data
            assertEquals("AssessmentConfig", assessmentConfig.type)

            authRepo.signOut()

        }
    }


}
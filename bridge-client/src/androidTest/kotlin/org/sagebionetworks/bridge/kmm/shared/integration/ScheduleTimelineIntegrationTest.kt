package org.sagebionetworks.bridge.kmm.shared.integration

import kotlinx.coroutines.flow.filter
import kotlinx.coroutines.flow.first
import kotlinx.datetime.Clock
import kotlinx.datetime.TimeZone
import org.koin.core.component.inject
import org.sagebionetworks.bridge.kmm.shared.cache.ResourceResult
import org.sagebionetworks.bridge.kmm.shared.models.UserSessionInfo
import org.sagebionetworks.bridge.kmm.shared.repo.AdherenceRecordRepo
import org.sagebionetworks.bridge.kmm.shared.repo.AuthenticationRepository
import org.sagebionetworks.bridge.kmm.shared.repo.ScheduleTimelineRepo
import org.sagebionetworks.bridge.kmm.shared.repo.StudyRepo
import kotlin.test.*

class ScheduleTimelineIntegrationTest: AbstractBaseIntegrationTest() {

    private val authRepo by inject<AuthenticationRepository>()
    private val timelineRepo by inject<ScheduleTimelineRepo>()
    private val adherenceRecordRepo by inject<AdherenceRecordRepo>()
    private val studyRepo by inject<StudyRepo>()


    @Test
    fun testLoadTimeline() {
        runTest {
            authRepo.signOut()
            // signIn
            assertFalse(authRepo.isAuthenticated())
            val externalId = System.getProperty("testExternalId01")
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

            // Load adherence records
            assertTrue(adherenceRecordRepo.loadRemoteAdherenceRecords(studyId))

            // Load participant schedule
            val timeLineFlow = timelineRepo.getSessionsForDay(studyId, Clock.System.now())
            val sliceResult = timeLineFlow.filter { it is ResourceResult.Success }.first()
            val slice = (sliceResult as ResourceResult.Success).data
            assertEquals(TimeZone.currentSystemDefault(), slice.timezone)

            authRepo.signOut()

        }
    }


}
package org.sagebionetworks.bridge.kmm.shared.repo

import kotlinx.coroutines.MainScope
import kotlinx.datetime.Clock
import kotlinx.serialization.encodeToString
import kotlinx.serialization.json.Json
import kotlinx.serialization.json.JsonPrimitive
import org.sagebionetworks.bridge.kmm.shared.*
import org.sagebionetworks.bridge.kmm.shared.cache.Resource
import org.sagebionetworks.bridge.kmm.shared.cache.ResourceDatabaseHelper
import org.sagebionetworks.bridge.kmm.shared.cache.ResourceStatus
import org.sagebionetworks.bridge.kmm.shared.cache.ResourceType
import org.sagebionetworks.bridge.kmm.shared.models.UserSessionInfo
import kotlin.test.Test
import kotlin.test.assertEquals
import kotlin.test.assertNotNull
import kotlin.test.assertNull

class ParticipantRepoTest : BaseTest() {

    val userSessionInfo = UserSessionInfo(
        id = "uniqueId",
        authenticated = true,
        studyIds = listOf("testStudyId"),
        sessionToken = "testSessionToken",
        reauthToken = "testReauthToken"
    )

    @Test
    fun testUpdateParticipant() {
        runTest {
            val db = ResourceDatabaseHelper(testDatabaseDriver())
            // Setup database with a cached UserSessionInfo object
            val resource = Resource(
                identifier = AuthenticationRepository.USER_SESSION_ID,
                secondaryId = ResourceDatabaseHelper.DEFAULT_SECONDARY_ID,
                type = ResourceType.USER_SESSION_INFO,
                studyId = ResourceDatabaseHelper.APP_WIDE_STUDY_ID,
                json = Json.encodeToString(userSessionInfo),
                lastUpdate = Clock.System.now().toEpochMilliseconds(),
                status = ResourceStatus.SUCCESS,
                needSave = false
            )
            db.insertUpdateResource(resource)
            val bridgeConfig = TestBridgeConfig()
            val testConfig = TestHttpClientConfig(bridgeConfig = bridgeConfig, db = db)
            val authRepo = AuthenticationRepository(getTestClient("", config = testConfig.copy(authProvider = null)), bridgeConfig,  db, MainScope(), TestEncryptedSharedSettings())
            val participantRepo = ParticipantRepo(getTestClient("", config = testConfig), db, MainScope(), authRepo)
            val session = authRepo.session()
            assertNotNull(session)
            assertNull(session.clientData)
            // Add client data
            val updateParticipantRecord = ParticipantRepo.UpdateParticipantRecord.getUpdateParticipantRecord(session)
            val clientData = JsonPrimitive("Test")
            updateParticipantRecord.clientData = clientData
            participantRepo.updateParticipant(updateParticipantRecord)
            // Verify the client data is saved to the session
            val updatedSession = authRepo.session()
            assertEquals(clientData, updatedSession?.clientData)
            assertEquals("testSessionToken", updatedSession?.sessionToken)
        }
    }
}

class TestBridgeConfig: BridgeConfig {
    override val appId: String
        get() = "bridge-client-kmm-test"
    override val appName: String
        get() = "BridgeClientKMM Tests"
    override val sdkVersion: Int
        get() = 1
    override val appVersion: Int
        get() = 1
    override val appVersionName: String
        get() = "Unit Tests"
    override val bridgeEnvironment: PlatformConfig.BridgeEnvironment
        get() = PlatformConfig.BridgeEnvironment.PRODUCTION
    override val osName: String
        get() = "Test"
    override val osVersion: String
        get() = "Test"
    override val deviceName: String
        get() = "Test"
    override var cacheCredentials: Boolean = false


}
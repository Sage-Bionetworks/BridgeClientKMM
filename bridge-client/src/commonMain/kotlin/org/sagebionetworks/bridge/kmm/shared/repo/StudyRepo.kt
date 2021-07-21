package org.sagebionetworks.bridge.kmm.shared.repo

import co.touchlab.stately.ensureNeverFrozen
import io.ktor.client.*
import kotlinx.coroutines.CoroutineScope
import kotlinx.coroutines.flow.Flow
import kotlinx.serialization.encodeToString
import kotlinx.serialization.json.Json
import org.sagebionetworks.bridge.kmm.shared.BridgeConfig
import org.sagebionetworks.bridge.kmm.shared.apis.StudyApi
import org.sagebionetworks.bridge.kmm.shared.cache.ResourceDatabaseHelper
import org.sagebionetworks.bridge.kmm.shared.cache.ResourceResult
import org.sagebionetworks.bridge.kmm.shared.cache.ResourceStatus
import org.sagebionetworks.bridge.kmm.shared.cache.ResourceType
import org.sagebionetworks.bridge.kmm.shared.models.Study
import org.sagebionetworks.bridge.kmm.shared.models.StudyInfo

class StudyRepo(internal val bridgeConfig: BridgeConfig, httpClient: HttpClient, databaseHelper: ResourceDatabaseHelper, backgroundScope: CoroutineScope) :
    AbstractResourceRepo(databaseHelper, backgroundScope) {

    init {
        ensureNeverFrozen()
    }


    internal var studyApi = StudyApi(
        httpClient = httpClient
    )

    /**
     * Get the information on a study that is useful for displaying, selecting, and signing into the study.
     * This call does not require authentication.
     *
     * @param studyId Study identifier
     * @return StudyInfo
     */
    suspend fun getStudyInfo(studyId: String): ResourceResult<StudyInfo> {
        return try {
            val studyInfo = studyApi.getStudyInfo(bridgeConfig.appId, studyId)
            ResourceResult.Success(studyInfo, ResourceStatus.SUCCESS)
        } catch (err: Throwable) {
            println(err)
            ResourceResult.Failed(ResourceStatus.FAILED)
        }
    }

    /**
     * Get a study for this app.
     * @param studyId Study identifier
     * @return Study
     */
    fun getStudy(studyId: String): Flow<ResourceResult<Study>> {
        return getResourceById(studyId, resourceType = ResourceType.STUDY, remoteLoad =  { loadRemoteStudy(studyId) },
            studyId = studyId
        )
    }

    private suspend fun loadRemoteStudyInfo(studyId: String) : String {
        return Json.encodeToString(studyApi.getStudyInfo(bridgeConfig.appId, studyId))
    }

    private suspend fun loadRemoteStudy(studyId: String) : String {
        return Json.encodeToString(studyApi.getStudy(studyId))
    }

}
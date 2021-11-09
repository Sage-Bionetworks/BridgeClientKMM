package org.sagebionetworks.bridge.kmm.shared.repo

import co.touchlab.stately.ensureNeverFrozen
import io.ktor.client.*
import io.ktor.client.features.*
import io.ktor.http.*
import io.ktor.util.network.*
import kotlinx.coroutines.CoroutineScope
import kotlinx.coroutines.flow.Flow
import kotlinx.coroutines.flow.mapNotNull
import kotlinx.coroutines.launch
import kotlinx.datetime.Clock
import kotlinx.serialization.encodeToString
import kotlinx.serialization.json.Json
import org.sagebionetworks.bridge.kmm.shared.apis.SchedulesV2Api
import org.sagebionetworks.bridge.kmm.shared.cache.*
import org.sagebionetworks.bridge.kmm.shared.models.AdherenceRecord
import org.sagebionetworks.bridge.kmm.shared.models.AdherenceRecordList
import org.sagebionetworks.bridge.kmm.shared.models.AdherenceRecordsSearch
import org.sagebionetworks.bridge.kmm.shared.models.SortOrder

class AdherenceRecordRepo(httpClient: HttpClient, databaseHelper: ResourceDatabaseHelper, backgroundScope: CoroutineScope) :
        AbstractResourceRepo(databaseHelper, backgroundScope) {

    init {
        ensureNeverFrozen()
    }


    internal var scheduleV2Api = SchedulesV2Api(
        httpClient = httpClient
    )

    /**
     * Get all of the locally cached [AdherenceRecord]s.
     */
    fun getAllCachedAdherenceRecords(studyId: String) : Flow<Map<String, List<AdherenceRecord>>> {
        return database.getResourcesAsFlow(ResourceType.ADHERENCE_RECORD, studyId).mapNotNull { it.mapNotNull { resource -> resource.loadResource<AdherenceRecord>() }.groupBy { adherenceRecord -> adherenceRecord.instanceGuid } }
    }

    /**
     * Get the locally cached [AdherenceRecord]s for the specified [instanceIds].
     */
    fun getCachedAdherenceRecords(instanceIds: List<String>, studyId: String) : Map<String, List<AdherenceRecord>> {
        val list: List<AdherenceRecord> = database.getResourcesByIds(instanceIds, ResourceType.ADHERENCE_RECORD, studyId).mapNotNull { it.loadResource() }
        return list.groupBy { it.instanceGuid }
    }

    /**
     * Download and cache locally all [AdherenceRecord]s for the given study.
     * For now this only requests records using the current timestamps.
     */
    suspend fun loadRemoteAdherenceRecords(studyId: String) : Boolean {
        val pageSize = 500
        var pageOffset = 0
        var adherenceRecordsSearch = AdherenceRecordsSearch(sortOrder = SortOrder.DESC, pageSize = pageSize, includeRepeats = true, currentTimestampsOnly = true)
        try {
            do {
                val curPageSize = pageSize
                val recordResult = loadAndCacheResults(studyId, adherenceRecordsSearch)
                pageOffset+= pageSize
                adherenceRecordsSearch = adherenceRecordsSearch.copy(offsetBy = pageOffset)
            } while (curPageSize + pageSize < recordResult.total)
        } catch (throwable: Throwable) {
            println(throwable)
            return false
        }
        return true
    }

    private suspend fun loadAndCacheResults(studyId: String, adherenceRecordsSearch: AdherenceRecordsSearch) : AdherenceRecordList {
        val recordsResult = scheduleV2Api.searchForAdherenceRecords(studyId, adherenceRecordsSearch)
        for (record in recordsResult.items) {
            insertUpdate(record, studyId)
        }
        return recordsResult
    }

    private fun insertUpdate(adherenceRecord: AdherenceRecord, studyId: String) {
        val json = Json.encodeToString(adherenceRecord)
        val resource = Resource(
            identifier = adherenceRecord.instanceGuid,
            secondaryId = adherenceRecord.startedOn.toString(),
            type = ResourceType.ADHERENCE_RECORD,
            studyId = studyId,
            json = json,
            lastUpdate = Clock.System.now().toEpochMilliseconds(),
            status = ResourceStatus.SUCCESS,
            needSave = true)
        database.insertUpdateResource(resource)
    }

    /**
     * Update the local cache with the specified [AdherenceRecord] and trigger a background call
     * to save to Bridge server.
     */
    fun createUpdateAdherenceRecord(adherenceRecord: AdherenceRecord, studyId: String) {
        insertUpdate(adherenceRecord, studyId)
        backgroundScope.launch {
            processUpdates(studyId)
        }

    }

    /**
     * Save any locally cached [AdherenceRecord]s that haven't been uploaded to Bridge server.
     * Any failures will remain in a needSave state and be tried again the next time.
     */
    private suspend fun processUpdates(studyId: String) {
        val resourcesToUpload = database.getResourcesNeedSave(ResourceType.ADHERENCE_RECORD, studyId)
        val records: List<AdherenceRecord> = resourcesToUpload.mapNotNull { it.loadResource() }
        if (records.isEmpty()) return
        var status = ResourceStatus.FAILED
        var needSave = true
        try {
            scheduleV2Api.updateAdherenceRecords(studyId, records)
            status = ResourceStatus.SUCCESS
            needSave = false
        } catch (throwable: Throwable) {
            println(throwable)
            when (throwable) {
                is ResponseException -> {
                    when (throwable.response.status) {
                        HttpStatusCode.Unauthorized -> {
                            // 401 unauthorized
                            // User hasn't authenticated or re-auth has failed.
                        }
                        HttpStatusCode.Gone -> {
                            //410 Gone
                            // The version of the client making the request no longer has access to this service.
                            // The user must update their app in order to continue using Bridge.
                        }
                        HttpStatusCode.PreconditionFailed -> {
                            //412 Not consented
                        }
                    }
                }

                is UnresolvedAddressException -> {
                    //Internet connection error
                    status = ResourceStatus.RETRY
                }
            }
        }
        for (resource in resourcesToUpload) {
            val toUpdate = resource.copy(status = status, needSave = needSave)
            database.insertUpdateResource(toUpdate)
        }

    }

    }
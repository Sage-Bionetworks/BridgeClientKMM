package org.sagebionetworks.bridge.kmm.shared.repo

import co.touchlab.kermit.Logger
import co.touchlab.stately.ensureNeverFrozen
import io.ktor.client.*
import io.ktor.client.plugins.*
import io.ktor.http.*
import io.ktor.util.network.*
import kotlinx.coroutines.*
import kotlinx.coroutines.channels.Channel
import kotlinx.coroutines.flow.Flow
import kotlinx.coroutines.flow.MutableStateFlow
import kotlinx.coroutines.flow.collect
import kotlinx.coroutines.flow.flow
import kotlinx.datetime.Clock
import kotlinx.datetime.Instant
import kotlinx.datetime.LocalDate
import kotlinx.serialization.encodeToString
import kotlinx.serialization.json.Json
import kotlinx.serialization.json.JsonObject
import org.sagebionetworks.bridge.kmm.shared.apis.ParticipantApi
import org.sagebionetworks.bridge.kmm.shared.cache.*
import org.sagebionetworks.bridge.kmm.shared.models.ForwardCursorReportDataList
import org.sagebionetworks.bridge.kmm.shared.models.ReportData

class ParticipantReportRepo(httpClient: HttpClient,
                            databaseHelper: ResourceDatabaseHelper,
                            backgroundScope: CoroutineScope) :
        AbstractResourceRepo(databaseHelper, backgroundScope) {

    init {
        ensureNeverFrozen()
    }

    private var participantApi = ParticipantApi(
        httpClient = httpClient
    )

    private var processUpdatesJob : Job? = null

    private val updatesFlow: MutableStateFlow<Pair<String?, Instant?>> = MutableStateFlow(Pair(null, null))



    /**
     * Get all cached reports associated with the given identifier
     */
    fun getCachedReports(studyId: String, identifier: String) : List<Report> {
        return database.getResourcesById(
            studyId = studyId,
            id = identifier,
            type = ResourceType.PARTICIPANT_REPORT
        ).mapNotNull { it.loadResource<ReportData>()?.toReport() }
    }

    /**
     * Download and cache locally all [Report]s for the given study, identifier and within the time range.
     */
    suspend fun loadRemoteReports(studyId: String, identifier: String, startTime: Instant, endTime: Instant) : Boolean {
        try {
            var offsetKey: String? = null
            do {
                val recordResult = loadAndCacheResults(studyId, identifier, startTime, endTime, offsetKey, null)
                offsetKey = recordResult.nextPageOffsetKey
            } while (recordResult.hasNext)
        } catch (throwable: Throwable) {
            Logger.e("Error loading remote participant reports", throwable)
            return false
        }
        return true
    }

    private suspend fun loadAndCacheResults(studyId: String, identifier: String, startTime: Instant, endTime: Instant, offsetKey: String?, pageSize: Int?) : ForwardCursorReportDataList {
        val results = participantApi.getUsersStudyParticipantReport(studyId, identifier, startTime, endTime, offsetKey, pageSize)
        for (record in results.items) {
            insertUpdate(studyId, identifier, record, false)
        }
        return results
    }


    /**
     * Update the local cache with the specified [Report] and trigger a background call
     * to save to Bridge server.
     */
    fun createUpdateReport(report: Report, studyId: String, identifier: String) {
        insertUpdate(studyId, identifier, report.toReportData(), true)
        runProcessLocalUpdates(studyId)
    }

    private fun runProcessLocalUpdates(studyId: String) {
        if (processUpdatesJob == null) {
            processUpdatesJob = backgroundScope.launch {
                updatesFlow.collect { pair ->
                    pair.first?.let {
                        processUpdates(it)
                    }
                }
            }
        }
        updatesFlow.value = Pair(studyId, Clock.System.now())
    }

    private fun insertUpdate(studyId: String, identifier: String, reportData: ReportData, needSave: Boolean) {
        val json = Json.encodeToString(reportData)
        val resource = Resource(
            identifier = identifier,
            secondaryId = reportData.date,
            type = ResourceType.PARTICIPANT_REPORT,
            studyId = studyId,
            json = json,
            lastUpdate = Clock.System.now().toEpochMilliseconds(),
            status = ResourceStatus.SUCCESS,
            needSave = needSave)
        database.insertUpdateResource(resource)
    }

    /**
     * Save any locally cached [ReportData]s that haven't been uploaded to Bridge server.
     * Any failures will remain in a needSave state and be tried again the next time.
     */
    private suspend fun processUpdates(studyId: String) {
        val resourcesToUpload = database.getResourcesNeedSave(ResourceType.PARTICIPANT_REPORT, studyId)
        if (resourcesToUpload.isEmpty()) return
        for (resource in resourcesToUpload) {
            processUpdates(studyId, resource)
        }
    }

    private suspend fun processUpdates(studyId: String, resourceToUpload: Resource) {
        val reportData = resourceToUpload.loadResource<ReportData>()
        if (reportData == null) return
        var status = ResourceStatus.FAILED
        var needSave = true
        try {
            participantApi.saveUsersStudyParticipantReportRecord(studyId, resourceToUpload.identifier, reportData)
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
        val toUpdate = resourceToUpload.copy(status = status, needSave = needSave)
        database.insertUpdateResource(toUpdate)
    }

}


/**
 * Client side version of participant [ReportData].
 */
data class Report internal constructor(

    /* An arbitrary JSON object containing whatever data should be saved for a report. */
    var data: JsonObject,
    /* The date (whether local or an ISO timestamp) of the report data. */
    val date: String,
    /* The date expressed as an ISO 8601 timestamp. */
    val dateTime: Instant?,
    /* The date expressed as a LocalDate (YYYY-MM-DD) */
    val localDate: LocalDate?,
    /* The studies this report record is associated to (these are set with the first record that is submitted and that creates a report index, and cannot be changed afterward unless the user is a study-wide user not associated to any specific study. */
    val studyIds: List<String>?,

) {

    /**
     * Construct a report that will be stored based on a timeStamp [Instant]. The timeStamp will be truncated to seconds before storing.
     */
    constructor(data: JsonObject, timeStamp: Instant, studyId: String) : this(
        data,
        Instant.fromEpochSeconds(timeStamp.epochSeconds, 0).toString(),
        Instant.fromEpochSeconds(timeStamp.epochSeconds, 0),
        null,
        listOf(studyId)
    )

    /**
     * Construct a report that will be stored based on a [LocalDate]
     */
    constructor(data: JsonObject, localDate: LocalDate, studyId: String) : this(
        data,
        localDate.toString(),
        null,
        localDate,
        listOf(studyId)
    )

}

internal fun Report.toReportData() : ReportData {
    return ReportData(
        data = data,
        date = date,
        studyIds = studyIds
    )
}

internal fun ReportData.toReport() : Report {
    return Report(
        data = data,
        date = date,
        dateTime = dateTime,
        localDate = localDate,
        studyIds = studyIds

    )
}
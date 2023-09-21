package org.sagebionetworks.bridge.kmm.shared.managers

import kotlinx.coroutines.MainScope
import kotlinx.coroutines.launch
import kotlinx.datetime.toKotlinInstant
import kotlinx.datetime.toNSDate
import kotlinx.serialization.json.JsonElement
import kotlinx.serialization.json.jsonObject
import org.koin.core.component.KoinComponent
import org.koin.core.component.inject
import org.sagebionetworks.bridge.kmm.shared.repo.ParticipantReportRepo
import org.sagebionetworks.bridge.kmm.shared.repo.Report
import platform.Foundation.NSDate

class NativeReportManager (
    private val studyId: String
) : KoinComponent {

    private val reportRepo : ParticipantReportRepo by inject(mode = LazyThreadSafetyMode.NONE)

    private val scope = MainScope()

    fun fetchReports(identifier: String, startDateTime: NSDate, endDateTime: NSDate, callBack: (List<NativeParticipantDataRecord>) -> Unit) {
        _fetchReports(identifier, startDateTime, endDateTime, true, callBack)
    }

    fun fetchCachedReports(identifier: String, startDateTime: NSDate, endDateTime: NSDate, callBack: (List<NativeParticipantDataRecord>) -> Unit) {
        _fetchReports(identifier, startDateTime, endDateTime, false, callBack)
    }

    private fun _fetchReports(identifier: String, startDateTime: NSDate, endDateTime: NSDate, loadFromServer: Boolean, callBack: (List<NativeParticipantDataRecord>) -> Unit) {
        scope.launch {
            val lowerBound = startDateTime.toKotlinInstant()
            val upperBound = endDateTime.toKotlinInstant()
            if (loadFromServer) {
                reportRepo.loadRemoteReports(
                    studyId,
                    identifier,
                    startTime = lowerBound,
                    endTime = upperBound
                )
            }
            val records = reportRepo.getCachedReports(studyId, identifier).mapNotNull { report ->
                report.dateTime?.let {
                   if (lowerBound <= it && it < upperBound) NativeParticipantDataRecord(identifier, it.toNSDate(), report.data) else null
                }
            }
            callBack(records)
        }
    }

    @Throws(Throwable::class)
    fun updateInsert(report: NativeParticipantDataRecord) {
        try {
            val uploadReport = Report(report.data.jsonObject, report.dateTime.toKotlinInstant(), studyId)
            reportRepo.createUpdateReport(uploadReport, studyId, report.identifier)
        } catch (err: Exception) {
            throw Throwable(err.message)
        }
    }

    @Throws(Throwable::class)
    fun updateInsert(reports: List<NativeParticipantDataRecord>, identifier: String) {
        try {
            val uploadReports = reports.map {
                Report(it.data.jsonObject, it.dateTime.toKotlinInstant(), studyId)
            }
            reportRepo.createUpdateReports(uploadReports, studyId, identifier)
        } catch (err: Exception) {
            throw Throwable(err.message)
        }
    }
}

data class NativeParticipantDataRecord(
    val identifier: String,
    val dateTime: NSDate,
    val data: JsonElement,
)


package org.sagebionetworks.bridge.kmm.shared

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
        scope.launch {
            reportRepo.loadRemoteReports(studyId, identifier, startTime = startDateTime.toKotlinInstant(), endTime = endDateTime.toKotlinInstant())
            val records = reportRepo.getCachedReports(studyId, identifier).mapNotNull { report ->
                report.dateTime?.let { NativeParticipantDataRecord(identifier, it.toNSDate(), report.data) }
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
}

data class NativeParticipantDataRecord(
    val identifier: String,
    val dateTime: NSDate,
    val data: JsonElement,
)


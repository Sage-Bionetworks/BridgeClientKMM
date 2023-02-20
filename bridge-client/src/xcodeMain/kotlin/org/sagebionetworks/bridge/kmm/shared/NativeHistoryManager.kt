package org.sagebionetworks.bridge.kmm.shared

import kotlinx.coroutines.MainScope
import kotlinx.coroutines.cancel
import kotlinx.coroutines.flow.collect
import kotlinx.coroutines.flow.collectLatest
import kotlinx.coroutines.launch
import org.koin.core.component.KoinComponent
import org.koin.core.component.inject
import org.sagebionetworks.bridge.kmm.shared.cache.*
import org.sagebionetworks.bridge.kmm.shared.repo.*

class NativeHistoryManager(
    private val studyId: String,
    private val viewUpdate: (List<AssessmentHistoryRecord>) -> Unit
) : KoinComponent {

    private val repo : ScheduleTimelineRepo by inject(mode = LazyThreadSafetyMode.NONE)

    private val scope = MainScope()

    fun observeHistory() {
        scope.launch {
            repo.adherenceRecordRepo.getAllCompletedCachedAssessmentAdherence(studyId).collect { historyList ->
                viewUpdate(historyList)
            }
        }
    }

    fun observeAllAdherence(callBack: (List<NativeAdherenceRecord>) -> Unit) {
        scope.launch {
            repo.adherenceRecordRepo.getAllCachedAdherenceRecords(studyId).collect { all ->
                callBack(
                    all.values.flatten().map { it.toNative() }
                )
            }
        }
    }

    @Throws(Throwable::class)
    fun onCleared() {
        try {
            scope.cancel()
        } catch (err: Exception) {
            throw Throwable(err.message)
        }
    }
}


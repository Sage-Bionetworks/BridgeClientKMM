package org.sagebionetworks.bridge.kmm.shared

import kotlinx.coroutines.MainScope
import kotlinx.coroutines.cancel
import kotlinx.coroutines.flow.collect
import kotlinx.coroutines.launch
import kotlinx.datetime.*
import kotlinx.serialization.json.JsonElement
import org.koin.core.component.KoinComponent
import org.koin.core.component.inject
import org.sagebionetworks.bridge.kmm.shared.cache.*
import org.sagebionetworks.bridge.kmm.shared.models.AdherenceRecord
import org.sagebionetworks.bridge.kmm.shared.models.AssessmentInfo
import org.sagebionetworks.bridge.kmm.shared.models.NotificationMessage
import org.sagebionetworks.bridge.kmm.shared.models.SessionInfo
import org.sagebionetworks.bridge.kmm.shared.repo.*
import platform.Foundation.*

class NativeHistoryManager(
    private val studyId: String,
    private val viewUpdate: (NativeScheduledSessionTimelineSlice) -> Unit
) : KoinComponent {

    private val repo : ScheduleTimelineRepo by inject(mode = LazyThreadSafetyMode.NONE)

    private val scope = MainScope()

    fun observeHistory() {
        scope.launch {
            repo.getPastSessions(studyId).collect { timelineResource ->
                (timelineResource as? ResourceResult.Success)?.data?.let { timelineSlice ->
                    viewUpdate(timelineSlice.toNaive())
                }
            }
        }
    }

    fun onCleared() {
        scope.cancel()
    }
}


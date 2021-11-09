package org.sagebionetworks.bridge.kmm.shared

import kotlinx.coroutines.MainScope
import kotlinx.coroutines.cancel
import kotlinx.coroutines.flow.collect
import kotlinx.coroutines.launch
import org.koin.core.component.KoinComponent
import org.koin.core.component.inject
import org.sagebionetworks.bridge.kmm.shared.cache.ResourceResult
import org.sagebionetworks.bridge.kmm.shared.cache.ResourceStatus
import org.sagebionetworks.bridge.kmm.shared.models.Study
import org.sagebionetworks.bridge.kmm.shared.models.StudyInfo
import org.sagebionetworks.bridge.kmm.shared.repo.StudyRepo

class NativeStudyInfoManager : KoinComponent {

    private val repo : StudyRepo by inject(mode = LazyThreadSafetyMode.NONE)

    private val scope = MainScope()

    fun fetchStudyInfo(studyId: String, callBack: (StudyInfo?, ResourceStatus) -> Unit) {
        scope.launch {
            when(val resource = repo.getStudyInfo(studyId)) {
                is ResourceResult.Success -> callBack(resource.data, resource.status)
                is ResourceResult.Failed -> callBack(null, resource.status)
            }
        }
    }
}

class NativeStudyManager(
    private val studyId: String,
    private val viewUpdate: (Study) -> Unit
) : KoinComponent {

    private val repo : StudyRepo by inject(mode = LazyThreadSafetyMode.NONE)

    private val scope = MainScope()

    fun observeStudy() {
        scope.launch {
            repo.getStudy(studyId).collect { resource ->
                (resource as? ResourceResult.Success)?.data?.let { result ->
                    viewUpdate(result)
                }
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


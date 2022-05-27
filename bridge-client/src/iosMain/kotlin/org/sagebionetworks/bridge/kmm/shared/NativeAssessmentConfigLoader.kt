package org.sagebionetworks.bridge.kmm.shared

import kotlinx.coroutines.MainScope
import kotlinx.coroutines.flow.collectLatest
import kotlinx.coroutines.launch
import org.koin.core.component.KoinComponent
import org.koin.core.component.inject
import org.sagebionetworks.bridge.kmm.shared.cache.ResourceResult
import org.sagebionetworks.bridge.kmm.shared.models.AssessmentInfo
import org.sagebionetworks.bridge.kmm.shared.repo.AssessmentConfigRepo
import platform.Foundation.NSData

class NativeAssessmentConfigLoader : KoinComponent {

    private val repo : AssessmentConfigRepo by inject(mode = LazyThreadSafetyMode.NONE)

    private val scope = MainScope()

    fun fetchAssessmentConfig(instanceGuid: String, assessmentInfo: AssessmentInfo, callBack: (NativeAssessmentConfig) -> Unit) {
        scope.launch {
            repo.getAssessmentConfig(assessmentInfo).collectLatest { resource ->
                callBack(
                    NativeAssessmentConfig(
                        instanceGuid = instanceGuid,
                        identifier = assessmentInfo.identifier,
                        config = (resource as? ResourceResult.Success)?.data?.config.toString()?.toNSData(),
                        restoredResult = null   // TODO: syoung 05/24/2022 Figure out how to get the cached result.
                    )
                )
            }
        }
    }
}

data class NativeAssessmentConfig(
    val instanceGuid: String,
    val identifier: String,
    val config: NSData?,
    val restoredResult: NSData?
)


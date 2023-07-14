package org.sagebionetworks.bridge.kmm.shared.upload

import kotlinx.coroutines.MainScope
import org.koin.core.component.KoinComponent
import org.koin.core.component.inject
import org.sagebionetworks.bridge.kmm.shared.cache.*
import org.sagebionetworks.bridge.kmm.shared.models.*
import org.sagebionetworks.bridge.kmm.shared.repo.*

class NativeUploadManager(
    private val studyId: String,
    private val viewUpdate: (UploadState) -> Unit
) : KoinComponent {

    private val repo : UploadRepo by inject(mode = LazyThreadSafetyMode.NONE)

    private val scope = MainScope()


}

data class UploadState(
    val s3Uploads: List<UploadSession>,
    val hasInFlightUploads: Boolean
)
package org.sagebionetworks.bridge.kmm.shared.upload

import co.touchlab.kermit.Logger
import kotlinx.coroutines.CoroutineScope
import kotlinx.coroutines.Dispatchers
import kotlinx.coroutines.IO
import kotlinx.coroutines.Job
import kotlinx.coroutines.MainScope
import kotlinx.coroutines.launch
import org.koin.core.component.KoinComponent
import org.koin.core.component.inject
import org.sagebionetworks.bridge.kmm.shared.cache.ResourceDatabaseHelper
import org.sagebionetworks.bridge.kmm.shared.cache.ResourceStatus
import org.sagebionetworks.bridge.kmm.shared.cache.ResourceType
import org.sagebionetworks.bridge.kmm.shared.cache.loadResource
import org.sagebionetworks.bridge.kmm.shared.models.UploadFile
import org.sagebionetworks.bridge.kmm.shared.models.UploadFileIdentifiable
import org.sagebionetworks.bridge.kmm.shared.models.UploadSession
import org.sagebionetworks.bridge.kmm.shared.models.UserSessionInfo
import org.sagebionetworks.bridge.kmm.shared.repo.*
import platform.Foundation.NSError

open class NativeUploadManager(
    private val studyId: String,
    private val updatePendingUploadCount: (Long) -> Unit
) : KoinComponent {

    private val repo : UploadRepo by inject(mode = LazyThreadSafetyMode.NONE)

    private val scope = MainScope()

    private var pendingCountJob: Job? = null

    fun observePendingUploadCount() {
        runCatching { pendingCountJob?.cancel() }
        pendingCountJob = scope.launch {
            repo.database.getPendingUploadCountAsFlow().collect {
                updatePendingUploadCount(it)
            }
        }
    }

    fun storeUploadFile(uploadFile: UploadFile) {
        repo.database.storeUploadFile(uploadFile)
    }

    fun getUploadFiles(): List<UploadFile> {
        return repo.getUploadFiles()
    }

    fun requestUploadSession(uploadFile: UploadFile, callBack: (UploadFile, UploadSession?) -> Unit) {
        scope.launch {
            try {
                val uploadSession = repo.getUploadSession(uploadFile)
                callBack(uploadFile, uploadSession)
            } catch (_: Throwable) {
                callBack(uploadFile, null)
            }
        }
    }

    fun markUploadFileFinished(filePath: String) {
        repo.markUploadFileFinished(UploadFileId(filePath))
    }

    fun processFinishedUploads(callBack: (Boolean) -> Unit) {
        scope.launch {
            try {
                repo.processFinishedUploads()
                callBack(true)
            } catch (_: Throwable) {
                callBack(false)
            }
        }
    }

    internal class UploadFileId(override val filePath: String) : UploadFileIdentifiable
}


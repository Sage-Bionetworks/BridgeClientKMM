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
import org.sagebionetworks.bridge.kmm.shared.models.S3UploadSession
import org.sagebionetworks.bridge.kmm.shared.models.UploadFile
import org.sagebionetworks.bridge.kmm.shared.models.UploadFileId
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
    private val adherenceRecordRepo : AdherenceRecordRepo by inject(mode = LazyThreadSafetyMode.NONE)

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

    fun queueAndRequestUploadSession(uploadFile: UploadFile, callBack: (S3UploadSession?) -> Unit) {
        scope.launch {
            repo.database.storeUploadFile(uploadFile)
            try {
                val uploadSession = repo.getS3UploadSession(uploadFile)
                callBack(uploadSession)
            } catch (_: Throwable) {
                callBack(null)
            }
        }
    }

    fun getUploadFiles(): List<String> {
        return repo.getUploadFiles().map { it.filePath }
    }

    fun requestUploadSession(filePath: String, callBack: (S3UploadSession?) -> Unit) {
        scope.launch {
            try {
                val uploadSession = repo.getS3UploadSessionForFile(filePath)
                callBack(uploadSession)
            } catch (_: Throwable) {
                callBack(null)
            }
        }
    }

    fun markUploadFileFinished(filePath: String, callBack: (Boolean) -> Unit) {
        markAndProcessFinishedUploads(filePath, callBack)
    }

    fun processFinishedUploads(callBack: (Boolean) -> Unit) {
        markAndProcessFinishedUploads(null, callBack)
    }

    private fun markAndProcessFinishedUploads(filePath: String? = null, callBack: (Boolean) -> Unit) {
        scope.launch {
            if (filePath != null) {
                repo.markUploadFileFinished(UploadFileId(filePath))
            }
            try {
                repo.processFinishedUploads()
                adherenceRecordRepo.processAdherenceRecordUpdates(studyId)
                callBack(true)
            } catch (_: Throwable) {
                callBack(false)
            }
        }
    }

}


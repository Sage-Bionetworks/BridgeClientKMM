package org.sagebionetworks.bridge.kmm.shared.managers

import kotlinx.coroutines.CoroutineScope
import kotlinx.coroutines.Dispatchers
import kotlinx.coroutines.IO
import kotlinx.coroutines.Job
import kotlinx.coroutines.MainScope
import kotlinx.coroutines.launch
import org.koin.core.component.KoinComponent
import org.koin.core.component.inject
import org.sagebionetworks.bridge.kmm.shared.models.S3UploadSession
import org.sagebionetworks.bridge.kmm.shared.models.UploadFile
import org.sagebionetworks.bridge.kmm.shared.models.UploadFileId
import org.sagebionetworks.bridge.kmm.shared.models.getUploadFileResourceId
import org.sagebionetworks.bridge.kmm.shared.repo.*

class NativeUploadManager : KoinComponent {

    private val repo : UploadRepo by inject(mode = LazyThreadSafetyMode.NONE)
    private val adherenceRecordRepo : AdherenceRecordRepo by inject(mode = LazyThreadSafetyMode.NONE)
    private val authManager : AuthenticationRepository by inject(mode = LazyThreadSafetyMode.NONE)
    private val scope = CoroutineScope(Dispatchers.IO)  // TODO: syoung 08/24/2023 Decide if this should be main scope?

    fun queueAndRequestUploadSession(uploadFile: UploadFile, callBack: (S3UploadSession?) -> Unit) {
        scope.launch {
            try {
                val uploadSession = repo.queueAndRequestUploadSession(uploadFile)
                callBack(uploadSession)
            } catch (_: Throwable) {
                callBack(null)
            }
        }
    }

    fun hasPendingUploads(): Boolean {
        return repo.database.getPendingUploadCount() > 0
    }

    fun getPendingUploadFiles(callBack: (List<PendingUploadFile>) -> Unit) {
        scope.launch {
            val ret = repo.getPendingUploadFiles()
            callBack(ret)
        }
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

    fun markUploadUnrecoverableFailure(filePath: String, callBack: () -> Unit) {
        scope.launch {
            repo.removeUploadFile(UploadFileId(filePath))
            callBack()
        }
    }

    fun markUploadFileFinished(filePath: String, callBack: (Boolean) -> Unit) {
        scope.launch {
            val uploadFile = UploadFileId(filePath)
            val uploadSession = repo.markUploadFileFinished(uploadFile)
            try {
                repo.completeUploadSession(uploadSession?.id, uploadFile.getUploadFileResourceId())
                callBack(true)
            } catch (_: Throwable) {
                callBack(false)
            }
        }
    }

    fun processFinishedUploads(callBack: (Boolean) -> Unit) {
        scope.launch {
            try {
                repo.processFinishedUploads()
                authManager.currentStudyId()?.let {
                    adherenceRecordRepo.processAdherenceRecordUpdates(it)
                }
                callBack(true)
            } catch (_: Throwable) {
                callBack(false)
            }
        }
    }

    fun hasMarkedFileAsUploaded(filePath: String): Boolean {
        return repo.getUploadedFileRecord(filePath) != null
    }
}

class PendingUploadObserver(
    private val updatePendingUploadCount: (Long) -> Unit
) : KoinComponent {

    private val repo: UploadRepo by inject(mode = LazyThreadSafetyMode.NONE)
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
}


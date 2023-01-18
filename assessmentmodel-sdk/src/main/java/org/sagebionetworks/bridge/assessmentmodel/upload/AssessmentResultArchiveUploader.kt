package org.sagebionetworks.bridge.assessmentmodel.upload

import android.content.Context
import android.content.Context.MODE_APPEND
import android.content.Context.MODE_PRIVATE
import android.content.res.AssetManager
import co.touchlab.kermit.Logger
import kotlinx.serialization.json.Json
import kotlinx.serialization.json.JsonElement
import kotlinx.serialization.json.JsonPrimitive
import okio.ByteString.Companion.toByteString
import org.sagebionetworks.assessmentmodel.AssessmentResult
import org.sagebionetworks.bridge.data.AndroidStudyUploadEncryptor
import org.sagebionetworks.bridge.data.Archive
import org.sagebionetworks.bridge.kmm.shared.upload.UploadFile
import org.sagebionetworks.bridge.kmm.shared.upload.UploadRequester
import org.spongycastle.cms.CMSException
import org.spongycastle.jcajce.provider.asymmetric.x509.CertificateFactory
import java.io.IOException
import java.security.DigestOutputStream
import java.security.MessageDigest
import java.security.NoSuchAlgorithmException
import java.security.cert.CertificateException
import java.security.cert.X509Certificate
import java.util.*
import org.sagebionetworks.bridge.kmm.shared.BridgeConfig as KmmBridgeConfig

class AssessmentResultArchiveUploader(
    val context: Context,
    val bridgeConfig: KmmBridgeConfig,
    val uploadRequester: UploadRequester) {

    val CONTENT_TYPE_DATA_ARCHIVE = "application/zip"

    val STUDY_PUBLIC_KEY = "study_public_key.pem"


    /**
     * Archive and queue the [assessmentResult] for upload using the specified [jsonCoder].
     * Specifying a [sessionWindowExpiration] will delay the upload until after that point in time.
     * Subsequent calls to this method with the same [assessmentInstanceId] will replace any delayed uploads.
     */
    fun archiveResultAndQueueUpload(assessmentResult: AssessmentResult,
                                    jsonCoder: Json,
                                    assessmentInstanceId: String,
                                    eventTimestamp: String,
                                    assessmentResultFilename: String = "assessmentResult.json",
                                    sessionWindowExpiration: kotlinx.datetime.Instant? = null) {

        val archiver = AssessmentArchiver(
            assessmentResult = assessmentResult,
            jsonCoder = jsonCoder,
            bridgeConfig = bridgeConfig,
            assessmentResultFilename = assessmentResultFilename
        )

        val assessmentRunUUID =  if (assessmentResult.runUUIDString.isEmpty()) {
            Logger.e("No runUUIDString in assessmentResult, created")
            UUID.randomUUID().toString()
        } else {
            assessmentResult.runUUIDString
        }

        val uploadMetadata: Map<String, JsonElement> = mapOf(
            "instanceGuid" to JsonPrimitive(assessmentInstanceId),
            "eventTimestamp" to JsonPrimitive(eventTimestamp)
        )


        val uploadFile = persist(assessmentRunUUID, archiver.buildArchive(), uploadMetadata, sessionWindowExpiration)
        Logger.i("UploadFile $uploadFile")
        uploadRequester.queueAndRequestUpload(context, uploadFile, assessmentInstanceId)
    }

    @Throws(
        IOException::class,
        CMSException::class,
        NoSuchAlgorithmException::class
    )
    fun persist(filename: String, archive: Archive, uploadMetadata: Map<String, JsonElement>, sessionWindowExpiration: kotlinx.datetime.Instant?): UploadFile {
        val encryptor = AndroidStudyUploadEncryptor(getPublicKey())

        val md5: MessageDigest = try {
            MessageDigest.getInstance("MD5")
        } catch (e: NoSuchAlgorithmException) {
            Logger.e("Unable to load md5", e)
            throw e
        }

        try {
            context.openFileOutput(filename, MODE_PRIVATE).use { os ->
                DigestOutputStream(os, md5).use { md5OutStream ->
                    encryptor.encrypt(md5OutStream).use { encryptedOutputStream ->
                        archive.writeTo(encryptedOutputStream)
                    }
                }
            }

            val size = context.openFileOutput(filename, MODE_APPEND).channel.size()

            val filePath = context.getFileStreamPath(filename).absolutePath

            val digest = md5.digest()
            val md5Hash = digest.toByteString().base64()

            return UploadFile(
                filePath = filePath,
                contentType = CONTENT_TYPE_DATA_ARCHIVE,
                fileLength = size,
                md5Hash = md5Hash,
                encrypted = true,
                metadata = uploadMetadata,
                sessionExpires = sessionWindowExpiration
            )

        } catch (e: CMSException) {
            Logger.e("Error encrypting archive", e)
            throw e
        }
    }

    @Throws(IOException::class, CertificateException::class)
    open fun getPublicKey(): X509Certificate? {
        try {
            context.assets.open(
                STUDY_PUBLIC_KEY,
                AssetManager.ACCESS_BUFFER
            ).use { publicKeyFile ->
                return CertificateFactory()
                    .engineGenerateCertificate(
                        publicKeyFile
                    ) as X509Certificate
            }
        } catch (e: IOException) {
            Logger.e("Could not load public key from /assets/study_public_key.pem", e)
            throw e
        }
    }

}
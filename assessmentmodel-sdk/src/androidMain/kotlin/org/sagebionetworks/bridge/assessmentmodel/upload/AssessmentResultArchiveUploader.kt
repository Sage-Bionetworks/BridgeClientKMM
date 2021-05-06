package org.sagebionetworks.bridge.assessmentmodel.upload

import android.content.Context
import android.content.Context.MODE_APPEND
import android.content.Context.MODE_PRIVATE
import android.content.res.AssetManager
import android.os.Build
import android.util.Log
import kotlinx.serialization.encodeToString
import kotlinx.serialization.json.Json
import org.joda.time.DateTime
import org.sagebionetworks.assessmentmodel.AssessmentResult
import org.sagebionetworks.bridge.data.AndroidStudyUploadEncryptor
import org.sagebionetworks.bridge.data.Archive
import org.sagebionetworks.bridge.data.ArchiveFile
import org.sagebionetworks.bridge.data.JsonArchiveFile
import org.sagebionetworks.bridge.kmm.shared.repo.AuthenticationRepository
import org.sagebionetworks.bridge.kmm.shared.upload.UploadFile
import org.sagebionetworks.bridge.kmm.shared.upload.UploadRequester
import org.spongycastle.cms.CMSException
import org.spongycastle.jcajce.provider.asymmetric.x509.CertificateFactory
import java.io.FileOutputStream
import java.io.IOException
import java.security.DigestOutputStream
import java.security.MessageDigest
import java.security.NoSuchAlgorithmException
import java.security.cert.CertificateException
import java.security.cert.X509Certificate
import java.util.*
import org.sagebionetworks.bridge.kmm.shared.BridgeConfig as KmmBridgeConfig

abstract class AssessmentResultArchiveUploader(
    val context: Context,
    val bridgeConfig: KmmBridgeConfig,
    val uploadRequester: UploadRequester,
    val authenticationRepository: AuthenticationRepository) {

    val CONTENT_TYPE_DATA_ARCHIVE = "application/zip"

    val STUDY_PUBLIC_KEY = "study_public_key.pem"

    // maybe we can pull from AppConfig? -liujoshua 04/02/2021
    abstract open fun getArchiveBuilderForActivity(assessmentResult: AssessmentResult): Archive.Builder

    fun archiveResultAndQueueUpload(assessmentResult: AssessmentResult, jsonCoder: Json) {
        if (assessmentResult.schemaIdentifier == null) {
            Log.w(
                "Archiver",
                "No schema found for assessment ${assessmentResult.assessmentIdentifier}"
            )
        }

        val appVersion = "version ${bridgeConfig.appVersionName}, build ${bridgeConfig.appVersion}"
        val builder = getArchiveBuilderForActivity(assessmentResult)
            .withAppVersionName(appVersion)
            .withPhoneInfo(bridgeConfig.deviceName)

        val metadataMap = getMetadataMap(assessmentResult, jsonCoder)

        // migrate once upload utils moved to use kotlinx/java8 time - liujoshua 04/02/2021
        val endDate = DateTime.parse(assessmentResult.endDateString!!.substringBefore("["))

        builder.addDataFile(
            JsonArchiveFile(
                "metadata.json",
                endDate,
                jsonCoder.encodeToString(metadataMap)
            )
        )

        for (archiveFile in toArchiveFiles(assessmentResult, jsonCoder)) {
            builder.addDataFile(archiveFile)
        }

        val uploadFile = persist(assessmentResult.runUUIDString, builder.build())
        Log.i("Archiver", "UploadFile $uploadFile")
        uploadRequester.queueAndRequestUpload(context, uploadFile)
    }

    @Throws(
        IOException::class,
        CMSException::class,
        NoSuchAlgorithmException::class
    )
    fun persist(filename: String, archive: Archive): UploadFile {
        val encryptor = AndroidStudyUploadEncryptor(getPublicKey())
        val fos: FileOutputStream

        val md5: MessageDigest = try {
            MessageDigest.getInstance("MD5")
        } catch (e: NoSuchAlgorithmException) {
            Log.e("Archiver", "Unable to load md5", e)
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
            val digestEnc = if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.O) {
                Base64.getEncoder().encodeToString(digest);
            } else {
                android.util.Base64.encodeToString(digest, android.util.Base64.DEFAULT);
            }

            return UploadFile(
                filePath,
                CONTENT_TYPE_DATA_ARCHIVE,
                size,
                digestEnc
            )

        } catch (e: CMSException) {
            Log.e("Archiver", "Error encrypting archive", e)
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
            Log.e(
                "Archiver", "Could not load public key from /assets/study_public_key.pem", e
            )
            throw e
        }
    }

    open fun getMetadataMap(
        assessmentResult: AssessmentResult,
        jsonCoder: Json
    ): MutableMap<String, String> {
        val appVersion = "version ${bridgeConfig.appVersionName}, build ${bridgeConfig.appVersion}"
        val os = "${bridgeConfig.osName}/${bridgeConfig.osVersion}"
        val session = authenticationRepository.session()
        val dataGroups =
            session?.dataGroups?.reduceIndexedOrNull { index, acc, s ->
                "$acc${if (index > 0) "," else ""}$s"
            } ?: ""

        // migrate once MTB is compatible with assessmentModels  0.4.3 - liujoshua 04/01/2021
        // val startDate =jsonCoder.encodeToString(assessmentResult.startDateTime)
        // val endDate = jsonCoder.encodeToString(assessmentResult.endDateTime)

        val endDate = DateTime.parse(assessmentResult.endDateString!!.substringBefore("["))
        val startDate = DateTime.parse(assessmentResult.startDateString!!.substringBefore("["))
            .withZone(endDate.zone)

        // add Android equivalent of rsdFrameworkVersion - liujoshua 04/01/2021
        return mutableMapOf(
            "taskIdentifier" to assessmentResult.identifier,
            "deviceInfo" to "${Build.PRODUCT} ${Build.MODEL}; $os",
            "appVersion" to appVersion,
            "deviceTypeIdentifier" to bridgeConfig.deviceName,
            "taskRunUUID" to assessmentResult.runUUIDString,
            "dataGroups" to dataGroups,
            "startDate" to startDate.toString(),
            "endDate" to endDate.toString()
        )
    }

    open fun toArchiveFiles(assessmentResult: AssessmentResult, jsonCoder: Json): Set<ArchiveFile> {
        return setOf()
    }
}
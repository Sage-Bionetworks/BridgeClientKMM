package org.sagebionetworks.bridge.assessmentmodel.upload

import android.os.Build
import co.touchlab.kermit.Logger
import com.google.common.io.Files
import kotlinx.datetime.Clock
import kotlinx.datetime.Instant
import kotlinx.serialization.Serializable
import kotlinx.serialization.encodeToString
import kotlinx.serialization.json.Json
import org.joda.time.DateTime
import org.joda.time.DateTimeZone
import org.sagebionetworks.assessmentmodel.*
import org.sagebionetworks.bridge.data.Archive
import org.sagebionetworks.bridge.data.ByteSourceArchiveFile
import org.sagebionetworks.bridge.data.JsonArchiveFile
import org.sagebionetworks.bridge.kmm.shared.BridgeConfig
import java.io.File

class AssessmentArchiver(
    private val assessmentResult: Result,
    private val jsonCoder: Json,
    private val bridgeConfig: BridgeConfig,
    // To serialize assessmentResult as part of archive, include a filename for the result.
    private val assessmentResultFilename: String? = null // Used when result is of type AssessmentResult
) {

    private val manifest: MutableSet<ArchiveFileInfo> = mutableSetOf()
    private val archiveBuilder: Archive.Builder

    init {
        val appVersion = "version ${bridgeConfig.appVersionName}, build ${bridgeConfig.appVersion}"
        val item = assessmentResult.identifier
        archiveBuilder = Archive.Builder.forActivity(item)
            .withAppVersionName(appVersion)
            .withPhoneInfo(bridgeConfig.deviceName)
    }

    fun buildArchive() : Archive {
        // Iterate through all the results within this collection and add if they are `JsonFileArchivableResult`.
        recursiveAdd(assessmentResult)

        //Add assessment result file to archive
        if (assessmentResult is AssessmentResult && assessmentResultFilename != null) {
            Logger.d("Writing result for assessment ${assessmentResult.identifier}")
            archiveBuilder.addDataFile(
                JsonArchiveFile(
                    assessmentResultFilename,
                    assessmentResult.endDateTime?.toJodaDateTime(),
                    jsonCoder.encodeToString(assessmentResult)
                )
            )

            //Add assessment result file info to manifest
            manifest.add(
                ArchiveFileInfo(
                    filename = assessmentResultFilename,
                    timestamp = assessmentResult.endDateTime?.toString() ?: Clock.System.now()
                        .toString(),
                    contentType = "application/json",
                    identifier = assessmentResult.identifier,
                    jsonSchema = assessmentResult.jsonSchema
                )
            )
        }

        //Add metadata file
        val appVersion = "version ${bridgeConfig.appVersionName}, build ${bridgeConfig.appVersion}"
        val os = "${bridgeConfig.osName}/${bridgeConfig.osVersion}"
        val metadata =  ArchiveMetadata(
            appName = bridgeConfig.appName,
            appVersion = appVersion,
            deviceInfo = "${Build.PRODUCT} ${Build.MODEL}; $os",
            deviceTypeIdentifier = bridgeConfig.deviceName,
            files = manifest.toList()
        )
        archiveBuilder.addDataFile(
            JsonArchiveFile(
                "metadata.json",
                assessmentResult.endDateTime?.toJodaDateTime(),
                jsonCoder.encodeToString(metadata)
            )
        )

        //Build and return the archive
        return archiveBuilder.build()
    }


    private fun addBranchResults(branchResult: BranchNodeResult, stepPath: String? = null) {
        recursiveAddFiles(branchResult.pathHistoryResults, stepPath)
        recursiveAddFiles(branchResult.inputResults, stepPath)
    }


    private fun recursiveAddFiles(results: Collection<Result>, stepPath: String? = null)  {
        results.forEach {
            recursiveAdd(it, stepPath)
            }
        }

    private fun recursiveAdd(result: Result, stepPath: String? = null) {
        val pathSuffix = stepPath?.let { "$it/" } ?: ""
        val identifier = result.identifier
        val path = "$pathSuffix$identifier"

        if (result is BranchNodeResult) {
            addBranchResults(result, path)
        } else if (result is CollectionResult) {
            recursiveAddFiles(result.inputResults, path)
        }
        if (result is JsonFileArchivableResult) {
            addJsonFileArchivableResult(result, path)
        }
        if (result is FileResult) {
            addFileResult(result, path)
        }
    }

    private fun addJsonFileArchivableResult(result: JsonFileArchivableResult, stepPath: String) {
        val jsonFile = result.getJsonArchivableFile(stepPath)
        //Add file to archive
        archiveBuilder.addDataFile(JsonArchiveFile(
            jsonFile.filename,
            result.endDateTime?.toJodaDateTime(),
            jsonFile.json
        ))
        //Add file info to manifest
        manifest.add(
            ArchiveFileInfo(
                filename = jsonFile.filename,
                timestamp = result.endDateTime?.toString() ?: Clock.System.now().toString(),
                contentType = "application/json",
                identifier = result.identifier,
                stepPath = stepPath,
                jsonSchema = jsonFile.jsonSchema
            )
        )
    }

    private fun addFileResult(resultData: FileResult, stepPath: String) : Boolean {
        Logger.i("Converting and archiving ${resultData.identifier} result")
        if (resultData.path == null) {
            Logger.w("Path is null , skipping file result: $resultData")
            return false
        }
        val file = File(resultData.path!!)
        if (!file.isFile) {
            Logger.w("No file found at relative path, skipping file result: $resultData")
            return false
        }
        if (file.length() > 100000000) {
            //Log as an exception so it gets reported to Crashlytics for apps that us it  -nbrown 2/10/23
            Logger.e("File larger than 100mb, skipping file result: $resultData", IllegalArgumentException("File larger than 100mb"))
            return false
        }

        archiveBuilder.addDataFile(
            ByteSourceArchiveFile(
                resultData.filename, resultData.endDateTime?.toJodaDateTime(),
                Files.asByteSource(file)
            )
        )
        manifest.add(
            ArchiveFileInfo(
                filename = resultData.filename,
                timestamp = resultData.endDateTime?.toString() ?: Clock.System.now().toString(),
                contentType = resultData.contentType,
                identifier = resultData.identifier, // Mapped to Result.identifier
                stepPath = stepPath,
                jsonSchema = resultData.jsonSchema
            )
        )
        return true
    }

}

@Serializable
data class ArchiveMetadata(
    val appName: String,
    val appVersion: String,
    val deviceInfo: String,
    val deviceTypeIdentifier: String,
    val files: List<ArchiveFileInfo>
)

@Serializable
data class ArchiveFileInfo(
    val filename: String,
    val timestamp: String,
    val contentType: String? = null,
    val identifier: String? = null,
    val stepPath: String? = null,
    val jsonSchema: String? = null
)

fun Instant.toJodaDateTime(): DateTime = org.joda.time.Instant(this.toEpochMilliseconds())
    .toDateTime(DateTimeZone.UTC)
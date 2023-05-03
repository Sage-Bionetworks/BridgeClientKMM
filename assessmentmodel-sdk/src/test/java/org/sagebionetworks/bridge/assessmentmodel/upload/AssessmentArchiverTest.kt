package org.sagebionetworks.bridge.assessmentmodel.upload

import co.touchlab.kermit.CommonWriter
import co.touchlab.kermit.Logger
import kotlinx.datetime.Clock
import kotlinx.datetime.Instant
import kotlinx.serialization.SerialName
import kotlinx.serialization.Serializable
import kotlinx.serialization.decodeFromString
import kotlinx.serialization.encodeToString
import kotlinx.serialization.json.Json
import kotlinx.serialization.modules.SerializersModule
import kotlinx.serialization.modules.plus
import kotlinx.serialization.modules.polymorphic
import kotlinx.serialization.modules.subclass
import org.junit.Assert.assertEquals
import org.junit.Assert.assertNotNull
import org.junit.Assert.assertTrue
import org.junit.Rule
import org.junit.Test
import org.junit.rules.TemporaryFolder
import org.sagebionetworks.assessmentmodel.AssessmentResult
import org.sagebionetworks.assessmentmodel.JsonArchivableFile
import org.sagebionetworks.assessmentmodel.JsonFileArchivableResult
import org.sagebionetworks.assessmentmodel.Result
import org.sagebionetworks.assessmentmodel.serialization.*
import org.sagebionetworks.bridge.kmm.shared.BridgeConfig
import org.sagebionetworks.bridge.kmm.shared.PlatformConfig
import java.io.ByteArrayInputStream
import java.io.ByteArrayOutputStream
import java.util.zip.ZipInputStream

class AssessmentArchiverTest {

    init {
        Logger.setLogWriters(CommonWriter())
    }

    val jsonCoder = Json{
        serializersModule = Serialization.SerializersModule.default + testResultSerializersModule
        encodeDefaults = true
    }

    @Rule @JvmField
    val tempFolder = TemporaryFolder()

    @Test
    fun testAssessmentArchiver() {
        val assessmentResult = AssessmentResultObject(
            identifier = "testAssessment1",
        )
        val resultFileName = "assessmentResult.json"
        val expectedFiles = setOf(resultFileName, "metadata.json", "info.json")
        verifyArchive(assessmentResult, resultFileName, expectedFiles)
    }

    @Test
    fun testAssessmentArchiverFileResults() {
        val assessmentResult = AssessmentResultObject(
            identifier = "testAssessment2",
        )
        val file = tempFolder.newFile("FileResult1")
        val fileResult = FileResultObject(identifier = file.name, filename = file.name, path = file.absolutePath)
        assessmentResult.pathHistoryResults.add(fileResult)
        val resultFileName = "assessmentResult.json"
        val expectedFiles = setOf(resultFileName, "metadata.json", "info.json", file.name)
        verifyArchive(assessmentResult, resultFileName, expectedFiles)
    }

    @Test
    fun testAssessmentArchiverAsyncResults() {
        val assessmentResult = AssessmentResultObject(
            identifier = "testAssessment3",
        )
        val file = tempFolder.newFile("FileResult1")
        val fileResult = FileResultObject(identifier = file.name, filename = file.name, path = file.absolutePath)
        assessmentResult.inputResults.add(fileResult)
        val resultFileName = "assessmentResult.json"
        val expectedFiles = setOf(resultFileName, "metadata.json", "info.json", file.name)
        verifyArchive(assessmentResult, resultFileName, expectedFiles)
    }

    @Test
    fun testAssessmentArchiverJsonFileResults() {
        val assessmentResult = AssessmentResultObject(
            identifier = "testAssessment3",
        )
        val jsonResult = JsonTestResult(identifier = "jsonTest")
        assessmentResult.pathHistoryResults.add(jsonResult)
        val resultFileName = "assessmentResult.json"
        val expectedFiles = setOf(resultFileName, "metadata.json", "info.json", "jsonTest.json")
        verifyArchive(assessmentResult, resultFileName, expectedFiles)
    }

    private fun verifyArchive(assessmentResult: AssessmentResult, resultFileName: String, expectedFiles: Set<String>) {
        val mutableExpectedFiles = expectedFiles.toMutableSet()

        val archiver = AssessmentArchiver(
            assessmentResult = assessmentResult,
            jsonCoder = jsonCoder,
            bridgeConfig = TestBridgeConfig(),
            assessmentResultFilename = resultFileName
        )

        val archive = archiver.buildArchive()
        val byteArrayOutputStream = ByteArrayOutputStream()
        archive.writeTo(byteArrayOutputStream)
        val zipInputStream = ZipInputStream(ByteArrayInputStream(byteArrayOutputStream.toByteArray()))
        var foundMetadataFile = false
        do {
            val entry = zipInputStream.nextEntry
            if (entry != null) {
                assertTrue(mutableExpectedFiles.remove(entry.name))
                if (entry.name == "metadata.json") {
                    val data = zipInputStream.readBytes()
                    val metadataJsonString = data.toString(Charsets.UTF_8)
                    val metadata: ArchiveMetadata = Json.decodeFromString(metadataJsonString)
                    val archiveFileInfo = metadata.files.find { it.filename == resultFileName }
                    assertNotNull(archiveFileInfo)
                    assertNotNull(assessmentResult.jsonSchema)
                    assertEquals(assessmentResult.jsonSchema, archiveFileInfo?.jsonSchema)
                    foundMetadataFile = true
                }
            }
        } while (entry != null)
        assertTrue(foundMetadataFile)
        assertTrue(mutableExpectedFiles.isEmpty())
    }

}

val testResultSerializersModule = SerializersModule {
    polymorphic(Result::class) {
        subclass(JsonTestResult::class)
    }
}


@Serializable
data class JsonTestResult(
    override val identifier: String,
    @SerialName("startDate")
    @Serializable(with = InstantSerializer::class)
    override var startDateTime: Instant = Clock.System.now(),
    @SerialName("endDate")
    @Serializable(with = InstantSerializer::class)
    override var endDateTime: Instant? = Clock.System.now(),
) : JsonFileArchivableResult {

    override fun copyResult(identifier: String): JsonTestResult {
        return copy(identifier = identifier)
    }

    override fun getJsonArchivableFile(stepPath: String): JsonArchivableFile {
        return JsonArchivableFile(
            filename = "$identifier.json",
            json = Json.encodeToString(this),
            jsonSchema = "https://sage-bionetworks.github.io/mobile-client-json/schemas/v2/test.json"
        )
    }

}

class TestBridgeConfig: BridgeConfig {
    override val appId: String
        get() = "bridge-client-kmm-tests"
    override val appName: String
        get() = "BridgeClientKMM Tests"
    override val sdkVersion: Int
        get() = 1
    override val appVersion: Int
        get() = 1
    override val appVersionName: String
        get() = "AssessmentModel-SDK Test"
    override val bridgeEnvironment: PlatformConfig.BridgeEnvironment
        get() = PlatformConfig.BridgeEnvironment.PRODUCTION
    override val osName: String
        get() = "AssessmentModel-SDK Test"
    override val osVersion: String
        get() = "AssessmentModel-SDK Test"
    override val deviceName: String
        get() = "AssessmentModel-SDK Test"

}
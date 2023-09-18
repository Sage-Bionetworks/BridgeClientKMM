package org.sagebionetworks.bridge.assessmentmodel.upload

import co.touchlab.kermit.CommonWriter
import co.touchlab.kermit.Logger
import com.fasterxml.jackson.databind.ObjectMapper
import com.networknt.schema.JsonSchemaFactory
import com.networknt.schema.SpecVersion
import kotlinx.datetime.Clock
import kotlinx.datetime.Instant
import kotlinx.serialization.SerialName
import kotlinx.serialization.Serializable
import kotlinx.serialization.decodeFromString
import kotlinx.serialization.encodeToString
import kotlinx.serialization.json.Json
import kotlinx.serialization.json.JsonArray
import kotlinx.serialization.json.JsonElement
import kotlinx.serialization.json.JsonPrimitive
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
import org.sagebionetworks.assessmentmodel.survey.AnswerType
import org.sagebionetworks.assessmentmodel.survey.BaseType
import org.sagebionetworks.bridge.kmm.shared.BridgeConfig
import org.sagebionetworks.bridge.kmm.shared.PlatformConfig
import java.io.ByteArrayInputStream
import java.io.ByteArrayOutputStream
import java.net.URI
import java.util.zip.ZipInputStream

class AssessmentArchiverTest {

    init {
        Logger.setLogWriters(CommonWriter())
    }

    val jsonCoder = Json{
        serializersModule = Serialization.SerializersModule.default + testResultSerializersModule
        encodeDefaults = true
        explicitNulls = false
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

    fun testAssessmentArchiverSurveyAnswers() {

        var assessmentResult = AssessmentResultObject("example_survey")
        val answerResult1 = AnswerResultObject("pizza", AnswerType.BOOLEAN, JsonPrimitive(true), questionText = "Do you like pizza?")
        val answerResult2 = AnswerResultObject("step2", AnswerType.INTEGER, JsonPrimitive(42), questionText = "What is the answer to the universe and everything?")
        val answerResult3 = AnswerResultObject("step3", AnswerType.Decimal(), JsonPrimitive(52.25), questionText = "How old are you?")
        val answerResult4 = AnswerResultObject("step4", AnswerType.STRING, JsonPrimitive("brown fox"), questionText = "Who jumped over the lazy dog?")
        val answerResult5 = AnswerResultObject("step5", AnswerType.Array(BaseType.INTEGER), JsonArray(listOf(JsonPrimitive(1),JsonPrimitive(11))), questionText = "What are your favorite numbers?")
        val answerResult6 = AnswerResultObject(  "pizza", AnswerType.BOOLEAN, JsonPrimitive(false), questionText = "Do you like pizza now?")
        val branchResult = BranchNodeResultObject("branch", mutableListOf(answerResult6))
        assessmentResult.pathHistoryResults.add(answerResult1)
        assessmentResult.pathHistoryResults.add(answerResult2)
        assessmentResult.pathHistoryResults.add(answerResult3)
        assessmentResult.pathHistoryResults.add(answerResult4)
        assessmentResult.pathHistoryResults.add(answerResult5)
        assessmentResult.pathHistoryResults.add(branchResult)

        val expectedAnswers = mapOf<String, JsonElement>(
            "pizza" to JsonPrimitive(true),
            "step2" to JsonPrimitive(42),
            "step3" to JsonPrimitive(52.25),
            "step4" to JsonPrimitive("brown fox"),
            "step5" to JsonPrimitive("1,11"),
            "branch_pizza" to JsonPrimitive(true),
        )

        val expectedAnswersSchema = SimpleJsonSchema(
            "answers_schema.json",
            "http://json-schema.org/draft-07/schema#",
            "object",
            "answers_schema",
            "example_survey",
            mutableMapOf(
                "pizza" to JsonSchemaProperty(BaseType.BOOLEAN, "Do you like pizza?"),
                "step2" to JsonSchemaProperty(BaseType.INTEGER, "What is the answer to the universe and everything?"),
                "step3" to JsonSchemaProperty(BaseType.NUMBER, "How old are you?"),
                "step4" to JsonSchemaProperty(BaseType.STRING,"Who jumped over the lazy dog?"),
                "step5" to JsonSchemaProperty(BaseType.STRING,"What are your favorite numbers?"),
                "branch_pizza" to JsonSchemaProperty(BaseType.BOOLEAN,"Do you like pizza now?")
            )
        )

        val resultFileName = "assessmentResult.json"
        val expectedFiles = setOf(resultFileName, "metadata.json", "info.json", "jsonTest.json", "answers.json", "answers_schema.json")
        verifyArchive(assessmentResult, resultFileName, expectedFiles, expectedAnswers, expectedAnswersSchema)
    }

    private fun verifyArchive(
        assessmentResult: AssessmentResult,
        resultFileName: String,
        expectedFiles: Set<String>,
        expectedAnswers: Map<String, JsonElement>? = null,
        expectedAnswersSchema: SimpleJsonSchema? = null
    ) {
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
                    validateJson(metadataJsonString, "https://sage-bionetworks.github.io/mobile-client-json/schemas/v2/ArchiveMetadata.json")
                }
                if (entry.name == "answers.json" && expectedAnswers != null) {
                    val data = zipInputStream.readBytes()
                    val jsonString = data.toString(Charsets.UTF_8)
                    val actual: Map<String, JsonElement> = Json.decodeFromString(jsonString)
                    assertEquals(expectedAnswers, actual)
                }
                if (entry.name == "answers_schema.json" && expectedAnswersSchema != null) {
                    val data = zipInputStream.readBytes()
                    val jsonString = data.toString(Charsets.UTF_8)
                    val actual: SimpleJsonSchema = Json.decodeFromString(jsonString)
                    assertEquals(expectedAnswersSchema, actual)
                }
            }
        } while (entry != null)
        assertTrue(foundMetadataFile)
        assertTrue(mutableExpectedFiles.isEmpty())
    }

}

fun validateJson(jsonString: String, schemaUrl: String) {
    val jsonSchema = JsonSchemaFactory.getInstance(SpecVersion.VersionFlag.V7).getSchema(
        URI(schemaUrl)
    )
    jsonSchema.initializeValidators()
    val jsonNode = ObjectMapper().readTree(jsonString)
    val errors = jsonSchema.validate(jsonNode)
    assertTrue(errors.toString(), errors.isEmpty())
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
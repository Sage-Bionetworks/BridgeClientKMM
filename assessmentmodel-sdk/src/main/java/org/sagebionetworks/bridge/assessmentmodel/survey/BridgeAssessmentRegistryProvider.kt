package org.sagebionetworks.bridge.assessmentmodel.survey

import kotlinx.serialization.PolymorphicSerializer
import kotlinx.serialization.json.Json
import org.sagebionetworks.assessmentmodel.*
import org.sagebionetworks.assessmentmodel.resourcemanagement.FileLoader
import org.sagebionetworks.assessmentmodel.resourcemanagement.ResourceInfo
import org.sagebionetworks.assessmentmodel.serialization.Serialization
import org.sagebionetworks.bridge.kmm.shared.repo.AssessmentConfigRepo

/**
 * Provides assessments from the local cache of AssessmentConfigs loaded from Bridge Server.
 */
class BridgeAssessmentRegistryProvider(override val fileLoader: FileLoader, val assessmentConfigRepo: AssessmentConfigRepo) : AssessmentRegistryProvider {

    val jsonCoder: Json
        get() = Serialization.JsonCoder.default

    override val modules: List<ModuleInfo>
        get() = listOf()

    override fun loadAssessment(assessmentPlaceholder: AssessmentPlaceholder): Assessment {
        assessmentPlaceholder.assessmentInfo.guid?.let {
            val jsonString =
                assessmentConfigRepo.getCachedAssessmentConfigByGuid(it)?.config?.toString()
            if (jsonString?.isNotEmpty() == true) {
                val serializer = PolymorphicSerializer(Assessment::class)
                return jsonCoder.decodeFromString(serializer, jsonString)
            }
        }
        throw IllegalStateException("Unable to load Bridge Survey  " + { assessmentPlaceholder.assessmentInfo.identifier })
    }

    /**
     * Checks if there is an AssessmentConfig matching the given AssessmentPlaceholder with non-empty JSON in the local cache.
     */
    override fun canLoadAssessment(assessmentPlaceholder: AssessmentPlaceholder): Boolean {
        assessmentPlaceholder.assessmentInfo.guid?.let {
            // Check that we have an AsessmentConfig and that it has Json
            return assessmentConfigRepo.getCachedAssessmentConfigByGuid(it)?.config?.toString()?.isNotEmpty() == true
        }
        return false
    }
}
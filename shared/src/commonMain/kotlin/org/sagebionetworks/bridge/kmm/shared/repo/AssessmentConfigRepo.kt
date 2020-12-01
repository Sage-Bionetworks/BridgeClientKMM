package org.sagebionetworks.bridge.kmm.shared.repo

import co.touchlab.stately.ensureNeverFrozen
import kotlinx.coroutines.CoroutineScope
import kotlinx.coroutines.MainScope
import kotlinx.coroutines.flow.Flow
import kotlinx.coroutines.flow.map
import kotlinx.coroutines.flow.onEach
import kotlinx.coroutines.launch
import kotlinx.datetime.Clock
import org.sagebionetworks.bridge.kmm.shared.apis.AssessmentsApi
import org.sagebionetworks.bridge.kmm.shared.apis.DefaultHttpClient
import org.sagebionetworks.bridge.kmm.shared.cache.DbDriverFactory
import org.sagebionetworks.bridge.kmm.shared.cache.Resource
import org.sagebionetworks.bridge.kmm.shared.cache.ResourceDatabaseHelper
import org.sagebionetworks.bridge.kmm.shared.cache.ResourceType

class AssessmentConfigRepo(databaseDriverFactory: DbDriverFactory, private val backgroundScope: CoroutineScope = MainScope()) {

    companion object {
        const val defaultUpdateFrequency = 10000// 60000 * 60
    }

    internal val database = ResourceDatabaseHelper(databaseDriverFactory)

    init {
        ensureNeverFrozen()
    }


    internal var assessmentsApi = AssessmentsApi(
        httpClient = DefaultHttpClient.httpClient
    )



    fun getAssessmentById(identifier: String): Flow<String?> {
        return database.getResource(identifier).onEach {
            if (it == null || it.lastUpdate + defaultUpdateFrequency < Clock.System.now()
                    .toEpochMilliseconds()
            ) {
                //Need to load assessment config from Bridge
                backgroundScope.launch() {
                    val assessApi = assessmentsApi
                    val assessment = assessApi.getAssessmentConfig(identifier)
                    val resource = Resource(
                        identifier,
                        ResourceType.ASSESSMENT_CONFIG,
                        assessment.config.toString(),
                        Clock.System.now().toEpochMilliseconds()
                    )
                    database.insertUpdateResource(resource)

                }

                //Need to make sure webcall is not already in flight
                // TODO: syoung 11/25/2020 Is this comment a TODO?
            }
        }.map { it?.json }

    }

}
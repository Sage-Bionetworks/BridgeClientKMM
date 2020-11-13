package org.sagebionetworks.bridge.kmm.shared.repo

import co.touchlab.stately.ensureNeverFrozen
import kotlinx.coroutines.MainScope
import kotlinx.coroutines.flow.Flow
import kotlinx.coroutines.flow.map
import kotlinx.coroutines.flow.onEach
import kotlinx.coroutines.launch
import kotlinx.datetime.Clock
import org.sagebionetworks.bridge.kmm.shared.apis.AssessmentsApi
import org.sagebionetworks.bridge.kmm.shared.apis.DefaultHttpClient
import org.sagebionetworks.bridge.kmm.shared.cache.*

class AssessmentConfigRepo(databaseDriverFactory: DatabaseDriverFactory) {

    companion object {
        const val defaultUpdateFrequency = 10000// 60000 * 60
    }

    private val database = ResourceDatabaseHelper(databaseDriverFactory)

    init {
        ensureNeverFrozen()
    }


    private val assessmentsApi = AssessmentsApi(
        httpClient = DefaultHttpClient.httpClient
    )



    fun getAssessmentById(identifier: String): Flow<String?> {
        return database.getResource(identifier).onEach {
            if (it == null || it.lastUpdate + defaultUpdateFrequency < Clock.System.now()
                    .toEpochMilliseconds()
            ) {
                //Need to load assessment config from Bridge
                MainScope().launch {

                    val assessApi = assessmentsApi//loadAssessmentsApi(userSession.sessionToken)
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
            }
        }.map { it?.json }

    }


}
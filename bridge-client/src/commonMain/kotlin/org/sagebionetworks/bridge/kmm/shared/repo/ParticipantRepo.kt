package org.sagebionetworks.bridge.kmm.shared.repo

import co.touchlab.kermit.Logger
import co.touchlab.stately.ensureNeverFrozen
import io.ktor.client.*
import io.ktor.client.plugins.*
import io.ktor.http.*
import io.ktor.util.network.*
import kotlinx.coroutines.CoroutineScope
import kotlinx.coroutines.launch
import kotlinx.datetime.Clock
import kotlinx.serialization.encodeToString
import kotlinx.serialization.json.Json
import kotlinx.serialization.json.JsonElement
import org.sagebionetworks.bridge.kmm.shared.apis.ParticipantApi
import org.sagebionetworks.bridge.kmm.shared.cache.*
import org.sagebionetworks.bridge.kmm.shared.models.*
import org.sagebionetworks.bridge.kmm.shared.models.ConsentSignature

class ParticipantRepo(httpClient: HttpClient,
                      databaseHelper: ResourceDatabaseHelper,
                      backgroundScope: CoroutineScope,
                      private val authenticationRepo: AuthenticationRepository) :
        AbstractResourceRepo(databaseHelper, backgroundScope) {

    init {
        ensureNeverFrozen()
    }

    internal var participantApi = ParticipantApi(
        httpClient = httpClient
    )

    /**
     * Update user's participant record. This will update the locally cached [UserSessionInfo] object,
     * and trigger a background process to update the Bridge server.
     */
    fun updateParticipant(record: UpdateParticipantRecord) {
        // Update UserSessionInfo resource and mark as needing update
        val userSessionInfo = authenticationRepo.session()?.copy(
            firstName = record.firstName,
            lastName = record.lastName,
            sharingScope = record.sharingScope,
            dataGroups = record.dataGroups,
            clientData = record.clientData,
            email = record.email,
            phone = record.phone
        )
        val resource = Resource(
            identifier = AuthenticationRepository.USER_SESSION_ID,
            secondaryId = ResourceDatabaseHelper.DEFAULT_SECONDARY_ID,
            type = ResourceType.USER_SESSION_INFO,
            studyId = ResourceDatabaseHelper.APP_WIDE_STUDY_ID,
            json = Json.encodeToString(userSessionInfo),
            lastUpdate = Clock.System.now().toEpochMilliseconds(),
            status = ResourceStatus.SUCCESS,
            needSave = true
        )
        database.insertUpdateResource(resource)
        backgroundScope.launch {
            processLocalUpdates()
        }
    }

    suspend fun createConsentSignature(subpopulationGuid: String): ResourceResult<UserSessionInfo> {
        try {
            val sessionInfo = authenticationRepo.session()
            val name = sessionInfo?.let {
                listOfNotNull(it.firstName, it.lastName).joinToString(" ").ifEmpty { null }
            } ?: "Name"
            val scope = sessionInfo?.sharingScope ?: SharingScope.SPONSORS_AND_PARTNERS
            val consentSignature = ConsentSignature(name = name, scope = scope)
            val userSession = participantApi.createConsentSignature(subpopulationGuid, consentSignature)
            authenticationRepo.updateCachedSession(null, userSession)
            return ResourceResult.Success(userSession, ResourceStatus.SUCCESS)
        } catch (err: Throwable) {
            Logger.e("Error adding consent", err)
        }
        return ResourceResult.Failed(ResourceStatus.FAILED)
    }

    internal suspend fun processLocalUpdates() {
        //Check if session needs updating
        val sessionResource = authenticationRepo.sessionResource()
        sessionResource?.let { resource ->
            if (resource.needSave) {
                val session = resource.loadResource<UserSessionInfo>()
                val studyParticipant =
                    session?.let { it1 -> UpdateParticipantRecord.getStudyParticipant(it1) }

                studyParticipant?.let {
                    var status = ResourceStatus.FAILED
                    var needSave = true
                    try {
                        participantApi.updateUsersParticipantRecord(it)
                        status = ResourceStatus.SUCCESS
                        needSave = false
                    } catch (throwable: Throwable) {
                        println(throwable)
                        when (throwable) {
                            is ResponseException -> {
                                // Can look at throwable.response.status if we find scenarios we want to mark for retry
                            }

                            is UnresolvedAddressException -> {
                                //Internet connection error
                                status = ResourceStatus.RETRY
                            }
                        }
                    }
                    val toUpdate = resource.copy(status = status, needSave = needSave)
                    database.insertUpdateResource(toUpdate)
                }

            }
        }

    }

    /**
     * Data class used for updating the editable fields on a study participant.
     */
    data class UpdateParticipantRecord private constructor (
        /* An ID assigned to this account by Bridge system. */
        val id: String,
        /* First name (given name) of the user. */
        var firstName: String? = null,
        /* Last name (family name) of the user. */
        var lastName: String? = null,
        var sharingScope: SharingScope? = null,
        /* The data groups set for this user. Data groups must be strings that are defined in the list of all valid data groups for the app, as part of the app object.   */
        val dataGroups: MutableList<String>? = null,
        /* Client data for a user should be in a syntactically valid JSON format. It will be returned as is to the client (as JSON).  */
        var clientData: JsonElement? = null,
        /* The user's email. */
        var email: String? = null,
        var phone: Phone? = null
    ) {

        internal fun toStudyParticipantRecord() : StudyParticipant {
            return StudyParticipant(
                id = id,
                firstName = firstName,
                lastName = lastName,
                sharingScope = sharingScope,
                dataGroups = dataGroups,
                clientData = clientData,
                email = email,
                phone = phone
            )
        }

        companion object {

            /**
             * Given a [UserSessionInfo] object, get an [UpdateParticipantRecord] which can be used to
             * update values on a study participant.
             */
            fun getUpdateParticipantRecord(session: UserSessionInfo) : UpdateParticipantRecord {
                return UpdateParticipantRecord(
                    id = session.id,
                    firstName = session.firstName,
                    lastName = session.lastName,
                    sharingScope = session.sharingScope,
                    dataGroups = session.dataGroups?.toMutableList(),
                    clientData = session.clientData,
                    email = session.email,
                    phone = session.phone
                )
            }

            internal fun getStudyParticipant(session: UserSessionInfo) : StudyParticipant {
                return getUpdateParticipantRecord(session).toStudyParticipantRecord()
            }

        }
    }
}
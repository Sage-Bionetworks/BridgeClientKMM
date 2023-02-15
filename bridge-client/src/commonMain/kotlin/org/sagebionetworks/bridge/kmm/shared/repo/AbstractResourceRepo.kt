package org.sagebionetworks.bridge.kmm.shared.repo

import io.ktor.client.plugins.*
import io.ktor.http.*
import io.ktor.util.network.*
import kotlinx.coroutines.CoroutineScope
import kotlinx.coroutines.flow.Flow
import kotlinx.coroutines.flow.distinctUntilChanged
import kotlinx.coroutines.flow.filter
import kotlinx.coroutines.flow.map
import kotlinx.coroutines.launch
import kotlinx.datetime.Clock
import org.sagebionetworks.bridge.kmm.shared.cache.*

abstract class AbstractResourceRepo(val database: ResourceDatabaseHelper, protected val backgroundScope: CoroutineScope) {

    internal inline fun <reified T: Any> getResourceByIdAsFlow(identifier: String,
                                                               studyId: String,
                                                               resourceType: ResourceType,
                                                               secondaryId: String? = null,
                                                               noinline remoteLoad: suspend () -> String,
                                                               noinline shouldUpdate: (Resource) -> Boolean = {false}): Flow<ResourceResult<T>> {
        return database.getResourceAsFlow(identifier, resourceType, studyId).filter { curResource ->
            var filterResource = true //Return current item in the flow
            if (curResource == null ||
                (!curResource.needSave && (shouldUpdate(curResource) ||
                (curResource.lastUpdate + defaultUpdateFrequency < Clock.System.now().toEpochMilliseconds())))
            ) {
                filterResource = false // don't return current item since we are going to update it

                //Need to load resource from Bridge
                backgroundScope.launch {
                    remoteLoadResource(database, identifier, secondaryId, resourceType, studyId, curResource, remoteLoad)
                }
            }
            filterResource
        }.distinctUntilChanged(areEquivalent = {old, new -> old?.json == new?.json}).map {
            processResult(it)
        }

    }

    internal suspend inline fun <reified T: Any> getResourceById(identifier: String,
                                                         studyId: String,
                                                         resourceType: ResourceType,
                                                         secondaryId: String? = null,
                                                         noinline remoteLoad: suspend () -> String) : ResourceResult<T> {
        var curResource = database.getResource(identifier, resourceType, studyId)
        if (curResource == null ||
                    (curResource.lastUpdate + defaultUpdateFrequency < Clock.System.now().toEpochMilliseconds())
        ) {
            curResource = remoteLoadResource(database, identifier, secondaryId, resourceType, studyId, curResource, remoteLoad)
        }
        return processResult(curResource)
    }


    internal companion object {

        const val defaultUpdateFrequency = 60000// 1 minute

        internal suspend fun remoteLoadResource(
            database: ResourceDatabaseHelper,
            identifier: String,
            secondaryId: String? = null,
            resourceType: ResourceType,
            studyId: String,
            curResource: Resource?, //Current resource from local cache if there is one
            remoteLoad: suspend () -> String
        ): Resource {
            //Mark the resource as pending update
            var resource = Resource(
                identifier = identifier,
                secondaryId = secondaryId ?: ResourceDatabaseHelper.DEFAULT_SECONDARY_ID,
                type = resourceType,
                studyId = studyId,
                json = curResource?.json,
                lastUpdate = Clock.System.now().toEpochMilliseconds(),
                status = ResourceStatus.PENDING,
                needSave = false
            )
            database.insertUpdateResource(resource)

            try {
                val resourceJson = remoteLoad()
                resource = Resource(
                    identifier = identifier,
                    secondaryId = secondaryId ?: ResourceDatabaseHelper.DEFAULT_SECONDARY_ID,
                    type = resourceType,
                    studyId = studyId,
                    json = resourceJson,
                    lastUpdate = Clock.System.now().toEpochMilliseconds(),
                    status = ResourceStatus.SUCCESS,
                    needSave = false
                )
                database.insertUpdateResource(resource)
            } catch (err: Throwable) {
                resource = processResponseException(database, identifier, secondaryId, resourceType, studyId, curResource, err)
                database.insertUpdateResource(resource)
            }
            return resource
        }

        private fun processResponseException(
            database: ResourceDatabaseHelper,
            identifier: String,
            secondaryId: String? = null,
            resourceType: ResourceType,
            studyId: String,
            curResource: Resource?,
            throwable: Throwable
        ): Resource {
            var status = ResourceStatus.FAILED
            var lastUpdate = Clock.System.now().toEpochMilliseconds()
            var json = curResource?.json
            when (throwable) {

                is ResponseException -> {
                    when (throwable.response.status) {
                        HttpStatusCode.NotModified -> {
                            // 304 not modified
                            // Update last modified time.
                            if (json.isNullOrEmpty()) {
                                //Shouldn't ever get here, but just in case.
                                //Don't actually have resource loaded, even though we got a 304
                                database.putEtag(throwable.response.call.request.url.toString(), null)
                                status = ResourceStatus.RETRY
                            } else {
                                status = ResourceStatus.SUCCESS
                                lastUpdate = Clock.System.now().toEpochMilliseconds()
                            }
                        }

                        HttpStatusCode.Unauthorized -> {
                            // 401 unauthorized
                            // User hasn't authenticated or re-auth has failed.
                            status = ResourceStatus.FAILED
                            json = null
                        }

                        HttpStatusCode.Gone -> {
                            //410 Gone
                            // The version of the client making the request no longer has access to this service.
                            // The user must update their app in order to continue using Bridge.
                            status = ResourceStatus.FAILED
                        }

                        HttpStatusCode.PreconditionFailed -> {
                            //412 Not consented
                            //Status: Failed
                            status = ResourceStatus.FAILED
                        }
                    }

                }

                is UnresolvedAddressException -> {
                    //Internet connection error
                    //Status: Retry
                    status = ResourceStatus.RETRY
                }


            }
            return Resource(
                identifier = identifier,
                secondaryId = secondaryId ?: ResourceDatabaseHelper.DEFAULT_SECONDARY_ID,
                type = resourceType,
                studyId = studyId,
                json = json,
                lastUpdate = lastUpdate,
                status = status,
                needSave = false
            )
        }


        inline fun <reified T : Any> processResult(resource: Resource?): ResourceResult<T> {
            resource?.let {

                val model = it.loadResource<T>()
                if (model != null) {
                    // If we have a model object, return it as a success.
                    return ResourceResult.Success(model, it.status)
                }

                when (it.status) {
                    ResourceStatus.PENDING -> {
                        return ResourceResult.InProgress
                    }
                    else -> {
                        return ResourceResult.Failed(it.status)
                    }

                }

            }
                ?: return ResourceResult.InProgress // If we don't have a resource, it hasn't been downloaded yet.

        }
    }
}
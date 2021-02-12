package org.sagebionetworks.bridge.kmm.shared.repo

import io.ktor.client.features.*
import io.ktor.http.*
import io.ktor.util.network.*
import kotlinx.coroutines.CoroutineScope
import kotlinx.coroutines.flow.Flow
import kotlinx.coroutines.flow.filter
import kotlinx.coroutines.flow.map
import kotlinx.coroutines.launch
import kotlinx.datetime.Clock
import org.sagebionetworks.bridge.kmm.shared.cache.*

abstract class AbstractResourceRepo(databaseDriverFactory: DbDriverFactory, private val resourceType: ResourceType, private val backgroundScope: CoroutineScope) {


    internal val database = ResourceDatabaseHelper(databaseDriverFactory)


    internal inline fun <reified T: Any> getResourceById(identifier: String,
                                                         noinline remoteLoad: suspend () -> String,
                                                         noinline shouldUpdate: (Resource) -> Boolean = {false}): Flow<ResourceResult<T>> {
        return database.getResourceAsFlow(identifier).filter { curResource ->
            var filterResource = true //Return current item in the flow
            if (curResource == null ||
                shouldUpdate(curResource) ||
                (ResourceStatus.PENDING != curResource.status && curResource.lastUpdate + defaultUpdateFrequency < Clock.System.now().toEpochMilliseconds())
            ) {
                filterResource = false // don't return current item since we are going to update it

                //Need to load resource from Bridge
                backgroundScope.launch() {
                    remoteLoadResource(database, identifier, resourceType, curResource, remoteLoad)
                }
            }
            filterResource
        }.map {
            processResult(it)
        }

    }

    companion object {

        const val defaultUpdateFrequency = 10000// 60000 * 60

        internal suspend fun remoteLoadResource(
            database: ResourceDatabaseHelper,
            identifier: String,
            resourceType: ResourceType,
            curResource: Resource?, //Current resource from local cache if there is one
            remoteLoad: suspend () -> String
        ): Resource {
            //Mark the resource as pending update
            var resource = Resource(
                identifier,
                resourceType,
                curResource?.json,
                Clock.System.now().toEpochMilliseconds(),
                ResourceStatus.PENDING
            )
            database.insertUpdateResource(resource)

            try {
                val resourceJson = remoteLoad()
                resource = Resource(
                    identifier,
                    resourceType,
                    resourceJson,
                    Clock.System.now().toEpochMilliseconds(),
                    ResourceStatus.SUCCESS
                )
                database.insertUpdateResource(resource)
            } catch (err: Throwable) {
                resource = processResponseException(identifier, resourceType, curResource, err)
                database.insertUpdateResource(resource)
            }
            return resource
        }

        private fun processResponseException(
            identifier: String,
            resourceType: ResourceType,
            curResource: Resource?,
            throwable: Throwable
        ): Resource {
            var status = ResourceStatus.FAILED
            var lastUpdate = curResource?.lastUpdate ?: Clock.System.now().toEpochMilliseconds()
            var json = curResource?.json
            when (throwable) {

                is ResponseException -> {
                    when (throwable.response.status) {
                        HttpStatusCode.NotModified -> {
                            // 304 not modified
                            // Update last modified time.
                            status = ResourceStatus.SUCCESS
                            lastUpdate = Clock.System.now().toEpochMilliseconds()
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
            val resource = Resource(
                identifier,
                resourceType,
                json,
                lastUpdate,
                status
            )
            return resource
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
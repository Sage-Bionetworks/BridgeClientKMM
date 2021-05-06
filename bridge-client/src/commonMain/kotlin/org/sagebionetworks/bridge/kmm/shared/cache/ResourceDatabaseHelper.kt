package org.sagebionetworks.bridge.kmm.shared.cache

import com.squareup.sqldelight.EnumColumnAdapter
import com.squareup.sqldelight.db.SqlDriver
import com.squareup.sqldelight.runtime.coroutines.asFlow
import com.squareup.sqldelight.runtime.coroutines.mapToList
import com.squareup.sqldelight.runtime.coroutines.mapToOneOrNull
import kotlinx.coroutines.flow.Flow

class ResourceDatabaseHelper(sqlDriver: SqlDriver) {
    internal val database = BridgeResourceDatabase(
        sqlDriver,
        Resource.Adapter(EnumColumnAdapter(), EnumColumnAdapter())
    )
    private val dbQuery = database.bridgeResourceDatabaseQueries


    internal fun clearDatabase() {
        dbQuery.transaction {
            dbQuery.removeAllResources()
        }
    }

    internal fun getResourceAsFlow(id: String): Flow<Resource?> {
        return dbQuery.selectResourceById(id).asFlow().mapToOneOrNull()
    }

    internal fun getResource(id: String): Resource? {
        return dbQuery.selectResourceById(id).executeAsOneOrNull()
    }

    internal fun removeResource(id: String) {
        dbQuery.removeResourceById(id)
    }

    internal fun insertUpdateResource(resource: Resource) {
        dbQuery.insertUpdateResource(
            identifier = resource.identifier,
            type = resource.type,
            json = resource.json,
            lastUpdate = resource.lastUpdate,
            status = resource.status
        )
    }

    internal fun getResourcesAsFlow(type: ResourceType): Flow<List<Resource>> {
        return dbQuery.selectAllResourcesByType(type).asFlow().mapToList()
    }

    internal fun getResources(type: ResourceType): List<Resource> {
        return dbQuery.selectAllResourcesByType(type).executeAsList()
    }

    internal fun removeAllResources(type: ResourceType) {
        dbQuery.removeAllResourcesByType(type)
    }

    /**
     * Remove all resources of the specified type and replace them with the specified list.
     * This is done as a single transaction.
     */
    internal fun removeAndUpdateResources(type: ResourceType, resources: List<Resource>) {
        database.transaction {
            dbQuery.removeAllResourcesByType(type)
            for(r in resources) {
                insertUpdateResource(r)
            }

        }
    }

}
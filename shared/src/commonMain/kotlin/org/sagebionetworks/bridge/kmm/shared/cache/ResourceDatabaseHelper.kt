package org.sagebionetworks.bridge.kmm.shared.cache

import com.squareup.sqldelight.EnumColumnAdapter
//import com.squareup.sqldelight.runtime.coroutines.asFlow
//import com.squareup.sqldelight.runtime.coroutines.mapToOneOrNull
import kotlinx.coroutines.flow.Flow
import org.sagebionetworks.bridge.kmm.shared.sqldelight.asFlow
import org.sagebionetworks.bridge.kmm.shared.sqldelight.mapToOneOrNull

internal class ResourceDatabaseHelper(databaseDriverFactory: DbDriverFactory) {
    internal val database = BridgeResourceDatabase(
        databaseDriverFactory.createDriver(),
        Resource.Adapter(EnumColumnAdapter())
    )
    private val dbQuery = database.bridgeResourceDatabaseQueries


    internal fun clearDatabase() {
        dbQuery.transaction {
            dbQuery.removeAllResources()
        }
    }

    internal fun getResource(id: String): Flow<Resource?> {
        return dbQuery.selectResourceById(id).asFlow().mapToOneOrNull()
    }

    internal fun insertUpdateResource(resource: Resource) {
        dbQuery.insertUpdateResource(
            identifier = resource.identifier,
            type = resource.type,
            json = resource.json,
            lastUpdate = resource.lastUpdate
        )
    }

}
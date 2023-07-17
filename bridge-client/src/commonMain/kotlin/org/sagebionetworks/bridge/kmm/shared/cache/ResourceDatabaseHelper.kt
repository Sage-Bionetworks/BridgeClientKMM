package org.sagebionetworks.bridge.kmm.shared.cache

import app.cash.sqldelight.ColumnAdapter
import app.cash.sqldelight.EnumColumnAdapter
import app.cash.sqldelight.Query
import app.cash.sqldelight.db.SqlDriver
import app.cash.sqldelight.coroutines.asFlow
import app.cash.sqldelight.coroutines.mapToList
import app.cash.sqldelight.coroutines.mapToOneOrDefault
import app.cash.sqldelight.coroutines.mapToOneOrNull
import kotlinx.coroutines.Dispatchers
import kotlinx.coroutines.flow.Flow
import kotlinx.coroutines.flow.distinctUntilChanged
import kotlinx.datetime.Clock
import kotlinx.datetime.LocalDateTime
import kotlinx.datetime.TimeZone
import kotlinx.serialization.decodeFromString
import kotlinx.serialization.encodeToString
import kotlinx.serialization.json.Json
import kotlinx.serialization.json.JsonElement
import org.sagebionetworks.bridge.kmm.shared.apis.EtagStorageCache
import org.sagebionetworks.bridge.kmm.shared.models.UploadFile
import org.sagebionetworks.bridge.kmm.shared.models.getUploadFileResourceId

class ResourceDatabaseHelper(sqlDriver: SqlDriver) : EtagStorageCache {

    private inline fun <reified T: Any>serializableColumnAdapter() = object: ColumnAdapter<T, String> {
        override fun decode(databaseValue: String): T {
            return Json.decodeFromString(databaseValue)
        }

        override fun encode(value: T): String {
            return Json.encodeToString(value)
        }
    }

    internal val database = BridgeResourceDatabase(
        sqlDriver,
        AdherenceRecords.Adapter(EnumColumnAdapter()),
        JsonData.Adapter(
            jsonAdapter = serializableColumnAdapter<JsonElement>(),
            expireAdapter = serializableColumnAdapter<LocalDateTime>(),
            timeZoneAdapter = serializableColumnAdapter<TimeZone>()
        ),
        Resource.Adapter(EnumColumnAdapter(), EnumColumnAdapter())
    )
    private val dbQuery = database.bridgeResourceDatabaseQueries


    /**
     * Clears all tables in the local database.
     */
    internal fun clearDatabase() {
        dbQuery.transaction {
            dbQuery.removeAllResources()
            dbQuery.removeAllEtags()
        }
        database.localDataCacheQueries.removeAllJsonData()
        database.participantScheduleQueries.clearAll()
    }

    internal fun getResourceAsFlow(id: String, type: ResourceType, studyId: String): Flow<Resource?> {
        return dbQuery.selectResourceById(id, type, studyId).asFlow().mapToOneOrNull(Dispatchers.Default).distinctUntilChanged(areEquivalent = {old, new -> old == new })
    }

    internal fun getResource(id: String, type: ResourceType, studyId: String): Resource? {
        return dbQuery.selectResourceById(id, type, studyId).executeAsOneOrNull()
    }

    internal fun getResourcesById(id: String, type: ResourceType, studyId: String): List<Resource> {
        return dbQuery.selectResourceById(id, type, studyId).executeAsList()
    }

    internal fun getResourcesBySecondaryId(secondaryId: String, type: ResourceType, studyId: String): List<Resource> {
        return dbQuery.selectResourceBySecondaryId(secondaryId, type, studyId).executeAsList()
    }

    internal fun getResourcesCount(types: List<ResourceType>): Long {
        return dbQuery.countResourceInList(types).executeAsOneOrNull() ?: 0
    }

    internal fun getPendingUploadCountAsFlow(): Flow<Long> {
        return pendingUploadQuery().asFlow().mapToOneOrDefault(0, Dispatchers.Default)
    }

    internal fun getPendingUploadCount(): Long {
        return pendingUploadQuery().executeAsOneOrNull() ?: 0
    }

    private fun pendingUploadQuery(): Query<Long> {
        return dbQuery.countPendingUploads(listOf(ResourceType.FILE_UPLOAD, ResourceType.UPLOAD_SESSION))
    }

    internal fun removeResource(id: String, type: ResourceType, studyId: String) {
        dbQuery.removeResourceById(id, type, studyId)
    }

    internal fun insertUpdateResource(resource: Resource) {
        dbQuery.transaction {
            dbQuery.insertUpdateResource(
                identifier = resource.identifier,
                secondaryId = resource.secondaryId,
                type = resource.type,
                json = resource.json,
                lastUpdate = resource.lastUpdate,
                status = resource.status,
                studyId = resource.studyId,
                needSave = resource.needSave
            )
        }
    }

    /**
     * Store an [UploadFile] to the local cache.
     */
    internal fun storeUploadFile(uploadFile: UploadFile) {
        val resource = Resource(
            identifier = uploadFile.getUploadFileResourceId(),
            type = ResourceType.FILE_UPLOAD,
            secondaryId = uploadFile.getSecondaryId(),
            studyId = APP_WIDE_STUDY_ID,
            json = Json.encodeToString(uploadFile),
            lastUpdate = Clock.System.now().toEpochMilliseconds(),
            status = ResourceStatus.SUCCESS,
            needSave = true
        )
        insertUpdateResource(resource)
    }

    internal fun getResourcesByIds(ids: List<String>, type: ResourceType, studyId: String) : List<Resource> {
        return dbQuery.selectResourceByIds(ids, type, studyId).executeAsList()
    }

    internal fun getResourcesNeedSave(type: ResourceType, studyId: String) : List<Resource> {
        return dbQuery.selectResourceNeedSave(type, studyId).executeAsList()
    }

    internal fun getResourcesAsFlow(type: ResourceType, studyId: String): Flow<List<Resource>> {
        return dbQuery.selectAllResourcesByType(type, studyId).asFlow().mapToList(Dispatchers.Default).distinctUntilChanged(areEquivalent = {old, new -> old == new })
    }

    internal fun getResources(type: ResourceType, studyId: String): List<Resource> {
        return dbQuery.selectAllResourcesByType(type, studyId).executeAsList()
    }

    internal fun removeAllResources(type: ResourceType, studyId: String) {
        dbQuery.removeAllResourcesByType(type, studyId)
    }

    /**
     * Remove all resources of the specified type and replace them with the specified list.
     * This is done as a single transaction.
     */
    internal fun removeAndUpdateResources(type: ResourceType, resources: List<Resource>, studyId: String) {
        database.transaction {
            dbQuery.removeAllResourcesByType(type, studyId)
            for(r in resources) {
                insertUpdateResource(r)
            }

        }
    }

    companion object {

        /**
         * For caching resources that are not specific to an individual study.
         */
        const val APP_WIDE_STUDY_ID = "AppWideStudyId"

        /**
         * For caching resources that don't have/need a secondary identifier.
         */
        const val DEFAULT_SECONDARY_ID = "DefaultSecondaryId"

    }


    override fun getEtag(url: String): String? {
        return dbQuery.selectEtag(url).executeAsOneOrNull()?.etag
    }

    override fun putEtag(urlKey: String, etag: String?) {
        if (etag != null) {
            dbQuery.insertUpdateEtag(urlKey, etag)
        } else {
            dbQuery.removeEtag(urlKey)
        }
    }

    fun removeAllEtags() {
        dbQuery.removeAllEtags()
    }

}
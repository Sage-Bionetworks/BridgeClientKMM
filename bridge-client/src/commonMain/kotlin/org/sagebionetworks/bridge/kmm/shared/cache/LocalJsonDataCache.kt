package org.sagebionetworks.bridge.kmm.shared.cache

import kotlinx.datetime.*
import kotlinx.serialization.json.JsonElement

class LocalJsonDataCache(databaseHelper: ResourceDatabaseHelper) {

    private val dbQuery = databaseHelper.database.localDataCacheQueries

    fun storeData(
        id: String,
        dataType: String,
        data: JsonElement,
        expire: LocalDateTime? = null
    ) {
        val expireDateTime = expire ?:  Instant.DISTANT_FUTURE.toLocalDateTime(TimeZone.currentSystemDefault())
        dbQuery.insertUpdateJsonData(
            identifier = id,
            dataType = dataType,
            json = data,
            lastUpdate = Clock.System.now().toEpochMilliseconds(),
            expire = expireDateTime,
            timeZone = TimeZone.currentSystemDefault()
        )
    }

    fun loadData(id: String, dataType: String) : JsonData? {
        return dbQuery.selectJsonDataById(id, dataType).executeAsOneOrNull()
    }

    fun removeExpiredData() {
        dbQuery.removeExpiredData(Clock.System.now().toLocalDateTime(TimeZone.currentSystemDefault()))
    }

}
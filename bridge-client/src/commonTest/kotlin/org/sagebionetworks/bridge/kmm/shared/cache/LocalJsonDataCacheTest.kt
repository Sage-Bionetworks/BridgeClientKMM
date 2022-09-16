package org.sagebionetworks.bridge.kmm.shared.cache

import kotlinx.coroutines.runBlocking
import kotlinx.datetime.Clock
import kotlinx.datetime.TimeZone
import kotlinx.datetime.toLocalDateTime
import kotlinx.serialization.json.Json
import org.sagebionetworks.bridge.kmm.shared.testDatabaseDriver
import kotlin.test.Test
import kotlin.test.assertEquals
import kotlin.test.assertNotNull
import kotlin.test.assertNull
import kotlin.time.Duration.Companion.seconds
import kotlin.time.ExperimentalTime

@OptIn(ExperimentalTime::class)
class LocalJsonDataCacheTest {

    @Test
    fun testDataCache() {
        runBlocking {
            val db = ResourceDatabaseHelper(testDatabaseDriver())
            val localCache = LocalJsonDataCache(db)

            val testIdPast = "TestIdPast"
            val dataType = "testDataType"
            val json = "{}"
            val data = Json.parseToJsonElement(json)
            val expirePast = Clock.System.now().minus(10.seconds).toLocalDateTime(TimeZone.currentSystemDefault())
            // Cache data that expires in the past
            localCache.storeData(
                id = testIdPast,
                dataType = dataType,
                data = data,
                expire = expirePast
            )

            // Check the past data
            var loadedData = localCache.loadData(testIdPast, dataType)
            assertNotNull(loadedData)
            assertEquals(testIdPast, loadedData.identifier)
            assertEquals(dataType, loadedData.dataType)
            assertEquals(data, loadedData.json)

            val testIdFuture = "TestIdFuture"
            val expireFuture = Clock.System.now().plus(60.seconds).toLocalDateTime(TimeZone.currentSystemDefault())
            // Cache data that expires in the future
            localCache.storeData(
                id = testIdFuture,
                dataType = dataType,
                data = data,
                expire = expireFuture
            )

            // Clear the expired data from cache
            localCache.removeExpiredData()
            // Check that expired data is gone
            loadedData = localCache.loadData(testIdPast, dataType)
            assertNull(loadedData)
            // Check that future data is still there
            loadedData = localCache.loadData(testIdFuture, dataType)
            assertNotNull(loadedData)
            assertEquals(testIdFuture, loadedData.identifier)
        }
    }
}

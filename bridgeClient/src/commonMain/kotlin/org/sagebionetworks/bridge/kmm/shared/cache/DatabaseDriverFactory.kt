package org.sagebionetworks.bridge.kmm.shared.cache

import com.squareup.sqldelight.db.SqlDriver

expect class DatabaseDriverFactory : DbDriverFactory{
    override fun createDriver(): SqlDriver
}

interface DbDriverFactory {

    fun createDriver(): SqlDriver
}
package org.sagebionetworks.bridge.kmm.shared.cache

import app.cash.sqldelight.db.SqlDriver

expect class DatabaseDriverFactory : DbDriverFactory{
    override fun createDriver(): SqlDriver
}

interface DbDriverFactory {

    fun createDriver(): SqlDriver
}
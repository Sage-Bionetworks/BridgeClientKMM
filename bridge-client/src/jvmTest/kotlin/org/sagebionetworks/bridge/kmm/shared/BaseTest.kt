package org.sagebionetworks.bridge.kmm.shared

import kotlinx.coroutines.CoroutineScope
import kotlinx.coroutines.runBlocking

actual abstract class BaseTest actual constructor() {

    actual fun <T> runTest(block: suspend CoroutineScope.() -> T) {
        runBlocking { block() }
    }
}
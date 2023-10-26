package org.sagebionetworks.bridge.kmm.shared

import kotlinx.coroutines.CoroutineScope
import kotlinx.coroutines.runBlocking
import org.junit.Rule

actual abstract class BaseTest {

    @get:Rule
    var coroutineTestRule = CoroutineTestRule()

    actual fun <T> runTest(block: suspend CoroutineScope.() -> T) {
        runBlocking { block() }
    }
}

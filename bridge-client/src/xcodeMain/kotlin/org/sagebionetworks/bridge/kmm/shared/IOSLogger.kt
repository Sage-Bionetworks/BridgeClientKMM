package org.sagebionetworks.bridge.kmm.shared

import co.touchlab.kermit.LogWriter
import co.touchlab.kermit.Logger
import co.touchlab.kermit.Severity
import io.ktor.client.plugins.*
import platform.Foundation.*

interface NativeLogWriter {
    fun log(severity: LogSeverity, message: String?, tag: String?, error: NSError?)
}

object IOSLogger {
    fun addLogWriter(logWriter: NativeLogWriter) {
        Logger.addLogWriter(WrappedLogWriter(logWriter))
    }
}

internal data class WrappedLogWriter(private val nativeLogWriter: NativeLogWriter) : LogWriter() {
    override fun log(severity: Severity, message: String, tag: String, throwable: Throwable?) {
        var logMessage = message
        var error: NSError? = null

        // If this is either an error or an assert, then log as an error.
        // Otherwise, convert the error to a message.
        if (throwable != null) {
            if (severity == Severity.Error || severity == Severity.Assert) {
                val kClass = throwable::class
                val domain = kClass.qualifiedName ?: kClass.simpleName ?: "KotlinError"
                val code = when (throwable) {
                    is ResponseException -> throwable.response.status.value.toLong()
                    else -> -999
                }
                error = NSError(
                    domain = domain,
                    code = code,
                    userInfo = mapOf(
                        NSLocalizedFailureReasonErrorKey to throwable.message
                    )
                )
            }
            else {
                logMessage.plus(throwable.toString())
            }
        }

        // Log the native-converted message.
        nativeLogWriter.log(
            severity = severity.toNative(),
            message = logMessage.ifEmpty { null },
            tag = tag,
            error = error
        )
    }
}

// It is recommended to *not* expose the Kermit logging library to iOS and instead
// to use a wrapper. syoung 02/10/2022
internal fun Severity.toNative() : LogSeverity {
    return when(this) {
        Severity.Verbose -> LogSeverity.Verbose
        Severity.Debug -> LogSeverity.Debug
        Severity.Info -> LogSeverity.Info
        Severity.Warn -> LogSeverity.Warn
        Severity.Error -> LogSeverity.Error
        Severity.Assert -> LogSeverity.Assert
    }
}

enum class LogSeverity {
    Verbose,
    Debug,
    Info,
    Warn,
    Error,
    Assert
}


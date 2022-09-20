/*
 * Copyright 2020 IceRock MAG Inc. Use of this source code is governed by the Apache 2.0 license.
 */

package org.sagebionetworks.bridge.kmm.shared.apis

import io.ktor.client.HttpClient
import io.ktor.client.plugins.HttpClientPlugin
import io.ktor.client.request.HttpRequest
import io.ktor.client.request.HttpRequestBuilder
import io.ktor.client.request.request
import io.ktor.client.request.takeFrom
import io.ktor.client.statement.*
import io.ktor.http.HttpStatusCode
import io.ktor.util.AttributeKey
import kotlinx.coroutines.sync.Mutex

internal class RefreshTokenFeature(
    private val updateTokenHandler: suspend () -> Boolean,
    private val isCredentialsActual: (HttpRequest) -> Boolean
) {

    class Config {
        var updateTokenHandler: (suspend () -> Boolean)? = null
        var isCredentialsActual: ((HttpRequest) -> Boolean)? = null

        // TODO: syoung 11/25/2020 Shouldn't these be `NullPointerException`?
        fun build() = RefreshTokenFeature(
            updateTokenHandler ?: throw IllegalArgumentException("updateTokenHandler should be passed"),
            isCredentialsActual ?: throw IllegalArgumentException("isCredentialsActual should be passed")
        )
    }

    companion object Feature : HttpClientPlugin<Config, RefreshTokenFeature> {

        private val refreshTokenHttpFeatureMutex = Mutex()

        override val key = AttributeKey<RefreshTokenFeature>("RefreshTokenFeature")

        override fun prepare(block: Config.() -> Unit) = Config().apply(block).build()

        override fun install(feature: RefreshTokenFeature, scope: HttpClient) {
            scope.receivePipeline.intercept(HttpReceivePipeline.After) { param ->
                //Only applicable if we are making a call to Bridge server
                if (subject.request.url.host.contains(AbstractApi.BRIDGE_SERVER_CHECK)) {
                    if (subject.status != HttpStatusCode.Unauthorized) {
                        proceedWith(subject)
                        return@intercept
                    }

                    refreshTokenHttpFeatureMutex.lock()

                    // If token of the request isn't actual, then token has already been updated and
                    // let's just to try repeat request.
                    if (!feature.isCredentialsActual(subject.request)) {
                        refreshTokenHttpFeatureMutex.unlock()
                        val requestBuilder = HttpRequestBuilder().takeFrom(subject.request)
                        val result: HttpResponse = scope.request(requestBuilder)
                        proceedWith(result)
                        return@intercept
                    }

                    // Else if token of the request is actual (same as in the storage), then need to send
                    // refresh request.
                    if (feature.updateTokenHandler.invoke()) {
                        // If the request refresh was successful, then let's just to try repeat request
                        refreshTokenHttpFeatureMutex.unlock()
                        val requestBuilder = HttpRequestBuilder().takeFrom(subject.request)
                        val result: HttpResponse = scope.request(requestBuilder)
                        proceedWith(result)
                    } else {
                        // If the request refresh was unsuccessful.
                        refreshTokenHttpFeatureMutex.unlock()
                        proceedWith(subject)
                    }
                }
            }
        }
    }
}
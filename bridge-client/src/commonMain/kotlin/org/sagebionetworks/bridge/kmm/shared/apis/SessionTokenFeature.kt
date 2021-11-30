/*
 * Copyright 2019 IceRock MAG Inc. Use of this source code is governed by the Apache 2.0 license.
 */

package org.sagebionetworks.bridge.kmm.shared.apis

import io.ktor.client.HttpClient
import io.ktor.client.features.HttpClientFeature
import io.ktor.client.request.HttpRequestPipeline
import io.ktor.client.request.header
import io.ktor.util.AttributeKey
import org.sagebionetworks.bridge.kmm.shared.apis.AbstractApi.Companion.BRIDGE_SERVER_CHECK

internal class SessionTokenFeature constructor(
    private val sessionTokenHeaderName: String,
    val sessionTokenProvider: SessionTokenProvider
) {

    class Config {
        var sessionTokenHeaderName: String? = null
        var sessionTokenProvider: SessionTokenProvider? = null
        // TODO: syoung 11/25/2020 Shouldn't these be `NullPointerException`?
        fun build() = SessionTokenFeature(
            sessionTokenHeaderName ?: throw IllegalArgumentException("HeaderName cannot be null"),
            sessionTokenProvider ?: throw IllegalArgumentException("SessionTokenProvider cannot be null")
        )
    }

    companion object Feature : HttpClientFeature<Config, SessionTokenFeature> {
        override val key = AttributeKey<SessionTokenFeature>("SessionTokenFeature")

        override fun prepare(block: Config.() -> Unit) = Config().apply(block).build()

        override fun install(feature: SessionTokenFeature, scope: HttpClient) {
            scope.requestPipeline.intercept(HttpRequestPipeline.State) {
                //Only applicable if we are making a call to Bridge server
                if (this.context.url.host.contains(BRIDGE_SERVER_CHECK)) {
                    feature.sessionTokenProvider.getSessionToken()?.apply {
                        context.headers.remove(feature.sessionTokenHeaderName)
                        context.header(feature.sessionTokenHeaderName, this)
                    }
                }
            }
        }
    }

    interface SessionTokenProvider {
        fun getSessionToken(): String?
    }
}
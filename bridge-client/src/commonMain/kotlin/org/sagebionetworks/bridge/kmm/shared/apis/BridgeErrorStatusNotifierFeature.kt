/*
 * Copyright 2019 IceRock MAG Inc. Use of this source code is governed by the Apache 2.0 license.
 */

package org.sagebionetworks.bridge.kmm.shared.apis

import io.ktor.client.HttpClient
import io.ktor.client.plugins.HttpClientPlugin
import io.ktor.client.request.HttpRequestPipeline
import io.ktor.client.request.header
import io.ktor.client.statement.*
import io.ktor.http.*
import io.ktor.util.AttributeKey
import org.sagebionetworks.bridge.kmm.shared.apis.AbstractApi.Companion.BRIDGE_SERVER_CHECK

internal class BridgeErrorStatusNotifierFeature constructor(
    val statusNotifier: BridgeErrorStatusNotifier
) {

    class Config {
        var statusNotifier: BridgeErrorStatusNotifier? = null
        fun build() = BridgeErrorStatusNotifierFeature(
            statusNotifier ?: throw IllegalArgumentException("statusNotifier cannot be null")
        )
    }

    companion object Feature : HttpClientPlugin<Config, BridgeErrorStatusNotifierFeature> {
        override val key = AttributeKey<BridgeErrorStatusNotifierFeature>("BridgeErrorStatusNotifierFeature")

        override fun prepare(block: Config.() -> Unit) = Config().apply(block).build()

        override fun install(feature: BridgeErrorStatusNotifierFeature, scope: HttpClient) {
            scope.receivePipeline.intercept(HttpReceivePipeline.After) {
                //Only applicable if we are making a call to Bridge server
                if (subject.request.url.host.contains(AbstractApi.BRIDGE_SERVER_CHECK)) {
                    if (subject.status.value in 400..499) {
                        feature.statusNotifier.notifyUIOfBridgeError(subject.status)
                    }
                }
            }
        }
    }
}

interface BridgeErrorStatusNotifier {
    fun notifyUIOfBridgeError(statusCode: HttpStatusCode)
}
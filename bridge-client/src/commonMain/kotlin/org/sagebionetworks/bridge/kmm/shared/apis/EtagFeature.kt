package org.sagebionetworks.bridge.kmm.shared.apis

import io.ktor.client.*
import io.ktor.client.plugins.*
import io.ktor.client.request.*
import io.ktor.client.statement.*
import io.ktor.http.*
import io.ktor.util.*

class EtagFeature private constructor(val storageCache: EtagStorageCache) {

    class Config() {
        var storageCache: EtagStorageCache? = null
        fun build() = EtagFeature(
            storageCache ?: throw IllegalArgumentException("EtagStorageCache cannot be null")
        )
    }

    companion object Feature : HttpClientPlugin<Config, EtagFeature> {
        override val key = AttributeKey<EtagFeature>("EtagFeature")

        override fun prepare(block: Config.() -> Unit): EtagFeature = Config().apply(block).build()

        override fun install(feature: EtagFeature, scope: HttpClient) {
            scope.requestPipeline.intercept(HttpRequestPipeline.State) {
                val eTag = feature.storageCache.getEtag(context.url.buildString())
                eTag?.let {
                    context.header(HttpHeaders.IfNoneMatch, it)
                }
            }
            scope.receivePipeline.intercept(HttpReceivePipeline.State) {
                val eTag = subject.headers.get("etag")
                val urlString = subject.request.url.toString()
                eTag?.let {
                    feature.storageCache.putEtag(urlString, eTag)
                }
            }
        }
    }


}

interface EtagStorageCache {

    fun getEtag(url: String): String?

    fun putEtag(urlKey: String, etag: String?)
}
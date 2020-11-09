package org.sagebionetworks.bridge.kmm.shared.apis

import io.ktor.client.*
import io.ktor.client.call.*
import io.ktor.client.request.*
import io.ktor.http.*

abstract class AbstractApi {

    protected abstract val _basePath: String
    protected abstract val _httpClient: HttpClient

    protected suspend inline fun <T, reified S: Any> postData(model: T, path: String) : S {
        val builder = HttpRequestBuilder()

        builder.method = HttpMethod.Post
        builder.url {
            takeFrom(_basePath)
            encodedPath = encodedPath.let { startingPath ->
                path(path)
                return@let startingPath + encodedPath.substring(1)
            }
        }
        builder.contentType()
        if(model != null) {
            builder.body = model
        }

        with(builder.headers) {
            append("Accept", "application/json")
            append("Content-Type", "application/json; charset=UTF-8")
        }

        try {
            return _httpClient.post(builder)
        } catch (pipeline: ReceivePipelineException) {
            throw pipeline.cause
        }
    }

    protected suspend inline fun <reified S: Any> getData(path: String) : S {
        val builder = HttpRequestBuilder()

        builder.method = HttpMethod.Get
        builder.url {
            takeFrom(_basePath)
            encodedPath = encodedPath.let { startingPath ->
                path(path)
                return@let startingPath + encodedPath.substring(1)
            }
        }

        with(builder.headers) {
            append("Accept", "application/json")
        }

        try {
            return _httpClient.get(builder)
        } catch (pipeline: ReceivePipelineException) {
            throw pipeline.cause
        }

    }

}
package org.sagebionetworks.bridge.kmm.shared.apis

import io.ktor.client.*
import io.ktor.client.call.*
import io.ktor.client.request.*
import io.ktor.client.statement.*
import io.ktor.http.*

abstract class AbstractApi(val basePath: String, val httpClient: HttpClient) {

    companion object {
        const val BASE_PATH = "https://webservices.sagebridge.org"
        const val BRIDGE_SERVER_CHECK = "webservices.sagebridge"
    }

    protected suspend inline fun <reified T, reified S: Any> postData(model: T, path: String) : S {
        return postDataResponse(model, path).body()
    }

    suspend inline fun <reified T> postDataResponse(model: T, path: String) : HttpResponse {
        val builder = HttpRequestBuilder()

        builder.method = HttpMethod.Post
        builder.url {
            takeFrom(basePath)
            encodedPath = encodedPath.let { startingPath ->
                path(path)
                return@let startingPath + encodedPath
            }
        }
        builder.contentType()
        if(model != null) {
            builder.setBody(model)
        }

        builder.header("Accept", "application/json")
        builder.header("Content-Type", "application/json; charset=UTF-8")

        try {
            return httpClient.post(builder).body()
        } catch (pipeline: ReceivePipelineException) {
            throw pipeline.cause
        }
    }

    protected suspend inline fun <reified S : Any> getData(
        path: String,
        modifiedDateTimeString: String? = null,
        queryParams: Map<String, String>? = null,
    ): S {
        return getDataResponse(path, modifiedDateTimeString, queryParams).body()
    }

    suspend fun getDataResponse(
        path: String,
        modifiedDateTimeString: String? = null,
        queryParams: Map<String, String>? = null,
    ): HttpResponse {
        val builder = HttpRequestBuilder()

        builder.method = HttpMethod.Get
        builder.url {
            takeFrom(basePath)
            encodedPath = encodedPath.let { startingPath ->
                path(path)
                return@let startingPath + encodedPath
            }
            with(parameters) {
                queryParams?.let {
                    it.entries.forEach { entry ->
                        append(entry.key, entry.value)
                    }
                }
            }
        }


        builder.header("Accept", "application/json")

        if (modifiedDateTimeString != null) {
            builder.header("If-Modified-Since", modifiedDateTimeString)
        }

        try {
            return httpClient.get(builder)
        } catch (pipeline: ReceivePipelineException) {
            throw pipeline.cause
        }

    }

}
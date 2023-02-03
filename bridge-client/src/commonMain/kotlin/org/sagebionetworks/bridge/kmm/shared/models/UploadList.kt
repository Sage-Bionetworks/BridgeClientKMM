package org.sagebionetworks.bridge.kmm.shared.models

import kotlinx.serialization.SerialName

@kotlinx.serialization.Serializable
internal data class UploadList(

    @SerialName("requestParams")
    val requestParams: RequestParams? = null,
    /* ResourceList */

    @SerialName("type")
    val type: kotlin.String? = null,

    /* The offsetKey to be provided in the next request to get the next page of  resources.  */
    @SerialName("nextPageOffsetKey")
    val nextPageOffsetKey: kotlin.String? = null,

    /* true if there is a further page of resources, false otherwise. */
    @SerialName("hasNext")
    val hasNext: kotlin.Boolean? = null,

    @SerialName("items")
    val items: kotlin.collections.List<Upload>? = null,

    )

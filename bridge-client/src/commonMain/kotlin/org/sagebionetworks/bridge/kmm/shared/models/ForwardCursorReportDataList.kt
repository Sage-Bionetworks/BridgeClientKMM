package org.sagebionetworks.bridge.kmm.shared.models

import kotlinx.serialization.SerialName


/**
 *
 * @param nextPageOffsetKey The offsetKey to be provided in the next request to get the next page of  resources.
 * @param hasNext true if there is a further page of resources, false otherwise.
 * @param items list of reports
 */
@kotlinx.serialization.Serializable
internal data class ForwardCursorReportDataList(

    /* The offsetKey to be provided in the next request to get the next page of  resources.  */
    @SerialName("nextPageOffsetKey")
    val nextPageOffsetKey: String? = null,

    /* true if there is a further page of resources, false otherwise. */
    @SerialName("hasNext")
    val hasNext: Boolean = false,

    @SerialName("items")
    val items: List<ReportData>,

    @SerialName("type")
    val type: String? = null

)

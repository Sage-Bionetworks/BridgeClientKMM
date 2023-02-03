package org.sagebionetworks.bridge.kmm.shared.models

import kotlinx.serialization.SerialName

@kotlinx.serialization.Serializable
internal data class EnrollmentDetailList(
    @SerialName("requestParams")
    val requestParams: RequestParams? = null,
    /* ResourceList */

    @SerialName("type")
    val type: kotlin.String? = null,

    /* The total number of records in the items list */
    @SerialName("total")
    val total: kotlin.Int,

    @SerialName("items")
    val items: kotlin.collections.List<EnrollmentDetail>,
)

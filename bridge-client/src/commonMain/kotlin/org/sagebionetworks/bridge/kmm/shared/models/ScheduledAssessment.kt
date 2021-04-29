/**
* Bridge Server API
* No description provided (generated by Openapi Generator https://github.com/openapitools/openapi-generator)
*
* OpenAPI spec version: 0.21.18
* 
*
* NOTE: This class is auto generated by the swagger code generator program.
* https://github.com/swagger-api/swagger-codegen.git
* Do not edit the class manually.
*/
package org.sagebionetworks.bridge.kmm.shared.models

import kotlinx.serialization.Serializable

import kotlinx.serialization.SerialName

/**
 * The `refKey` of this object will refer to the `key` value of an AssessmentInfo object in the assessments of the timeline. The `instanceGuid` is a unique GUID to identify any data that is generated from the execution of this scheduled assessment. This allows scientists to contextualize data based on when it was gathered in the execution of the study’s schedule.
 * @param refKey 
 * @param instanceGuid 
 * @param type ScheduledAssessment
 */
@Serializable
data class ScheduledAssessment (
    @SerialName("refKey")
    val refKey: kotlin.String? = null,
    @SerialName("instanceGuid")
    val instanceGuid: kotlin.String? = null,
    /* ScheduledAssessment */
    @SerialName("type")
    val type: kotlin.String? = null
) {

}

/**
* Bridge Server API
* No description provided (generated by Openapi Generator https://github.com/openapitools/openapi-generator)
*
* OpenAPI spec version: 0.22.11
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
 * 
 * @param placeName 
 * @param street 
 * @param mailRouting 
 * @param city 
 * @param division 
 * @param postalCode 
 * @param country 
 * @param type Address
 */
@Serializable
data class Address (
    @SerialName("placeName")
    val placeName: String? = null,
    @SerialName("street")
    val street: String? = null,
    @SerialName("mailRouting")
    val mailRouting: String? = null,
    @SerialName("city")
    val city: String? = null,
    @SerialName("division")
    val division: String? = null,
    @SerialName("postalCode")
    val postalCode: String? = null,
    @SerialName("country")
    val country: String? = null,
    /* Address */
    @SerialName("type")
    val type: String? = null
)

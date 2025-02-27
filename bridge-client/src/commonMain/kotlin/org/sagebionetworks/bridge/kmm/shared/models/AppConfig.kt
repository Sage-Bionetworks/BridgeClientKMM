/**
* Bridge Server API
* No description provided (generated by Openapi Generator https://github.com/openapitools/openapi-generator)
*
* OpenAPI spec version: 0.16.25
* 
*
* NOTE: This class is auto generated by the swagger code generator program.
* https://github.com/swagger-api/swagger-codegen.git
* Do not edit the class manually.
*/
package org.sagebionetworks.bridge.kmm.shared.models

import kotlinx.serialization.SerialName
import kotlinx.serialization.Serializable
import kotlinx.serialization.json.JsonElement

/**
 * An app configuration object. 
 * @param label 
 * @param createdOn The date and time the app config was created.
 * @param modifiedOn The date and time the app config was last modified.
 * @param guid 
 * @param deleted Has this app config been logically deleted (an admin can restore it)?
 * @param criteria 
 * @param clientData An arbitrary object that will be serialized and stored as JSON using the GSON serialization mechanisms. In Java this field is an Object; since the type of the object is not known, the rest-client includes a utility method: ``` MyCustomObject data = RestUtils.toType(     activity.getClientData(), MyCustomObject.class); ``` 
 * @param surveyReferences 
 * @param schemaReferences 
 * @param configReferences 
 * @param fileReferences 
 * @param configElements A map of app config element IDs to the app config element JSON of a specific app config element revision (the revision given in the configReferences map). 
 * @param version The optimistic locking version of the app config. This value must be submitted as part of the next update of the model. If it does not match the value on the server, a 409 error (Conflict) will prevent the update from occurring. It can also serve as a key to determine if a local cache of `AppConfig` needs to be updated. 
 * @param type AppConfig
 */
@Serializable
data class AppConfig (
    @SerialName("label")
    val label: String,
    /* The date and time the app config was created. */
    @SerialName("createdOn")
    val createdOn: String? = null,
    /* The date and time the app config was last modified. */
    @SerialName("modifiedOn")
    val modifiedOn: String? = null,
    @SerialName("guid")
    val guid: String? = null,
    /* Has this app config been logically deleted (an admin can restore it)? */
    @SerialName("deleted")
    val deleted: Boolean? = null,
    @SerialName("criteria")
    val criteria: Criteria? = null,
    /* An arbitrary object that will be serialized and stored as JSON using the GSON serialization mechanisms. In Java this field is an Object; since the type of the object is not known, the rest-client includes a utility method: ``` MyCustomObject data = RestUtils.toType(     activity.getClientData(), MyCustomObject.class); ```  */
    @SerialName("clientData")
    val clientData: JsonElement? = null,
    @SerialName("surveyReferences")
    val surveyReferences: List<SurveyReference>? = null,
    @SerialName("schemaReferences")
    val schemaReferences: List<SchemaReference>? = null,
    @SerialName("configReferences")
    val configReferences: List<ConfigReference>? = null,
    @SerialName("fileReferences")
    val fileReferences: List<FileReference>? = null,
    /* A map of app config element IDs to the app config element JSON of a specific app config element revision (the revision given in the configReferences map).  */
    @SerialName("configElements")
    val configElements: Map<String, JsonElement>? = null,
    /* The optimistic locking version of the app config. This value must be submitted as part of the next update of the model. If it does not match the value on the server, a 409 error (Conflict) will prevent the update from occurring. It can also serve as a key to determine if a local cache of `AppConfig` needs to be updated.  */
    @SerialName("version")
    val version: Long? = null,
    /* AppConfig */
    @SerialName("type")
    val type: String? = null
)


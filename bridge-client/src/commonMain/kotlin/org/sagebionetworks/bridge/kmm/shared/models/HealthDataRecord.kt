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

import kotlinx.serialization.Serializable
import kotlinx.serialization.SerialName

/**
 * See [Bridge Upload Data Format](/articles/study_design/upload_data_format.html) for details about this model object. Only researchers and administrators can retrieve this full record through an upload record in the API. 
 * @param appVersion App version, as reported by the app. Generally in the form \"version 1.0.0, build 2\". Must be 48 chars or less. 
 * @param createdOn ISO timestamp of when the data record was created, as reported by the submitting app
 * @param createdOnTimeZone The original timezone of the createdOn timestamp, expressed as a 4-digit string with sign. For example, -0800, +0900
 * @param &#x60;data&#x60; JSON map with key value pairs representing the record's data.
 * @param dayInStudy How many calendar days the participant has been in the study. For example, if the participant started on | 2019-07-24, then 2019-07-24 is day 1, 2019-07-25 is day 2, etc. Calendar days are calculated using the | same timezone as the Bridge Exporter (ie, America/Los_Angeles). 
 * @param id A unique GUID for this record.
 * @param metadata Arbitrary JSON blob of record metadata, as submitted by the app. For ResearchKit-based apps, this is info.json verbatim. 
 * @param phoneInfo Phone info, for example \"iPhone9,3\" or \"iPhone 5c (GSM)\". Must be 48 chars or less.
 * @param rawDataAttachmentId Attachment ID (S3 key) that contains the raw data. This is the unencrypted zip file for uploads, or JSON blob for directly submitted records 
 * @param schemaId [UploadSchema](#UploadSchema) ID for the record. 
 * @param schemaRevision [UploadSchema](#UploadSchema) revision for the record. 
 * @param appId App that this record lives in.
 * @param uploadDate Calendar date in YYYY-MM-DD format representing when the server received the upload, using the server's local time zone (US Pacific timezone). 
 * @param uploadId The upload GUID of the upload this record is processed from.
 * @param uploadedOn The date and time of the upload.
 * @param userMetadata JSON map with key value pairs representing metadata for this health data record, as submitted by the app. This corresponds with the uploadMetadataFieldDefinitions configured in the study. 
 * @param userSharingScope 
 * @param userExternalId The user's external ID at the time of this upload's submission.
 * @param userDataGroups The user's data groups at the time of this upload's submission.
 * @param userSubstudyMemberships A map where the keys are the substudy IDs assigned to the user at the time that user generated this  health data, and the values are the external IDs that were assigned to the user for each substudy (if no external ID was assigned, the value will be an empty string). 
 * @param validationErrors Error messages related to upload validation. Only generated if UploadValidationStrictness is set to REPORT.
 * @param version A version number issued for optimistic locking of record updates. Should not be set when creating a new health data record. When updating a record retrieved from the API, the object will have the version attribute and this must match the last value issued by the service or an update will fail. 
 * @param synapseExporterStatus 
 * @param type HealthDataRecord
 */
@Serializable
internal data class HealthDataRecord (
    /* The user's data groups at the time of this upload's submission. */
    @SerialName("userDataGroups")
    val userDataGroups: List<String>? = null,
    /* App version, as reported by the app. Generally in the form \"version 1.0.0, build 2\". Must be 48 chars or less.  */
    @SerialName("appVersion")
    val appVersion: String? = null,
    /* ISO timestamp of when the data record was created, as reported by the submitting app */
    @SerialName("createdOn")
    val createdOn: String? = null,
    /* The original timezone of the createdOn timestamp, expressed as a 4-digit string with sign. For example, -0800, +0900 */
    @SerialName("createdOnTimeZone")
    val createdOnTimeZone: String? = null,
    /* JSON map with key value pairs representing the record's data. */
    @SerialName("data")
    val `data`: kotlinx.serialization.json.JsonElement? = null,
    /* How many calendar days the participant has been in the study. For example, if the participant started on | 2019-07-24, then 2019-07-24 is day 1, 2019-07-25 is day 2, etc. Calendar days are calculated using the | same timezone as the Bridge Exporter (ie, America/Los_Angeles).  */
    @SerialName("dayInStudy")
    val dayInStudy: Int? = null,
    /* A unique GUID for this record. */
    @SerialName("id")
    val id: String? = null,
    /* Arbitrary JSON blob of record metadata, as submitted by the app. For ResearchKit-based apps, this is info.json verbatim.  */
    @SerialName("metadata")
    val metadata: kotlinx.serialization.json.JsonElement? = null,
    /* Phone info, for example \"iPhone9,3\" or \"iPhone 5c (GSM)\". Must be 48 chars or less. */
    @SerialName("phoneInfo")
    val phoneInfo: String? = null,
    /* Attachment ID (S3 key) that contains the raw data. This is the unencrypted zip file for uploads, or JSON blob for directly submitted records  */
    @SerialName("rawDataAttachmentId")
    val rawDataAttachmentId: String? = null,
    /* [UploadSchema](#UploadSchema) ID for the record.  */
    @SerialName("schemaId")
    val schemaId: String? = null,
    /* [UploadSchema](#UploadSchema) revision for the record.  */
    @SerialName("schemaRevision")
    val schemaRevision: Long? = null,
    /* App that this record lives in. */
    @SerialName("appId")
    val appId: String? = null,
    /* Calendar date in YYYY-MM-DD format representing when the server received the upload, using the server's local time zone (US Pacific timezone).  */
    @SerialName("uploadDate")
    val uploadDate: String? = null,
    /* The upload GUID of the upload this record is processed from. */
    @SerialName("uploadId")
    val uploadId: String? = null,
    /* The date and time of the upload. */
    @SerialName("uploadedOn")
    val uploadedOn: String? = null,
    /* JSON map with key value pairs representing metadata for this health data record, as submitted by the app. This corresponds with the uploadMetadataFieldDefinitions configured in the study.  */
    @SerialName("userMetadata")
    val userMetadata: kotlinx.serialization.json.JsonElement? = null,
    @SerialName("userSharingScope")
    val userSharingScope: SharingScope? = null,
    /* The user's external ID at the time of this upload's submission. */
    @SerialName("userExternalId")
    val userExternalId: String? = null,
    /* A map where the keys are the substudy IDs assigned to the user at the time that user generated this  health data, and the values are the external IDs that were assigned to the user for each substudy (if no external ID was assigned, the value will be an empty string).  */
    @SerialName("userSubstudyMemberships")
    val userSubstudyMemberships: Map<String, String>? = null,
    /* Error messages related to upload validation. Only generated if UploadValidationStrictness is set to REPORT. */
    @SerialName("validationErrors")
    val validationErrors: String? = null,
    /* A version number issued for optimistic locking of record updates. Should not be set when creating a new health data record. When updating a record retrieved from the API, the object will have the version attribute and this must match the last value issued by the service or an update will fail.  */
    @SerialName("version")
    val version: Long? = null,
    @SerialName("synapseExporterStatus")
    val synapseExporterStatus: SynapseExporterStatus? = null,
    /* HealthDataRecord */
    @SerialName("type")
    val type: String? = null
)


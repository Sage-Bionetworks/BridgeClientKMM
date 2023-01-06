package org.sagebionetworks.bridge.kmm.shared.models

import kotlinx.serialization.Serializable

import kotlinx.serialization.SerialName


/**
 * @param appId The app ID of the app the participant is joining.
 * @param email The user's email. Users can use the same email for different studies, but their account is identified by the email within an app.
 * @param phone
 * @param externalId An externally-assignable identifier a research partner can use to re-identify a user's data in the exported data set (this must be provided by the application, it is not created by Bridge). The value can be set on creation or added on an account update, but it will be returned in the `externalIds` mapping which specifies the study within which the external ID was defined. This field will be null when retrieved from the server.
 * @param password User's password.
 * @param consent **Create user API for admins only.** Create this user consented to all required consents. For testing purposes only.
 * @param firstName First name (given name) of the user.
 * @param lastName Last name (family name) of the user.
 * @param synapseUserId The numerical identifier for a Synapse account. For administrative accounts, this will allow the user to sign in using Synapse accounts, no further credentials are needed to access the system. This value can only be set when creating an account; otherwise the identifiers update API must be used to add the ID to an existing account.
 * @param notifyByEmail True if the user has consented to be contacted via email outside the application, false otherwise.
 * @param attributes A map of user profile attributes that have been set for this user (the attributes themselves must be specified in the app's configuration, and the values are stored encrypted in case they capture personally-identifying information).
 * @param sharingScope
 * @param roles
 * @param dataGroups The data groups set for this user. Data groups must be strings that are defined in the list of all valid data groups for the app, as part of the app object.
 * @param clientData Client data for a user should be in a syntactically valid JSON format. It will be returned as is to the client (as JSON).
 * @param languages Two letter language codes to assign to this user (these are initially retrieved from the user's `Accept-Language` header and then persisted as part of account configuration).
 * @param studyIds The studies this participant is associated to. For administrative accounts, these are the studies associated to the account's organization. For study participants, these will be the studies that the person is enrolled in.
 * @param externalIds The exernal IDs this participant is associated to, mapped to the study that issued the external ID. Typically a user signs up with the external ID, and is assigned to that study as a result.
 * @param orgMembership The identifier of the organization this account is a member of (this will be an administrative account and not a study participant). Once set, it cannot be changed on an update (there are separate organization membership APIs to change organizational membership).
 * @param note Optional note related to user account. Can only be edited and viewed by an administrative account.
 * @param clientTimeZone Participant's time zone. Can be updated or deleted. Must be an IANA time zone name.
 */
@Serializable
internal data class SignUp (

    /* The app ID of the app the participant is joining. */
    @SerialName("appId")
    val appId: String,

    /* The user's email. Users can use the same email for different studies, but their account is identified by the email within an app.  */
    @SerialName("email")
    val email: String? = null,

    @SerialName("phone")
    val phone: Phone? = null,

    /* An externally-assignable identifier a research partner can use to re-identify a user's data in the exported data set (this must be provided by the application, it is not created by Bridge). The value can be set on creation or added on an account update, but it will be returned in the `externalIds` mapping which specifies the study within which the external ID was defined. This field will be null when retrieved from the server.  */
    @SerialName("externalId")
    val externalId: String? = null,

    /* User's password. */
    @SerialName("password")
    val password: String? = null,

    /* **Create user API for admins only.** Create this user consented to all required consents. For testing purposes only.  */
    @SerialName("consent")
    val consent: Boolean? = null,

    /* First name (given name) of the user. */
    @SerialName("firstName")
    val firstName: String? = null,

    /* Last name (family name) of the user. */
    @SerialName("lastName")
    val lastName: String? = null,

    /* The numerical identifier for a Synapse account. For administrative accounts, this will allow the user to sign in using Synapse accounts, no further credentials are needed to access the system. This value can only be set when creating an account; otherwise the identifiers update API must be used to add the ID to an existing account.  */
    @SerialName("synapseUserId")
    val synapseUserId: String? = null,

    /* True if the user has consented to be contacted via email outside the application, false otherwise.  */
    @SerialName("notifyByEmail")
    val notifyByEmail: Boolean = true,

    /* A map of user profile attributes that have been set for this user (the attributes themselves must be specified in the app's configuration, and the values are stored encrypted in case they capture personally-identifying information).  */
    @SerialName("attributes")
    val attributes: Map<String, String>? = null,

    @SerialName("sharingScope")
    val sharingScope: SharingScope? = null,

    @SerialName("roles")
    val roles: List<Role>? = null,

    /* The data groups set for this user. Data groups must be strings that are defined in the list of all valid data groups for the app, as part of the app object.   */
    @SerialName("dataGroups")
    val dataGroups: List<String>? = null,

    /* Client data for a user should be in a syntactically valid JSON format. It will be returned as is to the client (as JSON).  */
    @SerialName("clientData")
    val clientData: kotlinx.serialization.json.JsonObject? = null,

    /* Two letter language codes to assign to this user (these are initially retrieved from the user's `Accept-Language` header and then persisted as part of account configuration).   */
    @SerialName("languages")
    val languages: List<String>? = null,

    /* The studies this participant is associated to. For administrative accounts, these are the studies associated to the account's organization. For study participants, these will be the studies that the person is enrolled in. */
    @SerialName("studyIds")
    val studyIds: List<String>? = null,

    /* The exernal IDs this participant is associated to, mapped to the study that issued the external ID. Typically a user signs up with the external ID, and is assigned to that study as a result. */
    @SerialName("externalIds")
    val externalIds: Map<String, String>? = null,
    
    /* The identifier of the organization this account is a member of (this will be an administrative account and not a study participant). Once set, it cannot be changed on an update (there are separate organization membership APIs to change organizational membership). */
    @SerialName("orgMembership")
    val orgMembership: String? = null,

    /* Optional note related to user account. Can only be edited and viewed by an administrative account. */
    @SerialName("note")
    val note: String? = null,

    /* Participant's time zone. Can be updated or deleted. Must be an IANA time zone name.  */
    @SerialName("clientTimeZone")
    val clientTimeZone: String? = null

) {

}


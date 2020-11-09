package org.sagebionetworks.bridge.kmm.shared.models

import kotlinx.serialization.Serializable

import kotlinx.serialization.SerialName

/**
 * To consent to participation in a subpopulation (also known as a consent group), participants submit their electronic signature. This can include an image of their actual signature.   At the time of consent, participants also submit a decision on how widely they will share their medical information with researchers (see the scope property of the ConsentSignature JSON object, below).  How you describe to participants the choice to share research data is important if they are to correctly understand the consequences of this decision. We suggest that applications present the following language to users when making this choice:  * **Option #1:** No data sharing. I do not agree to share my coded data (without my name) at this time; * **Option #2:** I agree to share my coded data (without my name) with researchers at the sponsor institution, and their partners, in order to conduct this study; * **Option #3:** I agree to share my coded data (without my name) with qualified researchers worldwide, for general health research.  Note that if your study does re-identify participants in the study, this language will have to be adjusted.
 * @param name The participant's name.
 * @param birthdate The participant's date of birth in ISO 8601 format (YYYY-MM-DD).
 * @param imageData Base 64 encoded image of the participant's signature. If `imageData` is supplied, `imageMimeType` must also be supplied.
 * @param imageMimeType Mime type of this image (e.g. \"image/png\"). If `imageData` is supplied, `imageMimeType` must also be supplied.
 * @param signedOn The date and time the referenced consent was signed and agreed to by the participant.
 * @param withdrewOn The date and time the participant withdrew consent (can be blank).
 * @param scope
 * @param type ConsentSignature
 */
@Serializable
internal data class ConsentSignature (
    /* The participant's name. */
    @SerialName("name")
    val name: kotlin.String,
    @SerialName("scope")
    val scope: SharingScope,
    /* The participant's date of birth in ISO 8601 format (YYYY-MM-DD). */
    @SerialName("birthdate")
    val birthdate: kotlin.String? = null,
    /* Base 64 encoded image of the participant's signature. If `imageData` is supplied, `imageMimeType` must also be supplied.  */
    @SerialName("imageData")
    val imageData: kotlin.String? = null,
    /* Mime type of this image (e.g. \"image/png\"). If `imageData` is supplied, `imageMimeType` must also be supplied.  */
    @SerialName("imageMimeType")
    val imageMimeType: kotlin.String? = null,
    /* The date and time the referenced consent was signed and agreed to by the participant. */
    @SerialName("signedOn")
    val signedOn: kotlin.String? = null,
    /* The date and time the participant withdrew consent (can be blank). */
    @SerialName("withdrewOn")
    val withdrewOn: kotlin.String? = null,
    /* ConsentSignature */
    @SerialName("type")
    val type: kotlin.String? = null
) {

}
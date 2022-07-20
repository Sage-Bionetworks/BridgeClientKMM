package org.sagebionetworks.bridge.kmm.shared.models

import kotlinx.datetime.Instant
import kotlinx.serialization.SerialName
import kotlinx.serialization.Serializable

@Serializable
class StudyActivityEventRequest (

    /* event identifier */
    @SerialName("eventId")
    val eventId: String,
    /* ISO 8601 date and time that the event occurred */
    @SerialName("timestamp")
    val timestamp: Instant,
    /* answer value for a question event */
    @SerialName("answerValue")
    val answerValue: String? = null,
    /* An IANA Time Zone Database (TZDB) name for the participant’s time zone at the time the record is submitted.
     If present, this field will be validated to be a valid time zone name. */
    @SerialName("clientTimeZone")
    val clientTimeZone: String? = null,
    /* CustomActivityEventRequest */
    @SerialName("type")
    val type: String? = "CustomActivityEventRequest"

)

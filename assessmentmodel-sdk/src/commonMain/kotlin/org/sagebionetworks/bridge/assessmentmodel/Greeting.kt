package org.sagebionetworks.bridge.assessmentmodel

class Greeting {
    fun greeting(): String {
        return "Hello, ${Platform().platform}!"
    }
}
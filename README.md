# BridgeClientKMM
A Kotlin Multiplatform Mobile [Bridge](https://developer.sagebridge.org/index.html) client built using Kotlin Serialization, Ktor, and Sqldelight.
#### Android

Kotlin DSL:

```kotlin
repositories {
    maven(url = "https://sagebionetworks.jfrog.io/artifactory/mobile-sdks/")
}

dependencies {
    //Core library
    implementation("org.sagebionetworks.bridge.kmm:bridge-client:0.3.1")
    //Support for archiving results from AssessmentModelKMM
    implementation("org.sagebionetworks.bridge.kmm:assessmentmodel-sdk:0.3.1")
}
```

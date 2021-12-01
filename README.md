# BridgeClientKMM
A Kotlin Multiplatform Mobile [Bridge](https://developer.sagebridge.org/index.html) client based on a repository design pattern, built using Kotlin Serialization, Ktor, and Sqldelight.

[Class Documentation](https://sage-bionetworks.github.io/BridgeClientKMM/)
#### Android

Kotlin DSL:

```kotlin
repositories {
    maven(url = "https://sagebionetworks.jfrog.io/artifactory/mobile-sdks/")
}

dependencies {
    //Core library
    implementation("org.sagebionetworks.bridge.kmm:bridge-client:0.3.2")
    //Support for archiving results from AssessmentModelKMM
    implementation("org.sagebionetworks.bridge.kmm:assessmentmodel-sdk:0.3.2")
}
```

BridgeClientKMM uses Koin for dependency injection and should be initialized as shown below:
```kotlin
class ExampleApplication : MultiDexApplication(), KoinComponent {

    override fun onCreate() {
        super.onCreate()

        initKoin (enableNetworkLogs = BuildConfig.DEBUG){
            androidLogger(Level.ERROR)
            androidContext(this@ExampleApplication)
            workManagerFactory()
            //Add any additional Koin modules here
            //modules(appModule)
        }
    }
}
```
To support encrypting uploads, place your study_public_key.pem in your app's assets directory.

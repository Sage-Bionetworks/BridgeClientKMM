buildscript {

    repositories {
        gradlePluginPortal()
        jcenter()
        google()
        mavenCentral()
        maven(url = "https://kotlin.bintray.com/kotlinx/")
    }
    dependencies {
        classpath("org.jetbrains.kotlin:kotlin-gradle-plugin:${Versions.kotlin}")
        classpath("com.android.tools.build:gradle:4.1.3")
        classpath("com.squareup.sqldelight:gradle-plugin:${Versions.sqlDelight}")
        classpath("org.jetbrains.kotlin:kotlin-serialization:${Versions.kotlin}")
        classpath("com.github.dcendents:android-maven-gradle-plugin:2.1")
    }
}

allprojects {
    group = "org.sagebionetworks.bridge.kmm"
    version = "0.2.9"
    repositories {
        jcenter()
        google()
        mavenCentral()
        maven(url = "http://repo-maven.sagebridge.org/")
        maven(url = "https://kotlin.bintray.com/kotlinx/")
        maven(url = "https://dl.bintray.com/sage-bionetworks/AssessmentModel-KotlinNative")
        maven(url = "https://dl.bintray.com/sage-bionetworks/BridgeClientKMM")
    }
}

buildscript {

    repositories {
        gradlePluginPortal()
        google()
        mavenCentral()
    }
    dependencies {
        classpath("org.jetbrains.kotlin:kotlin-gradle-plugin:${Versions.kotlin}")
        classpath("com.android.tools.build:gradle:7.0.3")
        classpath("com.squareup.sqldelight:gradle-plugin:${Versions.sqlDelight}")
        classpath("org.jetbrains.kotlin:kotlin-serialization:${Versions.kotlin}")
    }

}

plugins {
    id("maven-publish")
}

allprojects {
    group = "org.sagebionetworks.bridge.kmm"
    extra["sdkVersionCode"] = 1
    version = "0.3.2"
    extra["versionName"] = "android-sdk v${version}"

    repositories {
        google()
        mavenCentral()
        maven {
            url = uri("http://repo-maven.sagebridge.org/")
            isAllowInsecureProtocol = true
        }

        maven(url = "https://sagebionetworks.jfrog.io/artifactory/mobile-sdks/")
    }
}

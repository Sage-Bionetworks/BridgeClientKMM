buildscript {

    repositories {
        gradlePluginPortal()
        google()
        mavenCentral()
    }
    dependencies {
        classpath("org.jetbrains.kotlin:kotlin-gradle-plugin:${Versions.kotlin}")
        classpath("com.android.tools.build:gradle:7.1.3")
        classpath("com.squareup.sqldelight:gradle-plugin:${Versions.sqlDelight}")
        classpath("org.jetbrains.kotlin:kotlin-serialization:${Versions.kotlin}")
        classpath("dev.icerock.moko:network-generator:0.16.0")
    }

}

plugins {
    id("org.jetbrains.dokka") version "1.6.0"
    id("maven-publish")
}

tasks.dokkaHtmlMultiModule {
    outputDirectory.set(rootDir.resolve("build/dokka"))
}

allprojects {
    group = "org.sagebionetworks.bridge.kmm"
    extra["sdkVersionCode"] = 1
    version = "0.7.0"
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

    tasks.withType<org.jetbrains.dokka.gradle.DokkaTaskPartial>().configureEach {
        dokkaSourceSets {
            configureEach {
                includes.from(rootProject.file("dokka/moduledoc.md").path)
            }
        }
    }
}

buildscript {

    repositories {
        gradlePluginPortal()
        google()
        mavenCentral()
        maven("https://plugins.gradle.org/m2/")
    }
    dependencies {
        classpath(libs.bundles.gradlePlugins)
        classpath("dev.icerock.moko:network-generator:0.16.0")
    }

}

plugins {
    id("org.jetbrains.dokka") version "1.6.0"
    id("maven-publish")
//    id("org.jetbrains.kotlinx.kover") version "0.6.1"
}

// TODO: syoung 02/15/2022 Figure out why this plugin doesn't work on my machine.
//koverMerged {
//    enable()
//
//    htmlReport {
//        // set to true to run koverHtmlReport task during the execution of the check task (if it exists) of the current project
//        onCheck.set(true)
//    }
//
//    filters {
//
//        projects {
//            excludes += listOf("androidApp", "bridge-client-presentation")
//        }
//    }
//}

tasks.dokkaHtmlMultiModule {
    outputDirectory.set(rootDir.resolve("build/dokka"))
}

allprojects {
    group = "org.sagebionetworks.bridge.kmm"
    extra["sdkVersionCode"] = 1
    version = "0.18.2"
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
// TODO: syoung 02/15/2022 Figure out why this plugin doesn't work on my machine.
//    apply(plugin = "kover")
}

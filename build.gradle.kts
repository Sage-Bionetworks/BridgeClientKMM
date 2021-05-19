buildscript {

    repositories {
        gradlePluginPortal()
        google()
        mavenCentral()
    }
    dependencies {
        classpath("org.jetbrains.kotlin:kotlin-gradle-plugin:${Versions.kotlin}")
        classpath("com.android.tools.build:gradle:4.1.3")
        classpath("com.squareup.sqldelight:gradle-plugin:${Versions.sqlDelight}")
        classpath("org.jetbrains.kotlin:kotlin-serialization:${Versions.kotlin}")
    }

}

plugins {
    id("maven-publish")
}

allprojects {
    group = "org.sagebionetworks.bridge.kmm"
    version = "0.2.15"
    repositories {
        google()
        mavenCentral()
        maven(url = "http://repo-maven.sagebridge.org/")
        maven(url = "https://sagebionetworks.jfrog.io/artifactory/mobile-sdks/")
    }
    configurations.all {
        resolutionStrategy.eachDependency(Action {
            with(requested) {
                // remove after our transitive dependencies migrate - liujoshua 05/06/2021
                if (group == "org.koin") {
                    useTarget( "io.insert-koin:${name}:${version}")
                    because("Koin moved groups")
                }
                if (group == "org.jetbrains.kotlin") {
                    if (name.startsWith("kotlin-stdlib")) {
                        useTarget("org.jetbrains.kotlin:${name}:${Versions.kotlin}")
                    }
                }
            }
        })
    }
}

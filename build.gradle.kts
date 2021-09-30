buildscript {

    repositories {
        gradlePluginPortal()
        google()
        mavenCentral()
    }
    dependencies {
        classpath("org.jetbrains.kotlin:kotlin-gradle-plugin:${Versions.kotlin}")
        classpath("com.android.tools.build:gradle:4.2.1")
        classpath("com.squareup.sqldelight:gradle-plugin:${Versions.sqlDelight}")
        classpath("org.jetbrains.kotlin:kotlin-serialization:${Versions.kotlin}")
    }

}

plugins {
    id("maven-publish")
}

allprojects {
    group = "org.sagebionetworks.bridge.kmm"
    version = "0.2.24"
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
                // Needed due to dependency on kotlinx.datetime 0.2 which depends on kotlin 1.5.0
                // Remove after project moves to kotlin 1.5 -nbrown 5/19/2021
                if (group == "org.jetbrains.kotlin") {
                    if (name.startsWith("kotlin-stdlib")) {
                        useTarget("org.jetbrains.kotlin:${name}:${Versions.kotlin}")
                    }
                }
            }
        })
    }
}

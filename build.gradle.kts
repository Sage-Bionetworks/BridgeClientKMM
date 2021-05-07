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
        classpath("org.jfrog.buildinfo:build-info-extractor-gradle:4.21.0")
    }

}

plugins {
    id("maven-publish")
    id( "com.jfrog.artifactory") version "4.21.0"
}

allprojects {
    group = "org.sagebionetworks.bridge.kmm"
    version = "0.2.10"
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

artifactory {
    setContextUrl("https://sagebionetworks.jfrog.io/artifactory")
    publish(delegateClosureOf<org.jfrog.gradle.plugin.artifactory.dsl.PublisherConfig> {
        repository(delegateClosureOf<org.jfrog.gradle.plugin.artifactory.dsl.DoubleDelegateWrapper> {
            val username = System.getenv("artifactoryUser")
            val password = System.getenv("artifactoryPwd")
            setProperty("repoKey", "mobile-sdks")
            setProperty("username", username)
            setProperty("password", password)
            setProperty("maven", true)
        })
        defaults(delegateClosureOf<groovy.lang.GroovyObject> {
            invokeMethod("publications", kotlin.arrayOf(
                "ALL_PUBLICATIONS"
            )
            )
            setProperty("publishArtifacts", true)
        })
    })
}

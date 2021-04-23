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
        classpath("com.android.tools.build:gradle:4.1.2")
        classpath("com.squareup.sqldelight:gradle-plugin:${Versions.sqlDelight}")
        classpath("org.jetbrains.kotlin:kotlin-serialization:${Versions.kotlin}")
        classpath("com.github.dcendents:android-maven-gradle-plugin:2.1")
    }
}

allprojects {
    group = "org.sagebionetworks.bridge.kmm"
    version = "0.2.7"
    repositories {
        jcenter()
        google()
        mavenCentral()
        maven(url = "https://kotlin.bintray.com/kotlinx/")
        maven(url = "https://dl.bintray.com/ekito/koin")
        // Using snapshot build of kotlinx.datetime so we can use date parsing
        maven(url = "https://teamcity.jetbrains.com/guestAuth/app/rest/builds/buildType:(KotlinTools_KotlinxDatetime_Build_All),status:success,branch:master/artifacts/content/maven/")
    }
}

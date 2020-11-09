buildscript {

    val kotlin_version by extra("1.4.10")
    val sqlDelightVersion: String by project
    val kotlinVersion: String by project

    repositories {
        gradlePluginPortal()
        jcenter()
        google()
        mavenCentral()
        maven(url = "https://kotlin.bintray.com/kotlinx/")
    }
    dependencies {
        classpath("org.jetbrains.kotlin:kotlin-gradle-plugin:1.4.10")
        classpath("com.android.tools.build:gradle:4.1.0")
        classpath("com.squareup.sqldelight:gradle-plugin:$sqlDelightVersion")
        classpath("org.jetbrains.kotlin:kotlin-serialization:$kotlinVersion")
    }
}
group = "org.sagebionetworks.bridge.kmm"
version = "1.0-SNAPSHOT"

repositories {
    mavenCentral()
    maven(url = "https://kotlin.bintray.com/kotlinx/")
}

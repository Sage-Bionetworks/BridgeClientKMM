plugins {
    id("com.android.library")
    kotlin("android")
    id("kotlin-android")
    id ("maven-publish")
    id( "com.jfrog.artifactory")
}

android {
    compileSdkVersion(Versions.compile_sdk)
    defaultConfig {
        minSdkVersion(Versions.min_sdk)
        targetSdkVersion(Versions.target_sdk)
        versionCode = 1
        versionName = "android-sdk v${version}"
        buildConfigField("int", "VERSION_CODE", "${versionCode}")
        buildConfigField("String", "VERSION_NAME", "\"${versionName}\"")
        testInstrumentationRunner = "androidx.test.runner.AndroidJUnitRunner"
    }
    buildTypes {
        getByName("release") {
            isMinifyEnabled = false
        }
    }
    compileOptions {
        sourceCompatibility = JavaVersion.VERSION_1_8
        targetCompatibility = JavaVersion.VERSION_1_8
    }
    kotlinOptions {
        jvmTarget = "1.8"
    }
    buildFeatures {
        viewBinding = true
    }
}


dependencies {
        val assessment_version = "0.4.4"
        api(project(":bridge-client"))
        api("org.sagebionetworks.assessmentmodel:assessmentModel:$assessment_version")

        implementation(project(":bridge-client-presentation"))
        implementation("org.sagebionetworks.assessmentmodel:presentation:$assessment_version")

        api(Deps.Koin.android)

        // legacy Bridge dependencies
        // migrate to use kotlinx/java8 time and see if we can publish multi-platform
        // which will work with bridge - liujoshua 04/02/21
        implementation("org.sagebionetworks:BridgeDataUploadUtils:0.2.6") {
            exclude("joda-time", "joda-time")
            exclude("org.bouncycastle")
            exclude("com.madgag.spongycastle")
        }
        api("net.danlew:android.joda:2.9.9.4")
        val spongycastle = "1.58.0.0"
        implementation("com.madgag.spongycastle:core:$spongycastle")
        implementation("com.madgag.spongycastle:prov:$spongycastle")
        // marked api due to propagation of CMSException
        api("com.madgag.spongycastle:bcpkix-jdk15on:$spongycastle")
    }



publishing {
    publications {
        create<MavenPublication>("aar") {
            artifact("$buildDir/outputs/aar/${project.name}-release.aar")
        }
    }
}

plugins {
    id("com.android.application")
    kotlin("android")
    id("kotlin-android-extensions")
    id("kotlin-android")
}

repositories {
    gradlePluginPortal()
    google()
    jcenter()
    mavenCentral()
    maven(url = "https://kotlin.bintray.com/kotlinx/")
    maven(url = "https://oss.sonatype.org/content/repositories/snapshots")
    maven(url = "https://dl.bintray.com/sage-bionetworks/BridgeClientKMM" )
}
dependencies {
    implementation("org.jetbrains.kotlin:kotlin-stdlib:${Versions.kotlin}")
    implementation(Deps.AndroidX.annotation)
    implementation(project(":bridgeClient"))
    implementation(Deps.AndroidX.material)
    implementation(Deps.AndroidX.appcompat)
    implementation(Deps.AndroidX.constraintlayout)

    implementation(Deps.Koin.android)
    implementation(Deps.Koin.androidWorkManager)
    implementation(Deps.Koin.androidViewModel)

    // ViewModel
    implementation(Deps.AndroidX.lifecycle_viewmodel_ktx)
    // LiveData
    implementation(Deps.AndroidX.lifecycle_livedata_ktx)
}
android {
    compileSdkVersion(Versions.compile_sdk)
    defaultConfig {
        applicationId = "org.sagebionetworks.bridge.kmm.androidApp"
        minSdkVersion(Versions.min_sdk)
        targetSdkVersion(Versions.target_sdk)
        versionCode = 1
        versionName = "$version"
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
}
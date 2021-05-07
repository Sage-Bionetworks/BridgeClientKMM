plugins {
    id("com.android.application")
    kotlin("android")
    id("kotlin-android")
}

dependencies {
    implementation("org.jetbrains.kotlin:kotlin-stdlib:${Versions.kotlin}")
    implementation(Deps.AndroidX.annotation)
    implementation(project(":bridge-client"))
    implementation(project(":bridge-client-presentation"))
    implementation(Deps.AndroidX.material)
    implementation(Deps.AndroidX.appcompat)
    implementation(Deps.AndroidX.constraintlayout)

    implementation(Deps.Koin.android)
    implementation(Deps.Koin.androidWorkManager)

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
plugins {
    id("com.android.application")
    kotlin("android")
    id("kotlin-android")
}

dependencies {
    implementation("org.jetbrains.kotlin:kotlin-stdlib:${libs.versions.kotlin}")
    implementation(libs.androidx.annotation)
    implementation(project(":bridge-client"))
    implementation(project(":bridge-client-presentation"))
    implementation(libs.androidx.material)
    implementation(libs.androidx.appcompat)
    implementation(libs.androidx.constraintlayout)

    implementation(libs.koin.android)
    implementation(libs.koin.android.workmanager)

    // ViewModel
    implementation(libs.androidx.lifecycle.viewmodelKtx)
    // LiveData
    implementation(libs.androidx.lifecycle.livedataKtx)
}
android {
    compileSdk = libs.versions.compileSdk.get().toInt()
    android.buildFeatures.buildConfig = true
    defaultConfig {
        applicationId = "org.sagebionetworks.bridge.kmm.androidApp"
        minSdk = libs.versions.minSdk.get().toInt()
        targetSdk = libs.versions.targetSdk.get().toInt()
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
    namespace = "org.sagebionetworks.bridge.kmm.androidApp"
}
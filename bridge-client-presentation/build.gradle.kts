plugins {
    id("com.android.library")
    kotlin("android")
    id("kotlin-android")
    id ("maven-publish")
}

android {
    compileSdk = libs.versions.compileSdk.get().toInt()
    defaultConfig {
        minSdk = libs.versions.minSdk.get().toInt()
        targetSdk = libs.versions.targetSdk.get().toInt()
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
    namespace = "org.sagebionetworks.bridge.kmm.presentation"
}


dependencies {
    implementation("org.jetbrains.kotlin:kotlin-stdlib:${libs.versions.kotlin}")
    implementation(project(":bridge-client"))
    implementation(libs.androidx.coreKtx)
    implementation(libs.androidx.material)
    implementation(libs.androidx.appcompat)
    implementation(libs.androidx.constraintlayout)

    implementation(libs.koin.android)

    // ViewModel
    implementation(libs.androidx.lifecycle.viewmodelKtx)
    // LiveData
    implementation(libs.androidx.lifecycle.livedataKtx)
    implementation("androidx.legacy:legacy-support-v4:1.0.0")
    implementation("androidx.lifecycle:lifecycle-livedata-ktx:2.5.1")
    implementation("androidx.lifecycle:lifecycle-viewmodel-ktx:2.5.1")

    testImplementation(libs.junit)
    androidTestImplementation("androidx.test.ext:junit:1.1.3")
    androidTestImplementation("androidx.test.espresso:espresso-core:3.4.0")
}

afterEvaluate {
    publishing {
        publications {
            create<MavenPublication>("presentation") {
                from(components.getByName("release"))
            }
        }
    }
}

publishing {
    repositories {
        maven {
            url = uri("https://sagebionetworks.jfrog.io/artifactory/mobile-sdks/")
            credentials {
                username = System.getenv("artifactoryUser")
                password = System.getenv("artifactoryPwd")
            }
        }
    }
}

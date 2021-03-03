import org.jetbrains.kotlin.gradle.plugin.mpp.KotlinNativeTarget

plugins {
    id("com.android.library")
    kotlin("multiplatform")
    id("kotlin-android-extensions")
    id("com.squareup.sqldelight")
    kotlin("plugin.serialization")
    id("com.github.dcendents.android-maven")
}

tasks.withType<org.jetbrains.kotlin.gradle.tasks.KotlinCompile> {
    kotlinOptions.jvmTarget = "1.8"
}

repositories {
    gradlePluginPortal()
    google()
    jcenter()
    mavenCentral()
    maven(url = "https://kotlin.bintray.com/kotlinx/")
    maven(url = "https://oss.sonatype.org/content/repositories/snapshots")
}

sqldelight {
    database("BridgeResourceDatabase") {
        packageName = "org.sagebionetworks.bridge.kmm.shared.cache"
//        schemaOutputDirectory = file("src/schema")
    }
}

kotlin {
    android {
        publishLibraryVariants("release", "debug")
    }
    // Block from https://github.com/cashapp/sqldelight/issues/2044#issuecomment-721299517.
    val iOSTarget: (String, KotlinNativeTarget.() -> Unit) -> KotlinNativeTarget =
        if (System.getenv("SDK_NAME")?.startsWith("iphoneos") == true)
            ::iosArm64
        else
            ::iosX64
    iOSTarget("ios") {
        binaries {
            framework {
                baseName = "bridge_client"
            }
        }
    }
    sourceSets {
        val commonMain by getting {
            dependencies {
                implementation(Deps.Coroutines.core) {
                    version {
                        strictly(Versions.kotlinCoroutines)
                    }
                }
                implementation(Deps.SqlDelight.runtime)
                //Copied CoroutinesExtensions from SqlDelight repo to workaround dependency issue. -nathaniel 11/30/20
                //implementation("com.squareup.sqldelight:coroutines-extensions:$sqlDelightVersion")
                implementation(Deps.Serialization.core)
                implementation(Deps.Ktor.clientCore)
                //Is api to give depending modules access to JsonElement
                api(Deps.Ktor.clientSerialization)
                implementation(Deps.Ktor.clientLogging)
                implementation(Deps.kotlinxDateTime)
                implementation(Deps.stately)
                implementation(Deps.okio)
                // koin
                api(Deps.Koin.core)
            }
        }
        val commonTest by getting {
            dependencies {
                implementation(kotlin("test-common"))
                implementation(kotlin("test-annotations-common"))
                implementation(Deps.Ktor.clientMock)
                api(Deps.Koin.test)
            }
        }
        val androidMain by getting {
            dependencies {
                implementation(Deps.AndroidX.material)
                implementation(Deps.SqlDelight.androidDriver)
                implementation(Deps.Ktor.clientAndroid)
                implementation(Deps.AndroidX.work_runtime)
                implementation(Deps.AndroidX.work_runtime_kts)
                implementation(Deps.Koin.android)
                implementation(Deps.Koin.androidWorkManager)
            }
        }
        val androidTest by getting {
            dependencies {
                implementation(kotlin("test-junit"))
                implementation(Deps.Test.junit)
                implementation(Deps.SqlDelight.sqlliteDriver)
                implementation(Deps.Coroutines.test)
            }
        }
        val iosMain by getting {
            dependencies {
                implementation (Deps.SqlDelight.nativeDriver)
                implementation(Deps.Ktor.clientIos)
            }
        }

        val iosTest by getting
    }
}
android {
    compileSdkVersion(Versions.compile_sdk)
    sourceSets["main"].manifest.srcFile("src/androidMain/AndroidManifest.xml")
    sourceSets["main"].res.srcDirs("src/androidMain/res")
    defaultConfig {
        minSdkVersion(Versions.min_sdk)
        targetSdkVersion(Versions.target_sdk)
        versionCode = 1
        versionName = "android-sdk v${version}"
        buildConfigField("int", "VERSION_CODE", "${versionCode}")
        buildConfigField("String", "VERSION_NAME", "\"${versionName}\"")
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
}

val packForXcode by tasks.creating(Sync::class) {
    group = "build"
    val mode = System.getenv("CONFIGURATION") ?: "DEBUG"
    val sdkName = System.getenv("SDK_NAME") ?: "iphonesimulator"
    val targetName = "ios"// + if (sdkName.startsWith("iphoneos")) "Arm64" else "X64"
    val framework = kotlin.targets.getByName<KotlinNativeTarget>(targetName).binaries.getFramework(mode)
    inputs.property("mode", mode)
    dependsOn(framework.linkTask)
    val targetDir = File(buildDir, "xcode-frameworks")
    from({ framework.outputDirectory })
    into(targetDir)
}
tasks.getByName("build").dependsOn(packForXcode)

apply("../config/artifact-deploy.gradle")
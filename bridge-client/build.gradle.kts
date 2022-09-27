import com.android.build.gradle.internal.cxx.configure.gradleLocalProperties
import org.jetbrains.kotlin.gradle.plugin.mpp.Framework
import org.jetbrains.kotlin.gradle.plugin.mpp.KotlinNativeTarget
import org.jetbrains.kotlin.gradle.plugin.mpp.apple.XCFramework
import org.gradle.internal.classpath.Instrumented.systemProperty

plugins {
    id("com.android.library")
    kotlin("multiplatform")
    kotlin("plugin.serialization")
    id("app.cash.sqldelight")
    id("maven-publish")
    //Uncomment to enable model generation from swagger file
    //id("dev.icerock.mobile.multiplatform-network-generator")
    id("org.jetbrains.dokka")
}

tasks.withType<org.jetbrains.kotlin.gradle.tasks.KotlinCompile> {
    kotlinOptions.jvmTarget = "1.8"
}

sqldelight {
    database("BridgeResourceDatabase") {
        packageName = "org.sagebionetworks.bridge.kmm.shared.cache"
//        schemaOutputDirectory = file("src/schema")
    }
}

val iosFrameworkName = "BridgeClient"

kotlin {
    android {
        publishAllLibraryVariants()
        tasks.withType<Test> {
            systemProperty(
                "testExternalId01",
                gradleLocalProperties(rootProject.rootDir)
                    .getProperty("testExternalId01")
                    ?: System.getenv("testExternalId01")
            )
        }
    }

    val xcframework = XCFramework(iosFrameworkName)

    // ios() includes x86 sim & arm64 device
    ios {
        binaries.framework {
            baseName = iosFrameworkName
            xcframework.add(this)
        }
    }
    // iosSimulatorArm64() adds Apple Silicon simulator support
    iosSimulatorArm64 {
        binaries.framework {
            baseName = iosFrameworkName
            xcframework.add(this)
        }
    }

    targets.withType<KotlinNativeTarget> {
        compilations.all {
            kotlinOptions {
                freeCompilerArgs += "-linker-options"
                freeCompilerArgs += "-application_extension"
            }
        }
    }

    sourceSets {
        val commonMain by getting {
            dependencies {
                implementation(libs.sqlDelight.runtime)
                implementation(libs.sqlDelight.coroutinesExt)
                implementation(libs.coroutines.core)
                api(libs.kotlinx.serialization)
                implementation(libs.ktor.client.core)
                //Is api to give depending modules access to JsonElement
                api(libs.ktor.client.serialization)
                api(libs.ktor.client.contentNegotiation)
                implementation(libs.ktor.client.logging)
                implementation(libs.kotlinx.dateTime)
                implementation(libs.touchlab.stately)
                implementation(libs.okio)
                // koin
                api(libs.koin.core)
                // Kermit
                implementation(libs.touchlab.kermit)
            }
        }

        val commonTest by getting {
            dependencies {
                implementation(kotlin("test-common"))
                implementation(kotlin("test-annotations-common"))
                implementation(libs.ktor.client.mock)
                api(libs.koin.test)
            }
        }
        val androidMain by getting {
            dependencies {
                implementation(libs.sqlDelight.android)
                implementation(libs.ktor.client.android)
                implementation(libs.androidx.work.runtime)
                implementation(libs.androidx.work.runtimeKts)
                implementation(libs.koin.android)
                implementation(libs.koin.android.workmanager)
            }
        }
        val androidTest by getting {
            dependencies {
                implementation(kotlin("test-junit"))
                implementation(libs.junit)
                implementation(libs.sqlDelight.jvm)
                implementation(libs.coroutines.test)
            }
        }
        val iosMain by getting {
            dependencies {
                implementation(libs.sqlDelight.native)
                implementation(libs.ktor.client.ios)
            }
        }

        val iosTest by getting

        // Set up dependencies between the source sets for Mac Silicon
        val iosSimulatorArm64Main by sourceSets.getting
        val iosSimulatorArm64Test by sourceSets.getting
        iosSimulatorArm64Main.dependsOn(iosMain)
        iosSimulatorArm64Test.dependsOn(iosTest)
    }
}
android {
    compileSdk = libs.versions.compileSdk.get().toInt()
    sourceSets["main"].manifest.srcFile("src/androidMain/AndroidManifest.xml")
    sourceSets["main"].res.srcDirs("src/androidMain/res")
    sourceSets["main"].java.srcDirs("src/androidMain/kotlin")
    defaultConfig {
        minSdk = libs.versions.minSdk.get().toInt()
        targetSdk = libs.versions.targetSdk.get().toInt()
        val versionCode = extra["sdkVersionCode"]
        val versionName = extra["versionName"]
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
    testOptions {
        unitTests.isReturnDefaultValues = true
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

/**
 * To generate client models:
 *  1. Uncomment the following and the plugin definition above
 *  2. Copy latest Bridge swagger file to: bridge-client/src/spec/swagger.json
 *  3. Run gradle openApiGenerate
 *  4. Resulting files will be in build/generated/moko-network/bridge/src/main/kotlin
 */
//mokoNetwork {
//    spec("bridge") {
//        inputSpec = file("$rootDir/bridge-client/src/spec/swagger.json")
//        packageName = "org.sagebionetworks.bridge.kmm.shared"
//        isInternal = false
//        isOpen = true
//        configureTask {
//            // here can be configuration of https://github.com/OpenAPITools/openapi-generator GenerateTask
//        }
//        enumFallbackNull = false
//    }
//}

//endregion

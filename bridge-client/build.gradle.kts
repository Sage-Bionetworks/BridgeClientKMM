import org.jetbrains.kotlin.gradle.plugin.mpp.Framework
import org.jetbrains.kotlin.gradle.plugin.mpp.KotlinNativeTarget

plugins {
    id("com.android.library")
    kotlin("multiplatform")
    kotlin("plugin.serialization")
    id("com.squareup.sqldelight")
    id ("maven-publish")
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
    }

    ios {
        binaries {
            framework {
                baseName = iosFrameworkName
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
                implementation(Deps.SqlDelight.coroutineExtensions)
                api(Deps.Serialization.core)
                implementation(Deps.Ktor.clientCore)
                //Is api to give depending modules access to JsonElement
                api(Deps.Ktor.clientSerialization)
                implementation(Deps.Serialization.core)
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

//region XcFramework tasks
val xcFrameworkPath = "build/xcframework/$iosFrameworkName.xcframework"
val swiftPMPath = "${project.rootDir}/SwiftPackage/Binaries/$iosFrameworkName.xcframework"

tasks.create<Delete>("deleteSwiftPMFramework") { delete = setOf(swiftPMPath) }
tasks.create<Delete>("deleteXcFramework") { delete = setOf(xcFrameworkPath) }

val buildXcFramework by tasks.registering {
    val isSwiftPM = (project.findProperty("SWIFT_PM") == "true")
    if (isSwiftPM) {
        dependsOn("deleteSwiftPMFramework")
    } else {
        dependsOn("deleteXcFramework")
    }
    group = "build"
    val defaultMode = if (isSwiftPM) "RELEASE" else "DEBUG"
    val mode = System.getenv("CONFIGURATION") ?: project.findProperty("XCODE_CONFIGURATION") as? String ?: defaultMode
    val frameworks = arrayOf("iosArm64", "iosX64")
        .map { kotlin.targets.getByName<KotlinNativeTarget>(it).binaries.getFramework(mode) }
    inputs.property("mode", mode)
    dependsOn(frameworks.map { it.linkTask })
    doLast { buildXcFramework(frameworks, isSwiftPM) }
}

fun buildXcFramework(frameworks: List<Framework>, isSwiftPM: Boolean) {
    val buildArgs: () -> List<String> = {
        val arguments = mutableListOf("-create-xcframework")
        frameworks.forEach {
            arguments += "-framework"
            arguments += "${it.outputDirectory}/${it.baseName}.framework"
            arguments += "-debug-symbols"
            arguments += "${it.outputDirectory}/${it.baseName}.framework.dSYM"
        }
        arguments += "-output"
        arguments += if (isSwiftPM) swiftPMPath else xcFrameworkPath
        arguments
    }
    exec {
        executable = "xcodebuild"
        args = buildArgs()
    }
}
//endregion

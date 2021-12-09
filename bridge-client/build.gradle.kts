import com.android.build.gradle.internal.cxx.configure.gradleLocalProperties
import org.jetbrains.kotlin.gradle.plugin.mpp.Framework
import org.jetbrains.kotlin.gradle.plugin.mpp.KotlinNativeTarget
import org.jetbrains.kotlin.gradle.plugin.mpp.apple.XCFramework
import org.gradle.internal.classpath.Instrumented.systemProperty

plugins {
    id("com.android.library")
    kotlin("multiplatform")
    kotlin("plugin.serialization")
    id("com.squareup.sqldelight")
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
                    ?: System.getenv("TEST_EXTERNAL_ID_01")
            )
        }
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
                implementation(Deps.SqlDelight.nativeDriver)
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
    sourceSets["main"].java.srcDirs("src/androidMain/kotlin")
    defaultConfig {
        minSdkVersion(Versions.min_sdk)
        targetSdkVersion(Versions.target_sdk)
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

//region XcFramework tasks
val swiftPMPath = "${project.rootDir}/SwiftPackage/Binaries/$iosFrameworkName.xcframework"

tasks.create<Delete>("deleteSwiftPMFramework") { delete = setOf(swiftPMPath) }

val buildXcFramework by tasks.registering {
    dependsOn("deleteSwiftPMFramework")
    group = "build"
    val mode = project.findProperty("XCODE_CONFIGURATION") as? String ?: "RELEASE"
    val frameworks = arrayOf("iosArm64", "iosX64")
        .map { kotlin.targets.getByName<KotlinNativeTarget>(it).binaries.getFramework(mode) }
    inputs.property("mode", mode)
    dependsOn(frameworks.map { it.linkTask })
    doLast { buildXcFramework(frameworks) }
}

fun buildXcFramework(frameworks: List<Framework>) {
    val buildArgs: () -> List<String> = {
        val arguments = mutableListOf("-create-xcframework")
        frameworks.forEach {
            arguments += "-framework"
            arguments += "${it.outputDirectory}/${it.baseName}.framework"
            arguments += "-debug-symbols"
            arguments += "${it.outputDirectory}/${it.baseName}.framework.dSYM"
        }
        arguments += "-output"
        arguments += swiftPMPath
        arguments
    }
    exec {
        executable = "xcodebuild"
        args = buildArgs()
    }
}
//endregion

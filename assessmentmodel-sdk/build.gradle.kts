import org.jetbrains.kotlin.gradle.plugin.mpp.KotlinNativeTarget

plugins {
    id("com.android.library")
    kotlin("multiplatform")
    id("com.github.dcendents.android-maven")
}


tasks.withType<org.jetbrains.kotlin.gradle.tasks.KotlinCompile> {
    kotlinOptions.jvmTarget = "1.8"
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
                baseName = "assessmentmodel_sdk"
            }
        }
    }
    sourceSets {
        val assessment_version = "0.4.2"

        val commonMain by getting {
            dependencies {

            }
        }
        val androidMain by getting {
            dependencies {
                // these dependencies should go in commonMain - liujoshua 04/02/2021
                implementation(project(":bridge-client"))
                api("org.sagebionetworks.assessmentmodel:assessmentModel:$assessment_version")

                implementation(project(":bridge-client-presentation"))
                implementation("org.sagebionetworks.assessmentmodel:presentation:$assessment_version")
            }
        }
        val iosMain by getting
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
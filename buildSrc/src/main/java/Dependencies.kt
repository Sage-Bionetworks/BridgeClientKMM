object Versions {
    const val min_sdk = 23
    const val target_sdk = 29
    const val compile_sdk = 29

    //Kotlin
    const val kotlin = "1.4.32"
    const val kotlinCoroutines = "1.4.3-native-mt"
    const val ktor = "1.5.3"
    const val kotlinxSerialization = "1.1.0"
    const val kotlinxDateTime = "0.2.0"
    const val multiplatformSettings = "0.7.1"
    const val koin = "3.0.1"
    const val sqlDelight = "1.5.0"
    const val okio = "3.0.0-alpha.4"
    const val stately = "1.1.1"

    object AndroidX {
        val annotation = "1.1.0"
        val appcompat = "1.2.0"
        val constraintlayout = "2.0.4"
        val core = "1.3.2"
        val lifecycle = "2.2.0"
        val material =  "1.3.0"
        val recyclerview = "1.1.0"
        val test = "1.3.0"
        val test_ext = "1.1.2"
        val workManager = "2.5.0"
    }

    const val slf4j = "1.7.30"

    const val junit = "4.13"

}

object Deps {

    val kotlinxDateTime = "org.jetbrains.kotlinx:kotlinx-datetime:${Versions.kotlinxDateTime}"
    val okio = "com.squareup.okio:okio-multiplatform:${Versions.okio}"
    val stately = "co.touchlab:stately-common:${Versions.stately}"

    object AndroidX {
        val annotation = "androidx.annotation:annotation:${Versions.AndroidX.annotation}"
        val appcompat = "androidx.appcompat:appcompat:${Versions.AndroidX.appcompat}"
        val core_ktx = "androidx.core:core-ktx:${Versions.AndroidX.core}"
        val constraintlayout = "androidx.constraintlayout:constraintlayout:${Versions.AndroidX.constraintlayout}"
        val recyclerView = "androidx.recyclerview:recyclerview:${Versions.AndroidX.recyclerview}"
        val lifecycle_runtime = "androidx.lifecycle:lifecycle-runtime-ktx:${Versions.AndroidX.lifecycle}"
        val lifecycle_viewmodel = "androidx.lifecycle:lifecycle-viewmodel:${Versions.AndroidX.lifecycle}"
        val lifecycle_viewmodel_ktx = "androidx.lifecycle:lifecycle-viewmodel-ktx:${Versions.AndroidX.lifecycle}"
        val lifecycle_livedata = "androidx.lifecycle:lifecycle-livedata:${Versions.AndroidX.lifecycle}"
        val lifecycle_livedata_ktx = "androidx.lifecycle:lifecycle-livedata-ktx:${Versions.AndroidX.lifecycle}"
        val lifecycle_extension = "androidx.lifecycle:lifecycle-extensions:${Versions.AndroidX.lifecycle}"
        val material = "com.google.android.material:material:${Versions.AndroidX.material}"
        val work_runtime = "androidx.work:work-runtime:${Versions.AndroidX.workManager}"
        val work_runtime_kts = "androidx.work:work-runtime-ktx:${Versions.AndroidX.workManager}"
    }

    object Test {
        const val junit = "junit:junit:${Versions.junit}"
    }

    object Coroutines {
        val core = "org.jetbrains.kotlinx:kotlinx-coroutines-core:${Versions.kotlinCoroutines}"
        val android =
            "org.jetbrains.kotlinx:kotlinx-coroutines-android:${Versions.kotlinCoroutines}"
        val test = "org.jetbrains.kotlinx:kotlinx-coroutines-test:${Versions.kotlinCoroutines}"
    }

    object Koin {
        val core = "io.insert-koin:koin-core:${Versions.koin}"
        val test = "io.insert-koin:koin-test:${Versions.koin}"
        val android = "io.insert-koin:koin-android:${Versions.koin}"
        val androidViewModel = "io.insert-koin:koin-androidx-viewmodel:${Versions.koin}"
        val androidWorkManager =  "io.insert-koin:koin-androidx-workmanager:${Versions.koin}"
    }

    object Ktor {
        val clientCore = "io.ktor:ktor-client-core:${Versions.ktor}"
        val clientJson = "io.ktor:ktor-client-json:${Versions.ktor}"
        val clientLogging = "io.ktor:ktor-client-logging:${Versions.ktor}"
        val clientSerialization = "io.ktor:ktor-client-serialization:${Versions.ktor}"

        val clientAndroid = "io.ktor:ktor-client-android:${Versions.ktor}"
        val slf4j = "org.slf4j:slf4j-simple:${Versions.slf4j}"
        val clientIos = "io.ktor:ktor-client-ios:${Versions.ktor}"
        val clientMock = "io.ktor:ktor-client-mock:${Versions.ktor}"
    }

    object Serialization {
        val core =
            "org.jetbrains.kotlinx:kotlinx-serialization-json:${Versions.kotlinxSerialization}"
    }

    object SqlDelight {
        val runtime = "com.squareup.sqldelight:runtime:${Versions.sqlDelight}"
        val coroutineExtensions =
            "com.squareup.sqldelight:coroutines-extensions:${Versions.sqlDelight}"
        val androidDriver = "com.squareup.sqldelight:android-driver:${Versions.sqlDelight}"

        val nativeDriver = "com.squareup.sqldelight:native-driver:${Versions.sqlDelight}"
        val sqlliteDriver = "com.squareup.sqldelight:sqlite-driver:${Versions.sqlDelight}"
    }

    //Not currently using, but may be useful in the future
    object MultiplatformSettings {
        val multiplatformSettings = "com.russhwolf:multiplatform-settings:${Versions.multiplatformSettings}"
        val multiplatformSettingsNoArg = "com.russhwolf:multiplatform-settings-no-arg:${Versions.multiplatformSettings}"
        val multiplatformSettingsCoroutines = "com.russhwolf:multiplatform-settings-coroutines-native-mt:${Versions.multiplatformSettings}"
        val multiplatformSettingsTest = "com.russhwolf:multiplatform-settings-test:${Versions.multiplatformSettings}"
    }
}

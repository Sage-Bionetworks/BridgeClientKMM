package org.sagebionetworks.bridge.kmm.shared

import android.content.Context
import android.content.pm.PackageInfo
import android.content.pm.PackageManager
import android.os.Build
import android.os.Build.VERSION
import android.text.TextUtils
import android.util.Log
import org.sagebionetworks.bridge.kmm.android.BuildConfig
import org.sagebionetworks.bridge.kmm.android.R

class AndroidBridgeConfig(context: Context) : BridgeConfig {

    private val applicationContext = context.applicationContext

    override val appId: String = applicationContext.resources.getString(R.string.osb_app_id)

    override val appName: String = applicationContext.resources.getString(R.string.osb_app_name)

    override val sdkVersion: Int = BuildConfig.VERSION_CODE

    override val appVersion: Int
        get(){
            return try {
                val pInfo: PackageInfo = applicationContext.getPackageManager()
                    .getPackageInfo(applicationContext.getPackageName(), 0)
                pInfo.versionCode
            } catch (e: PackageManager.NameNotFoundException) {
                Log.e( javaClass.name, "Error retrieving application's version code, using SDK's", e)
                BuildConfig.VERSION_CODE
            }
        }

    override val appVersionName: String
        get() {
            return try {
                val pInfo: PackageInfo = applicationContext.getPackageManager()
                    .getPackageInfo(applicationContext.getPackageName(), 0)
                pInfo.versionName
            } catch (e: PackageManager.NameNotFoundException) {
                Log.e(javaClass.name, "Error retrieving application's version name, using SDK's", e)
                BuildConfig.VERSION_NAME
            }
        }

    override val osName: String = "Android"

    override val osVersion: String = VERSION.RELEASE

    override val deviceName: String
        get() {
            var manufacturer = Build.MANUFACTURER
            if (TextUtils.isEmpty(manufacturer)) {
                manufacturer = "Unknown"
            }
            var model = Build.MODEL
            if (TextUtils.isEmpty(model)) {
                model = "Android"
            }
            return if (model.startsWith(manufacturer!!)) {
                capitalize(model)
            } else {
                capitalize(manufacturer) + " " + model
            }
        }

    fun capitalize(s: String?): String {
        if (s == null || s.length == 0) {
            return ""
        }
        val first = s[0]
        return if (Character.isUpperCase(first)) {
            s
        } else {
            Character.toUpperCase(first).toString() + s.substring(1)
        }
    }


}
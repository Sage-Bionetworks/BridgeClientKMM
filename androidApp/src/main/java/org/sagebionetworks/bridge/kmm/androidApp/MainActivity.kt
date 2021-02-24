package org.sagebionetworks.bridge.kmm.androidApp

import android.content.Intent
import android.os.Bundle
import android.widget.TextView
import androidx.appcompat.app.AppCompatActivity
import androidx.lifecycle.Observer
import androidx.lifecycle.asLiveData
import kotlinx.coroutines.MainScope
import org.koin.android.ext.android.inject
import org.sagebionetworks.bridge.kmm.androidApp.ui.login.LoginActivity
import org.sagebionetworks.bridge.kmm.presentation.auth.ExternalIdSignInActivity
import org.sagebionetworks.bridge.kmm.shared.cache.DatabaseDriverFactory
import org.sagebionetworks.bridge.kmm.shared.cache.ResourceResult
import org.sagebionetworks.bridge.kmm.shared.repo.AssessmentConfigRepo
import org.sagebionetworks.bridge.kmm.shared.repo.AuthenticationRepository

class MainActivity : AppCompatActivity() {

    val assessmentConfigRepo: AssessmentConfigRepo by inject()
    val authenticationRepository: AuthenticationRepository by inject()

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        if (!authenticationRepository.isAuthenticated()) {
            val launchIntent = Intent(this, ExternalIdSignInActivity::class.java)
                .setData(intent.data)
                .addFlags(Intent.FLAG_ACTIVITY_CLEAR_TOP or Intent.FLAG_ACTIVITY_SINGLE_TOP)

            startActivity(launchIntent)
        }

    }

    override fun onResume() {
        super.onResume()
        val tv: TextView = findViewById(R.id.text_view)

        if (authenticationRepository.isAuthenticated()) {
            assessmentConfigRepo.getAssessmentById("eGhiQTT2a6SCCmjTod6CDb0t").asLiveData()
                .observe(this, Observer { t ->
                    when (t) {
                        is ResourceResult.Success -> {tv.text = t.data.config.toString()}
                        is ResourceResult.InProgress -> {tv.text = "loading..."}
                        is ResourceResult.Failed -> {tv.text = "failed to load"}
                    }
                })
        }
    }
}

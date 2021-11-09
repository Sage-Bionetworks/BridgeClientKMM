package org.sagebionetworks.bridge.kmm.presentation.auth

import android.os.Bundle
import android.view.View
import androidx.appcompat.app.AppCompatActivity
import org.koin.androidx.viewmodel.ext.android.viewModel
import org.sagebionetworks.bridge.kmm.presentation.databinding.ExternalIdSignInActivityBinding

class ExternalIdSignInActivity : AppCompatActivity() {

    private val viewModel: ExternalIdSignInViewModel by viewModel()

    private lateinit var binding: ExternalIdSignInActivityBinding


    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        binding = ExternalIdSignInActivityBinding.inflate(layoutInflater)
        setContentView(binding.root)

        viewModel.signInResult.observe(this, {
            binding.progressBar.visibility = View.GONE
            when(it) {
                is SignInResult.Success -> {
                    setResult(RESULT_OK)
                    finish()
                }
                is SignInResult.Failed -> {
                    binding.signInErrorText.visibility = View.VISIBLE
                }
            }
        })

        binding.signIn.setOnClickListener {
            binding.signInErrorText.visibility = View.GONE
            binding.progressBar.visibility = View.VISIBLE
            viewModel.login(binding.externalId.text.toString())
        }
    }

}
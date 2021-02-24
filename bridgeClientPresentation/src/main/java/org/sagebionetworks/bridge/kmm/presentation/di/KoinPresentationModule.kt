package org.sagebionetworks.bridge.kmm.presentation.di

import org.koin.androidx.viewmodel.dsl.viewModel
import org.koin.dsl.module
import org.sagebionetworks.bridge.kmm.presentation.auth.ExternalIdSignInViewModel

val presentationModule = module {

    viewModel { ExternalIdSignInViewModel(get()) }

}
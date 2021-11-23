package org.sagebionetworks.bridge.kmm.androidApp.di

import org.koin.androidx.viewmodel.dsl.viewModel
import org.koin.dsl.module
import org.sagebionetworks.bridge.kmm.androidApp.ui.login.LoginViewModel

val appModule = module {

    viewModel { LoginViewModel(get()) }

}
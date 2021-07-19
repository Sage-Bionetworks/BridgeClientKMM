package org.sagebionetworks.bridge.kmm.shared

import kotlinx.coroutines.MainScope
import kotlinx.coroutines.cancel
import kotlinx.coroutines.flow.collect
import kotlinx.coroutines.launch
import org.koin.core.component.KoinComponent
import org.koin.core.component.inject
import org.sagebionetworks.bridge.kmm.shared.cache.*
import org.sagebionetworks.bridge.kmm.shared.models.UserSessionInfo
import org.sagebionetworks.bridge.kmm.shared.repo.AppConfigRepo
import org.sagebionetworks.bridge.kmm.shared.repo.AuthenticationRepository
import org.sagebionetworks.bridge.mpp.network.generated.models.AppConfig

class NativeAppConfigManager(
    private val viewUpdate: (AppConfig?, ResourceStatus?) -> Unit
) : KoinComponent {

    private val repo : AppConfigRepo by inject(mode = LazyThreadSafetyMode.NONE)

    private val scope = MainScope()

    fun observeAppConfig() {
        scope.launch {
            repo.getAppConfig().collect { resourceResult ->
                when (resourceResult) {
                    is ResourceResult.Success -> {viewUpdate(resourceResult.data, resourceResult.status)}
                    is ResourceResult.InProgress -> {viewUpdate(null, ResourceStatus.PENDING)}
                    is ResourceResult.Failed -> {viewUpdate(null, resourceResult.status)}
                }
            }
        }
    }

    @Throws(Throwable::class)
    fun onCleared() {
        try {
            scope.cancel()
        } catch (err: Exception) {
            throw Throwable(err.message)
        }
    }
}

fun AppConfig.configElementJson(identifier: String) : String? {
    return this.configElements?.get(identifier)?.toString()
}

fun AppConfig.clientDataJson() : String? {
    return this.clientData?.toString()
}
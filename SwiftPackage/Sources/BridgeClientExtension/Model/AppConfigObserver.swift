//
//  AppConfigObserver.swift
//
//

import Foundation
import BridgeClient
import JsonModel

/// This is a threadsafe wrapper for the Kotlin class ``BridgeClient.UserSessionInfo``.
public final class AppConfigObserver : ObservableObject {
    
    var appConfig : AppConfig? {
        get { self._appConfig }
        set {
            self._appConfig = processResultOnMainThread {
                self.isLaunching = false
                self.copyFrom(newValue)
                return newValue
            }
        }
    }
    private var _appConfig : AppConfig?
    
    init() {}
    
    /// Is the app launching?
    @Published public var isLaunching: Bool = true
    
    /// Client data for a user should be in a syntactically valid JSON format. It will be returned as is to the client
    /// (as JSON).
    @Published public var clientData: Data?
    
    /// A map of app config element IDs to the app config element JSON of a specific app config element revision
    /// (the revision given in the configReferences map).
    @Published public var configElements: [String : Data]?
    
    /// A map of schema identifiers to revisions.
    @Published public var schemaReferences: [String : Int]?
    
    /// Get the config element with the given identifier.
    public func configElementJson(identifier: String) -> Data? {
        configElements?[identifier]
    }
    
    func copyFrom(_ newValue: AppConfig?) {
        guard let config = newValue else { return }
        self.clientData = config.clientDataJson()
        self.configElements = config.mapConfigElements()
        self.schemaReferences = config.schemaReferences?.reduce(into: [String : Int]()) { dictionary, ref in
            ref.revision.map {
                dictionary[ref.id] = $0.intValue
            }
        }
    }
}

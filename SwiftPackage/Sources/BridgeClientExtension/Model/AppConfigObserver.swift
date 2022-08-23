//
//  AppConfigObserver.swift
//
//
//  Copyright © 2021 Sage Bionetworks. All rights reserved.
//
// Redistribution and use in source and binary forms, with or without modification,
// are permitted provided that the following conditions are met:
//
// 1.  Redistributions of source code must retain the above copyright notice, this
// list of conditions and the following disclaimer.
//
// 2.  Redistributions in binary form must reproduce the above copyright notice,
// this list of conditions and the following disclaimer in the documentation and/or
// other materials provided with the distribution.
//
// 3.  Neither the name of the copyright holder(s) nor the names of any contributors
// may be used to endorse or promote products derived from this software without
// specific prior written permission. No license is granted to the trademarks of
// the copyright holders even if such marks are included in this software.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE
// FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
// DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
// SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
// CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
// OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
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

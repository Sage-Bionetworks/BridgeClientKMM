//
//  MockAppManager.swift
//  BridgeFileUploads
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

@testable import BridgeClient
@testable import BridgeClientUI

// MARK: MockAuthManager
class MockAuthManager : NativeAuthenticationManager {
    fileprivate var mockUserSessionInfo: UserSessionInfo? = UserSessionInfo(firstName: nil, lastName: nil, externalId: nil, id: "not-a-real-user-id", notifyByEmail: nil, attributes: nil, sharingScope: nil, createdOn: nil, emailVerified: nil, phoneVerified: nil, status: nil, roles: nil, dataGroups: nil, clientData: nil, languages: nil, studyIds: ["not-a-real-study-id"], externalIds: nil, authenticated: true, sessionToken: "not-a-real-session-token", reauthToken: nil, environment: nil, email: nil, phone: nil, dataSharing: nil, signedMostRecentConsent: nil, synapseUserId: nil, consented: true, consentStatuses: nil, enrollments: nil, orgMembership: nil, type: "UserSessionInfo")
    
    override func session() -> UserSessionInfo? {
        return mockUserSessionInfo
    }
    
    override func notifyUIOfBridgeError(statusCode: Ktor_httpHttpStatusCode) {
        print("Test would notify UI of Bridge status code \(statusCode) here")
    }
    
    var mockError: KotlinError?
    override func reauth(completion: @escaping (KotlinError?) -> Void) {
        completion(mockError)
    }
}

// MARK: MockBridgeClientAppManager
class MockBridgeClientAppManager : BridgeClientAppManager {
    let mockAuthManager = MockAuthManager {_ in }
    
    override var authManager: NativeAuthenticationManager! {
        mockAuthManager
    }
    
    override var session: UserSessionInfo? {
        set {
            mockAuthManager.mockUserSessionInfo = newValue
        }
        get {
            mockAuthManager.session()
        }
    }
}

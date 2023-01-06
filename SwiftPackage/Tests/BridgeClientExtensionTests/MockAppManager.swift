//
//  MockAppManager.swift
//  BridgeFileUploads
//

@testable import BridgeClient
@testable import BridgeClientExtension

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
class MockBridgeClientAppManager : UploadAppManager {
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

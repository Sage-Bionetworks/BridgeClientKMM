//
//  MockAppManager.swift
//  BridgeFileUploads
//

@testable import BridgeClient
@testable import BridgeClientExtension

// MARK: MockAuthManager
class MockAuthManager : NativeAuthenticationManager {
    fileprivate var mockUserSessionInfo: UserSessionInfo? = UserSessionInfo(sessionToken: "not-a-real-session-token", reauthToken: "not-a-real-reauth-token")
    
    override func session() -> UserSessionInfo? {
        return mockUserSessionInfo
    }
    
    override func notifyUIOfBridgeError(statusCode: Ktor_httpHttpStatusCode) {
        print("Test would notify UI of Bridge status code \(statusCode) here")
    }
    
    enum MockReauthError : String, Error {
        case notConnected, invalidReauthToken
    }
    
    var mockReauthError: MockReauthError?
    override func reauth(completion: @escaping (KotlinError?) -> Void) {
        let mockError = mockReauthError.map {
            switch $0 {
            case .invalidReauthToken:
                mockUserSessionInfo = .init(sessionToken: "", reauthToken: nil)
            case .notConnected:
                break
            }
            return KotlinError(message: $0.rawValue)
        }
        if mockReauthError == nil {
            mockUserSessionInfo = .init(sessionToken: "different-not-a-real-session-token", reauthToken: "different-not-a-real-reauth-token")
        }
        completion(mockError)
    }
}

extension UserSessionInfo {
    public convenience init(sessionToken: String, reauthToken: String?) {
        self.init(firstName: nil, lastName: nil, externalId: nil, id: "not-a-real-user-id", notifyByEmail: nil, attributes: nil, sharingScope: nil, createdOn: nil, emailVerified: nil, phoneVerified: nil, status: nil, roles: nil, dataGroups: nil, clientData: nil, languages: nil, studyIds: ["not-a-real-study-id"], externalIds: nil, authenticated: reauthToken != nil, sessionToken: sessionToken, reauthToken: reauthToken, environment: nil, email: nil, phone: nil, dataSharing: nil, signedMostRecentConsent: nil, synapseUserId: nil, consented: true, consentStatuses: nil, enrollments: nil, orgMembership: nil, type: "UserSessionInfo")
    }
}

// MARK: MockBridgeClientAppManager
class MockBridgeClientAppManager : UploadAppManager {
    let mockAuthManager = MockAuthManager {_ in }
    
    override var authManager: NativeAuthenticationManager! {
        mockAuthManager
    }
    
    override var sessionToken: String? {
        mockAuthManager.mockUserSessionInfo?.sessionToken
    }
}

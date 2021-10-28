//
//  UserSessionInfoObserver.swift
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
public final class UserSessionInfoObserver : ObservableObject {
    
    var userSessionInfo : UserSessionInfo? {
        get { self._userSessionInfo }
        set {
            self._userSessionInfo = processResultOnMainThread {
                self.copyFrom(newValue)
                return newValue
            }
        }
    }
    private var _userSessionInfo : UserSessionInfo?
    
    init() {}
    
    /// Whether or not the session is authenticated.
    @Published public var isAuthenticated: Bool = false
    
    // MARK: Name
    
    /// First name (given name) of the user.
    @Published public var firstName: String?
    /// Last name (family name) of the user.
    @Published public var lastName: String?

    // MARK: Custom Data

    /// The date and time the account was created.
    @Published public var createdOn: Date?
    
    /// A map of user profile attributes that have been set for this user (the attributes themselves must
    /// be specified in the app's configuration, and the values are stored encrypted in case they capture
    /// personally-identifying information).
    @Published public var attributes: [String : String]?

    /// The data groups set for this user. Data groups must be strings that are defined in the list of all valid data groups for the app, as part of the app object.
    @Published public var dataGroups: [String]?
    
    /// Client data for a user should be in a syntactically valid JSON format. It will be returned as is to the client (as JSON).
    @Published public var clientData: Data?

    // MARK: Study and External ID
    
    /// The studies this participant is associated to.
    @Published public var studyIds: [String] = []
    
    /// An externally-assignable identifier a research partner can use to re-identify a user's data in the
    /// exported data set (this must be provided by the application, it is not created by Bridge). It is a
    /// string that can be set or updated to any value without constraints, unless Bridge is configured
    /// to manage the study's external IDs. Then the ID must be submitted on sign up, and cannot be
    /// modified afterward.
    @Published public var externalId: String?
    
    /// The exernal IDs this participant is associated to, mapped to the study that issued the external ID.
    /// Typically a user signs up with the external ID, and is assigned to that study as a result.
    @Published public var externalIds: [String : String]?
    
    /// For certain studies, there is a pattern used to add an `externalId` that *includes* the `studyId`
    /// as a suffix. This code is used to test for that case and strip the `studyId` if it is appended to the
    /// `externalId`.
    public func participantId(for studyId: String) -> String? {
        guard let externalId = self.externalIds?[studyId] ?? self.externalId
        else {
            return nil
        }
        let studySuffix = ":\(studyId)"
        if externalId.hasSuffix(studySuffix) {
            return String(externalId.dropLast(studySuffix.count))
        }
        else {
            return externalId
        }
    }
    
    // MARK: Contact Information
    
    /// The user's email.
    @Published public var email: String?
    /// The user's phone.
    @Published public var phone: String?

    /// Has the user verified that they have control of this email address?
    @Published public var emailVerified: Bool?
    /// Has the user verified that they have control of this phone number?
    @Published public var phoneVerified: Bool?
    
    /// True if the user has consented to be contacted via email outside the application, false otherwise.
    @Published public var notifyByEmail: Bool?
    
    private func copyFrom(_ newValue: UserSessionInfo?) {
        self.isAuthenticated = newValue?.authenticated ?? false
        self.firstName = newValue?.firstName
        self.lastName = newValue?.lastName
        self.createdOn = newValue?.createdOn.flatMap { ISO8601TimestampFormatter.date(from: $0) }
        self.attributes = newValue?.attributes
        self.dataGroups = newValue?.dataGroups
        self.clientData = newValue?.clientDataJson()
        self.studyIds = newValue?.studyIds ?? []
        self.externalId = newValue?.externalId
        self.externalIds = newValue?.externalIds
        self.email = newValue?.email
        self.phone = newValue?.phone.map { $0.nationalFormat ?? $0.number }
        self.emailVerified = newValue?.emailVerified?.boolValue
        self.phoneVerified = newValue?.phoneVerified?.boolValue
        self.notifyByEmail = newValue?.notifyByEmail?.boolValue
    }
}

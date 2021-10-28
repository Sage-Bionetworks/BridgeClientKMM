//
//  PrivacyNotice.swift
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

/// A codable list of privacy notice items grouped by ``Category``.
public struct PrivacyNotice : Codable, Hashable {
    
    public let notices: [Item]
    
    public struct Item : Codable, Hashable, Identifiable {
        public var id: String { icon }
        
        /// The  category for the item.
        public let category: Category
        /// The name of the image asset (defined within this module) to show for this item.
        public let icon: String
        /// The description text to show for this item.
        public let text: String
    }
    
    public enum Category: String, CaseIterable, Codable {
        case weWill="we_will", weWont="we_wont", youCan="you_can"
    }

    public static let `default`: PrivacyNotice = {
        let decoder = JSONDecoder()
        return try! decoder.decode(PrivacyNotice.self, from: json)
    }()
}

extension AppConfigObserver {
    /// By default, the ``PrivacyNotice`` is the same for all studies supported by a given app and is defined
    /// as a `ConfigElement` in Bridge with the identifier "PrivacyNotice".
    func decodePrivacyNotice() -> PrivacyNotice? {
        do {
            guard let data = self.configElementJson(identifier: "PrivacyNotice")
            else {
                return nil
            }
            let decoder = JSONDecoder()
            return try decoder.decode(PrivacyNotice.self, from: data)
        }
        catch let err {
            print("WARNING! Failed to decode config: \(err)")
            return nil
        }
    }
}

fileprivate let json = """
    {
        "type": "PrivacyNotice",
        "notices": [
            {
                "category": "we_will",
                "icon": "privacy_we_will_collect_pii",
                "text": "Collect the data you give us when you register and when you use the App. This may include sensitive data like your health information."
            },
            {
                "category": "we_will",
                "icon": "privacy_we_will_collect_data",
                "text": "Collect standard usage data or log information."
            },
            {
                "category": "we_will",
                "icon": "privacy_we_will_protect_data",
                "text": "Protect your privacy and store the data in a secure cloud server in the US."
            },
            {
                "category": "we_will",
                "icon": "privacy_we_will_share_data",
                "text": "Share de-identified data with other researchers in the US and abroad."
            },
            {
                "category": "we_will",
                "icon": "privacy_we_will_store_data",
                "text": "Retain your data as long as we need it unless you request deletion."
            },
            {
                "category": "we_will",
                "icon": "privacy_we_will_delete_data",
                "text": "Delete your data when you ask us to."
            },
            {
                "category": "we_will",
                "icon": "privacy_we_will_notify_changes",
                "text": "Tell you if we make changes to our privacy policy."
            },
            {
                "category": "we_wont",
                "icon": "privacy_we_wont_access_contacts",
                "text": "Access your contacts, photos or other personal information stored on your phone."
            },
            {
                "category": "we_wont",
                "icon": "privacy_we_wont_sell_data",
                "text": "Sell or rent your data."
            },
            {
                "category": "we_wont",
                "icon": "privacy_we_wont_track_other_apps",
                "text": "Track your browsing activities on other Apps."
            },
            {
                "category": "we_wont",
                "icon": "privacy_we_wont_use_for_advertising",
                "text": "Use your data for advertising."
            },
            {
                "category": "you_can",
                "icon": "privacy_you_can_request_access",
                "text": "Ask to access, download or delete your data."
            },
            {
                "category": "you_can",
                "icon": "privacy_you_can_allow_passive_data",
                "text": "Decide if we can collect passive data from your device, like how much time you use your device each day."
            },
            {
                "category": "you_can",
                "icon": "privacy_you_can_optional_permissions",
                "text": "Decide what optional information to give us. For example, giving us your zipcode will tell us about the weather or air quality where you are."
            },
            {
                "category": "you_can",
                "icon": "privacy_you_can_permit_microphone",
                "text": "Allow us to turn on your phone camera or microphone when it is necessary to use the App."
            },
            {
                "category": "you_can",
                "icon": "privacy_you_can_choose_to_share",
                "text": "Choose to share your data for future research."
            },
            {
                "category": "you_can",
                "icon": "privacy_you_can_receive_notifications",
                "text": "Opt in to receive notifications and invitations about other research."
            }
        ]
    }
    """.data(using: .utf8)!

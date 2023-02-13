//
//  PrivacyNotice.swift
//

import Foundation
import BridgeClient
import BridgeClientExtension

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
            Logger.log(severity: .warn, message: "Failed to decode config: \(err)")
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

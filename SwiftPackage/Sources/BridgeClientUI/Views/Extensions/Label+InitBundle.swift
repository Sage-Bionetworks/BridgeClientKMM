//
//  Label+InitBundle.swift
//

import SwiftUI

extension Label where Title == Text, Icon == Image {

    init(_ titleKey: LocalizedStringKey, image name: String, bundle: Bundle?) {
        self.init(
            title: { Text(titleKey, bundle: bundle) },
            icon: { Image(name, bundle: bundle) }
        )
    }

    init(_ titleKey: LocalizedStringKey, systemImage name: String, bundle: Bundle?) {
        self.init(
            title: { Text(titleKey, bundle: bundle) },
            icon: { Image(systemName: name) }
        )
    }
}

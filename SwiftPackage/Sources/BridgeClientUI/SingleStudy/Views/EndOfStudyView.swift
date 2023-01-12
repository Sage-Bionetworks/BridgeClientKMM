//
//  EndOfStudyView.swift
//

import SwiftUI
import SharedMobileUI

public struct EndOfStudyView: View {
    @EnvironmentObject var bridgeManager: SingleStudyAppManager
 
    private let waitMessage = EndOfStudyStatusView(
        image: "Uploading",
        isBehind: true,
        offset: 55.0,
        title: LocalizedStringKey("Hang tight..."),
        detail: LocalizedStringKey("Please don’t close the app quite yet. We’re uploading your contributions to the cloud."))
    private let allDoneMessage = EndOfStudyStatusView(
        image:"End of Study",
        isBehind: false,
        offset: 120.0,
        title: LocalizedStringKey("Well done!"),
        detail: LocalizedStringKey("You’ve completed the study.\n\nThank you for your contributions."))
    
    public init() {}
    
    public var body: some View {
        ScreenBackground {
            if bridgeManager.isUploading {
                waitMessage
            }
            else {
                allDoneMessage
            }
        }
    }
}

fileprivate struct EndOfStudyStatusView: View {
    let image: String
    let isBehind: Bool
    let offset: CGFloat
    let title: LocalizedStringKey
    let detail: LocalizedStringKey
    
    var body: some View {
        VStack {
            CompositeTintedImage("\(image).tinted", defaultImage: image, isBehind: isBehind, bundle: .module)
                .padding(.bottom, 30)
            Text(title, bundle: .module)
                .font(DesignSystem.fontRules.headerFont(at: 3))
                .padding(.bottom, 16)
            Text(detail, bundle: .module)
                .font(DesignSystem.fontRules.bodyFont(at: 1, isEmphasis: false))
                .padding(.horizontal, 30)
                .padding(.bottom, 30)
        }
        .background(
            Color.sageWhite
                .shadow(color: .init(.sRGB, white: 0.0, opacity: 0.25), radius: 4, x: 4.0, y: 4.0)
                .padding(.top, offset)
        )
        .frame(width: 271)
    }
}

// syoung 08/16/2021 SwiftUI fails to build complex UI in a shared framework. Therefore, the preview
// for this element is in iosApp.
struct EndOfStudyView_Previews: PreviewProvider {
    static var previews: some View {
        Text("Hello, World!")
    }
}


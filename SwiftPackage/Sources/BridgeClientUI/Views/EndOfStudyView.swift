//
//  EndOfStudyView.swift
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

import SwiftUI
import SharedMobileUI

public struct EndOfStudyView: View {
    @EnvironmentObject var bridgeManager: SingleStudyAppManager
    
    private let waitMessage = EndOfStudyStatusView(
        image: "Uploading",
        isBehind: true,
        offset: 55.0,
        title: LocalizedStringKey("Hang tight..."),
        detail: LocalizedStringKey("Please don't close the app quite yet. We're uploading your contributions to the cloud."))
    private let allDoneMessage = EndOfStudyStatusView(
        image:"End of Study",
        isBehind: false,
        offset: 120.0,
        title: LocalizedStringKey("Well done!"),
        detail: LocalizedStringKey("You've completed the study.\n\nThank you for your contributions."))
    
    public init() {}
    
    public var body: some View {
        ScreenBackground(content: message)
    }
    
    @ViewBuilder
    private func message() -> some View {
        if bridgeManager.isUploadingResults {
            waitMessage
        }
        else {
            allDoneMessage
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


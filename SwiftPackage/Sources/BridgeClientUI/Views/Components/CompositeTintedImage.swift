//
//  CompositeTintedImage.swift
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

public struct CompositeTintedImage: View {
    private let isBehind: Bool
    private let defaultImage: Image
    private let tintedImage: Image
    private let color: Color
    
    public init(_ tinted: String, background: String, bundle: Bundle? = nil, color: Color = .accentColor) {
        self.isBehind = false
        self.tintedImage = Image(decorative: tinted, bundle: bundle).renderingMode(.template)
        self.defaultImage = Image(background, bundle: bundle).renderingMode(.original)
        self.color = color
    }
    
    public init(_ tinted: String, foreground: String, bundle: Bundle? = nil, color: Color = .accentColor) {
        self.isBehind = true
        self.tintedImage = Image(decorative: tinted, bundle: bundle).renderingMode(.template)
        self.defaultImage = Image(foreground, bundle: bundle).renderingMode(.original)
        self.color = color
    }
    
    init(_ tinted: String, defaultImage: String, isBehind: Bool, bundle: Bundle? = nil, color: Color = .accentColor) {
        self.isBehind = isBehind
        self.tintedImage = Image(decorative: tinted, bundle: bundle).renderingMode(.template)
        self.defaultImage = Image(defaultImage, bundle: bundle).renderingMode(.original)
        self.color = color
    }

    public var body: some View {
        ZStack {
            if isBehind {
                tinted()
            }
            defaultImage
            if !isBehind {
                tinted()
            }
        }
    }
    
    @ViewBuilder
    func tinted() -> some View {
        tintedImage
            .foregroundColor(color)
    }
}

// syoung 08/16/2021 SwiftUI fails to build complex UI in a shared framework. Therefore, the preview
// for this element is in iosApp.
struct CompositeTintedImage_Previews: PreviewProvider {
    static var previews: some View {
        Text("Hello, World!")
    }
}

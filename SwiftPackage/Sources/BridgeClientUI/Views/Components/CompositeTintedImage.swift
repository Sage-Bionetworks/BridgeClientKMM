//
//  CompositeTintedImage.swift
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

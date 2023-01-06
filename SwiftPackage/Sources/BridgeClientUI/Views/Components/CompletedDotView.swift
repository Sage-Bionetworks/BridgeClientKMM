//
//  CompletedDotView.swift
//

import SwiftUI

public struct CompletedDotView: View {
    private let dotSize: CGFloat = 21.33
    private let color: Color
    
    public init(color: Color) {
        self.color = color
    }
    
    public var body: some View {
        ZStack {
            Circle()
                .fill(color)
                .frame(width: dotSize, height: dotSize)
                .offset(x: 2.67, y: 1.33)
            Circle()
                .strokeBorder()
                .frame(width: dotSize, height: dotSize)
            Image(decorative: "checkmark", bundle: .module)
        }
    }
}

struct CompletedDotView_Previews: PreviewProvider {
    static var previews: some View {
        CompletedDotView(color: .accentColor)
    }
}

//
//  LaunchView.swift
//

import SwiftUI

struct LaunchView: View {
    var body: some View {
        Image("Launching")
            .resizable()
            .aspectRatio(contentMode: .fit)
    }
}

struct LaunchView_Previews: PreviewProvider {
    static var previews: some View {
        LaunchView()
    }
}

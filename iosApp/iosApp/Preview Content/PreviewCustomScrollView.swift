//
//  PreviewCustomScrollView.swift
//

import SwiftUI
import BridgeClientUI

struct PreviewCustomScrollView: View {
    @State var items: [Item] = [Int](0..<100).map { .init(id: "\($0) Hello, World") }
    var body: some View {
        CustomScrollView {
            LazyVStack {
                ForEach(items) { item in
                    Button(item.id) {
                        items.remove(where: { $0 == item})
                    }
                }
            }
        }
    }
    
    struct Item : Identifiable, Hashable {
        let id: String
    }
}

struct PreviewCustomScrollView_Previews: PreviewProvider {
    static var previews: some View {
        PreviewCustomScrollView()
    }
}

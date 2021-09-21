//
//  CustomScrollView.swift
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

public struct CustomScrollView<Content : View>: View {
    private let content: Content
    @StateObject private var viewModel: ViewModel = .init()

    public init(_ content: @escaping () -> Content) {
        self.content = content()
    }
    
    public var body: some View {
        ContentView(height: $viewModel.viewHeight) {
            ScrollViewReader { scrollView in
                ZStack(alignment: .bottomTrailing) {
                    
                    ScrollView(.vertical) {
                        ZStack(alignment: .top) {
                            GeometryReader { proxy in
                                Color.clear
                                    .preference(key: ScrollFramePreferenceKey.self,
                                                value: proxy.frame(in: .named("scroll")))
                            }
                            makePageMarkers()
                            ContentView(height: $viewModel.scrollHeight) {
                                content
                            }
                        }
                    }
                    .coordinateSpace(name: "scroll")
                    .frame(maxWidth: .infinity)
                    .onPreferenceChange(ScrollFramePreferenceKey.self) { value in
                        // syoung 09/09/2021 So... it turns out that this isn't always called
                        // on the main thread so it was getting updated multiple times per
                        // frame.
                        DispatchQueue.main.async {
                            viewModel.scrollOffset = abs(floor(value.minY))
                        }
                    }
                    
                    makeButtons(scrollView: scrollView)

                } // end ZStack (for overlay buttons)
            }// end ScrollViewReader
        }
    }// end body
    
    @ViewBuilder
    private func makeButtons(scrollView: ScrollViewProxy) -> some View {
        VStack(alignment: .trailing, spacing: 13) {
            Button("Scroll Up", bundle: .module) {
                viewModel.scrollUp(scrollView)
            }
            .buttonStyle(ScrollButtonStyle(up: true, enabled: $viewModel.upEnabled))
            
            Button("Scroll Down", bundle: .module) {
                viewModel.scrollDown(scrollView)
            }
            .buttonStyle(ScrollButtonStyle(up: false, enabled: $viewModel.downEnabled))
        }
        .opacity(viewModel.scrollEnabled ? 1 : 0)
        .padding(.trailing, 9)
        .padding(.bottom, 16)
    }
    
    @ViewBuilder
    private func makePageMarkers() -> some View {
        LazyVStack(spacing: 0) {
            ForEach(viewModel.pages) { page in
                Color.clear
                    .frame(height: viewModel.height(for: page))
            }
        }
    }
    
    struct Placeholder : Identifiable, Hashable {
        let id: UUID = .init()
    }
    
    class ViewModel : ObservableObject {
        @Published var pages: [Placeholder] = []
        @Published var upEnabled: Bool = true
        @Published var downEnabled: Bool = true
        @Published var scrollEnabled: Bool = true
        
        @Published var scrollOffset: CGFloat = 0 {
            didSet {
                upEnabled = scrollOffset > 10
                downEnabled = scrollHeight - (scrollOffset + viewHeight) > 10 || (round(scrollOffset) == 0)
            }
        }
        
        @Published var viewHeight: CGFloat = 0 {
            didSet {
                updatePages()
            }
        }
        
        @Published var scrollHeight: CGFloat = 0 {
            didSet {
                updatePages()
            }
        }
        
        func height(for page: Placeholder) -> CGFloat {
            page == pages.last
                ? (scrollHeight - (CGFloat(pages.count - 1) * viewHeight))
                : viewHeight
        }
        
        func scrollUp(_ scrollView: ScrollViewProxy) {
            let normalizedOffset = scrollOffset / viewHeight
            let currentIndex = Int(ceil(normalizedOffset))
            let index = max(currentIndex - 1, 0)
            scrollView.scrollTo(pages[index].id, anchor: .top)
        }
        
        func scrollDown(_ scrollView: ScrollViewProxy) {
            let normalizedOffset = scrollOffset / viewHeight
            let currentIndex = Int(round(normalizedOffset))
            let index = min(currentIndex + 1, pages.count - 1)
            scrollView.scrollTo(pages[index].id, anchor: .bottom)
        }
        
        private func updatePages() {
            scrollEnabled = scrollHeight > viewHeight
            guard scrollHeight > 0, viewHeight > 0, scrollEnabled
            else {
                // Do not load any pages if the view is longer than the content.
                self.pages = []
                return
            }
            // Figure out how many pages are needed.
            let pageCount = Int(ceil(scrollHeight/viewHeight))
            if pages.count > 0 {
                // Lop off the end. If there are more pages than there are currently
                // then doing so will refresh the last page with a new height by
                // replacing the UUID that is used as the identifier.
                pages = Array(pages[0..<(min(pageCount, pages.count) - 1)])
            }
            // Finally, add pages until the counts match.
            // Note: syoung 08/18/2021 The view crashes if you do not add one at a time.
            while pages.count < pageCount {
                pages.append(.init())
            }
        }
    }
    
    struct ContentView<Content : View>: View {
        private let content: Content
        @Binding private var contentHeight: CGFloat
        
        public init(height: Binding<CGFloat>, _ content: @escaping () -> Content) {
            self._contentHeight = height
            self.content = content()
        }
        
        var body: some View {
            ZStack {
                content
            }
            .background(GeometryReader { proxy in
                Color.clear
                    .preference(key: ViewHeightPreferenceKey.self,
                                value: proxy.size.height)
            })
            .onPreferenceChange(ViewHeightPreferenceKey.self) { value in
                DispatchQueue.main.async {
                    guard contentHeight != floor(value) else { return }
                    contentHeight = floor(value)
                }
            }
        }
    }

    struct ScrollButtonStyle : ButtonStyle {
        let up: Bool
        @Binding var enabled: Bool
        
        @ViewBuilder
        func makeBody(configuration: Self.Configuration) -> some View {
            VStack {
                if up {
                    Image(systemName: "arrow.up")
                        .font(.system(size: 18))
                }
                Text("scroll", bundle: .module)
                    .font(.latoFont(10, relativeTo: nil, weight: .regular))
                if !up {
                    Image(systemName: "arrow.down")
                        .font(.system(size: 18))
                }
            }
            .opacity(enabled ? 1 : 0.3)
            .foregroundColor(.textForeground)
            .frame(width: 48, height: 48)
            .background(enabled ? Color.accentColor : Color.hexDEDEDE)
            .clipShape(Capsule())
            .shadow(color: .sageBlack.opacity(0.25), radius: 4, x: 0, y: 4)
            .opacity((enabled || !up) ? 1 : 0)
        }
    }
}

fileprivate struct ScrollFramePreferenceKey: PreferenceKey {
    static var defaultValue: CGRect = .zero
    static func reduce(value: inout CGRect, nextValue: () -> CGRect) {}
}

fileprivate struct ViewHeightPreferenceKey: PreferenceKey {
    static var defaultValue: CGFloat = .zero
    static func reduce(value: inout CGFloat, nextValue: () -> CGFloat) {}
}

extension Button where Label == Text {
    init(_ titleKey: LocalizedStringKey, bundle: Bundle?, action: @escaping () -> Void) {
        self.init(action: action, label: { Text(titleKey, bundle: bundle) })
    }
}

// syoung 08/16/2021 SwiftUI fails to build complex UI in a shared framework. Therefore, the preview
// for this element is in iosApp.
struct CustomScrollView_Previews: PreviewProvider {
    static var previews: some View {
        Text("Hello, World")
    }
}

//
//  CustomTabView.swift
//

import SwiftUI
import SharedMobileUI

public protocol TabItem : Identifiable, Hashable {
    /// The title for the tab item.
    func title() -> Text
    
    /// The icon to show when *not* selected.
    func icon() -> Image
    
    /// The icon to show when it is selected. By default, this will be tinted using the ``Color.accentColor``.
    func selectedIcon() -> Image
    
    /// If `true`, then this is an underlay-style icon and image so when selected, *both* the ``icon()``
    /// and ``selectedIcon()`` are shown. If `false`, then the ``icon()`` is hidden when selected.
    var isUnderlay: Bool { get }
}

/// The default implementation is to use an enum where the images are named with a specific pattern.
public protocol EnumTabItem : TabItem {
    var rawValue: String { get }
    var bundle: Bundle? { get }
}

public extension EnumTabItem {
    var id: String { rawValue }
    var iconName: String { rawValue }
    
    var isUnderlay: Bool { true }
    
    func icon() -> Image {
        .init(decorative: iconName, bundle: bundle)
    }
    
    func selectedIcon() -> Image {
        .init(decorative: "\(iconName).selected", bundle: bundle)
    }
}

public struct CustomTabView<Tab : TabItem, Content : View>: View {
    @Binding private var selectedTab : Tab
    private let tabs: [Tab]
    private let placement: VerticalAlignment
    private let titles: [Tab : Text]
    private let icons: [Tab : Image]
    private let selectedIcons: [Tab : Image]
    private let content: (Tab) -> Content
    
    public init(selectedTab: Binding<Tab>, tabs: [Tab], placement: VerticalAlignment, @ViewBuilder content: @escaping (Tab) -> Content) {
        self._selectedTab = selectedTab
        self.tabs = tabs
        self.placement = placement
        self.titles = tabs.reduce([Tab: Text]()) { (dict, tab) -> [Tab: Text] in
            var dict = dict
            dict[tab] = tab.title()
            return dict
        }
        self.icons = tabs.reduce([Tab: Image]()) { (dict, tab) -> [Tab: Image] in
            var dict = dict
            dict[tab] = tab.icon()
            return dict
        }
        self.selectedIcons = tabs.reduce([Tab: Image]()) { (dict, tab) -> [Tab: Image] in
            var dict = dict
            dict[tab] = tab.selectedIcon()
            return dict
        }
        self.content = content
    }
    
    public var body: some View {
        GeometryReader { geometry in
            VStack(spacing: 0) {
                if placement == .bottom {
                    content(selectedTab)
                        .frame(maxHeight: .infinity)
                    Divider()
                        .background(Color.hexDEDEDE)
                }
                
                tabBar()
                
                if placement == .top {
                    content(selectedTab)
                        .frame(maxWidth: .infinity, maxHeight: .infinity)
                        .gesture(
                            DragGesture().updating($translation) { value, state, _ in
                                state = value.translation.width
                            }.onEnded { value in
                                let offset = value.translation.width / geometry.size.width * 1.25
                                let newIndex = (CGFloat(tabs.firstIndex(of: selectedTab)!) - offset).rounded()
                                self.selectedTab = tabs[min(max(Int(newIndex), 0), tabs.count - 1)]
                            }
                        )
                }
            }
        }
    }
    
    // Keeps track of how much did user swipe left or right.
    @GestureState private var translation: CGFloat = 0
    
    // The size of the tab buttons
    private let buttonSize: CGFloat = 64
    
    // Used to set the allowed max height of all titles so that different length
    // strings will all be at the same height.
    // Modified from https://georgegarside.com/blog/ios/swiftui-equal-scaling-text-size-to-fit/
    @State private var labelHeight: CGFloat = SizePreferenceKey.defaultValue
    
    @ViewBuilder
    private func tabBar() -> some View {
        HStack(alignment: .bottom, spacing: 0) {
            ForEach(tabs) { tab in
                let isSelected = self.selectedTab == tab
                VStack(spacing: 0) {
                    tabButton(for: tab, isSelected: isSelected)
                        .frame(height: buttonSize, alignment: .bottom)
                        .frame(minWidth: buttonSize)
                    if placement == .top {
                        Rectangle()
                            .fill(isSelected ? Color.accentColor : Color.hexE5E5E5)
                            .frame(height: 4)
                    }
                }
                .frame(minWidth: 0, maxWidth: .infinity)
            }
        }
        .onPreferenceChange(SizePreferenceKey.self, perform: { labelHeight = $0 })
        .background(backgroundColor().edgesIgnoringSafeArea(.all))
    }
    
    let buttonFont: [Bool : Font] = [
        true : DesignSystem.fontRules.buttonFont(at: 2, isSelected: true),
        false : DesignSystem.fontRules.buttonFont(at: 2, isSelected: false)
    ]
    
    let buttonColor: [Bool : Color] = [
        true : DesignSystem.fontRules.buttonColor(at: 2, isSelected: true),
        false : DesignSystem.fontRules.buttonColor(at: 2, isSelected: false)
    ]
    
    @ViewBuilder
    private func tabButton(for tab: Tab, isSelected: Bool) -> some View {
        let imageTopOffset: CGFloat = (placement == .bottom) ? 4 : 0
        Button(action: { self.selectedTab = tab }) {
            ZStack(alignment: .bottom) {
                ZStack {
                    selectedIcons[tab]
                        .foregroundColor(.accentColor)
                        .opacity(isSelected ? 1 : 0)
                    icons[tab]
                        .opacity(!isSelected || tab.isUnderlay ? 1 : 0)
                }
                .padding(.top, imageTopOffset)
                .frame(height: buttonSize - imageTopOffset, alignment: .top)
                titles[tab]!
                    .textCase(placement == .top ? .uppercase : nil)
                    .font(buttonFont[isSelected])
                    .foregroundColor(buttonColor[isSelected])
                    .scaledToFit()
                    .minimumScaleFactor(0.5)
                    .lineLimit(1)
                    .background(GeometryReader {
                        Color.clear.preference(key: SizePreferenceKey.self, value: $0.size.height)
                    })
                    .frame(maxHeight: labelHeight)
                    .padding(.top, 5)
                    .padding(.bottom, 9)
            }
        }
        .accessibility(label: titles[tab]!)
        .accessibility(addTraits: isSelected ? [.isSelected] : [.isButton])
        .accessibility(removeTraits: isSelected ? [.isButton] : [.isSelected])
    }
    
    private func backgroundColor() -> Color {
        placement == .bottom ? .hexFDFDFD : .screenBackground
    }
}

fileprivate struct SizePreferenceKey: PreferenceKey {
    static var defaultValue: CGFloat = 28.0
    static func reduce(value: inout CGFloat, nextValue: () -> CGFloat) {
        value = min(value, nextValue())
    }
}

// syoung 08/16/2021 SwiftUI fails to build complex UI in a shared framework. Therefore, the preview
// for this element is in iosApp.
struct CustomTabView_Previews: PreviewProvider {
    static var previews: some View {
        Text("Hello, World!")
    }
}


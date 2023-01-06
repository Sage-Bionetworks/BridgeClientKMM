//
//  AssessmentInfoMap.swift
//

import SwiftUI
import BridgeClient
import SharedMobileUI
import AssessmentModel
import AssessmentModelUI

/// A protocol for mapping the display information about an assessment.
public protocol AssessmentInfoExtension {
    /// The **Bridge 2.0** assessment identifier. (Not to be confused with the "task identifier" used in
    /// mappings of BridgeSDK/BridgeApp "legacy" assessments.)
    var assessmentIdentifier: String { get }
    
    /// The title of the assessment.
    func title() -> Text
    
    /// The icon to use when displaying an `AssessmentTimelineCardView`.
    ///
    /// - Note: This is different from the smaller icon used for displaying BridgeSDK/BridgeApp
    /// lists of tasks.
    func icon() -> ContentImage
    
    /// The color to use when displaying an `AssessmentTimelineCardView`.
    func color() -> Color
}

/// The `AssessmentInfoMap` is an environmental variable that is used to allow shared views
/// to know about the `Color`, `Text`, and `Image` to use for a given assessment while
/// allowing those values to be set at the app level. Since this framework does not directly link in
/// any assessment libraries, the app has the responsibility for setting up those mappings.
///
/// - Note: This struct uses `BridgeClient.AssessmentInfo` in its mapping and its
/// functions should only ever be called from the main thread.
public struct AssessmentInfoMap {
    private let mappings: [String : Mapping]
    private let defaultColor: Color
    
    private struct Mapping {
        let title: Text
        let icon: ContentImage
        let color: Color
    }
    
    private let durationFormatter: DateComponentsFormatter = {
        let formatter = DateComponentsFormatter()
        formatter.unitsStyle = .short
        formatter.allowedUnits = .minute
        return formatter
    }()
    
    public init(extensions: [AssessmentInfoExtension] = [], defaultColor: Color = .accentColor) {
        self.defaultColor = defaultColor
        self.mappings = extensions.reduce([String : Mapping]()) { (dict, input) -> [String : Mapping] in
            var dict = dict
            dict[input.assessmentIdentifier] = Mapping(title: input.title(), icon: input.icon(), color: input.color())
            return dict
        }
    }
    
    /// The mapped title for a given assessment.
    public func title(for info: BridgeClient.AssessmentInfo) -> Text {
        !info.label.isEmpty ? Text(LocalizedStringKey(info.label)) : (mappings[info.assessmentId]?.title ?? Text(info.assessmentId))
    }
    
    /// The mapped icon to use for a given assessment when displaying an `AssessmentTimelineCardView`.
    public func icon(for info: BridgeClient.AssessmentInfo) -> ContentImage {
        mappings[info.assessmentId]?.icon ?? ContentImage(icon: info.iconKey, isList: true)
    }
    
    /// The mapped color to use for a given assessment when displaying an `AssessmentTimelineCardView`.
    public func color(for info: BridgeClient.AssessmentInfo) -> Color {
        if let hexString = info.colorScheme?.foreground,
           let color = Color.init(hex: hexString) {
            return color
        }
        else {
            return mappings[info.assessmentId]?.color ?? defaultColor
        }
    }
    
    /// The estimated time required to perform the assessment.
    public func estimatedTime(for info: BridgeClient.AssessmentInfo) -> Text {
        let duration: TimeInterval = Double(truncating: info.minutesToComplete ?? 3) * 60
        return Text(durationFormatter.string(from: duration) ?? "")
    }
}

extension BridgeClient.AssessmentInfo {
    fileprivate var assessmentId: String { identifier }
    fileprivate var iconKey: SageResourceImage.Name {
        self.imageResource.flatMap { SageResourceImage.Name(rawValue: $0.name) } ?? .allCases.first!
    }
}

public struct AssessmentInfoMapEnvironmentKey: EnvironmentKey {
    public static let defaultValue: AssessmentInfoMap = .init()
}

extension EnvironmentValues {
    public var assessmentInfoMap: AssessmentInfoMap {
        get { self[AssessmentInfoMapEnvironmentKey.self] }
        set { self[AssessmentInfoMapEnvironmentKey.self] = newValue }
    }
}

extension View {
    public func assessmentInfoMap(_ assessmentInfoMap: AssessmentInfoMap) -> some View {
        environment(\.assessmentInfoMap, assessmentInfoMap)
    }
}


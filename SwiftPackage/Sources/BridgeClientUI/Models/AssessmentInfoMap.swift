//
//  AssessmentInfoMap.swift
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
import BridgeClient
import SharedMobileUI

public protocol AssessmentInfoExtension {
    var assessmentIdentifier: String { get }
    func title() -> Text
    func icon() -> Image
    func color() -> Color
}

public struct AssessmentInfoMap {
    private let mappings: [String : Mapping]
    
    private struct Mapping {
        let title: Text
        let icon: Image
        let color: Color
    }
    
    private let durationFormatter: DateComponentsFormatter = {
        let formatter = DateComponentsFormatter()
        formatter.unitsStyle = .short
        formatter.allowedUnits = .minute
        return formatter
    }()
    
    public init(extensions: [AssessmentInfoExtension] = []) {
        self.mappings = extensions.reduce([String : Mapping]()) { (dict, input) -> [String : Mapping] in
            var dict = dict
            dict[input.assessmentIdentifier] = Mapping(title: input.title(), icon: input.icon(), color: input.color())
            return dict
        }
    }
    
    public func title(for info: AssessmentInfo) -> Text {
        info.label.map { Text(LocalizedStringKey($0)) } ?? mappings[info.assessmentId]?.title ?? Text(info.assessmentId)
    }
    
    public func icon(for info: AssessmentInfo) -> Image {
        mappings[info.assessmentId]?.icon ?? Image(info.assessmentId, bundle: Bundle.main, label: title(for: info))
    }
    
    public func color(for info: AssessmentInfo) -> Color {
        if let hexString = info.colorScheme?.foreground,
           let color = Color.init(hex: hexString) {
            return color
        }
        else {
            return mappings[info.assessmentId]?.color ?? .appBlue
        }
    }
    
    public func estimatedTime(for info: AssessmentInfo) -> Text {
        let duration: TimeInterval = Double(truncating: info.minutesToComplete ?? 3) * 60
        return Text(durationFormatter.string(from: duration) ?? "")
    }
}

extension AssessmentInfo {
    fileprivate var assessmentId: String { identifier ?? "" }
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


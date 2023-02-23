//
//  StudyIdLoginView.swift
//


import SwiftUI
import BridgeClient
import SharedMobileUI

struct StudyIdLoginView: View {
    @Binding var studyId: String
    @Binding var status: ResourceStatus?
    
    public var body: some View {
        VStack(spacing: 0) {
            
            Image("AppLogo")
                .padding(.bottom, 55)
            
            Text("Please enter your Study ID below to begin.", bundle: .module)
                .font(DesignSystem.fontRules.headerFont(at: 2))
                .foregroundColor(.textForeground)
                .fixedSize(horizontal: false, vertical: true)
                .padding(.horizontal, 18)
                .padding(.bottom, 55)
            
            TextEntryLoginView(value: $studyId, status: $status,
                               label: Text("Study ID", bundle: .module),
                               error: Text("Sorry, we cannot find this study. Please try again or contact your Study Coordinator.", bundle: .module))
        }
        .padding(.horizontal, 32)
    }

}

struct StudyIdLoginView_Preview : View {
    @State var studyId: String
    @State var status: ResourceStatus?
    
    init(studyId: String = "", status: ResourceStatus? = nil) {
        self.studyId = studyId
        self.status = status
    }
    
    var body: some View {
        StudyIdLoginView(studyId: $studyId, status: $status)
    }
}

struct StudyIdLoginView_Previews: PreviewProvider {
    static var previews: some View {
        Group {
            StudyIdLoginView_Preview(studyId: "foo", status: .failed)
            StudyIdLoginView_Preview()
                .previewDevice("iPhone 12 mini")
                .environment(\.sizeCategory, .accessibilityExtraLarge)
        }
    }
}

//
//  ExternalIdLoginView.swift
//
//

import SwiftUI
import BridgeClient
import BridgeClientUI
import SharedMobileUI

public struct ExternalIdLoginView: View {
    @EnvironmentObject var bridgeManager: SingleStudyAppManager
    @State var externalId: String = ""
    @State var status: ResourceStatus?
    
    public var body: some View {
        VStack {
            VStack(alignment: .leading, spacing: 8, content: {
                Text(bridgeManager.title)
                    .font(.poppinsFont(18, relativeTo: .title, weight: .semibold))
                
                if let studyID = bridgeManager.studyId {
                    Text("Study ID:  \(studyID)")
                        .font(.latoFont(15, relativeTo: .subheadline, weight: .regular))
                }
            })
            .padding(.horizontal, 60)

            HStack {
                Text("Participant ID:")
                    .font(Font.poppinsFont(14, relativeTo: .title2, weight: .medium))
                Spacer()
            }.padding(.top, 50)
                
            TextField("", text: $externalId)
                .padding(.horizontal)
                .padding(.vertical)
                .border(/*@START_MENU_TOKEN@*/Color.black/*@END_MENU_TOKEN@*/, width: /*@START_MENU_TOKEN@*/1/*@END_MENU_TOKEN@*/)
    
            HStack {
                Spacer()
                Button("Login", action: signIn)
                    .buttonStyle(NavigationButtonStyle())
                    .overlay(
                            ProgressView()
                                .padding(.trailing, 8)
                                .colorInvert()
                                .opacity(status == ResourceStatus.pending ? 1.0 : 0.0)
                        , alignment: .trailing)
                    .disabled(status == ResourceStatus.success || status == ResourceStatus.pending)
            }
            .padding(.top, 20)
            if status == ResourceStatus.failed {
                Text("This Participant Id will not work for this study.")
                    .foregroundColor(.red)
            }
        }
        .padding(.horizontal, 40)
    }
    
    func signIn() {
        guard externalId.count > 0 else { return }
        self.status = ResourceStatus.pending
        bridgeManager.loginWithExternalId(externalId, password: externalId) { status in
            self.status = status
        }
    }
}

struct ExternalIdLoginView_Previews: PreviewProvider {
    static var previews: some View {
        Group {
            ExternalIdLoginView()
                .environmentObject(SingleStudyAppManager(appId: kPreviewStudyId))
            ExternalIdLoginView()
                .preferredColorScheme(.dark)
                .environmentObject(SingleStudyAppManager(appId: kPreviewStudyId))
        }
    }
}

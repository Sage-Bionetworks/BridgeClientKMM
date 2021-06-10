//
//  ExternalIdLoginView.swift
//
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

public struct ExternalIdLoginView: View {
    @EnvironmentObject var bridgeManager: BridgeClientAppManager
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
                    .disabled(status == ResourceStatus.success ||
                                status == ResourceStatus.pending)
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
        bridgeManager.loginWithExternalId(externalId) { status in
            self.status = status
        }
    }
}

struct ExternalIdLoginView_Previews: PreviewProvider {
    static var previews: some View {
        Group {
            ExternalIdLoginView()
                .environmentObject(BridgeClientAppManager(appId: "preview"))
            ExternalIdLoginView()
                .preferredColorScheme(.dark)
                .environmentObject(BridgeClientAppManager(appId: "preview"))
        }
    }
}

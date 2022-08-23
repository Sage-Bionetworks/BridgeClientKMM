//
//  LoginView.swift
//  BiAffectPreview
//
//  Copyright © 2022 BiAffect. All rights reserved.
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
import BridgeClientUI
import SharedMobileUI

extension Color {
    static let errorRed: Color = .init("error.red", bundle: .module)
}

struct LoginView: View {
    @EnvironmentObject var bridgeManager: SingleStudyAppManager
    @State var loginStatus: ResourceStatus?
    @State var participantId = ""
    
    // For this app, there is no log into the study and then as the participant.
    let studyId = kStudyId

    var body: some View {
        // For this preview app, everyone is signed in with the same login.
        VStack(alignment: .trailing) {
            Spacer()
            textEntry()
            loginButton()
            Spacer()
        }
        .padding(32)
    }
    
    @ViewBuilder
    func textEntry() -> some View {
        VStack(alignment: .leading, spacing: 4) {
            Text("Participant ID")
                .font(DesignSystem.fontRules.headerFont(at: 5))
                .foregroundColor((loginStatus == .failed) ? .errorRed : .textForeground)
            
            TextField("", text: $participantId, onEditingChanged: { isEditing in
                if isEditing && (loginStatus == .failed) {
                    self.loginStatus = nil // When the user starts editing, hide the error.
                }
            }, onCommit: {
                self.loginParticipant()
            })
            .keyboardType(.asciiCapable)
            .autocapitalization(.none)
            .disableAutocorrection(true)
            .lineLimit(1)
            .padding(.horizontal)
            .padding(.vertical)
            .border((loginStatus == .failed) ? Color.errorRed : Color.sageBlack, width: 1)
            .disabled(loginStatus == .pending)
            
            if (loginStatus == .failed) {
                Text("Sorry, we cannot find this Participant ID. Please try again or contact your Study Coordinator.")
                    .font(DesignSystem.fontRules.bodyFont(at: 1, isEmphasis: false))
                    .foregroundColor(.errorRed)
                    .fixedSize(horizontal: false, vertical: true)
                    .padding(.vertical, 12)
            }
            else {
                Spacer()
                    .frame(height: 16)
            }
        }
    }
    
    @ViewBuilder
    func loginButton() -> some View {
        Button(action: loginParticipant) {
            Text("Login")
        }
        .buttonStyle(NavigationButtonStyle(.text))
        .buttonEnabled(loginStatus != .pending)
        .overlay(progressSpinner(), alignment: .trailing)
    }
    
    @ViewBuilder
    func progressSpinner() -> some View {
        ProgressView()
            .padding(.trailing, 8)
            .colorInvert()
            .opacity(loginStatus == .pending ? 1.0 : 0.0)
    }
     
    private var studyInfoManager: NativeStudyInfoManager = .init()
    
    func loginParticipant() {
        self.loginStatus = .pending
        self.studyInfoManager.fetchStudyInfo(studyId: studyId) { (studyInfo, status) in
            let observer = StudyObserver(identifier: studyId)
            if let studyInfo = studyInfo, status == .success, observer.update(from: studyInfo) {
                bridgeManager.study = observer
                let externalId = "\(participantId):\(studyId)"
                bridgeManager.loginWithExternalId(externalId, password: externalId) { status in
                    self.loginStatus = status
                }
            }
            self.loginStatus = status
        }
    }
}

struct LoginView_Previews: PreviewProvider {
    static var previews: some View {
        LoginView()
    }
}

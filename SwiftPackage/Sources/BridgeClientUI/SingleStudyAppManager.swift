//
//  SingleStudyAppManager.swift
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

fileprivate let kStudyIdKey = "studyId"

public final class SingleStudyAppManager : BridgeClientAppManager {
    
    @Published public var studyId: String? {
        didSet {
            UserDefaults.standard.set(studyId, forKey: kStudyIdKey)
        }
    }
    
    public override func didSetUserSessionInfo(oldValue: UserSessionInfo?) {
        super.didSetUserSessionInfo(oldValue: oldValue)
        updateStudy()
    }
    
    @Published public var study: Study?
    @Published public var isStudyComplete: Bool = false
    
    private var studyManager: NativeStudyManager!
    
    public override init(platformConfig: PlatformConfig) {
        super.init(platformConfig: platformConfig)
        self.studyId = self.isPreview ? kPreviewStudyId : UserDefaults.standard.string(forKey: kStudyIdKey)
    }
    
    public override func appWillFinishLaunching(_ launchOptions: [UIApplication.LaunchOptionsKey : Any]?) {
        super.appWillFinishLaunching(launchOptions)
        self.studyManager = NativeStudyManager() { [weak self] study in
            self?.study = study
        }
        updateStudy()
    }
    
    public override func signOut() {
        try? studyManager?.onCleared()
        studyManager = nil
        study = nil
        super.signOut()
    }
    
    public func fetchStudyInfo(_ studyId: String, completion: @escaping ((StudyInfo?, BridgeClient.ResourceStatus) -> Void)) {
        self.studyId = studyId
        self.studyManager.fetchStudyInfo(studyId: studyId, callBack: completion)
    }
    
    private var observedStudyId: String?
    
    private func updateStudy() {
        guard (authManager?.isAuthenticated() ?? false),
              let studyIds = userSessionInfo?.studyIds, studyIds.count > 0,
              let studyManager = self.studyManager
        else {
            return
        }
        let previousStudyId = observedStudyId
        if studyId == nil || !studyIds.contains(studyId!) {
            studyId = studyIds.first
            print("Setting studyId=\(studyId!)")
        }
        guard let studyId = self.studyId, studyId != previousStudyId
        else {
            return
        }

        try? studyManager.onCleared()
        self.observedStudyId = studyId
        studyManager.observeStudy(studyId: studyId)
    }
}


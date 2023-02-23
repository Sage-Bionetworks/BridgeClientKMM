//
//  LoginView.swift
//

import SwiftUI
import BridgeClient
import BridgeClientExtension
import SharedMobileUI

extension Color {
    static let errorRed: Color = .init("error.red", bundle: .module)
}

public struct SingleStudyLoginView: View {
    @EnvironmentObject var bridgeManager: SingleStudyAppManager
    
    public init() {
    }
    
    public var body: some View {
        SingleStudyLoginWrapperView(bridgeManager: bridgeManager)
    }
}

public struct SingleStudyLoginWrapperView : View {
    @ObservedObject private var bridgeManager: AbstractSingleStudyAppManager
    
    public init(bridgeManager: AbstractSingleStudyAppManager) {
        self.bridgeManager = bridgeManager
    }
    
    @StateObject var navigator: PagedNavigationViewModel = .init(pageCount: 2, progressHidden: true)
    
    @State var studyId: String = ""
    @State var participantId: String = ""
    @State var studyInfo: StudyObserver?
    @State var studyInfoStatus: ResourceStatus?
    @State var loginStatus: ResourceStatus?
    
    private enum ViewState: String {
        case studyId, externalIdLogin, phoneLogin
    }
    
    @State private var viewState: ViewState = .studyId
    
    public var body: some View {
        VStack {
            header()
            
            Spacer()
            
            switch viewState {
            case .studyId:
                StudyIdLoginView(studyId: $studyId, status: $studyInfoStatus)
            case .externalIdLogin:
                ExternalIdLoginView(externalId: $participantId, status: $loginStatus, studyInfo: $studyInfo)
            case .phoneLogin:
                Text("// TODO: Implement syoung 07/22/2021")
            }
            PagedNavigationBar()
                .overlay(progressSpinner(), alignment: .trailing)
                .padding(.horizontal, 34)
            
            Spacer()
        }
        .environmentObject(navigator)
        .onAppear {
            setupNavigator()
            updateViewState()
        }
    }
    
    @ViewBuilder
    func header() -> some View {
        if let study = self.studyInfo, viewState != .studyId {
            let headerColor: Color = study.backgroundColor
            LogoImage(url: study.studyLogoUrl)
                .background(headerColor.edgesIgnoringSafeArea(.top))
        }
        else {
            EmptyView()
        }
    }
    
    @ViewBuilder
    func progressSpinner() -> some View {
        ProgressView()
            .padding(.trailing, 8)
            .colorInvert()
            .opacity(isLoading ? 1.0 : 0.0)
    }
    
    var isLoading: Bool {
        studyInfoStatus == .pending || loginStatus == .pending || loginStatus == .success
    }
    
    func updateViewState() {
        navigator.backEnabled = studyInfoStatus == .success
        guard navigator.backEnabled else {
            viewState = .studyId
            navigator.forwardButtonText = nil
            return
        }
        navigator.forwardButtonText = Text("Login", bundle: .module)
        if let signInTypes = self.studyInfo?.signInTypes, signInTypes.contains(.phoneMessage) {
            viewState = .phoneLogin
        }
        else {
            viewState = .externalIdLogin
        }
    }
    
    func setupNavigator() {
        navigator.goForward = goForward
        navigator.goBack = goBack
    }
    
    func goForward() {
        switch viewState {
        case .studyId:
            fetchStudyInfo()
        case .externalIdLogin:
            signInWithExternalId()
        case .phoneLogin:
            signInWithPhone()
        }
    }
    
    func goBack() {
        self.studyInfoStatus = nil
        self.loginStatus = nil
        self.updateViewState()
    }
    
    private var studyInfoManager: NativeStudyInfoManager = .init()
    
    func fetchStudyInfo() {
        guard studyId.count > 0,
              self.studyInfoStatus != .pending,
              self.studyInfoStatus != .success
        else {
            return
        }
        self.studyInfoStatus = .pending
        
        self.studyInfoManager.fetchStudyInfo(studyId: studyId) { (studyInfo, status) in
            let observer = StudyObserver(identifier: studyId)
            if let studyInfo = studyInfo, status == .success, observer.update(from: studyInfo) {
                self.studyInfo = observer
                bridgeManager.study = observer
            }
            else {
                self.studyInfo = nil
            }
            self.studyInfoStatus = status
            self.updateViewState()
        }
    }
    
    func signInWithExternalId() {
        guard participantId.count > 0,
              self.loginStatus != .pending,
              self.loginStatus != .success
        else {
            return
        }
        self.loginStatus = .pending
        let externalId = "\(participantId):\(studyId)"
        #if DEBUG
        debugPrint(externalId)
        #endif
        bridgeManager.loginWithExternalId(externalId, password: externalId) { status in
            self.loginStatus = status
        }
    }
    
    func signInWithPhone() {
        // TODO: Implement syoung 07/22/2021
    }
}

struct LoginView_Previews: PreviewProvider {
    static var previews: some View {
        Group {
            SingleStudyLoginView()
                .environmentObject(SingleStudyAppManager(appId: kPreviewStudyId))
        }
    }
}

let previewStudyInfo_ExternalId =
    StudyInfo(identifier: kPreviewStudyId,
              name: "Sleep & Cognition",
              details: nil,
              phase: StudyPhase.design,
              studyLogoUrl: "https://docs.sagebridge.org/5rht4Xajwu2N69EPlHXfjT-Y.1632172103361",
              colorScheme: .init(foreground: nil, background: "#CC8899", activated: nil, inactivated: nil, type: "ColorScheme"),
              signInTypes: [.externalIdPassword],
              type: "StudyInfo")

let previewStudyInfo_Phone =
    StudyInfo(identifier: kPreviewStudyId,
              name: "Sleep & Cognition",
              details: nil,
              phase: StudyPhase.design,
              studyLogoUrl: nil,
              colorScheme: nil,
              signInTypes: [.phoneMessage],
              type: "StudyInfo")

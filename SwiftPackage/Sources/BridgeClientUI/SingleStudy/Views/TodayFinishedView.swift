// Created 2/21/23
// swift-tools-version:5.0

import SwiftUI
import BridgeClientExtension
import SharedMobileUI

protocol TodayFinishedViewProtocol : View {
    init()
}

struct TodayFinishedView : View, TodayFinishedViewProtocol {
    @EnvironmentObject private var bridgeManager: SingleStudyAppManager
    @EnvironmentObject private var viewModel: TodayTimelineViewModel
    
    var body: some View {
        UploadingMessageView(isUploading: $bridgeManager.isUploading,
                             networkStatus: $bridgeManager.networkStatus,
                             isNextSessionSoon: viewModel.isNextSessionSoon)
    }
}

struct UploadingMessageView : View {
    @Binding var isUploading: Bool
    @Binding var networkStatus: NetworkStatus
    let isNextSessionSoon: Bool
    
    var body: some View {
        ZStack {
            uploadingView()
                .opacity(isUploading ? 1 : 0)
            TodayUpToDateView()
                .opacity(isUploading ? 0 : 1)
        }
    }
    
    @ViewBuilder
    func uploadingView() -> some View {
        VStack(spacing: 24) {
            if networkStatus == .notConnected || networkStatus == .cellularDenied {
                Image(systemName: "wifi.exclamationmark")
                    .scaleEffect(x: 1.5, y: 1.5, anchor: .center)
                    .foregroundColor(.red)
            } else {
                progressSpinner()
            }
            uploadingMessageText()
                .font(.italicLatoFont(22))
        }
        .padding()
    }
    
    @ViewBuilder
    func progressSpinner() -> some View {
        if #available(iOS 15.0, *) {
            ProgressView()
                .tint(.accentColor)
                .scaleEffect(x: 1.5, y: 1.5, anchor: .center)
        } else {
            ProgressView()
        }
    }
    
    @ViewBuilder
    func uploadingMessageText() -> some View {
        switch networkStatus {
        case .cellularDenied:
            Text("Connect to WiFi or turn on cellular data in your phone's \"Settings\" to allow the app to upload your results.", bundle: .module)
        case .notConnected:
            Text("Please connect to the internet to upload your results.", bundle: .module)
        default:
            if isNextSessionSoon {
                Text("Your results are uploading...", bundle: .module)
            } else {
                Text("Your results are uploading. Please wait to close the app.", bundle: .module)
            }
        }
    }
}

struct TodayUpToDateView : View, TodayFinishedViewProtocol {
    var body: some View {
        ZStack {
            Image(decorative: "available_complete", bundle: .module)
            Text("Nice, you’re all up to date!", bundle: .module)
                // TODO: syoung 09/23/2021 Cut the image so that I can make this text dynamic.
                .font(.latoFont(fixedSize: 18))
        }
        .padding(.vertical, 24)
    }
}

struct PreviewAllTodayFinished : View {
    @State var isUploading: Bool = true
    @State var networkStatus: NetworkStatus = .connected
    @State var isNextSessionSoon: Bool = true
    
    var body: some View {
        VStack {
            UploadingMessageView(isUploading: $isUploading, networkStatus: $networkStatus, isNextSessionSoon: isNextSessionSoon)
            Spacer()
            Form {
                Toggle("isUploading", isOn: $isUploading)
                Toggle("isNextSessionSoon", isOn: $isNextSessionSoon)
                Picker("Network Connection", selection: $networkStatus) {
                    ForEach(NetworkStatus.allCases, id: \.self) { value in
                        Text(value.stringValue)
                            .tag(value)
                    }
                }
            }
        }
    }
}

struct TodayFinishedView_Previews: PreviewProvider {
    static var previews: some View {
        PreviewAllTodayFinished()
            .environmentObject(SingleStudyAppManager(appId: kPreviewStudyId))
    }
}

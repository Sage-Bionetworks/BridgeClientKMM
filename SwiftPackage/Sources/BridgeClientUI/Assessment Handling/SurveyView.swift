//
//  SurveyView.swift
//  
//

import SwiftUI
import JsonModel
import ResultModel
import AssessmentModel
import AssessmentModelUI
import BridgeClientExtension

/// Light-weight protocol for handling building the result archive.
public protocol ArchiveFactory {
    func buildResult(from assessmentState: AssessmentState, schedule: AssessmentScheduleInfo) -> ResultArchiveBuilder?
}

public struct DefaultArchiveFactory : ArchiveFactory {
    public init() {}
    
    public func buildResult(from assessmentState: AssessmentState, schedule: AssessmentScheduleInfo) -> ResultArchiveBuilder? {
        AssessmentArchiveBuilder(assessmentState.assessmentResult.deepCopy(),
                                 schedule: schedule,
                                 adherenceData: assessmentState.assessmentResult.buildScore(),
                                 outputDirectory: assessmentState.outputDirectory)
    }
}

extension Array where Element == ResultData {
    func mapAnswers() -> [String : JsonSerializable]? {
        let ret = self.reduce(into: [String : JsonSerializable]()) { dictionary, result in
            if let answerResult = result as? AnswerResult {
                answerResult.jsonValue.map {
                    dictionary[result.identifier] = $0.jsonObject()
                }
            }
            else if let branchResult = result as? BranchNodeResult {
                branchResult.buildScore().map {
                    dictionary[result.identifier] = $0
                }
            }
            else if let collectionResult = result as? CollectionResult {
                collectionResult.children.mapAnswers().map {
                    dictionary[result.identifier] = $0
                }
            }
        }
        return ret.count > 0 ? ret : nil
    }
}

extension BranchNodeResult {
    func buildScore() -> JsonSerializable? {
        let dict1 = self.stepHistory.mapAnswers() ?? [:]
        let dict2 = self.asyncResults?.mapAnswers() ?? [:]
        let ret = dict1.merging(dict2, uniquingKeysWith: { (first, _) in first })
        return ret.count > 0 ? ret : nil
    }
}

public struct SurveyView<DisplayView : AssessmentDisplayView>: View {
    let assessmentInfo: AssessmentScheduleInfo
    let handler: ScheduledAssessmentHandler
    let factory: ArchiveFactory
    let taskIdentifier: String
    
    @StateObject var viewModel: ViewModel = .init()
    
    public init(_ assessmentInfo: AssessmentScheduleInfo, handler: ScheduledAssessmentHandler, taskIdentifier: String? = nil, archiveFactory: ArchiveFactory? = nil) {
        self.assessmentInfo = assessmentInfo
        self.handler = handler
        self.factory = archiveFactory ?? DefaultArchiveFactory()
        self.taskIdentifier = taskIdentifier ?? assessmentInfo.assessmentIdentifier
    }
    
    public var body: some View {
        content()
            .onAppear {
                loadAssessment()
            }
            .onDisappear {
                viewModel.loadingTask?.cancel()
            }
    }
    
    @ViewBuilder
    func content() -> some View {
        if let assessment = viewModel.assessmentState {
            DisplayView(assessment)
                .assessmentStateListener(assessment, info: assessmentInfo, handler: handler, factory: factory)
        }
        else {
            ProgressView()
        }
    }
    
    func loadAssessment() {
        guard viewModel.assessmentState == nil, viewModel.loadingTask == nil else { return }
        viewModel.loadingTask = Task {
            do {
                let config = try await handler.fetchAssessmentConfig(for: assessmentInfo)
                guard !Task.isCancelled else { return }
                viewModel.assessmentState = try DisplayView.instantiateAssessmentState(
                    taskIdentifier,
                    config: config.config,
                    restoredResult: config.restoreResult,
                    interruptionHandling: nil)
            } catch {
                debugPrint("Failed to load assessment \(assessmentInfo.assessmentInfo.identifier): \(error)")
                handler.updateAssessmentStatus(assessmentInfo, status: .error(error))
            }
        }
    }

    @MainActor
    class ViewModel : ObservableObject {
        @Published var assessmentState: AssessmentState?
        var loadingTask: Task<Void, Never>?

        deinit {
            loadingTask?.cancel()
        }
    }
}

extension View {
    func assessmentStateListener(_ assessmentState: AssessmentState, info: AssessmentScheduleInfo, handler: ScheduledAssessmentHandler, factory: ArchiveFactory) -> some View {
        modifier(AssessmentViewListener(assessmentState: assessmentState, assessmentInfo: info, handler: handler, factory: factory))
    }
}

struct AssessmentViewListener : ViewModifier {
    @ObservedObject var assessmentState: AssessmentState
    let assessmentInfo: AssessmentScheduleInfo
    let handler: ScheduledAssessmentHandler
    let factory: ArchiveFactory
    @State var hasSaved: Bool = false
    
    func body(content: Content) -> some View {
        content
            .onChange(of: assessmentState.status) { _ in
                guard let status = bridgeStatus() else { return }
                handler.updateAssessmentStatus(assessmentInfo, status: status)
            }
    }
    
    func bridgeStatus() -> ScheduledAssessmentStatus? {
        switch assessmentState.status {
        case .running:
            return nil
            
        case .readyToSave:
            self.hasSaved = true
            return factory.buildResult(from: assessmentState, schedule: assessmentInfo).map {
                .readyToSave($0)
            }
            
        case .finished:
            if self.hasSaved {
                return .finished
            }
            else {
                return factory.buildResult(from: assessmentState, schedule: assessmentInfo).map {
                    .saveAndFinish($0)
                } ?? .finished
            }
            
        case .continueLater:
            if shouldSave() {
                return .saveForLater(assessmentState.assessmentResult)
            }
            else {
                return .restartLater
            }
            
        case .declined:
            return .declined(assessmentState.assessmentResult.startDate)
            
        case .error:
            return .error(assessmentState.navigationError ?? ValidationError.unknown)
        }
    }
    
    func shouldSave() -> Bool {
        assessmentState.interruptionHandling.canSaveForLater && assessmentState.hasPartialResults
    }
}

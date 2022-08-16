//
//  SageResearchTaskDelegate.swift
//
//  Copyright © 2021-2022 Sage Bionetworks. All rights reserved.
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

import Foundation
import BridgeClient
import BridgeClientUI
import BridgeClientExtension
import JsonModel
import Research
import ResearchUI

/// A wrapper that can be used to launch and control an assessment developed using SageResearch.
open class SageResearchTaskDelegate : NSObject, RSDTaskViewControllerDelegate {
    
    /// The timeline manager that "called" this assessment.
    public let assessmentManager: TodayTimelineViewModel
    
    /// The schedule info for this assessment.
    public let scheduledAssessment: AssessmentScheduleInfo!
    
    /// The archive manager to use for archiving Sage Research assessments.
    ///
    /// The base class uses lazy initialization of a private ivar to back this publicly exposed open
    /// property. That allows both only instantiating the archive manager if necessary as well as
    /// loading it with a pointer to the ``BridgeClientAppManager``. If a subclass of this
    /// task delegate needs to customize the archive, it can override the open property above to
    /// do so, but the lazy load pattern is recommended.
    ///
    /// - Note: ``SageResearchArchiveManager`` is self-retaining. It handles retaining both
    /// itself and the ``RSDTaskViewModel`` while processing is done on a background queue.
    /// Then it will release the task view model and itself when it's done.
    ///
    open var sageResearchArchiveManager: SageResearchArchiveManager {
        _sageResearchArchiveManager
    }
    lazy private var _sageResearchArchiveManager: SageResearchArchiveManager = {
        let manager = SageResearchArchiveManager()
        manager.load(bridgeManager: assessmentManager.bridgeManager)
        return manager
    }()
    
    /// A flag used to track whether or not "ready to save" was called by the assessment.
    public private(set) var didCallReadyToSave: Bool = false
    
    /// The schedule identifier to attach to the task view model.
    public var scheduleIdentifier: String {
        "\(scheduledAssessment.session.instanceGuid)|\(scheduledAssessment.instanceGuid)"
    }
    
    /// Default initializer.
    ///
    /// - Parameters:
    ///   - assessmentManager: The timeline manager that launched the assessment.
    ///   - selectedAssessment: (Optional) The assessment info for creating this assessment. If nil, the ``assessmentManager.selectedAssessment`` will be used.
    public init(_ assessmentManager: TodayTimelineViewModel, selectedAssessment: AssessmentScheduleInfo? = nil) {
        self.assessmentManager = assessmentManager
        self.scheduledAssessment = selectedAssessment ?? assessmentManager.selectedAssessment
    }
    
    // MARK: RSDTaskViewControllerDelegate
    
    open func taskController(_ taskController: RSDTaskController, didFinishWith reason: RSDTaskFinishReason, error: Error?) {
        if reason != .completed && !self.didCallReadyToSave {
            // If the task finished with an error or discarded results, then delete the output directory.
            taskController.taskViewModel.deleteOutputDirectory(error: error)
            if let err = error {
                debugPrint("WARNING! Task failed: \(err)")
            }
        }
        
        let taskResult = taskController.taskViewModel.taskResult
        let clientData = (taskController.task as? RSDTrackingTask)?.taskData(for: taskResult)?.json
        let declined = taskController.taskViewModel.didAbandon
        let endedOn = (reason == .completed) && !declined ? taskResult.endDate : nil
        
        Task {
            await dismissAssessment(startedOn: taskResult.startDate, endedOn: endedOn, declined: declined, clientData: clientData)
        }
    }
    
    @MainActor
    func dismissAssessment(startedOn: Date, endedOn: Date?, declined: Bool, clientData: JsonSerializable?) {
        assessmentManager.updateAdherenceRecord(scheduleInfo: scheduledAssessment, startedOn: startedOn, endedOn: endedOn, declined: declined, clientData: clientData)
        assessmentManager.isPresentingAssessment = false
    }
    
    open func taskController(_ taskController: RSDTaskController, readyToSave taskViewModel: RSDTaskViewModel) {
        self.didCallReadyToSave = true
        sageResearchArchiveManager.archiveAndUpload(taskController.taskViewModel, schedule: scheduledAssessment)
    }
}


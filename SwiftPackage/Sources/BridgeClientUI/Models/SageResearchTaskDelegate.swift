//
//  SageResearchTaskDelegate.swift
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

import Foundation
import BridgeClient
import JsonModel
import Research
import ResearchUI

open class SageResearchTaskDelegate : NSObject, RSDTaskViewControllerDelegate {
    
    public let assessmentManager: TodayTimelineViewModel
    public let scheduledAssessment: AssessmentScheduleInfo!
    
    /// The archive manager to use for archiving Sage Research assessments.
    open var sageResearchArchiveManager: SageResearchArchiveManager {
        _sageResearchArchiveManager
    }
    lazy private var _sageResearchArchiveManager: SageResearchArchiveManager = {
        let manager = SageResearchArchiveManager()
        manager.load(bridgeManager: assessmentManager.bridgeManager)
        return manager
    }()
    
    public private(set) var didCallReadyToSave: Bool = false
    
    public var scheduleIdentifier: String {
        "\(scheduledAssessment.session.instanceGuid)|\(scheduledAssessment.instanceGuid)"
    }
    
    public init(_ assessmentManager: TodayTimelineViewModel) {
        self.assessmentManager = assessmentManager
        self.scheduledAssessment = assessmentManager.selectedAssessment
    }
    
    open func taskController(_ taskController: RSDTaskController, didFinishWith reason: RSDTaskFinishReason, error: Error?) {
        
        // Dismiss the view
        assessmentManager.isPresentingAssessment = false
        
        if reason != .completed && !self.didCallReadyToSave {
            // If the task finished with an error or discarded results, then delete the output directory.
            taskController.taskViewModel.deleteOutputDirectory(error: error)
            if let err = error {
                debugPrint("WARNING! Task failed: \(err)")
            }
        }
        
        let taskResult = taskController.taskViewModel.taskResult
        let clientData = (taskController.task as? RSDTrackingTask)?.taskData(for: taskResult)?.json
        let endedOn = (reason == .completed) ? taskResult.endDate : nil
        let declined = (reason == .earlyExit)
        
        assessmentManager.updateAdherenceRecord(scheduleInfo: scheduledAssessment,
                                   startedOn: taskResult.startDate,
                                   endedOn: endedOn,
                                   declined: declined,
                                   clientData: clientData)
    }
    
    open func taskController(_ taskController: RSDTaskController, readyToSave taskViewModel: RSDTaskViewModel) {
        self.didCallReadyToSave = true
        sageResearchArchiveManager.archiveAndUpload(taskController.taskViewModel, schedule: scheduledAssessment)
    }
}


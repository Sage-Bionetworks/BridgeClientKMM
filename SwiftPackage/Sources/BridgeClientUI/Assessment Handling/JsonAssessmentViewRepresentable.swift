//
//  JsonAssessmentViewRepresentable.swift
//  
//
//  Copyright © 2022 Sage Bionetworks. All rights reserved.
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
import BridgeClientExtension
import JsonModel

/// This class can be used as a pointer or using `public final` and implementing a subclass that implements the protocol
/// for showing a view controller from SwiftUI. It is intended as a "minimum bar" for adding a third-party assessment to an app
/// where the data is uploaded to bridge and an adherence record is update.
open class JsonAssessmentViewRepresentable { // : UIViewControllerRepresentable {
    public let scheduleInfo: AssessmentScheduleInfo
    public let handler: ScheduledAssessmentHandler
    public let startedOn: Date = Date()
    
    public init(_ scheduleInfo: AssessmentScheduleInfo, handler: ScheduledAssessmentHandler) {
        self.scheduleInfo = scheduleInfo
        self.handler = handler
    }
    
    /// Method to call to dismiss your view that is running the assessment.
    /// - Parameter result: The result of the assessment. If nil, then this is assumed to map to a state of ``ScheduledAssessmentStatus.restartLater``.
    @MainActor
    open func dismiss(_ result: Result<JsonFile, Error>?) {
        if let result = result {
            switch result {
            case .success(let jsonFile):
                if let builder = JsonResultArchiveBuilder(json: jsonFile.json,
                                                          filename: jsonFile.filename,
                                                          schema: jsonFile.schema,
                                                          timestamp: jsonFile.timestamp,
                                                          startedOn: startedOn,
                                                          schedule: scheduleInfo) {
                    handler.updateAssessmentStatus(scheduleInfo, status: .saveAndFinish(builder))
                }
                else {
                    handler.updateAssessmentStatus(scheduleInfo, status: .error(ValidationError.unexpectedNull("ERROR! Failed to build the result archive.")))
                }
            case .failure(let error):
                handler.updateAssessmentStatus(scheduleInfo, status: .error(error))
            }
        }
        else {
            handler.updateAssessmentStatus(scheduleInfo, status: .restartLater)
        }
    }
    
    public struct JsonFile : Hashable, Codable {
        public let json: Data
        public let filename: String
        public let timestamp: Date
        public let schema: URL
        
        public init(json: Data, filename: String, timestamp: Date, schema: URL) {
            self.json = json
            self.filename = filename
            self.timestamp = timestamp
            self.schema = schema
        }
    }
}

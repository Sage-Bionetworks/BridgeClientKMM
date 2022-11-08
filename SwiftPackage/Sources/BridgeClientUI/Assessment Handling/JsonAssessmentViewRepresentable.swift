//
//  JsonAssessmentViewRepresentable.swift
//  
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

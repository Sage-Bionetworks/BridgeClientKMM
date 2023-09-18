// Created 9/13/23
// swift-tools-version:5.0

import XCTest
@testable import BridgeClientExtension
import JsonModel
import ResultModel

final class AssessmentArchiveBuilderTests: XCTestCase {

    override func setUpWithError() throws {
        // Put setup code here. This method is called before the invocation of each test method in the class.
    }

    override func tearDownWithError() throws {
        // Put teardown code here. This method is called after the invocation of each test method in the class.
    }

    func testSurveyAnswerBuilder() async throws {
        
        let assessmentResult = AssessmentResultObject(identifier: "example_survey")
        let answerResult1 = AnswerResultObject(identifier: "pizza", value: .boolean(true), questionText: "Do you like pizza?")
        let answerResult2 = AnswerResultObject(identifier: "step2", value: .integer(42), questionText: "What is the answer to the universe and everything?")
        let answerResult3 = AnswerResultObject(identifier: "step3", value: .number(52.25), questionText: "How old are you?")
        let answerResult4 = AnswerResultObject(identifier: "step4", value: .string("brown fox"), questionText: "Who jumped over the lazy dog?")
        let answerResult5 = AnswerResultObject(identifier: "step5", value: .array([1,11]), questionText: "What are your favorite numbers?")
        let answerResult6 = AnswerResultObject(identifier: "pizza", value: .boolean(false), questionText: "Do you like pizza now?")
        let branchResult = BranchNodeResultObject(identifier: "branch", stepHistory: [answerResult6])
        assessmentResult.stepHistory = [answerResult1, answerResult2, answerResult3, answerResult4, answerResult5, branchResult]
        
        guard let builder = AssessmentArchiveBuilder(assessmentResult) else {
            XCTFail("Unexpected NULL when creating the archiver")
            return
        }
        builder.archive.isTest = true
        let _ = try await builder.buildArchive()
        
        // Check each answer type
        XCTAssertEqual(builder.answers["pizza"] as? Bool, true)
        XCTAssertEqual(builder.answers["step2"] as? Int, 42)
        XCTAssertEqual(builder.answers["step3"] as? Double, 52.25)
        XCTAssertEqual(builder.answers["step4"] as? String, "brown fox")
        XCTAssertEqual(builder.answers["step5"] as? String, "1,11")
        
        // Check that the answers match the expected values
        let expectedAnswers = try JSONSerialization.jsonObject(with: """
        {
            "pizza" : true,
            "step2" : 42,
            "step3" : 52.25,
            "step4" : "brown fox",
            "step5" : "1,11",
            "branch_pizza" : false
        }
        """.data(using: .utf8)!) as! NSDictionary
        let answers = try builder.archive.addedFiles["answers.json"].map { try JSONSerialization.jsonObject(with: $0) } as? NSDictionary
        XCTAssertEqual(expectedAnswers, answers)

        // Check that the schema matches
        let expectedSchema = try JSONSerialization.jsonObject(with: """
        {
            "$id" : "answers_schema.json",
            "$schema" : "http://json-schema.org/draft-07/schema#",
            "type" : "object",
            "title" : "answers_schema",
            "description" : "example_survey",
            "properties" : {
                "pizza" : {
                    "type" : "boolean",
                    "description" : "Do you like pizza?"
                },
                "step2" : {
                    "type" : "integer",
                    "description" : "What is the answer to the universe and everything?"
                },
                "step3" : {
                    "type" : "number",
                    "description" : "How old are you?"
                },
                "step4" : {
                    "type" : "string",
                    "description" : "Who jumped over the lazy dog?"
                },
                "step5" : {
                    "type" : "string",
                    "description" : "What are your favorite numbers?"
                },
                "branch_pizza" : {
                    "type" : "boolean",
                    "description" : "Do you like pizza now?"
                }
            }
        }
        """.data(using: .utf8)!) as! NSDictionary
        let schema = try builder.archive.addedFiles["answers_schema.json"].map { try JSONSerialization.jsonObject(with: $0) } as? NSDictionary
        XCTAssertEqual(expectedSchema, schema)
    }
}

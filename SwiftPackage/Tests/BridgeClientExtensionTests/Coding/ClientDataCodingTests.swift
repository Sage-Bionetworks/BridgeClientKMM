//
//  ClientDataCodingTests.swift
//

import XCTest
import JsonModel
import BridgeClient
@testable import BridgeClientExtension

final class ClientDataCodingTests: XCTestCase {
    
    func testNativeAdherenceRecord() {
        do {
            let expectedClientData = ["foo" : "baruu"]
            let obj = NativeAdherenceRecord(instanceGuid: UUID().uuidString,
                                            eventTimestamp: ISO8601DateFormatter.string(from: Date(), timeZone: .current, formatOptions: .withInternetDateTime),
                                            timezoneIdentifier: TimeZone.current.identifier,
                                            startedOn: Date(),
                                            finishedOn: nil,
                                            declined: false,
                                            clientData: (expectedClientData as [String : JsonSerializable]).toBridgeClientJsonElement())
            let dictionary1 = try obj.clientDataDictionary()
            let testFoo = try obj.decodeClientData(TestFoo.self)
            
            XCTAssertEqual(expectedClientData, dictionary1 as? [String : String])
            XCTAssertEqual("baruu", testFoo?.foo)
        }
        catch let err {
            XCTFail("Failed to encode/decode client data. \(err)")
        }
    }
    
    func testAdherenceRecord() {
        let json = """
        {
            "instanceGuid": "\(UUID().uuidString)",
            "eventTimestamp": "2021-05-12T12:23:10.141Z",
            "startedOn":"2021-05-12T23:44:54.319Z",
            "finishedOn":"2021-05-12T23:44:54.319Z",
            "clientTimeZone": "America/Los_Angeles",
            "clientData": { "foo" : "baruu" },
            "type": "AdherenceRecord"
        }
        """.data(using: .utf8)!
        let expectedClientData = ["foo" : "baruu"]
        
        do {
            let obj = try BridgeClient.JsonDecoder(jsonData: json).decodeAdherenceRecord()
            
            let dictionary1 = try obj.clientDataDictionary()
            let testFoo = try obj.decodeClientData(TestFoo.self)

            XCTAssertEqual(expectedClientData, dictionary1 as? [String : String])
            XCTAssertEqual("baruu", testFoo?.foo)
        }
        catch let err {
            XCTFail("Failed to encode/decode client data. \(err)")
        }
    }
    
    struct TestFoo : Codable {
        let foo: String
    }
}

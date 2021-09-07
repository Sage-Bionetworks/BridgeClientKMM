//
//  ClientDataCodingTests.swift
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

import XCTest
import JsonModel
import BridgeClient
@testable import BridgeClientUI

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

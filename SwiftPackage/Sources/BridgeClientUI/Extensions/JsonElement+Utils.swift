//
//  JsonSerializable+Utils.swift
//
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

extension JsonModel.JsonSerializable {
    public func toBridgeClientJsonElement() -> BridgeClient.Kotlinx_serialization_jsonJsonElement? {
        do {
            let data = try JSONSerialization.data(withJSONObject: self, options: .fragmentsAllowed)
            guard let string = String(data: data, encoding: .utf8) else { return nil }
            let decoder = BridgeClient.JsonElementDecoder(jsonString: string)
            return try decoder.decodeObject()
        } catch {
            return nil
        }
    }
}

extension BridgeClient.Kotlinx_serialization_jsonJsonElement {
    public func toJsonElement() -> JsonModel.JsonElement? {
        do {
            let jsonString = try self.encodeObject()
            guard let data = jsonString.data(using: .utf8) else { return nil }
            let decoder = JSONDecoder()
            return try decoder.decode(JsonElement.self, from: data)
        } catch {
            return nil
        }
    }
}


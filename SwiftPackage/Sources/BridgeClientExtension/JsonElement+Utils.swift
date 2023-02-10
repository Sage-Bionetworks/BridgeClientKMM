//
//  JsonSerializable+Utils.swift
//
//

import Foundation
import BridgeClient
import JsonModel
import ResultModel

extension JsonModel.JsonSerializable {
    public func toBridgeClientJsonElement() -> BridgeClient.Kotlinx_serialization_jsonJsonElement? {
        do {
            let data = try JSONSerialization.data(withJSONObject: self, options: .fragmentsAllowed)
            let decoder = BridgeClient.JsonElementDecoder(jsonData: data)
            return try decoder.decodeObject()
        } catch {
            return nil
        }
    }
}

extension AssessmentResult {
    public func toBridgeClientJsonElement() -> BridgeClient.Kotlinx_serialization_jsonJsonElement? {
        do {
            let data = try self.jsonEncodedData()
            let decoder = BridgeClient.JsonElementDecoder(jsonData: data)
            return try decoder.decodeObject()
        } catch {
            Logger.log(severity: .warn, message: "WARNING! Failed to encode result: \(error)")
            return nil
        }
    }
}

// syoung 07/23/2021 This no longer works. Kotlin is returning an `BridgeClient.KMapAsNSDictionary`
// instead of `BridgeClient.Kotlinx_serialization_jsonJsonElement` and that object does not respond
// to the selector (because it's not a Kotlinx_serialization_jsonJsonElement). I'm leaving this
// code in (for now) in the hopes that they will fix this.
//
//extension BridgeClient.Kotlinx_serialization_jsonJsonElement {
//
//    public func toJsonElement() -> JsonModel.JsonElement? {
//        do {
//            let data = try self.encodeObject()
//            let decoder = JSONDecoder()
//            return try decoder.decode(JsonElement.self, from: data)
//        } catch {
//            return nil
//        }
//    }
//
//    public func decodeObject<T : Decodable>(_ type: T.Type, using factory: SerializationFactory = .init()) throws -> T? {
//        let data = try self.encodeObject()
//        let decoder = factory.createJSONDecoder()
//        return try decoder.decode(type, from: data)
//    }
//}


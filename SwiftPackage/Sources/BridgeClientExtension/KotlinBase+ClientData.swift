//
//  KotlinBase+ClientData.swift
//
//

import Foundation
import BridgeClient
import JsonModel

public protocol KotlinBase_ClientData : AnyObject {
    func clientDataJson() -> Data?
}

extension KotlinBase_ClientData {
    
    public func clientDataDictionary() throws -> [String : Any]? {
        guard let data = self.clientDataJson()
        else {
            return nil
        }
        return try JSONSerialization.jsonObject(with: data, options: []) as? [String : Any]
    }
    
    public func decodeClientData<T : Decodable>(_ type: T.Type, using factory: SerializationFactory = .init()) throws -> T? {
        guard let data = self.clientDataJson()
        else {
            return nil
        }
        let decoder = factory.createJSONDecoder()
        return try decoder.decode(type, from: data)
    }
}

extension AppConfig : KotlinBase_ClientData {
}

extension Study : KotlinBase_ClientData {
}

extension UserSessionInfo : KotlinBase_ClientData {
}

extension AdherenceRecord : KotlinBase_ClientData {
}

extension NativeAdherenceRecord : KotlinBase_ClientData {
}


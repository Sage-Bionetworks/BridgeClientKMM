//
//  PlatformConfigImpl.swift
//

import Foundation
import BridgeClient

public class PlatformConfigImpl : IOSPlatformConfig {
        
    public let appGroupIdentifier: String?
    public let appId: String
    public let appName: String
    public let appVersionName: String
    public let appVersion: Int32
    public let deviceName: String
    public let bridgeEnvironment: PlatformConfigBridgeEnvironment
    public let osName: String
    public let osVersion: String
    public let defaultConsentGuid: String?
    public let cacheCredentials: Bool
    
    
    public var deviceInfo: String {
        "\(deviceName); \(osName)/\(osVersion)"
    }
    
    public init(appId: String? = nil, appGroupIdentifier: String? = nil, bridgeEnvironment: PlatformConfigBridgeEnvironment = .production, defaultConsentGuid: String? = nil, cacheCredentials: Bool = false) {
        
        self.appId = appId ?? Bundle.main.bridgeAppId
        self.appGroupIdentifier = appGroupIdentifier
        self.appName = Bundle.main.executableName
        self.appVersionName = Bundle.main.fullVersion
        self.appVersion = Int32(Bundle.main.buildNumber)
        self.bridgeEnvironment = bridgeEnvironment
        self.defaultConsentGuid = defaultConsentGuid
        self.cacheCredentials = cacheCredentials
        
        #if os(watchOS)
        let device = WKInterfaceDevice.current()
        self.osName = device.systemName
        self.osVersion = device.systemVersion
        self.deviceName = device.machineName
        #elseif os(macOS)
        self.osName = "macOS"
        self.osVersion = ProcessInfo().operatingSystemVersionString
        self.deviceName = "Mac"
        #else
        let device = UIDevice.current
        self.osName = device.systemName
        self.osVersion = device.systemVersion
        self.deviceName = device.machineName
        #endif
    }
}

extension PlatformConfig {
    
    public var localizedAppName : String {
        Bundle.localizedAppName
    }
}

extension IOSBridgeConfig {
    
    public func sharedDocumentDirectory() throws -> URL {
        try appGroupIdentifier.flatMap { sharedId in
            FileManager.default.containerURL(forSecurityApplicationGroupIdentifier: sharedId)
        } ?? FileManager.default.url(for: .documentDirectory, in: .userDomainMask, appropriateFor: nil, create: true)
    }
}

extension Bundle {
    /// The localized name of this application.
    /// This method looks at the plist for the main bundle and returns the most
    /// appropriate display name.
    static public var localizedAppName : String {
        let mainBundle = Bundle.main
        if let bundleInfo = mainBundle.localizedInfoDictionary ?? mainBundle.infoDictionary {
            if let name = bundleInfo["CFBundleDisplayName"] as? String {
                return name
            }
            else if let name = bundleInfo["CFBundleName"] as? String {
                return name
            }
            else if let name = bundleInfo["CFBundleExecutable"] as? String {
                return name
            }
        }
        return "???"
    }
}

extension Bundle {
    
    fileprivate var bridgeAppId: String {
        return "sage-assessment-test"
    }
    
    /// The executable name is the bundle's non-localized name.
    fileprivate var executableName: String {
        if let bundleInfo = infoDictionary {
            if let name = bundleInfo["CFBundleExecutable"] as? String {
                return name
            }
            else if let name = bundleInfo["CFBundleName"] as? String {
                return name
            }
            else if let name = bundleInfo["CFBundleDisplayName"] as? String {
                return name
            }
        }
        return "???"
    }
    
    fileprivate var buildNumber: Int {
        guard let build = object(forInfoDictionaryKey: kCFBundleVersionKey as String) as? String
        else {
            return 0
        }
        return Int(build) ?? 0
    }
    
    /// The full version is a non-localized string that uses both the "short version"
    /// string and the build number.
    fileprivate var fullVersion: String {
        guard let version = object(forInfoDictionaryKey: "CFBundleShortVersionString")
        else {
            return "???"
        }
        return "version \(version), build \(buildNumber)"
    }
}


#if os(watchOS)
import WatchKit
extension WKInterfaceDevice {
    
    /// An identifier for the device type pulled from the system info.
    fileprivate var deviceTypeIdentifier: String {
        var systemInfo = utsname()
        uname(&systemInfo)
        let machineMirror = Mirror(reflecting: systemInfo.machine)
        let id = machineMirror.children.reduce("") { id, element in
            guard let value = element.value as? Int8, value != 0 else { return id }
            return id + String(UnicodeScalar(UInt8(value)))
        }
        return id
    }
    
    /// A human-readable mapped name for a given device type.
    fileprivate var machineName: String {
        let id = deviceTypeIdentifier
        switch id {
        case "Watch1":                                      return "Apple Watch Series 1"
        case "Watch2,6","Watch2,7","Watch2,3","Watch2,4":   return "Apple Watch Series 2"
        case "Watch3,1","Watch3,2","Watch3,3","Watch3,4":   return "Apple Watch Series 3"
        case "Watch4,1","Watch4,2","Watch4,3","Watch4,4":   return "Apple Watch Series 4"
        case "Watch5,1","Watch5,2","Watch5,3","Watch5,4":   return "Apple Watch Series 5"
        case "i386", "x86_64":                              return "Apple Watch Simulator"
            
        default:                                            return id
        }
    }
}

#elseif os(macOS)

import AppKit

#else
import UIKit
extension UIDevice {
    
    /// An identifier for the device type pulled from the system info.
    fileprivate var deviceTypeIdentifier: String {
        var systemInfo = utsname()
        uname(&systemInfo)
        let machineMirror = Mirror(reflecting: systemInfo.machine)
        let id = machineMirror.children.reduce("") { id, element in
            guard let value = element.value as? Int8, value != 0 else { return id }
            return id + String(UnicodeScalar(UInt8(value)))
        }
        return id
    }
    
    /// A human-readable mapped name for a given device type.
    fileprivate var machineName: String {
        // Use the hardcoded machine name b/c each os version seems to change this
        _hardcodedMachineName()
    }
    
    private func _hardcodedMachineName() -> String {
        
        let id = deviceTypeIdentifier
        switch id {
        case "iPod5,1":                                     return "iPod Touch 5"
        case "iPod7,1":                                     return "iPod Touch 6"
        case "iPod9,1":                                     return "iPod Touch 7"
            
        case "iPhone3,1", "iPhone3,2", "iPhone3,3":         return "iPhone 4"
        case "iPhone4,1":                                   return "iPhone 4s"
        case "iPhone5,1", "iPhone5,2":                      return "iPhone 5"
        case "iPhone5,3", "iPhone5,4":                      return "iPhone 5c"
        case "iPhone6,1", "iPhone6,2":                      return "iPhone 5s"
        case "iPhone7,2":                                   return "iPhone 6"
        case "iPhone7,1":                                   return "iPhone 6 Plus"
        case "iPhone8,1":                                   return "iPhone 6s"
        case "iPhone8,2":                                   return "iPhone 6s Plus"
        case "iPhone9,1", "iPhone9,3":                      return "iPhone 7"
        case "iPhone9,2", "iPhone9,4":                      return "iPhone 7 Plus"
        case "iPhone8,4":                                   return "iPhone SE"
        case "iPhone10,1", "iPhone10,4":                    return "iPhone 8"
        case "iPhone10,2", "iPhone10,5":                    return "iPhone 8 Plus"
        case "iPhone10,3", "iPhone10,6":                    return "iPhone X"
        case "iPhone11,2":                                  return "iPhone XS"
        case "iPhone11,4":                                  return "iPhone XS Max"
        case "iPhone11,6":                                  return "iPhone XS Max Global"
        case "iPhone11,8":                                  return "iPhone XR"
        case "iPhone12,1":                                  return "iPhone 11"
        case "iPhone12,3":                                  return "iPhone 11 Pro"
        case "iPhone12,5":                                  return "iPhone 11 Pro Max"
        case "iPhone12,8":                                  return "iPhone SE 2nd Gen"
        case "iPhone13,1":                                  return "iPhone 12 Mini"
        case "iPhone13,2":                                  return "iPhone 12"
        case "iPhone13,3":                                  return "iPhone 12 Pro"
        case "iPhone13,4":                                  return "iPhone 12 Pro Max"
        case "iPhone14,2":                                  return "iPhone 13 Pro"
        case "iPhone14,3":                                  return "iPhone 13 Pro Max"
        case "iPhone14,4":                                  return "iPhone 13 Mini"
        case "iPhone14,5":                                  return "iPhone 13"
        case "iPhone14,6":                                  return "iPhone SE 3rd Gen"
        case "iPhone14,7":                                  return "iPhone 14"
        case "iPhone14,8":                                  return "iPhone 14 Plus"
        case "iPhone15,2":                                  return "iPhone 14 Pro"
        case "iPhone15,3":                                  return "iPhone 14 Pro Max"
        case "iPhone15,4":                                  return "iPhone 15"
        case "iPhone15,5":                                  return "iPhone 15 Plus"
        case "iPhone16,1":                                  return "iPhone 15 Pro"
        case "iPhone16,2":                                  return "iPhone 15 Pro Max"
            
        case "iPad2,1", "iPad2,2", "iPad2,3", "iPad2,4":    return "iPad 2"
        case "iPad3,1", "iPad3,2", "iPad3,3":               return "iPad 3"
        case "iPad3,4", "iPad3,5", "iPad3,6":               return "iPad 4"
        case "iPad4,1", "iPad4,2", "iPad4,3":               return "iPad Air"
        case "iPad5,3", "iPad5,4":                          return "iPad Air 2"
        case "iPad6,11", "iPad6,12":                        return "iPad 5"
        case "iPad2,5", "iPad2,6", "iPad2,7":               return "iPad Mini"
        case "iPad4,4", "iPad4,5", "iPad4,6":               return "iPad Mini 2"
        case "iPad4,7", "iPad4,8", "iPad4,9":               return "iPad Mini 3"
        case "iPad5,1", "iPad5,2":                          return "iPad Mini 4"
        case "iPad6,3", "iPad6,4":                          return "iPad Pro 9.7 Inch"
        case "iPad6,7", "iPad6,8":                          return "iPad Pro 12.9 Inch"
        case "iPad7,1", "iPad7,2":                          return "iPad Pro 12.9 Inch 2. Generation"
        case "iPad7,3", "iPad7,4":                          return "iPad Pro 10.5 Inch"
        case "iPad7,5", "iPad7,6":                          return "iPad 6"
        case "iPad7,11","iPad7,12":                         return "iPad 7 10.2 Inch"
        case "iPad8,1","iPad8,2","iPad8,3","iPad8,4":       return "iPad Pro 3 11 Inch"
        case "iPad8,5","iPad8,6","iPad8,7","iPad8,8":       return "iPad Pro 3 12.9 Inch"
        case "iPad11,1","iPad11,2":                         return "iPad Mini 5"
        case "iPad11,3","iPad11,4":                         return "iPad Air 3"
        case "iPad11,6","iPad11,7":                         return "iPad 8th Gen"
        case "iPad12,1","iPad12,2":                         return "iPad 9th Gen"
        case "iPad14,1","iPad14,2":                         return "iPad mini 6th Gen"
        case "iPad13,1","iPad13,2":                         return "iPad Air 4th Gen"
        case "iPad13,4","iPad13,5","iPad13,6","iPad13,7":   return "iPad Pro 11 inch 5th Gen"
        case "iPad13,8","iPad13,9","iPad13,10","iPad13,11": return "iPad Pro 12.9 inch 5th Gen"
        case "iPad13,16","iPad13,17":                       return "iPad Air 5th Gen"
        case "iPad13,18","iPad13,19":                       return "iPad 10th Gen"
        case "iPad14,3","iPad14,4":                         return "iPad Pro 11 inch 4th Gen"
        case "iPad14,5","iPad14,6":                         return "iPad Pro 12.9 inch 6th Gen"
            
        case "i386", "x86_64", "arm64":                     return "Simulator"
            
        default:
            if #available(iOS 16.0, *) {
                // With iOS 16, the name is *not* the name given to the device by the user.
                // Instead, it is the "friendly" machine name for the device.
                // https://developer.apple.com/documentation/uikit/uidevice/1620015-name
                // That said, it appears that in some cases, only the "iPhone" and not the
                // model is being returned so also check for that. syoung 10/20/2023
                return self.name != "iPhone" ? self.name : id
            } else {
                return id
            }
        }
    }
}
#endif

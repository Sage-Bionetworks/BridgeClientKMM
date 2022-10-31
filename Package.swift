// swift-tools-version:5.3
// The swift-tools-version declares the minimum version of Swift required to build this package.

import PackageDescription

let package = Package(
    name: "BridgeClient",
    defaultLocalization: "en",
    platforms: [
        .iOS(.v14),
    ],
    products: [
        // Products define the executables and libraries a package produces, and make them visible to other packages.
        .library(
            name: "BridgeClient",
            targets: [
                "BridgeClient",
                "BridgeClientExtension",
                "BridgeClientUI",
            ]),
        .library(
            name: "BridgeClientAppExtension",
            targets: [
                "BridgeClient",
                "BridgeClientExtension",
            ]),
    ],
    dependencies: [
        // Dependencies declare other packages that this package depends on.
        // .package(url: /* package url */, from: "1.0.0"),
        .package(name: "SharedMobileUI",
                 url: "https://github.com/Sage-Bionetworks/SharedMobileUI-AppleOS.git",
                 from: "0.13.0"),
        .package(name: "BridgeArchiver",
                 url: "https://github.com/Sage-Bionetworks/BridgeArchiver-Swift.git",
                 from: "0.3.0"),
        .package(name: "JsonModel",
                 url: "https://github.com/Sage-Bionetworks/JsonModel-Swift.git",
                 "1.6.0"..<"3.0.0"),
        .package(name: "AssessmentModel",
                 url: "https://github.com/Sage-Bionetworks/AssessmentModelKMM.git",
                 from: "0.9.0"),
    ],
    targets: [
        // Targets are the basic building blocks of a package. A target can define a module or a test suite.
        // Targets can depend on other targets in this package, and on products in packages this package depends on.
        .binaryTarget(name: "BridgeClient",
                      path: "SwiftPackage/Binaries/release/BridgeClient.xcframework"),
        
        .target(name: "BridgeClientExtension",
                dependencies: [
                    "BridgeClient",
                    "BridgeArchiver",
                    "JsonModel",
                ],
                path: "SwiftPackage/Sources/BridgeClientExtension"),
        .testTarget(name: "BridgeClientExtensionTests",
                    dependencies: [
                        "BridgeClient",
                        "BridgeClientExtension",
                    ],
                    path: "SwiftPackage/Tests/BridgeClientExtensionTests",
                    resources: [.process("Resources")]),
        
        .target(name: "BridgeClientUI",
                dependencies: [
                    "BridgeClient",
                    "BridgeClientExtension",
                    "SharedMobileUI",
                    "JsonModel",
                    .product(name: "AssessmentModel", package: "AssessmentModel"),
                    .product(name: "AssessmentModelUI", package: "AssessmentModel"),
                ],
                path: "SwiftPackage/Sources/BridgeClientUI",
                resources: [.process("Resources")]),
        .testTarget(name: "BridgeClientUITests",
                    dependencies: [
                        "BridgeClient",
                        "BridgeClientUI",
                    ],
                    path: "SwiftPackage/Tests/BridgeClientUITests"),
    ]
)

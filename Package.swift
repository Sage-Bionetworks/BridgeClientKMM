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
                "BridgeClientUI",
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
        .package(name: "SageResearch",
                 url: "https://github.com/Sage-Bionetworks/SageResearch.git",
                 from: "4.1.5"),
        .package(name: "JsonModel",
                 url: "https://github.com/Sage-Bionetworks/JsonModel-Swift.git",
                 from: "1.2.0"),
        // TODO: syoung 04/13/2021 Add AssessmentModel-KotlinNative once that repo is set up
        // to build the xcframework when the version is updated.
    ],
    targets: [
        // Targets are the basic building blocks of a package. A target can define a module or a test suite.
        // Targets can depend on other targets in this package, and on products in packages this package depends on.
        .binaryTarget(name: "BridgeClient",
                      path: "SwiftPackage/Binaries/release/BridgeClient.xcframework"),
        .target(name: "BridgeClientUI",
                dependencies: [
                    "BridgeClient",
                    "SharedMobileUI",
                    "BridgeArchiver",
                    "JsonModel",
                    .product(name: "Research", package: "SageResearch"),
                    .product(name: "ResearchUI", package: "SageResearch"),
                ],
                path: "SwiftPackage/Sources/BridgeClientUI",
                resources: [.process("Resources")]),
        .testTarget(name: "BridgeClientUITests",
                    dependencies: [
                        "BridgeClient",
                        "BridgeClientUI",
                    ],
                    path: "SwiftPackage/Tests/BridgeClientUITests",
                    resources: [.process("Resources")]),
    ]
)

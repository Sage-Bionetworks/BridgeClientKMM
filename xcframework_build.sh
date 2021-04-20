#!/bin/sh

#  xcframework_build.sh
#  iosApp
# 

rm -rf ./SwiftPackage/Binaries/BridgeClient.xcframework
rm -rf ./bridge-client/build/bin/
./gradlew :bridge-client:packForXCode -PXCODE_CONFIGURATION="RELEASE" -PXCODE_SDK_NAME="iphoneos"
mv ./bridge-client/build/bin/ios ./bridge-client/build/bin/iosArm64
./gradlew :bridge-client:packForXCode -PXCODE_CONFIGURATION="RELEASE" -PXCODE_SDK_NAME="iphonesimulator"
mv ./bridge-client/build/bin/ios ./bridge-client/build/bin/iosX64
xcodebuild -create-xcframework -framework ./bridge-client/build/bin/iosArm64/releaseFramework/BridgeClient.framework -framework ./bridge-client/build/bin/iosX64/releaseFramework/BridgeClient.framework -output ./SwiftPackage/Binaries/BridgeClient.xcframework


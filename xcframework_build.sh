#!/bin/sh

#  xcframework_build.sh
#  iosApp
# 

./gradlew :bridge-client:assembleBridgeClientXCFramework
rm -rf SwiftPackage/Binaries/*
cp -r bridge-client/build/XCFrameworks/* SwiftPackage/Binaries

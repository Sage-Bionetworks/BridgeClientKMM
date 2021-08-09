#!/bin/sh

#  xcframework_build.sh
#  iosApp
# 

./gradlew :bridge-client:buildXcFramework -PXCFRAMEWORK="true" -PSWIFT_PM="true" -PXCODE_CONFIGURATION="DEBUG"

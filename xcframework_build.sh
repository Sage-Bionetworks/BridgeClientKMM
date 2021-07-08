#!/bin/sh

#  xcframework_build.sh
#  iosApp
# 

./gradlew :bridge-client:buildXcFramework -PSWIFT_PM="true"


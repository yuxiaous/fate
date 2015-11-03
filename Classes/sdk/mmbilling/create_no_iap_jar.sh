#!/bin/sh

jarfile=$1

if [ "$jarfile" != "" ]; then
    ~/android-sdk-macosx/build-tools/22.0.1/aapt r -v $jarfile mmiap.xml
    ~/android-sdk-macosx/build-tools/22.0.1/aapt r -v $jarfile CopyrightDeclaration.xml
    ~/android-sdk-macosx/build-tools/22.0.1/aapt r -v $jarfile VERSION
fi

#!/bin/sh
cd ../../../
rm -rf publish
./tools/cocos2d-console/bin/cocos jscompile -s src -d publish/src
./tools/cocos2d-console/bin/cocos jscompile -s config -d publish/config
./tools/cocos2d-console/bin/cocos jscompile -s frameworks/js-bindings/bindings/script -d publish/script

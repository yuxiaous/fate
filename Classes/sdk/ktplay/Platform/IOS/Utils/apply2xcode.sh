#!/bin/sh

arg1=$1

if [ ! -n "$arg1" ]; then
	echo "input xcode .xcodeproj  path "
else
  PROJECT_NAME=${arg1}
  
  
  python ./apply2xcode.py  ${PROJECT_NAME} 
fi 



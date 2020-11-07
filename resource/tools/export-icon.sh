#!/bin/sh

file=$1
name=${file%.*}
ext=${file##*.}
size=$2

# echo $name $ext

function zoom() {
    # echo $name-$1.$ext
    sips -Z $1 $file --out $name-$1.$ext
}

if [ "$size" == "" ]; then
    zoom 57
    zoom 72
    zoom 76
    zoom 114
    zoom 120
    zoom 144
    zoom 152
else
    zoom $size
fi


#!/bin/sh
var1=$(pwd | grep -o '[^/]*$')
var=${PWD##*/}
mkdir build
cd build
cmake ..
make
./$var
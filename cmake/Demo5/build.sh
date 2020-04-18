#!/bin/sh
var=${PWD##*/}
mkdir build
cd build
cmake ..
make
#./$var
make test
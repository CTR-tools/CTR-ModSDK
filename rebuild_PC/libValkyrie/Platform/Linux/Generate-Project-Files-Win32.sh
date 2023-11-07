#!/bin/sh
dir=${PWD%/*}
dir=${dir%/*}
dir=${dir%/*}
dir=${dir%/*}
cd ${dir}
cmake -DCMAKE_BUILD_TYPE=Debug . -B${dir}/Build/Build_Linux/
cd ${dir}/Build/Build_Linux/
cmake --build .
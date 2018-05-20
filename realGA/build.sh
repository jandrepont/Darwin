#!/usr/bin/env bash
cd "$(dirname "${BASH_SOURCE[0]}")"



mkdir -p dist/
mkdir -p build/
rm dist/*
cd build

CORES=$(nproc)
echo "Running build with $CORES threads."

rm -rf *
cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_C_COMPILER=gcc -DCMAKE_CXX_COMPILER=g++ ..
#make VERBOSE=1
make -j$CORES
mv realGA ../dist

rm -rf *
cmake -DCMAKE_BUILD_TYPE=Debug -DCMAKE_C_COMPILER=gcc -DCMAKE_CXX_COMPILER=g++ ..
#make VERBOSE=1
make -j$CORES
mv realGA ../dist


cd ..
rm -rf build


exit 0

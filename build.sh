#!/bin/bash
set -euo pipefail
rm -rf ./build
mkdir -p build && cd build
cmake ..
cmake --build .
cmake --build . --target test
cmake --build . --target package
cmake --build . --target docs
ctest -j $(nproc)
#cpack -G DEB

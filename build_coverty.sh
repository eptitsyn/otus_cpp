#!/bin/bash

set -euo pipefail

mkdir -p build_coverty && cd build_coverty

cmake ..

cmake --build .

cd ..
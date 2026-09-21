#!/bin/bash

set -e

SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
cd "$SCRIPT_DIR"

mkdir -p build
cd build
cmake -DSHS_CMF_QT=OFF -DSHS_CMF_UNUSE_SHS_SETTINGS=ON -DCMAKE_CXX_FLAGS="-Wall" ..
cmake --build .

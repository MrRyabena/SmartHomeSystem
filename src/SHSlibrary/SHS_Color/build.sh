#!/usr/bin/env bash

set -e

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

cmake -S "${SCRIPT_DIR}/src" \
-B "${SCRIPT_DIR}/build"

cmake --build "${SCRIPT_DIR}/build"

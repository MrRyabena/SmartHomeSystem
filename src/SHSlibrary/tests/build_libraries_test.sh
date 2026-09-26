#!/usr/bin/env bash

set -e

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

"${BASH}" "${SCRIPT_DIR}/../SHS_Color/build.sh"

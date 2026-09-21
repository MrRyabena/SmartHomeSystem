#!/bin/bash

BUILD_DIR="build"

set -e

SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
cd "$SCRIPT_DIR"

show_help() {
    echo "Usage: $0 [options]"
    echo ""
    echo "Options:"
    echo "  -h, --help    Show this help message"
    echo "  -c, --clear   Clear the previous build directory ($BUILD_DIR)"
    echo "  -b, --build   Build the tests (CMake configuration and compilation)"
    echo "  -r, --run     Build and automatically run the tests"
    echo ""
    echo "Examples:"
    echo "  $0 -c -r  (clears the previous build, rebuilds the project and runs the tests)"
    echo "  $0 -b     (builds the project without running the tests)"
    echo "  $0 -cr     (builds the project and runs the tests)"
}

check_and_install_cmake() {
    if ! command -v cmake &> /dev/null; then
        echo -e "${GREEN}[INFO]${NC} CMake is not installed. Installing CMake..."
        sudo apt update && sudo apt install -y cmake
        echo -e "${GREEN}[INFO]${NC} CMake successfully installed!"
    fi
}

check_and_install_gtest() {
    if [ ! -f "/usr/include/gtest/gtest.h" ]; then
        echo -e "${GREEN}[INFO]${NC} Google Test is not installed in the system. Starting installation..."
        sudo apt update && sudo apt install -y libgtest-dev cmake
        
        # In case of older systems, where libgtest-dev provides only the source code
        if [ ! -f "/usr/lib/x86_64-linux-gnu/libgtest.a" ] && [ ! -f "/usr/lib/libgtest.a" ]; then
            echo -e "${GREEN}[INFO]${NC} Compiling the source code of gtest..."
            cd /usr/src/googletest/googletest || cd /usr/src/gtest
            sudo cmake . && sudo make && sudo cp lib/libgtest*.a /usr/lib/
            cd - > /dev/null
        fi
        echo -e "${GREEN}[INFO]${NC} Google Test successfully installed!"
    fi
}

build_tests() {
    mkdir -p "$BUILD_DIR"
    cd "$BUILD_DIR"
    cmake ..
    cmake --build .
    chmod +x ShsCoreTests
}

run_tests() {
    ./ShsCoreTests
}

CLEAR=false
BUILD=false
RUN=false

GREEN='\033[0;32m'
YELLOW='\033[1;33m'
RED='\033[0;31m'
NC='\033[0m' # No Color

if [[ $# -eq 0 ]]; then
    echo -e "${RED}[ERROR]${NC} No arguments provided. Please specify at least one option."
    show_help
    exit 1
fi

while [[ $# -gt 0 ]]; do
    case "$1" in
        -h|--help)
            show_help
            exit 0
            ;;
        -c|--clear)
            CLEAR=true
            shift
            ;;
        -b|--build)
            BUILD=true
            shift
            ;;
        -r|--run)
            RUN=true
            shift
            ;;
        -*)

            OPTIND=1
            while getopts "cbr" opt "$1"; do
                case "$opt" in
                    c) CLEAR=true ;;
                    b) BUILD=true ;;
                    r) RUN=true ;;
                    *) show_help; exit 1 ;;
                esac
            done
            shift
            ;;
        *)
            echo -e "${RED}[ERROR]${NC} Unknown argument: $1"
            show_help
            exit 1
            ;;
    esac
done

check_and_install_cmake
check_and_install_gtest

if [ "$CLEAR" = true ]; then
    echo -e "${GREEN}[INFO]${NC} Clearing the previous build directory ($BUILD_DIR)..."
    rm -rf "$BUILD_DIR"
    echo -e "${GREEN}[INFO]${NC} Previous build directory cleared."
fi

if [ "$BUILD" = true ] || [ "$RUN" = true ]; then
    echo -e "${GREEN}[INFO]${NC} Building the tests..."
    build_tests
    echo -e "${GREEN}[INFO]${NC} Tests built successfully."
fi

if [ "$RUN" = true ]; then
    echo -e "${GREEN}[INFO]${NC} Running the tests..."
    run_tests
    echo -e "${GREEN}[INFO]${NC} Tests completed."
fi




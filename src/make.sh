# This is a simple file for transferring libraries to the Arduino environment.

# Last update: v1.1.0
#  Versions:
#    v1.1.0 — created.
#

# Уou must specify the path to the folder in the file libraries_path:

source libraries_paths.sh

if [[ "$1" == "--help" || "$1" == "-h" ]]; then
    echo "Usage: make.sh [OPTION]"
    echo
    echo "This script transfers libraries to the specified environment."
    echo
    echo "Options:"
    echo "  --qt, -q       Transfer libraries to the Qt environment."
    echo "  --ard, -a      Transfer libraries to the Arduino environment."
    echo "  --oth, -o      Transfer libraries to other specified environments."
    echo "  --help, -h     Display this help message and exit."
    echo
    echo "You must specify the path to the folder in the file libraries_path."
    echo
    #exit 0
elif [[ "$1" == "--qt" || "$1" == "-q" ]]; then
    for dir in "${QT_PATHS[@]}"; do
        rm -rf "$dir/SHScore"
        rm -rf "$dir/SHSqt_core"

        cp -r ./SHScore "$dir/SHScore"
        cp -r ./SHSqt_core "$dir/SHSqt_core"
    done
elif [[ "$1" == "--ard" || "$1" == "-a" ]]; then
    for dir in "${ARDUINO_PATHS[@]}"; do

        rm -rf "${dir}SHScore"
        rm -rf "${dir}SHSlibrary"
        rm -rf "${dir}SHStests"
        rm -rf "${dir}SHSsettings"

        cp -r ./SHScore/ "${dir}SHScore/"
        cp -r ./SHStests/source/ "${dir}SHStests/"

        for lib in ./SHSlibrary/*/; do
            cp -r "$lib" "${dir}"
        done

        for dir_ in "$dir"*/; do
            cp -r "$dir_" "$dir"
        done

        cp -r ./SHSsettings/ "${dir}SHSsettings/"
    done
elif [[ "$1" == "--oth" || "$1" == "-o" ]]; then
    for dir in "${OTHER_PATHS[@]}"; do
        rm -rf "$dir/SHScore"
        rm -rf "$dir/SHSqt_core"

        cp -r ./SHScore "$dir/SHScore"
        cp -r ./SHSqt_core "$dir/SHSqt_core"
    done
fi

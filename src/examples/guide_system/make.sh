source ../../libraries_paths.sh

mkdir -p "${ARDUINO_PATHS}SHSconfig/"
cp -r gs_config.h "${ARDUINO_PATHS}SHSconfig/"


MODULE_3_PATH="module_3/GUIapp/SHSbuild"

mkdir -p "${MODULE_3_PATH}/SHSconfig"
cp -r gs_config.h "${MODULE_3_PATH}/SHSconfig"
cp -r "../../SHScore" ${MODULE_3_PATH}
cp -r "../../SHSqt_core" ${MODULE_3_PATH}

mkdir -p "${MODULE_3_PATH}/SHSlogos"
cp -r "../../../SHSlogos/logo.svg" "${MODULE_3_PATH}/SHSlogos"

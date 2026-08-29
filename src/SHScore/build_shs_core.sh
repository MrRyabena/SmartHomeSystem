mkdir -p build
cd build
cmake -DSHS_CMF_QT=OFF -DSHS_CMF_UNUSE_SHS_SETTINGS=ON -DCMAKE_CXX_FLAGS="-Wall" ..
cmake --build .

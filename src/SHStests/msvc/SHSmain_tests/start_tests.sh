# It was created for automatic assembly and test run.

# Last update: v1.1.0
#  Versions:
#    v1.1.0 — created.

mkdir build
cd build
cmake ..
cmake --build .
./SHSmain_tests

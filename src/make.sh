# This is a simple file for transferring libraries to the Arduino environment.

# Last update: v1.1.0
#  Versions:
#    v1.1.0 — created.
#

# Уou must specify the path to the folder here:
ArduinoLibraries=/mnt/c/Users/Daniil/Documents/Arduino/libraries/

echo "ArduinoLibraries directory is: $ArduinoLibraries"

rm -rf "${ArduinoLibraries}SHScore/"
cp -r ./SHScore/ "${ArduinoLibraries}SHScore/"

rm -rf  "${ArduinoLibraries}SHSlibrary"
cp -r ./SHSlibrary/ "${ArduinoLibraries}SHSlibrary/"

rm -rf "${ArduinoLibraries}SHStests"
cp -r ./SHStests/source/ "${ArduinoLibraries}SHStests/"

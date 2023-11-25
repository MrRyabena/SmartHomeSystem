#include <iostream>
#include <windows.h>
#include <direct.h>

using namespace std;

#define LIB "C:/Users/Daniil/Documents/Arduino/libraries/SHS_library"
#define INP "B:/SmartHomeSystem/SHSlibrary"
#define LIB2 "C:/Users/Daniil/Documents/Arduino/libraries/devAPI"
#define INP2 "B:/SmartHomeSystem/devAPI"

int main()
{

  system("RD /S /Q \"" LIB "\""); // B:/at work/SmartHomeSystem/synchronizer/core\"");
  mkdir(LIB);
  system("xcopy \"" INP "\" \"" LIB "\" /e");

  system("RD /S /Q \"" LIB2 "\""); // B:/at work/SmartHomeSystem/synchronizer/core\"");
  mkdir(LIB2);
  system("xcopy \"" INP2 "\" \"" LIB2 "\" /e");

  system("pause");

  return 0;
}

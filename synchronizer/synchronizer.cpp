#include <iostream>
#include <windows.h>
#include <direct.h>

using namespace std;

#define LIB "C:/Users/Daniil/Documents/Arduino/libraries/SHScore"
#define INP "B:/SmartHomeSystem/src/SHScore"
#define LIB2 "C:/Users/Daniil/Documents/Arduino/libraries/SHSlibrary"
#define INP2 "B:/SmartHomeSystem/src/SHSlibrary"

int main()
{

  while (true)
  {
    system("RD /S /Q \"" LIB "\""); // B:/at work/SmartHomeSystem/synchronizer/core\"");
    mkdir(LIB);
    system("xcopy \"" INP "\" \"" LIB "\" /e");

    system("RD /S /Q \"" LIB2 "\""); // B:/at work/SmartHomeSystem/synchronizer/core\"");
    mkdir(LIB2);
    system("xcopy \"" INP2 "\" \"" LIB2 "\" /e");

    system("pause");
  }

  return 0;
}

#include <iostream>
#include <windows.h>
#include<direct.h>


using namespace std;


#define LIB "C:/Users/Daniil/Documents/Arduino/libraries/SHS_library"
#define INP "B:/SmartHomeSystem/SHSlibrary"



int main() {



  system("RD /S /Q \"" LIB "\""); // B:/at work/SmartHomeSystem/synchronizer/core\"");
  mkdir(LIB);
  
  system("xcopy \"" INP "\" \"" LIB "\" /e");

  int a;
  cin >> a;
}


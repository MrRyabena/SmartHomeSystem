#pragma once

/*
  Last update: v2.0.0
  Versions:
    v1.1.0 — created.
    v2.0.0 — Added a space in dout(), changed the debug-flag
*/

#include "shs_settings_private.h"


#ifdef SHS_SF_DEBUG

#ifdef SHS_SF_ARDUINO
#include <Arduino.h>
#define dinit() ({Serial.begin(115200); Serial.println("");})
#define dout(value) ({Serial.print(value); Serial.print(' ');})
#define doutln(value) Serial.println(value);
#define dsep() Serial.println("----------------------------------------");


#else
#include <iostream>
#define dinit()
#define dout(value) std::cout << value << ' ';
#define doutln(value) std::cout << value << std::endl;
#define dsep() std::cout << "----------------------------------------" << std::endl;


#endif

#else
#define dinit()
#define dout(value)
#define doutln(value)
#define dsep()
#endif

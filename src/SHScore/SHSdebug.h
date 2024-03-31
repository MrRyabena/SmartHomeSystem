#pragma once

/*
  Last update: v1.1.0
  Versions:
    v1.1.0 — created.
*/

#include "SHSsettings_private.h"
#ifdef DEBUG

#if __has_include(<Arduino.h>)
#include <Arduino.h>
#define dout(value) Serial.print(value);
#define doutln(value) Serial.println(value);
#define dsep() Serial.println("----------------------------------------");

#else
#include <iostream>
#define dout(value) std::cout << value;
#define doutln(value) std::cout << value << std::endl;
#define dsep() std::cout << "----------------------------------------" << std::endl;

#endif

#else

#define dout(value)
#define doutln(value)
#define dsep()
#endif
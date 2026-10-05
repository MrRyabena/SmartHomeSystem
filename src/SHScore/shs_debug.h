#pragma once

#include "shs_settings_private.h"


#ifdef SHS_SF_DEBUG

#ifdef SHS_SF_ARDUINO
#include <Arduino.h>
#define dinit() do { Serial.begin(115200); Serial.println(""); } while(0)
#define dout(value) do { Serial.print(value); Serial.print(' '); } while(0)
#define doutln(value) do { Serial.println(value); } while (0)
#define dfunc() do { dout(__PRETTY_FUNCTION__); } while (0)
#define dsep() do { Serial.println("----------------------------------------"); } while (0)


#else
#include <iostream>
#define dinit()
#define dout(value) do { std::cout << value << ' '; } while(0)
#define doutln(value) do { std::cout << value << std::endl; } while(0)
#define dfunc() do { std::cout << __PRETTY_FUNCTION__ << std::endl; } while(0)
#define dsep() do { std::cout << "----------------------------------------" << std::endl; } while(0)


#endif

#else
#define dinit()
#define dout(value)
#define doutln(value)
#define dfunc()
#define dsep()
#endif

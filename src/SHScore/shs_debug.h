#pragma once

/*
  Last update: v1.1.0
  Versions:
    v1.1.0 — created.
*/

#include "shs_settings_private.h"
#ifdef DEBUG

#ifdef SHS_SF_ARDUINO
#include <Arduino.h>
#define dinit() Serial.begin(115200);
#define dout(value) (Serial.print(value); Serial.print(' ');)
#define doutln(value) Serial.println(value);
#define dsep() Serial.println("----------------------------------------");

#elif defined(SHS_SF_QT)
#include <QDebug>
#include <iostream>
#define dinit()
#define dout(value) std::cout << value << ' ';
#define doutln(value) qDebug() << value;
#define dsep() qDebug() << "----------------------------------------";


#else
#include <iostream>
#define dinit()
#define dout(value) std::cout << value << ' ';
#define doutln(value) std::cout << value << std::endl;
#define dsep() std::cout << "----------------------------------------" << std::endl;


#endif

#else
#define dinit
#define dout(value)
#define doutln(value)
#define dsep()
#endif
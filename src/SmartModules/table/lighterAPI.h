#pragma once

#define BRARpin 10
#define BRALpin 9
#define BULBpin 6
#define FANpin 11
#define FANpwm 12
#define FANth A0



namespace LighterAPI {
  
enum API : uint8_t {
  started,
  request,
  answer,
  
  setMode,

  analogSetPin,
  digitalSetPin,

  getAnalogVal,
  getAnalogAverageVal,
  getDigitalVal,
  setK,

  setSettings,
  getSettings,

  getValue,
  getRPM,
  outRPM,
  outAnalogVal,
  outAnalogAverage,
  outSettings,

};
};

namespace LighterAPI {
enum Mode : uint8_t {
  off,
  on,

};

struct Settings {

  Mode mode = off;
  uint8_t braRval{};
  uint8_t braLval{};
  uint8_t bulbval{};
  bool flag{};
  uint8_t pwm{};

};


};
/*
// values
braRvalue
braLvalue
bulb0value
K

// sensors
th0    A0
th1    A1
th2    A2
th3    A3

ph0    A4
ph1    A5
ph2    A6

tah

// settings
get/set

*/


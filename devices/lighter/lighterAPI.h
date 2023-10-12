#pragma once

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
  getSettigns,

  getValue,
  outAnalogVal,
  outAnalogAverage,

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


#pragma once

enum API : uint8_t {
  started,
  setMode,

  analogSetPin,
  digitalSetPin,
  getAnalogVal,
  getDigitalVal,
  setK,

  setSettings,
  getSettigns,

  getValue,
  outAnalogAverage,

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


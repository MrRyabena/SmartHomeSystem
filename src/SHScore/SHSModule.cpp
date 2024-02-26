#include "SHSModule.h"

shs::Module shs::module = Module();

shs::Module::Module()
    : ntp(3, 1800),
      config(),
      errorsHandler(),
      processes(),
      sensors(),
      load() {}

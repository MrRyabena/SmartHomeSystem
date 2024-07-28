#pragma once

/*
  Last update: v2.0.0
  Versions:
    v0.1.0 — created.
    v1.0.0 — release.
    v2.0.0 — changed types, using shs::ID, added virtual destructor.
*/

/*
  This is an abstract class of API-handler.
  If you want to create your API-class for something, you must inherit from shs::API.
*/

#include <stdint.h>

#include "shs_ByteCollector.h"
#include "shs_types.h"

namespace shs
{
  class API;
};

class shs::API
{
public:
  explicit API(const shs::t::shs_ID_t id) : API_ID(id) {}
  virtual ~API() = default;

  virtual uint8_t handler(shs::ByteCollector<> &data) = 0;

  shs::t::shs_ID_t API_ID{};

  bool operator<(const shs::API &other) const { return API_ID < other.API_ID; }
  bool operator>(const shs::API &other) const { return API_ID > other.API_ID; }
  bool operator==(const shs::API &other) const { return API_ID == other.API_ID; }
  bool operator!=(const shs::API &other) const { return API_ID != other.API_ID; }
};

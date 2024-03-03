#pragma once

/*
  Last update: v1.0.0
  Versions:
    v0.2.0 — created.
    v1.0.0 — release.
*/

/*
  This is a class for automatically connecting and polling data handlers.
  It is used in data transfer protocols.
*/

#include <vector>
#include "SHSAPI.h"
#include "SHSByteCollector.h"

namespace shs
{
    class CallbacksKeeper;
};

class shs::CallbacksKeeper
{
public:
    explicit CallbacksKeeper() {}
    
    void attach(shs::API *object);
    void detach(shs::API *object);

    uint8_t handler(shs::ByteCollector &data);

protected:
    std::vector<shs::API *> m_ptrs;
    uint8_t m_find(shs::API *object);
};

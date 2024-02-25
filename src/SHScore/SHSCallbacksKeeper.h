#pragma once

/*
  Last update: v1.1.0
  Versions:
    v1.1.0 — created.
*/

#include <vector>
#include "SHSAPI.h"

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

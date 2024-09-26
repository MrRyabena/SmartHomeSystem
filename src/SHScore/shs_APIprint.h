#pragma once


#include "shs_API.h"
#include "shs_types.h"
#include "shs_ByteCollector.h"
#include "shs_ByteCollectorIterator.h"
#include "shs_debug.h"


namespace shs
{
    class APIprint;
}


class shs::APIprint : public shs::API
{
public:
    APIprint(const shs::t::shs_ID_t ID) : shs::API(ID) {}

    void handle(shs::ByteCollectorReadIterator<>& it) override
    {
        dsep();
        doutln("DTP packet:");
        for (auto i = 0; i < it.size(); i++)
        {
            dout(static_cast< int >(it.read()));
            dout(' ');
        }
        doutln();
        dsep();
    }
};

#pragma once

/*
  Last update: v2.0.0
  Versions:
    v0.2.0 — created for debugging API-handlers.
*/

/*
  API-handlers debug
*/

#include "shs_settings_private.h"

#ifdef SHS_SF_DEBUG

#include "shs_API.h"
#include "shs_types.h"
#include "shs_ByteCollector.h"
#include "shs_ByteCollectorIterator.h"
#include "shs_DTPpacket.h"
#include "shs_debug.h"


namespace shs
{
    class APIprint;
}


/**
 * @brief Debug-only API handler that prints received DTP packets.
 */
class shs::APIprint : public shs::API
{
public:
    /**
     * @brief Creates a debug API printer for the given identifier.
     */
    APIprint(const shs::t::shs_ID_t ID) : shs::API(ID) {}

    /**
     * @brief Prints the incoming packet contents to the debug output.
     */
    shs::DTPpacket handle(shs::ByteCollectorReadIterator<>& it) override
    {
        dsep();
        doutln("DTP packet:");
        for (auto i = 0; i < it.size(); i++)
        {
            dout(static_cast<int>(it.read()));
            dout(' ');
        }
        doutln();
        dsep();

        return shs::DTPpacket();
    }
};

#endif  // #ifdef SHS_SF_DEBUG

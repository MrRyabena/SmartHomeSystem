#pragma once

/*
  Last update: v2.1.0
  Versions:
    v2.0.0 — created.
    v2.1.0 — fixed a bug. There is a critical error that has not been fixed yet.
    v2.3.0 — updated docs.
*/

/*
  Classes for working with DTP service data.
*/

#include <stdint.h>

#include "shs_settings_private.h"

#ifdef SHS_SF_AVR
#include <shs_lib_AVR_STD_memory.h>
#else
#include <memory>
#endif 

#include "shs_API.h"
#include "shs_types.h"
#include "shs_DTPpacket.h"


namespace shs
{
    class DTP_API;
}


/**
 * @brief API handler that serves built-in DTP service commands.
 */
class shs::DTP_API : public shs::API
{
public:
    /**
     * @brief Creates the built-in DTP API handler.
     */
    DTP_API(shs::t::shs_ID_t ID);

    /**
     * @brief Destroys the DTP API handler.
     */
    ~DTP_API() = default;

    /**
     * @brief Handles built-in DTP service commands.
     */
    shs::DTPpacket handle(shs::ByteCollectorReadIterator<>& it) override;

    /**
     * @brief Handles built-in DTP service commands (static version).
     */
    static shs::DTPpacket static_handle(shs::ByteCollectorReadIterator<>& it);

    /**
     * @brief Builds an initial handshake packet.
     */
    static shs::DTPpacket getInitialPacket(shs::t::shs_ID_t ID = 0);

    /**
     * @brief Builds an answer to an initial handshake.
     */
    static shs::DTPpacket getInitialAnswerPacket(shs::t::shs_ID_t ID = 0, bool success = true);

    /**
     * @brief Builds a connection request packet.
     */
    static shs::DTPpacket getConnectionRequestPacket(shs::t::shs_ID_t ID = 0);

    /**
     * @brief Builds an answer to a connection request.
     */
    static shs::DTPpacket getConnectionRequestAnswerPacket(shs::t::shs_ID_t ID = 0, bool success = true);
};

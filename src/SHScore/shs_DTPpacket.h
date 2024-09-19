#pragma once

#include "shs_settings_private.h"
#include "shs_types.h"
#include "shs_CRC.h"
#include "shs_ByteCollector.h"
#include "shs_ID.h"


/*
    0x00  1B  -- message size
    0x01  4B  -- sender's ID
    0x05  4B  -- recipient's ID
    0x09  xB  -- data
    0xXX  1B  -- CRC
*/

namespace shs
{
    class DTPpacket;
}

class shs::DTPpacket
{
public:
    explicit DTPpacket(
        const shs::t::shs_ID_t senderID, const shs::t::shs_ID_t recipientID,
        shs::ByteCollector<>&& data
    );

    explicit DTPpacket(
        const shs::t::shs_ID_t senderID, const shs::t::shs_ID_t recipientID,
        const uint8_t* data, const uint8_t size
    );


    DTPpacket(shs::ByteCollector<>&& bc_data) : bc(std::move(bc_data)) {}


public:

    shs::t::shs_ID_t get_senderID()    const { shs::t::shs_ID_t id; for (uint8_t i = 0; i < sizeof(shs::t::shs_ID_t); i++) *(reinterpret_cast< uint8_t* >(&id) + i) = bc[1 + i]; return id; }
    shs::t::shs_ID_t get_recipientID() const { shs::t::shs_ID_t id; for (uint8_t i = 0; i < sizeof(shs::t::shs_ID_t); i++) *(reinterpret_cast< uint8_t* >(&id) + i) = bc[5 + i]; return id; }
    uint8_t          get_datasize()    const { return bc[0]; }

    [[nodiscard]] uint8_t check() const;


    shs::ByteCollector<> bc;
    static constexpr auto DTP_OFFSETbeg = 1 + 4 + 4;

    enum Error : uint8_t { ok, size_less, size_bigger, invalid_crc };
};

#pragma once

#include "shs_settings_private.h"
#include "shs_types.h"
#include "shs_CRC.h"
#include "shs_ByteCollector.h"
#include "shs_ByteCollectorIterator.h"
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
    [[nodiscard]] static shs::t::shs_ID_t get_senderID(shs::ByteCollectorReadIterator<>& it) { it.set_position(1); shs::t::shs_ID_t id{}; it.get(id); return id; }
    [[nodiscard]] static shs::t::shs_ID_t get_recipientID(shs::ByteCollectorReadIterator<>& it) { it.set_position(1 + sizeof(shs::t::shs_ID_t)); shs::t::shs_ID_t id{}; it.get(id); return id; }
    [[nodiscard]] static uint8_t get_datasize(shs::ByteCollectorReadIterator<>& it) { it.set_position(0); return it.read(); }
    [[nodiscard]] static uint8_t check(shs::ByteCollectorReadIterator<>& it);

    [[nodiscard]] shs::t::shs_ID_t get_senderID()    const { return get_senderID(bc.getReadIt()); }
    [[nodiscard]] shs::t::shs_ID_t get_recipientID() const { return get_recipientID(bc.getReadIt()); }
    [[nodiscard]] uint8_t          get_datasize()    const { return bc[0]; }

    [[nodiscard]] uint8_t check() const;


    shs::ByteCollector<> bc;
    static constexpr auto DTP_OFFSETbeg = 1 + 4 + 4;

    enum Error : uint8_t { ok, size_less, size_bigger, invalid_crc };
};

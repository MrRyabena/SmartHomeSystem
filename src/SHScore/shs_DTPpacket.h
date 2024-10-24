#pragma once

#include "shs_settings_private.h"
#include "shs_types.h"
#include "shs_CRC.h"
#include "shs_ByteCollector.h"
#include "shs_ByteCollectorIterator.h"
#include "shs_ID.h"

/*
    0x00  1B  -- message size
    0x01  1B  -- DTP code
    0x03  4B  -- sender's ID     \ * may be unused
    0x06  4B  -- recipient's ID  | *
    0x0a  xB  -- data
    0xXX  1B  -- CRC             | *
*/

namespace shs
{
    class DTPpacket;
}

class shs::DTPpacket
{
public:

    explicit DTPpacket(const bool empty) : bc() {}

    explicit DTPpacket(
        const shs::t::shs_ID_t senderID, const shs::t::shs_ID_t recipientID,
        shs::ByteCollector<>&& data
    );

    explicit DTPpacket(
        const shs::t::shs_ID_t senderID, const shs::t::shs_ID_t recipientID,
        const uint8_t* data, const uint8_t size
    );

    explicit DTPpacket(const uint8_t* data, const uint8_t size);


    DTPpacket(shs::ByteCollector<>&) = delete;
    DTPpacket& operator=(DTPpacket&) = delete;

    DTPpacket(shs::ByteCollector<>&& bc_data) : bc(std::move(bc_data)) {}
    DTPpacket& operator=(DTPpacket&& other) noexcept
    {
        if (this != &other)
        {
            bc = std::move(other.bc);
        }
        return *this;
    }


    DTPpacket(DTPpacket&& other) noexcept : bc(std::move(other.bc)) {}


    [[nodiscard]] static shs::t::shs_ID_t get_senderID(shs::ByteCollectorReadIterator<> it) { it.set_position(2); shs::t::shs_ID_t id{}; it.get(id); return id; }
    [[nodiscard]] static shs::t::shs_ID_t get_recipientID(shs::ByteCollectorReadIterator<> it) { it.set_position(2 + sizeof(shs::t::shs_ID_t)); shs::t::shs_ID_t id{}; it.get(id); return id; }
    [[nodiscard]] static uint8_t get_datasize(shs::ByteCollectorReadIterator<> it) { it.set_position(0); return it.read() - (it.read() == STANDARD ? DTPstandard_OFFSETbeg - 1 : DTPstandard_OFFSETbeg); }
    [[nodiscard]] static uint8_t get_dataBeg(shs::ByteCollectorReadIterator<> it) { it.set_position(1); return it.read() == STANDARD ? 1 + 1 + 4 + 4 : 2; }
    [[nodiscard]] static uint8_t check(shs::ByteCollectorReadIterator<> it);


    [[nodiscard]] shs::t::shs_ID_t get_senderID()    const { return get_senderID(bc.getReadIt(true)); }
    [[nodiscard]] shs::t::shs_ID_t get_recipientID() const { return get_recipientID(bc.getReadIt(true)); }
    [[nodiscard]] uint8_t          get_datasize()    const { return get_datasize(bc.getReadIt(true)); }
    [[nodiscard]] uint8_t          get_readIt() { return bc.setPositionRead(get_dataBeg(bc.getReadIt(true))); }

    [[nodiscard]] uint8_t check() const;

    [[nodiscard]] bool empty() { return bc.empty(); }


    shs::ByteCollector<> bc;
    static constexpr auto DTPstandard_OFFSETbeg = 1 + 1 + 4 + 4;
    static constexpr auto DTPfast_OFFSETbeg = 1 + 1;



    enum Error : uint8_t { ok, size_less, size_bigger, invalid_crc };
    enum DTPcode : uint8_t { STANDARD = 1, FAST, };
};

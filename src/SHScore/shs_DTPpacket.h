#pragma once

#include "shs_settings_private.h"
#include "shs_types.h"
#include "shs_CRC.h"
#include "shs_ByteCollector.h"
#include "shs_ByteCollectorIterator.h"
#include "shs_ID.h"

#include <memory>

/*
    0x00  1B  -- message size
    0x01  1B  -- DTP code
    0x02  4B  -- sender's ID     \ * may be unused
    0x05  4B  -- recipient's ID  | *
    0x09  xB  -- data
    0xXX  1B  -- CRC             | *
*/

namespace shs
{
    class DTPpacket;
}

class shs::DTPpacket
{
public:
    enum Error : uint8_t { ok, size_less, size_bigger, invalid_crc };
    enum DTPcode : uint8_t { STANDARD = 1, FAST, INITIAL, INITIAL_ANSWER, DEINITIAL, CONNECTION_REQUEST };

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
    DTPpacket& operator=(const DTPpacket&) = delete;
    DTPpacket(const DTPpacket&) = delete;

    int value = 10;
    int val2 = std::move(value);

    DTPpacket(shs::ByteCollector<>&& bc_data) noexcept : bc(std::move(bc_data)) {}
    DTPpacket(DTPpacket&& other) noexcept : bc(std::move(other.bc)) {}
    DTPpacket& operator=(DTPpacket&& other) noexcept
    {
        if (this != &other) bc = std::move(other.bc);
        return *this;
    }

    ~DTPpacket() = default;


    [[nodiscard]] static uint8_t get_DTPcode(shs::ByteCollectorReadIterator<> it) { it.set_position(1); return it.read(); }
    [[nodiscard]] static shs::t::shs_ID_t get_senderID(shs::ByteCollectorReadIterator<> it) { if (get_DTPcode(it) != FAST) return shs::t::shs_ID_t(0); shs::t::shs_ID_t id{}; it.get(id); return id; }
    [[nodiscard]] static shs::t::shs_ID_t get_recipientID(shs::ByteCollectorReadIterator<> it) { if (get_DTPcode(it) != FAST) return shs::t::shs_ID_t(0); it.set_position(2 + sizeof(shs::t::shs_ID_t)); shs::t::shs_ID_t id{}; it.get(id); return id; }
    [[nodiscard]] static uint8_t get_datasize(shs::ByteCollectorReadIterator<> it) { return int(it[0]) - (it[1] == STANDARD ? DTPstandard_OFFSETbeg + 1 : DTPstandard_OFFSETbeg); }
    [[nodiscard]] static uint8_t get_dataBeg(shs::ByteCollectorReadIterator<> it) { return it[1] == STANDARD ? DTPstandard_OFFSETbeg : 2; }
    [[nodiscard]] static uint8_t check(shs::ByteCollectorReadIterator<> it);


    [[nodiscard]] uint8_t          get_DTPcode()     const { return get_DTPcode(bc.getReadIt(true)); }
    [[nodiscard]] shs::t::shs_ID_t get_senderID()    const { return get_senderID(bc.getReadIt(true)); }
    [[nodiscard]] shs::t::shs_ID_t get_recipientID() const { return get_recipientID(bc.getReadIt(true)); }
    [[nodiscard]] uint8_t          get_datasize()    const { return get_datasize(bc.getReadIt(true)); }
    [[nodiscard]] uint8_t          get_readIt() { return bc.setPositionRead(get_dataBeg(bc.getReadIt(true))); }

    [[nodiscard]] uint8_t check() const;

    [[nodiscard]] bool empty() { return bc.empty(); }

    void set_DTPcode(const DTPcode code)
    {
        bc[1] = code;
        bc.back() = shs::CRC8::crcBuf(bc.getPtr(), bc.size() - 1);
    }


    shs::ByteCollector<> bc;
    static constexpr auto DTPstandard_OFFSETbeg = 1 + 1 + 4 + 4;
    static constexpr auto DTPfast_OFFSETbeg = 1 + 1;
};

#pragma once


/*
  Last update: v2.0.0
  Versions:
    v2.0.0 — created a new component of DTP.
*/

#include "shs_settings_private.h"
#include "shs_types.h"
#include "shs_CRC.h"
#include "shs_ByteCollector.h"
#include "shs_ByteCollectorIterator.h"
#include "shs_ID.h"

#include <memory>

namespace shs
{
    class DTPpacket;
}


/*
  Class for creating, encrypting, and decrypting messages.
  Scheme:
    0x00  1B  -- message size
    0x01  1B  -- DTP code
    0x02  4B  -- sender's ID       *
    0x05  4B  -- recipient's ID    *
    0x09  xB  -- data
    0xXX  1B  -- CRC               *

   (* may be unused)
*/
class shs::DTPpacket
{
public:
    enum Error : uint8_t { ok, size_less, size_bigger, invalid_crc };
    enum DTPcode : uint8_t { STANDARD = 1, FAST, INITIAL, INITIAL_ANSWER, DEINITIAL, CONNECTION_REQUEST };

    DTPpacket() noexcept : bc() {}

    explicit DTPpacket(
        const shs::t::shs_ID_t senderID, const shs::t::shs_ID_t recipientID,
        shs::ByteCollector<>&& data
    ) noexcept;

    explicit DTPpacket(
        const shs::t::shs_ID_t senderID, const shs::t::shs_ID_t recipientID,
        const shs::ByteCollector<>& data
    ) noexcept;

    explicit DTPpacket(
        const shs::t::shs_ID_t senderID, const shs::t::shs_ID_t recipientID,
        const uint8_t* data, const uint8_t size
    ) noexcept;

    explicit DTPpacket(const uint8_t* data, const uint8_t size) noexcept;

    explicit DTPpacket(shs::ByteCollector<>&& bc_data) noexcept : bc(std::move(bc_data)) {}
    explicit DTPpacket(const shs::ByteCollector<>& bc_data) noexcept : bc(bc_data) {}

    DTPpacket(DTPpacket&& other) noexcept : bc(std::move(other.bc)) {}
    DTPpacket(const DTPpacket& other) noexcept : bc(other.bc) {}

    DTPpacket& operator=(DTPpacket&& other) noexcept
    {
        if (this != &other) bc = std::move(other.bc);
        return *this;
    }

    DTPpacket& operator=(const DTPpacket& other) noexcept
    {
        if (this != &other) bc = other.bc;
        return *this;
    }

    ~DTPpacket() noexcept = default;


    [[nodiscard]] static uint8_t get_DTPcode(shs::ByteCollectorReadIterator<> it) { it.set_position(1); return it.read(); }
    [[nodiscard]] static shs::t::shs_ID_t get_senderID(shs::ByteCollectorReadIterator<> it) { if (get_DTPcode(it) == FAST) return shs::t::shs_ID_t(0); shs::t::shs_ID_t id{}; it.set_position(2); it.get(id); return id; }
    [[nodiscard]] static shs::t::shs_ID_t get_recipientID(shs::ByteCollectorReadIterator<> it) { if (get_DTPcode(it) == FAST) return shs::t::shs_ID_t(0); it.set_position(2 + sizeof(shs::t::shs_ID_t)); shs::t::shs_ID_t id{}; it.get(id); return id; }
    [[nodiscard]] static uint8_t get_datasize(shs::ByteCollectorReadIterator<> it) { return int(it[0]) - (it[1] == STANDARD ? DTPstandard_OFFSETbeg + 1 : DTPstandard_OFFSETbeg); }
    [[nodiscard]] static uint8_t get_dataBeg(shs::ByteCollectorReadIterator<> it) { return it[1] == STANDARD ? DTPstandard_OFFSETbeg : 2; }
    [[nodiscard]] static uint8_t check(shs::ByteCollectorReadIterator<> it);


    [[nodiscard]] uint8_t          get_DTPcode()     const { return get_DTPcode(bc.getReadIt(true)); }
    [[nodiscard]] shs::t::shs_ID_t get_senderID()    const { return get_senderID(bc.getReadIt(true)); }
    [[nodiscard]] shs::t::shs_ID_t get_recipientID() const { return get_recipientID(bc.getReadIt(true)); }
    [[nodiscard]] uint8_t          get_datasize()    const { return get_datasize(bc.getReadIt(true)); }
    [[nodiscard]] uint8_t          get_readIt() { return bc.setPositionRead(get_dataBeg(bc.getReadIt(true))); }

    [[nodiscard]] uint8_t check() const;

    [[nodiscard]] bool empty() const { return bc.empty(); }
    operator bool() const { return bc.empty(); }


    void set_DTPcode(const DTPcode code)
    {
        bc[1] = code;
        bc.back() = shs::CRC8::crcBuf(bc.getPtr(), bc.size() - 1);
    }


    shs::ByteCollector<> bc;
    static constexpr auto DTPstandard_OFFSETbeg = 1 + 1 + 4 + 4;
    static constexpr auto DTPfast_OFFSETbeg = 1 + 1;
};

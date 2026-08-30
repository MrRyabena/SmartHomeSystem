#pragma once


/*
  Last update: v2.0.0
  Versions:
    v2.0.0 — created a new component of DTP.
    v2.3.0 — updated docs.
*/

#include "shs_settings_private.h"

#ifdef SHS_SF_AVR
#include <shs_lib_AVR_STD_memory.h>
#else
#include <memory>
#endif 

#include "shs_types.h"
#include "shs_CRC.h"
#include "shs_ByteCollector.h"
#include "shs_ByteCollectorIterator.h"
#include "shs_ID.h"


namespace shs
{
    class DTPpacket;
}


/**
 * @brief Packet helper for constructing, parsing, and validating DTP messages.
 *
 * Layout:
 *  0x00  1B  -- message size
 *  0x01  1B  -- DTP code
 *  0x02  4B  -- sender's ID       *
 *  0x06  4B  -- recipient's ID    *
 *  0x0A  xB  -- data
 *  0xXX  1B  -- CRC               *
 *
 * (* may be unused)
 */
class shs::DTPpacket
{
public:
    enum Error : uint8_t { ok, size_less, size_bigger, invalid_crc };
    enum DTPcode : uint8_t { STANDARD = 1, FAST, INITIAL, INITIAL_ANSWER, DEINITIAL, CONNECTION_REQUEST, MASK, CONNECTION_REQUEST_ANSWER };

    /**
     * @brief Creates an empty packet.
     */
    DTPpacket() noexcept : bc() {}

    /**
     * @brief Creates a outgoing packet from owned byte data.
        * @param senderID Sender endpoint ID.
        * @param recipientID Recipient endpoint ID.
        * @param data Owned payload bytes.
     */
    explicit DTPpacket(
        const shs::t::shs_ID_t senderID, const shs::t::shs_ID_t recipientID,
        shs::ByteCollector<>&& data
    ) noexcept;

    /**
     * @brief Creates a masked outgoing packet from owned byte data.
        * @param senderID Sender endpoint ID.
        * @param recipientID Recipient endpoint ID.
        * @param mask Additional mask ID.
        * @param data Owned payload bytes.
     */
    explicit DTPpacket(
        const shs::t::shs_ID_t senderID, const shs::t::shs_ID_t recipientID,
        const shs::t::shs_ID_t mask,
        shs::ByteCollector<>&& data
    ) noexcept;

    /**
     * @brief Creates a outgoing packet from shared byte data.
        * @param senderID Sender endpoint ID.
        * @param recipientID Recipient endpoint ID.
        * @param data Payload bytes to copy.
     */
    explicit DTPpacket(
        const shs::t::shs_ID_t senderID, const shs::t::shs_ID_t recipientID,
        const shs::ByteCollector<>& data
    ) noexcept;

    /**
     * @brief Creates a masked outgoing packet from shared byte data.
        * @param senderID Sender endpoint ID.
        * @param recipientID Recipient endpoint ID.
        * @param mask Additional mask ID.
        * @param data Payload bytes to copy.
     */
    explicit DTPpacket(
        const shs::t::shs_ID_t senderID, const shs::t::shs_ID_t recipientID,
        const shs::t::shs_ID_t mask,
        const shs::ByteCollector<>& data
    ) noexcept;

    /**
     * @brief Creates a outgoing packet from a raw byte buffer.
        * @param senderID Sender endpoint ID.
        * @param recipientID Recipient endpoint ID.
        * @param data Pointer to payload bytes.
        * @param size Payload size in bytes.
     */
    explicit DTPpacket(
        const shs::t::shs_ID_t senderID, const shs::t::shs_ID_t recipientID,
        const uint8_t* data, const uint8_t size
    ) noexcept;

    /**
     * @brief Creates a masked outgoing packet from a raw byte buffer.
        * @param senderID Sender endpoint ID.
        * @param recipientID Recipient endpoint ID.
        * @param mask Additional mask ID.
        * @param data Pointer to payload bytes.
        * @param size Payload size in bytes.
     */
    explicit DTPpacket(
        const shs::t::shs_ID_t senderID, const shs::t::shs_ID_t recipientID,
        const shs::t::shs_ID_t mask,
        const uint8_t* data, const uint8_t size
    ) noexcept;

    /**
     * @brief Decodes a incoming packet from a raw byte buffer.
        * @param data Pointer to serialized packet bytes.
        * @param size Packet size in bytes.
     */
    explicit DTPpacket(const uint8_t* data, const uint8_t size) noexcept;

    /**
     * @brief Wraps an existing byte collector as a packet. Decodes a incoming packet.
        * @param bc_data Byte collector to move.
     */
    explicit DTPpacket(shs::ByteCollector<>&& bc_data) noexcept : bc(std::move(bc_data)) {}

    /**
     * @brief Wraps an existing byte collector as a packet. Decodes a incoming packet.
        * @param bc_data Byte collector to copy.
     */
    explicit DTPpacket(const shs::ByteCollector<>& bc_data) noexcept : bc(bc_data) {}

    /**
     * @brief Moves a packet.
        * @param other Packet to move from.
     */
    DTPpacket(DTPpacket&& other) noexcept : bc(std::move(other.bc)) {}

    /**
     * @brief Copies a packet.
        * @param other Packet to copy from.
     */
    DTPpacket(const DTPpacket& other) noexcept : bc(other.bc) {}

    /**
     * @brief Moves packet contents from another packet.
        * @param other Packet to move from.
        * @return Reference to this packet.
     */
    DTPpacket& operator=(DTPpacket&& other) noexcept
    {
        if (this != &other) bc = std::move(other.bc);
        return *this;
    }

    /**
     * @brief Copies packet contents from another packet.
        * @param other Packet to copy from.
        * @return Reference to this packet.
     */
    DTPpacket& operator=(const DTPpacket& other) noexcept
    {
        if (this != &other) bc = other.bc;
        return *this;
    }

    /**
     * @brief Destroys the packet.
     */
    ~DTPpacket() noexcept = default;


    /**
     * @brief Returns the DTP code from a read iterator.
        * @param it Iterator over packet bytes.
        * @return Parsed DTP code.
     */
    [[nodiscard]] static uint8_t get_DTPcode(shs::ByteCollectorReadIterator<> it) { return it[1]; }

    /**
     * @brief Returns the sender ID from a read iterator.
        * @param it Iterator over packet bytes.
        * @return Parsed sender ID.
     */
    [[nodiscard]] static shs::t::shs_ID_t get_senderID(shs::ByteCollectorReadIterator<> it);

    /**
     * @brief Returns the recipient ID from a read iterator.
        * @param it Iterator over packet bytes.
        * @return Parsed recipient ID.
     */
    [[nodiscard]] static shs::t::shs_ID_t get_recipientID(shs::ByteCollectorReadIterator<> it);

    /**
     * @brief Returns the payload size from a read iterator.
        * @param it Iterator over packet bytes.
        * @return Payload size in bytes.
     */
    [[nodiscard]] static uint8_t get_datasize(shs::ByteCollectorReadIterator<> it);

    /**
     * @brief Returns the offset where payload data begins.
        * @param it Iterator over packet bytes.
        * @return Payload start offset.
     */
    [[nodiscard]] static uint8_t get_dataBeg(shs::ByteCollectorReadIterator<> it);

    /**
     * @brief Validates the packet layout and checksum from a read iterator.
        * @param it Iterator over packet bytes.
        * @return Value from Error enum.
     */
    [[nodiscard]] static uint8_t check(shs::ByteCollectorReadIterator<> it);

    /**
     * @brief Returns the mask ID from a read iterator.
        * @param it Iterator over packet bytes.
        * @return Parsed mask ID.
     */
    [[nodiscard]] static shs::t::shs_ID_t get_mask(shs::ByteCollectorReadIterator<> it);

    /**
     * @brief Returns the packet DTP code.
        * @return Packet DTP code.
     */
    [[nodiscard]] uint8_t          get_DTPcode()     const { return get_DTPcode(bc.getReadIt(true)); }

    /**
     * @brief Returns the sender ID.
        * @return Sender endpoint ID.
     */
    [[nodiscard]] shs::t::shs_ID_t get_senderID()    const { return get_senderID(bc.getReadIt(true)); }

    /**
     * @brief Returns the recipient ID.
        * @return Recipient endpoint ID.
     */
    [[nodiscard]] shs::t::shs_ID_t get_recipientID() const { return get_recipientID(bc.getReadIt(true)); }

    /**
     * @brief Returns the payload size.
        * @return Payload size in bytes.
     */
    [[nodiscard]] uint8_t          get_datasize()    const { return get_datasize(bc.getReadIt(true)); }

    /**
     * @brief Returns a read iterator positioned at the payload start.
        * @return Read position index returned by ByteCollector.
     */
    [[nodiscard]] uint8_t          get_readIt() { return bc.setPositionRead(get_dataBeg(bc.getReadIt(true))); }

    /**
     * @brief Returns the packet mask.
        * @return Mask endpoint ID.
     */
    [[nodiscard]] shs::t::shs_ID_t get_mask()        const { return get_mask(bc.getReadIt(true)); }

    /**
     * @brief Validates the stored packet.
        * @return Value from Error enum.
     */
    [[nodiscard]] uint8_t check() const;

    /**
     * @brief Reports whether the packet is empty.
        * @return True when packet has no bytes.
     */
    [[nodiscard]] bool empty() const { return bc.empty(); }

    /**
     * @brief Reports whether the packet contains data.
        * @return True when packet is empty in current implementation semantics.
     */
    operator bool() const { return bc.empty(); }


    /**
     * @brief Updates the packet code and refreshes the checksum.
        * @param code New DTP code.
     */
    void set_DTPcode(const DTPcode code)
    {
        bc[1] = code;
        bc.back() = shs::CRC8::crcBuf(bc.getPtr(), bc.size() - 1);
    }

    /**
     * @brief Updates or inserts the packet mask and refreshes the checksum.
        * @param mask New mask ID.
     */
    void set_mask(const shs::t::shs_ID_t mask)
    {
        if (get_DTPcode() != DTPcode::MASK) bc.insert(&mask, sizeof(mask), 0x9);
        else for (auto i = 10; i < 10 + sizeof(mask); i++) bc[i] = reinterpret_cast<const uint8_t*>(&mask)[i - 10];
        bc.back() = shs::CRC8::crcBuf(bc.getPtr(), bc.size() - 1);
    }


    shs::ByteCollector<> bc;
    static constexpr auto DTPstandard_OFFSETbeg = 1 + 1 + 4 + 4;
    static constexpr auto DTPfast_OFFSETbeg = 1 + 1;
};

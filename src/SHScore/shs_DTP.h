#pragma once

/*
  Smart Home System Data Transfer Protocol

  The idea is taken from https://github.com/GyverLibs/GyverBus
*/

/*
  Last update: v2.0.0
  Versions:
	v0.1.0 — created.
	v0.2.0
	  - Divided into two classes.
	  - A new type of handlers.
	  - Added inheritance from class shs::CallbacksKeeper.
	  - Using a new class for CRC.
	v1.0.0 — release.
	  - Namespaces added.
	  - Variable names have been corrected.
	v2.0.0 — global changes, divided into components and expanded.
	  - Divided into component classes:
		- shs::DTP — container class for linking data buses and API handlers
		- shs::DTPbus — abstract class of a data bus that accepts and sends messages
		- shs::DTPdiscover — class for searching for devices on a local network
		- shs::DTPless — comparison operators (for search and sorting algorithms)
		- shs::DTPpacket — a class for creating, encrypting, and decrypting messages
	  - Tested.
	v2.3.0 — updated docs, fixes.
	   - multiple fixes and improvements — corrected data-shift logic
	   - add DTP code `MASK`
	   - stability and initialization fixes
 */


#include "shs_settings_private.h"
#ifndef SHS_SF_AVR

#include <memory>
#include <vector>
#include <deque>


#include "shs_Process.h"
#include "shs_API.h"
#include "shs_SortedBuf.h"
#include "shs_algorithm.h"
#include "shs_ID.h"
#include "shs_types.h"
#include "shs_DTPbus.h"
#include "shs_DTPpacket.h"
#include "shs_DTPless.h"
#include "shs_ProgramTimer.h"
#include "shs_DTPbusController.h"

#ifdef SHS_SF_NETWORK
#include "shs_DTPdiscover.h"
#include "shs_TcpSocket.h"
#endif    // #ifdef SHS_SF_NETWORK

#include "shs_debug.h"

namespace shs
{
	class DTP;
}

/**
 * @brief Container that links DTP buses, API handlers, and discovery helpers.
 */
class shs::DTP : public shs::Process
{
public:

	shs::t::shs_ID_t moduleID;

	/**
	 * @brief Creates a DTP container for the given module ID.
	 * @param module_id Module ID to use for this DTP instance.
	 * @param discover Optional shared pointer to a discovery helper. If not provided,
	 * a new instance will be created internally.
	 */
	explicit DTP(const shs::t::shs_ID_t module_id
	#ifdef SHS_SF_NETWORK
		,
		std::shared_ptr<shs::DTPdiscover> discover = nullptr
	#endif
	)
		: moduleID(module_id)
	#ifdef SHS_SF_NETWORK
		,
		m_discover(discover ? discover : std::make_shared<shs::DTPdiscover>(module_id))
	#endif
	{}

	/**
	 * @brief Destroys the DTP container.
	 */
	~DTP() override = default;

	/**
	 * @brief Sends a packet through the bus that serves the recipient module.
	 * @param packet Packet to route and send.
	 * @return Number of bytes sent or 0 on failure.
	 */
	uint8_t sendPacket(const shs::DTPpacket& packet);

	/**
	 * @brief Sends raw bytes through the bus that serves the recipient module.
	 * @param bc Byte collector with outgoing payload.
	 * @param id Recipient module ID.
	 * @return Number of bytes sent or 0 on failure.
	 */
	uint8_t sendRAW(shs::ByteCollector<>& bc, const uint8_t id) { auto bus = findBusFromModule(id); return (bus ? bus->sendRAW(bc) : 0); }

	/**
	 * @brief Sends raw bytes from an iterator through the bus that serves the recipient module.
	 * @param it Read iterator over outgoing bytes.
	 * @param id Recipient module ID.
	 * @return Number of bytes sent or 0 on failure.
	 */
	uint8_t sendRAW(shs::ByteCollectorReadIterator<>& it, const uint8_t id) { auto bus = findBusFromModule(id); return (bus ? bus->sendRAW(it) : 0); }

	/**
	 * @brief Sends a raw byte buffer through the bus that serves the recipient module.
	 * @param data Pointer to outgoing byte buffer.
	 * @param size Buffer size in bytes.
	 * @param id Recipient module ID.
	 * @return Number of bytes sent or 0 on failure.
	 */
	uint8_t sendRAW(const uint8_t* data, const uint8_t size, const uint8_t id) { auto bus = findBusFromModule(id); return (bus ? bus->sendRAW(data, size) : 0); }

	/**
	 * @brief Finds the bus that owns the given module ID.
	 * @param moduleID Module ID to search for.
	 * @return Pointer to matching bus or nullptr if not found.
	 */
	shs::DTPbus* findBusFromModule(const uint8_t moduleID) const;

	/**
	 * @brief Attaches a new bus and assigns it a unique bus ID when needed.
	 * @param bus Shared pointer to the bus instance to attach.
	 * @return Assigned bus ID.
	 */
	shs::t::shs_busID_t attachBus(std::shared_ptr<shs::DTPbus> bus);

	/**
	 * @brief Attaches a new bus and assigns it a unique bus ID when needed.
	 * @param bus Owned bus instance to attach.
	 * @return Assigned bus ID.
	 */
	[[deprecated("Use attachBus(std::shared_ptr<shs::DTPbus>) instead")]]
	shs::t::shs_busID_t attachBus(std::unique_ptr<shs::DTPbus>&& bus) { return attachBus(std::shared_ptr<shs::DTPbus>(std::move(bus))); }

	/**
	 * @brief Detaches a bus by its bus ID.
	 * @param id Bus ID to detach.
	 */
	void detachBus(const shs::t::shs_busID_t& id) { m_buss.detach(id); }

	/**
	 * @brief Returns the bus with the given ID or nullptr if it is missing.
	 * @param id Bus ID to query.
	 * @return Pointer to bus or nullptr when absent.
	 */
	std::shared_ptr<shs::DTPbus> getBus(const shs::t::shs_busID_t& id) const { auto it = m_buss.get(id); return it != m_buss.end() ? it->get() : nullptr; }

	/**
	 * @brief Generates an unused bus ID.
	 * @return Unique bus ID not currently in use.
	 */
	shs::t::shs_busID_t getUniqueBusID() const;


	/**
	 * @brief Attaches an owned API handler.
	 * @param api Owned API handler.
	 */
	void attachAPI(std::unique_ptr<shs::API>&& api) { m_APIs.attach(std::move(api)); }

	/**
	 * @brief Attaches a non-owned API handler.
	 * @param api Non-owned API handler pointer.
	 */
	void attachAPI(shs::API* api) { m_externalAPIs.attach(api); }

	/**
	 * @brief Detaches both owned and external API handlers with the given ID.
	 * @param id API ID to detach.
	 */
	void detachAPI(const shs::t::shs_ID_t& id) { m_APIs.detach(id); m_externalAPIs.detach(id); }

	/**
	 * @brief Returns an attached owned API handler.
	 * @param id API ID to query.
	 * @return Reference to attached API handler.
	 */
	shs::API& getAPI(const shs::t::shs_ID_t& id) const { return *(m_APIs.get(id)->get()); }

	/**
	 * @brief Starts all buses and the discovery helper.
	 */
	void start() override;
	void tick() override;
	/**
	 * @brief Stops all buses.
	 */
	void stop() override { for (auto& bus : m_buss) bus->stop(); }

private:
	struct OutgoingPacket
	{
		enum class BusStatus : uint8_t { NOT_FOUND, WAITING_FROM_DISCOVER, DISCOVERED };
		shs::DTPpacket packet;
		shs::ProgramTimer timer;
		BusStatus status;

		explicit OutgoingPacket(const shs::DTPpacket& pkt) : packet(pkt), status(BusStatus::NOT_FOUND), timer(20'000) {}
		explicit OutgoingPacket(shs::DTPpacket&& pkt) : packet(std::move(pkt)), status(BusStatus::NOT_FOUND), timer(20'000) {}
	};

	shs::SortedBuf<std::shared_ptr<shs::DTPbus>, DTPless::BUS> m_buss;
	shs::SortedBuf<std::unique_ptr<shs::API>, DTPless::API> m_APIs;
	shs::SortedBuf<shs::API*, DTPless::API> m_externalAPIs;
	std::vector<shs::DTPbusController> m_bus_controllers;
	std::deque<OutgoingPacket> m_outgoing_packets;
#ifdef SHS_SF_NETWORK
	std::shared_ptr<shs::DTPdiscover> m_discover;
#endif
};


#endif    // #ifndef SHS_SF_AVR

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
*/

#include "shs_settings_private.h"
#ifndef SHS_SF_AVR

#include <memory>
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
#include "shs_DTPdiscover.h"
#include "shs_TcpSocket.h"

#include "shs_debug.h"

namespace shs
{
	class DTP;
}

/*
  Container class for linking data buses and API handlers.
*/
class shs::DTP : public shs::Process
{
public:

	shs::t::shs_ID_t moduleID;


	explicit DTP(const shs::t::shs_ID_t module_id) : moduleID(module_id), m_discover(std::make_shared<shs::DTPdiscover>(module_id)) {}

	~DTP() override = default;

	// sending data
	uint8_t sendPacket(const shs::DTPpacket& packet);
	uint8_t sendRAW(shs::ByteCollector<>& bc, const uint8_t id) { auto bus = findBusFromModule(id); return (bus ? bus->sendRAW(bc) : 0); }
	uint8_t sendRAW(shs::ByteCollectorReadIterator<>& it, const uint8_t id) { auto bus = findBusFromModule(id); return (bus ? bus->sendRAW(it) : 0); }
	uint8_t sendRAW(const uint8_t* data, const uint8_t size, const uint8_t id) { auto bus = findBusFromModule(id); return (bus ? bus->sendRAW(data, size) : 0); }

	shs::DTPbus* findBusFromModule(const uint8_t moduleID) const;

	// BUS
	shs::t::shs_busID_t attachBus(std::unique_ptr<shs::DTPbus>&& bus)
	{
		doutln("DTP::attachBus");
		if (bus && (bus->busID == 0 || m_buss.get(bus) != m_buss.end())) bus->busID = getUniqueBusID();
		doutln("set busID");
		return (*m_buss.attach(std::move(bus)))->busID;
	}

	void detachBus(const shs::t::shs_busID_t& id) { m_buss.detach(id); }
	shs::DTPbus* getBus(const shs::t::shs_busID_t& id) const { auto it = m_buss.get(id); return it != m_buss.end() ? it->get() : nullptr; }

	shs::t::shs_busID_t getUniqueBusID() const;


	// API
	void attachAPI(std::unique_ptr<shs::API>&& api) { m_APIs.attach(std::move(api)); }
	void attachAPI(shs::API* api) { m_externalAPIs.attach(api); }
	void detachAPI(const shs::t::shs_ID_t& id) { m_APIs.detach(id); m_externalAPIs.detach(id); }
	shs::API& getAPI(const shs::t::shs_ID_t& id) const { return *(m_APIs.get(id)->get()); }

	// shs::Process
	void start() override { for (auto& bus : m_buss) bus->start(); if(m_discover) m_discover->start(); }
	void tick() override;
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

	shs::SortedBuf<std::unique_ptr<shs::DTPbus>, DTPless::BUS> m_buss;
	shs::SortedBuf<std::unique_ptr<shs::API>, DTPless::API> m_APIs;
	shs::SortedBuf<shs::API*, DTPless::API> m_externalAPIs;
	std::deque<OutgoingPacket> m_outgoing_packets;
	std::shared_ptr<shs::DTPdiscover> m_discover;
};


#endif    // #ifndef SHS_SF_AVR

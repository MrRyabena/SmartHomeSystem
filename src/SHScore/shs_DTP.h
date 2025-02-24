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


#include <memory>


#include "shs_Process.h"
#include "shs_API.h"
#include "shs_SortedBuf.h"
#include "shs_algorithm.h"
#include "shs_ID.h"
#include "shs_types.h"
#include "shs_DTPbus.h"
#include "shs_DTPpacket.h"
#include "shs_DTPless.h"


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


  explicit DTP(const shs::t::shs_ID_t module_id) : moduleID(module_id) {}

  ~DTP() override = default;

  // sending data
  uint8_t sendPacket(const shs::DTPpacket& packet) { auto bus = findBusFromModule(packet.get_recipientID().getModuleID()); return (bus ? bus->sendPacket(packet) : 0); }
  uint8_t sendRAW(shs::ByteCollector<>& bc, const uint8_t id) { auto bus = findBusFromModule(id); return (bus ? bus->sendRAW(bc) : 0); }
  uint8_t sendRAW(shs::ByteCollectorReadIterator<>& it, const uint8_t id) { auto bus = findBusFromModule(id); return (bus ? bus->sendRAW(it) : 0); }
  uint8_t sendRAW(const uint8_t* data, const uint8_t size, const uint8_t id) { auto bus = findBusFromModule(id); return (bus ? bus->sendRAW(data, size) : 0); }

  shs::DTPbus* findBusFromModule(const uint8_t moduleID) const;

  // BUS
  shs::t::shs_busID_t attachBus(std::unique_ptr<shs::DTPbus>&& bus)
  {
    if (bus->busID == 0 || m_buss.get(bus) != m_buss.end()) bus->busID = getUniqueBusID();
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
  void start() override { for (auto& bus : m_buss) bus->start(); }
  void tick() override;
  void stop() override { for (auto& bus : m_buss) bus->stop(); }

private:
  shs::SortedBuf<std::unique_ptr<shs::DTPbus>, DTPless::BUS> m_buss;
  shs::SortedBuf<std::unique_ptr<shs::API>, DTPless::API> m_APIs;
  shs::SortedBuf<shs::API*, DTPless::API> m_externalAPIs;
};

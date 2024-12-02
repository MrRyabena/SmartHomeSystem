#pragma once

/*
  Smart Home System Data Transmission Protocol

  The idea is taken from https://github.com/GyverLibs/GyverBus
*/

/*
  Last update: v1.0.0
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
    v2.0.0 — global changes
      - 
*/


#include <memory>


#include "shs_Process.h"
#include "shs_API.h"
#include "shs_SortedBuf.h"
#include "shs_algorithm.h"
#include "shs_ID.h"
#include "shs_DTPbus.h"
#include "shs_DTPpacket.h"


namespace shs
{
    class DTP;

    namespace DTPless
    {
        struct API;
        struct BUS;
    }
}


struct shs::DTPless::API
{
    bool operator()(const shs::API* lhs, const shs::API* rhs) const { return *lhs < *rhs; }
    bool operator()(const std::unique_ptr<shs::API>& lhs, const std::unique_ptr<shs::API>& rhs) const { return *lhs < *rhs; }

    bool operator()(const shs::API* lhs, const shs::t::shs_ID_t rhs) const { return lhs->API_ID < rhs; }
    bool operator()(const shs::t::shs_ID_t lhs, const shs::API* rhs) const { return lhs < rhs->API_ID; }

    bool operator()(const std::unique_ptr<shs::API>& lhs, const shs::t::shs_ID_t rhs) const { return lhs->API_ID < rhs; }
    bool operator()(const shs::t::shs_ID_t lhs, const std::unique_ptr<shs::API>& rhs) const { return lhs < rhs->API_ID; }
};


struct shs::DTPless::BUS
{
    bool operator()(const shs::DTPbus* lhs, const shs::DTPbus* rhs) const { return *lhs < *rhs; }
    bool operator()(const std::unique_ptr<shs::DTPbus>& lhs, const std::unique_ptr<shs::DTPbus>& rhs) const { return *lhs < *rhs; }

    bool operator()(const shs::DTPbus* lhs, const shs::t::shs_busID_t rhs) const { return lhs->busID < rhs; }
    bool operator()(const shs::t::shs_busID_t lhs, const shs::DTPbus* rhs) const { return lhs < rhs->busID; }

    bool operator()(const std::unique_ptr<shs::DTPbus>& lhs, const shs::t::shs_busID_t rhs) const { return lhs->busID < rhs; }
    bool operator()(const shs::t::shs_busID_t lhs, const std::unique_ptr<shs::DTPbus>& rhs) const { return lhs < rhs->busID; }
};


class shs::DTP : public shs::Process
{
public:

    shs::t::shs_ID_t moduleID;


    explicit DTP(const shs::t::shs_ID_t module_id) : moduleID(module_id) {}


    // shs::Process
    void start() override { for (auto& bus : m_buss) bus->start(); }
    void tick() override;
    void stop() override { for (auto& bus : m_buss) bus->stop(); }


    // BUS
    shs::t::shs_busID_t attachBus(std::unique_ptr<shs::DTPbus>&& bus)
    {

        if (bus->busID == 0 || m_buss.get(bus) != m_buss.end()) bus->busID = getUniqueBusID();
        return (*m_buss.attach(std::move(bus)))->busID;
    }

    void detachBus(const shs::t::shs_busID_t& id) { m_buss.detach(id); }
    shs::DTPbus& getBus(const shs::t::shs_busID_t& id) const { return *(m_buss.get(id)->get()); }

    shs::t::shs_busID_t getUniqueBusID() const;


    // API
    void attachAPI(std::unique_ptr<shs::API>&& api) { m_APIs.attach(std::move(api)); }
    void detachAPI(const shs::t::shs_ID_t& id) { m_APIs.detach(id); }
    shs::API& getAPI(const shs::t::shs_ID_t& id) const { return *(m_APIs.get(id)->get()); }

private:
    shs::SortedBuf<std::unique_ptr<shs::DTPbus>, DTPless::BUS> m_buss;
    shs::SortedBuf<std::unique_ptr<shs::API>, DTPless::API> m_APIs;
};

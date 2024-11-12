#pragma once


#include "shs_Process.h"
#include "shs_API.h"
#include "shs_SortedBuf.h"
#include "shs_algorithm.h"
#include "shs_ID.h"
#include "shs_DTPbus.h"
#include "shs_DTPpacket.h"

#include <memory>

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

    bool operator()(const shs::DTPbus* lhs, const shs::t::shs_ID_t rhs) const { return lhs->busID < rhs; }
    bool operator()(const shs::t::shs_ID_t lhs, const shs::DTPbus* rhs) const { return lhs < rhs->busID; }

    bool operator()(const std::unique_ptr<shs::DTPbus>& lhs, const shs::t::shs_ID_t rhs) const { return lhs->busID < rhs; }
    bool operator()(const shs::t::shs_ID_t lhs, const std::unique_ptr<shs::DTPbus>& rhs) const { return lhs < rhs->busID; }
};


class shs::DTP : public shs::Process
{
public:

    void start() override { for (auto& bus : m_buss) bus->start(); }
    void tick() override;
    void stop() override { for (auto& bus : m_buss) bus->stop(); }

    void attachBus(std::unique_ptr<shs::DTPbus>&& bus) { m_buss.attach(std::move(bus)); }
    void detachBus(const shs::t::shs_ID_t& id) { m_buss.detach(id); }
    std::unique_ptr<shs::DTPbus>& getBus(const shs::t::shs_ID_t& id) { return *m_buss.get(id); }

    void attachAPI(std::unique_ptr<shs::API>&& api) { m_APIs.attach(std::move(api)); }
    void detachAPI(const shs::t::shs_ID_t& id) { m_APIs.detach(id); }
    std::unique_ptr<shs::API>& getAPI(const shs::t::shs_ID_t& id) { return *m_APIs.get(id); }


private:
    shs::SortedBuf<std::unique_ptr<shs::DTPbus>, DTPless::BUS> m_buss;
    shs::SortedBuf<std::unique_ptr<shs::API>, DTPless::API> m_APIs;
};

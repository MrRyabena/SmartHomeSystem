#pragma once


#include "shs_API.h"
#include "shs_types.h"
#include "shs_DTPbus.h"

namespace shs
{

    namespace DTPless
    {
        struct API;
        struct BUS;
    }
}



struct shs::DTPless::API
{
    inline bool operator()(const shs::API* lhs, const shs::API* rhs) const { return *lhs < *rhs; }
    inline bool operator()(const std::unique_ptr<shs::API>& lhs, const std::unique_ptr<shs::API>& rhs) const { return *lhs < *rhs; }

    inline bool operator()(const shs::API* lhs, const shs::t::shs_ID_t rhs) const { return lhs->API_ID < rhs; }
    inline bool operator()(const shs::t::shs_ID_t lhs, const shs::API* rhs) const { return lhs < rhs->API_ID; }

    inline bool operator()(const std::unique_ptr<shs::API>& lhs, const shs::t::shs_ID_t rhs) const { return lhs->API_ID < rhs; }
    inline bool operator()(const shs::t::shs_ID_t lhs, const std::unique_ptr<shs::API>& rhs) const { return lhs < rhs->API_ID; }
};


struct shs::DTPless::BUS
{
    inline bool operator()(const shs::DTPbus* lhs, const shs::DTPbus* rhs) const { return *lhs < *rhs; }
    inline bool operator()(const std::unique_ptr<shs::DTPbus>& lhs, const std::unique_ptr<shs::DTPbus>& rhs) const { return *lhs < *rhs; }

    inline bool operator()(const shs::DTPbus* lhs, const shs::t::shs_busID_t rhs) const { return lhs->busID < rhs; }
    inline bool operator()(const shs::t::shs_busID_t lhs, const shs::DTPbus* rhs) const { return lhs < rhs->busID; }

    inline bool operator()(const std::unique_ptr<shs::DTPbus>& lhs, const shs::t::shs_busID_t rhs) const { return lhs->busID < rhs; }
    inline bool operator()(const shs::t::shs_busID_t lhs, const std::unique_ptr<shs::DTPbus>& rhs) const { return lhs < rhs->busID; }
};


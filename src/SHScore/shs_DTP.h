#pragma once


#include "shs_API.h"
#include "shs_SortedBuf.h"
#include "shs_algorithm.h"
#include "shs_DTPbus.h"
#include "shs_DTPpacket.h"

namespace shs
{
    class DTP;
    namespace DTPless
    {
        struct APIptr;
        struct APIid;
    }
}

struct shs::DTPless::APIptr { bool operator()(const shs::API* lhs, const shs::API* rhs) const { return lhs->API_ID < rhs->API_ID; } };
struct shs::DTPless::APIid
{
    bool operator()(const shs::API* lhs, const shs::t::shs_ID_t rhs) const { return lhs->API_ID < rhs; }
    bool operator()(const shs::t::shs_ID_t lhs, const shs::API* rhs) const { return lhs < rhs->API_ID; }
};


class shs::DTP : public shs::SortedBuf<shs::API*>
{
public:



private:
};

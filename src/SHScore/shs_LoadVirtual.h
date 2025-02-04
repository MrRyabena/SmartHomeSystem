#pragma once

#include <memory>

#include "shs_Load.h"
#include "shs_API.h"
#include "shs_types.h"
#include "shs_DTP.h"
#include "shs_DTPpacket.h"
#include "shs_Load_API.h"


namespace shs
{
    class LoadVirtual;
}


class shs::LoadVirtual : public shs::Load, public shs::API
{
public:
    LoadVirtual(const shs::t::shs_ID_t thisID, const shs::t::shs_ID_t virtualID, shs::DTP& dtp, const Type l_type = shs::Load::Type::UNKNOWN)
        : Load(l_type), API(thisID), m_dtp(dtp), m_virtualID(virtualID)
    {}

    ~LoadVirtual() = default;

    
    // -------------------- API --------------------
    using Commands = shs::Load_API::Commands;
    shs::DTPpacket handle(shs::ByteCollectorReadIterator<>& it) override { return shs::DTPpacket(); }

    
    // -------------------- Load --------------------
    void setup() override {}

    void on(const uint16_t value = UINT16_MAX) override;
    void off() override;


protected:
    shs::t::shs_ID_t m_virtualID;
    shs::DTP& m_dtp;
};

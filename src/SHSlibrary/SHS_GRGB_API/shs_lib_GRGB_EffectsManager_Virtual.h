#pragma once


#include <shs_API.h>
#include <shs_DTP.h>
#include <shs_DTPpacket.h>
#include <shs_ByteCollectorIterator.h>
#include <shs_types.h>

#include <shs_lib_APIids.h>
#include <shs_utils.h>

#include "shs_lib_GRGB_EffectsManager_API.h"

namespace shs
{
    class GRGB_EffectsManager_Virtual;
}

class shs::GRGB_EffectsManager_Virtual : public shs::API
{
public:
    using Commands = shs::GRGB_EffectsManager_API::Commands;

    GRGB_EffectsManager_Virtual(shs::t::shs_ID_t this_id, shs::t::shs_ID_t virtual_id, shs::DTP& dtp)
        : API(this_id.setComponentID(shs::etoi(shs::lib::APIids::GRGB_EFFECTS_MANAGER_API))), m_dtp(dtp), m_virtual_id(virtual_id.setComponentID(shs::etoi(shs::lib::APIids::GRGB_EFFECTS_MANAGER_API)))
    {}

    void setColorWheel(shs::t::shs_time_t dt, int16_t shift = 1)
    {
        shs::ByteCollector<> bc(7);
        bc.push_back(Commands::SET_COLOR_WHEEL, 1);
        bc.push_back(dt, 4);
        bc.push_back(shift, 2);

        m_sendPacket(std::move(bc));
    }

    void setBreathing(shs::t::shs_time_t dt, int16_t increment = 1,
        uint16_t start_brightness = 0, uint8_t min_brightness = 0, uint8_t max_brightness = 0xff)
    {
        shs::ByteCollector<> bc(11);
        bc.push_back(Commands::SET_BREATHING, 1);
        bc.push_back(dt, 4);
        bc.push_back(increment, 2);
        bc.push_back(start_brightness, 2);
        bc.push_back(min_brightness, 1);
        bc.push_back(max_brightness, 1);

        m_sendPacket(std::move(bc));
    }

    void resetColorWheel() { m_sendCommand(Commands::RESET_COLOR_WHEEL); }
    void resetBreathing() { m_sendCommand(Commands::RESET_BREATHING); }

    shs::DTPpacket handle(shs::ByteCollectorReadIterator<>& it) override { return {}; }

protected:
    shs::DTP& m_dtp;
    shs::t::shs_ID_t m_virtual_id;

    void m_sendCommand(Commands cmd)
    {
        shs::ByteCollector<> bc(1);
        bc.push_back(cmd, 1);

        m_sendPacket(std::move(bc));
    }

    void m_sendPacket(shs::ByteCollector<>&& bc)
    {
        shs::DTPpacket packet(API_ID, m_virtual_id, std::move(bc));
        m_dtp.sendPacket(packet);
    }
};

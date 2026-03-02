#pragma once


#include <shs_API.h>
#include <shs_DTP.h>

#include "shs_lib_GRGB_API.h"

namespace shs
{
    class GRGB_Virtual;
}


class shs::GRGB_Virtual : public shs::API
{
public:
    using Commands = GRGB_API::Commands;

    GRGB_Virtual(shs::t::shs_ID_t this_id, shs::t::shs_ID_t virtual_id, shs::DTP& dtp);
    ~GRGB_Virtual() = default;

    [[nodiscard]] shs::DTPpacket handle(shs::ByteCollectorReadIterator<>& it) override
    {
        return shs::DTPpacket();
    }

    void enable() { m_sendCommand(Commands::enable); }
    void disable() { m_sendCommand(Commands::disable); }
    void setPower(const bool power) { m_sendCommand(Commands::setPower, power); }
    void setRGB(const uint8_t r, const uint8_t g, const uint8_t b, int16_t br = -1);
    void setHSVfast(const uint8_t h, const uint8_t s, const uint8_t v) { m_sendHSV(h, s, v, true); }
    void setHSV(const uint8_t h, const uint8_t s, const uint8_t v) { m_sendHSV(h, s, v, false); }
    void setWheel(const uint16_t color, const int16_t br = -1);
    void setWheel8(const uint8_t color, const int16_t br = -1);
    void setKelvin(const uint16_t kelvin, const int16_t br = -1);
    void setKelvinFast(const uint16_t kelvin, const int16_t br = -1);
    void setHEX(const uint32_t hex, const int16_t br = -1);
    void setHEX16(const uint16_t hex, const int16_t br = -1);
    void setColor(const uint8_t color, const int16_t br = -1);
    void setBrightness(const uint8_t brightness) { m_sendCommand(Commands::setBrightness, brightness); }
    void setCRT(const uint8_t crt) { m_sendCommand(Commands::setCRT, crt); }
    void tick() { m_sendCommand(Commands::tick); }
    void fadeMode(const uint8_t mode) { m_sendCommand(Commands::fadeMode, mode); }
    void setFadePeriod(const uint32_t period);
    
private:
    shs::DTP& m_dtp;
    shs::t::shs_ID_t m_virtual_id;

    void m_sendCommand(const Commands cmd);
    void m_sendCommand(const Commands cmd, const uint8_t arg);
    void m_sendHSV(const uint8_t h, const uint8_t s, const uint8_t v, const bool fast);

    void m_send(shs::ByteCollector<>&& bc) { m_dtp.sendPacket(shs::DTPpacket(API_ID, m_virtual_id, std::move(bc))); }
};

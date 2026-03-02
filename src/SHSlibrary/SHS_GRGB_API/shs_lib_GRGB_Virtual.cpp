#include "shs_lib_GRGB_Virtual.h"

#include <shs_utils.h>
#include <shs_lib_APIids.h>

shs::GRGB_Virtual::GRGB_Virtual(shs::t::shs_ID_t this_id, shs::t::shs_ID_t virtual_id, shs::DTP& dtp)
    : shs::API(this_id), m_dtp(dtp), m_virtual_id(virtual_id.setComponentID(shs::etoi(shs::lib::APIids::GRGB_API)))
{}


void shs::GRGB_Virtual::setRGB(const uint8_t r, const uint8_t g, const uint8_t b, int16_t br)
{
    shs::ByteCollector<> bc(5 + sizeof(br));

    bc.push_back(Commands::setRGB, 1);
    bc.push_back(r, 1);
    bc.push_back(g, 1);
    bc.push_back(b, 1);
    bc.push_back(br, 2);

    m_send(std::move(bc));
}

void shs::GRGB_Virtual::setWheel(const uint16_t color, const int16_t br)
{
    shs::ByteCollector<> bc(1 + 2 + 2);
    bc.push_back(Commands::setWheel, 1);
    bc.push_back(color, 2);
    bc.push_back(br, 2);

    m_send(std::move(bc));
}

void shs::GRGB_Virtual::m_sendCommand(const Commands cmd)
{
    shs::ByteCollector<> bc(1);
    bc.push_back(cmd, 1);

    m_send(std::move(bc));
}

void shs::GRGB_Virtual::m_sendCommand(const Commands cmd, const uint8_t arg)
{
    shs::ByteCollector<> bc(2);
    bc.push_back(cmd, 1);
    bc.push_back(arg, 1);

    m_send(std::move(bc));
}

void shs::GRGB_Virtual::setWheel8(const uint8_t color, const int16_t br)
{
    shs::ByteCollector<> bc(1 + 1 + 2);
    bc.push_back(Commands::setWheel8, 1);
    bc.push_back(color, 1);
    bc.push_back(br, 2);

    m_send(std::move(bc));
}

void shs::GRGB_Virtual::setKelvin(const uint16_t kelvin, const int16_t br)
{
    shs::ByteCollector<> bc(1 + 2 + 2);
    bc.push_back(Commands::setKelvin, 1);
    bc.push_back(kelvin, 2);
    bc.push_back(br, 2);

    m_send(std::move(bc));
}

void shs::GRGB_Virtual::setKelvinFast(const uint16_t kelvin, const int16_t br)
{
    shs::ByteCollector<> bc(1 + 2 + 2);
    bc.push_back(Commands::setKelvinFast, 1);
    bc.push_back(kelvin, 2);
    bc.push_back(br, 2);

    m_send(std::move(bc));
}

void shs::GRGB_Virtual::setHEX(const uint32_t hex, const int16_t br)
{
    shs::ByteCollector<> bc(1 + 4 + 2);
    bc.push_back(Commands::setHEX, 1);
    bc.push_back(hex, 4);
    bc.push_back(br, 2);

    m_send(std::move(bc));
}

void shs::GRGB_Virtual::setHEX16(const uint16_t hex, const int16_t br)
{
    shs::ByteCollector<> bc(1 + 2 + 2);
    bc.push_back(Commands::setHEX16, 1);
    bc.push_back(hex, 2);
    bc.push_back(br, 2);

    m_send(std::move(bc));
}

void shs::GRGB_Virtual::setColor(const uint8_t color, const int16_t br)
{
    shs::ByteCollector<> bc(1 + 1 + 2);
    bc.push_back(Commands::setColor, 1);
    bc.push_back(color, 1);
    bc.push_back(br, 2);

    m_send(std::move(bc));
}


void shs::GRGB_Virtual::setFadePeriod(const uint32_t period)
{
    shs::ByteCollector<> bc(1 + 4);
    bc.push_back(Commands::setFadePeriod, 1);
    bc.push_back(period, 4);

    m_send(std::move(bc));
}

void shs::GRGB_Virtual::m_sendHSV(uint8_t h, uint8_t s, uint8_t v, bool fast)
{
    shs::ByteCollector<> bc(4);
    bc.push_back(fast ? Commands::setHSVfast : Commands::setHSV, 1);
    bc.push_back(h, 1);
    bc.push_back(s, 1);
    bc.push_back(v, 1);

    m_send(std::move(bc));
}


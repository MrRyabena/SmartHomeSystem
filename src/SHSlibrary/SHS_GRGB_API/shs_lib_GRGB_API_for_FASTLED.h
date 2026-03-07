#pragma once

/*
  Last update: v2.3.0
  Versions:
    v2.3.0 — created.
*/

#include <memory>

#include "shs_lib_GRGB_API.h"
#include <FastLED.h>

#include <shs_API.h>
#include <shs_ByteCollector.h>
#include <shs_ByteCollectorIterator.h>
#include <shs_DTPpacket.h>
#include <shs_types.h>
#include <shs_Process.h>

#include <shs_lib_APIids.h>
#include <shs_utils.h>


namespace shs
{
    class GRGB_API;
    class GRGB_API_for_FASTLED;
};


class shs::GRGB_API_for_FASTLED : public shs::API, public shs::Process
{
public:
    GRGB_API_for_FASTLED(CFastLED& fastLED, shs::t::shs_ID_t ID) : API(ID.setComponentID(shs::etoi(shs::lib::APIids::GRGB_API))), m_fastLED(fastLED)
    {
        m_grgb.attach([this]() { this->m_update_FastLED(); });
    }

    ~GRGB_API_for_FASTLED() = default;

    using Commands = shs::GRGB_API::Commands;

    [[nodiscard]] shs::DTPpacket handle(shs::ByteCollectorReadIterator<>& it) override
    {
        it.set_position(shs::DTPpacket::get_dataBeg(it));

        switch (it.read())
        {
            case Commands::enable:   m_grgb.enable();  break;
            case Commands::disable:  m_grgb.disable(); break;
            case Commands::setPower: m_grgb.setPower(it.read()); break;
            [[likely]] case Commands::setRGB: m_grgb.setRGB(it.read(), it.read(), it.read(), it.read()); break;
            [[likely]] case Commands::setBrightness: { const uint8_t br = it.read(); m_grgb.setBrightness(br); m_fastLED.setBrightness(br); } break;
            case Commands::fadeMode: m_grgb.fadeMode(it.read()); break;
            case Commands::setFadePeriod: { uint32_t t{}; it.get(t, 4); m_grgb.setFadePeriod(t); } break;
            case Commands::setWheel8: m_grgb.setWheel8(it.read(), it.read()); break;

            default: return shs::DTPpacket(); break;
        }
        m_update_FastLED();

        return shs::DTPpacket();
    }

    GRGB& getGRGB() { return m_grgb; }

    void start() override {}
    void stop() override {}
    void tick() override { m_grgb.tick();}


protected:
    GRGB m_grgb;
    CFastLED& m_fastLED;

    void m_update_FastLED()
    {
        m_fastLED.showColor(CRGB(m_grgb.R, m_grgb.G, m_grgb.B));
    }
};

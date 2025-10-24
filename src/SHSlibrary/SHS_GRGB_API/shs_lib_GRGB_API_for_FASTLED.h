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


namespace shs
{
    class GRGB_API;
};


class shs::GRGB_API_for_FASTLED : public shs::API
{
public:
    GRGB_API_for_FASTLED(FastLED& fastLED, const shs::t::shs_ID_t ID) : API(ID), m_fastLED(fastLED) {}

    ~GRGB_API_for_FASTLED() = default;

    using Commands = shs::GRGB_API::Commands;

    [[nodiscard]] shs::DTPpacket handle(shs::ByteCollectorReadIterator<>& it) override
    {
        it.set_position(shs::DTPpacket::get_dataBeg(it));

        switch (it.read())
        {
            case enable:   m_grgb.enable();  break;
            case disable:  m_grgb.disable(); break;
            case setPower: m_grgb.setPower(it.read()); break;
            [[likely]] case setRGB: m_grgb.setRGB(it.read(), it.read(), it.read(), it.read()); break;
            [[likely]] case setBrightness: { const uint8_t br = it.read(); m_grgb.setBrightness(br); m_fastLED.setBrightness(br); } break;
            case fadeMode: m_grgb.fadeMode(it.read()); break;
            case setFadePeriod: { uint32_t t{}; it.get(t, 4); m_grgb.setFadePeriod(t); } break;
            case setWheel8: m_grgb.setWheel8(it.read(), it.read()); break;

            default: return shs::DTPpacket(); break;
        }
        m_update_FastLED();

        return shs::DTPpacket();
    }


protected:
    GRGB m_grgb;
    FastLED& m_fastLED;

    m_update_FastLED()
    {
        m_fastLED.showColor(CRGB(m_grgb.R, m_grgb.G, m_grgb.B));
    }
};

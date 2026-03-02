#pragma once

/*
  Last update: v2.1.0
  Versions:
    v2.0.0 — created.
    v2.1.0 — fixed bugs, tested.
*/

#include <memory>

#include <GRGB.h>

#include <shs_API.h>
#include <shs_ByteCollector.h>
#include <shs_ByteCollectorIterator.h>
#include <shs_DTPpacket.h>
#include <shs_types.h>
#include <shs_utils.h>
#include <shs_lib_APIids.h>
namespace shs
{
    class GRGB_API;
};


class shs::GRGB_API : public shs::API
{
public:
    GRGB_API(GRGB& grgb, shs::t::shs_ID_t ID) : shs::API(ID.setComponentID(shs::etoi(shs::lib::APIids::GRGB_API))), m_grgb(grgb) {}

    ~GRGB_API() = default;

    enum Commands : uint8_t
    {
        enable,
        disable,
        setPower,
        setRGB,
        setHSVfast,
        setHSV,
        setWheel,
        setWheel8,
        setKelvin,
        setKelvinFast,
        setHEX,
        setHEX16,
        setColor,
        setBrightness,
        setCRT,
        tick,
        fadeMode,
        setFadePeriod
    };


    [[nodiscard]] shs::DTPpacket handle(shs::ByteCollectorReadIterator<>& it) override
    {
        it.set_position(shs::DTPpacket::get_dataBeg(it));

        switch (it.read())
        {
            case enable:   m_grgb.enable();  break;
            case disable:  m_grgb.disable(); break;
            case setPower: m_grgb.setPower(it.read()); break;
            [[likely]] case setRGB: m_grgb.setRGB(it.read(), it.read(), it.read(), it.read()); break;
            [[likely]] case setBrightness: m_grgb.setBrightness(it.read()); break;
            case fadeMode: m_grgb.fadeMode(it.read()); break;
            case setFadePeriod: { uint32_t t{}; it.get(t, 4); m_grgb.setFadePeriod(t); } break;
            case setWheel8: m_grgb.setWheel8(it.read(), it.read()); break;
            case setHSVfast: m_grgb.setHSVfast(it.read(), it.read(), it.read()); break;
            case setHSV: m_grgb.setHSV(it.read(), it.read(), it.read()); break;
            case setWheel: { uint16_t c{}; it.get(c, 2); m_grgb.setWheel(c); } break;
            case setKelvin: { uint16_t k{}; it.get(k, 2); m_grgb.setKelvin(k); } break;
            case setKelvinFast: { uint16_t k{}; it.get(k, 2); m_grgb.setKelvinFast(k); } break;
            case setHEX: { uint32_t h{}; it.get(h, 4); m_grgb.setHEX(h); } break;
            case setHEX16: { uint16_t h{}; it.get(h, 2); m_grgb.setHEX16(h); } break;
            case setColor: m_grgb.setColor(it.read()); break;
            case setCRT: m_grgb.setCRT(it.read()); break;
            case tick: m_grgb.tick(); break;

            default: break;
        }

        return shs::DTPpacket();
    }


private:
    GRGB& m_grgb;
};

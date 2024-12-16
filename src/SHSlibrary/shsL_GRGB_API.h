#pragma once

#include <memory>

#include <GRGB.h>

#include <shs_API.h>
#include <shs_ByteCollector.h>
#include <shs_ByteCollectorIterator.h>
#include <shs_DTPpacket.h>
#include <shs_types.h>


namespace shs
{
    class GRGB_API;
};


class shs::GRGB_API : public shs::API
{
public:
    GRGB_API(GRGB& grgb, const shs::t::shs_ID_t ID) : shs::API(ID), m_grgb(grgb) {}

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


    void handle(shs::ByteCollectorReadIterator<>& it) override
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

            default: break;
        }

        return std::move(shs::DTPpacket(true));
    }


private:
    GRGB& m_grgb;
};

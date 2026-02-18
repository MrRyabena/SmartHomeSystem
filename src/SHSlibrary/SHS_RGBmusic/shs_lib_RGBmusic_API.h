#pragma once

#include <memory>

#include "shs_lib_RGBmusic.h"

#include <shs_API.h>
#include <shs_ByteCollector.h>
#include <shs_ByteCollectorIterator.h>
#include <shs_DTPpacket.h>


namespace shs
{
    class RGBmusic_API;
}


class shs::RGBmusic_API : public shs::API
{
public:
    explicit RGBmusic_API(shs::RGBmusic& rgb_music, const shs::t::shs_ID_t id)
        : API(id), m_rgb_music(rgb_music)
    {}


    enum Commands : uint8_t
    {
        enable,
        disable,
        setEffect,
        getEffect,
        effect,
        setMinBright,
        setDt,
        setWindow,
        setTrsh,
        setVolDt,
        setVolK,
        setVolMin,
        setVolMax,
        setAmpliDt,
        setAmpliK,
        setPulseMax,
        setPulseMin,
        setPulseTimeout,
    };


    [[nodiscard]] shs::DTPpacket handle(shs::ByteCollectorReadIterator<>& it) override
    {
        it.set_position(shs::DTPpacket::get_dataBeg(it));

        switch (it.read())
        {
            case enable: m_rgb_music.start(); break;
            case disable: m_rgb_music.stop(); break;
            [[likely]] case setEffect: m_rgb_music.setEffect(static_cast<shs::RGBmusic::Effects>(it.read())); break;

            case getEffect:
                {
                    shs::ByteCollector<> bc(2);
                    bc.push_back(Commands::effect, 1);
                    bc.push_back(m_rgb_music.getEffect(), 1);

                    return shs::DTPpacket(API_ID, shs::DTPpacket::get_senderID(it), bc);
                }
                break;
            case setDt: m_rgb_music.analyzer.setDt((it.read() << 8) | it.read()); break;
            case setWindow: m_rgb_music.analyzer.setWindow(it.read()); break;
            case setTrsh: m_rgb_music.analyzer.setTrsh((it.read() << 8) | it.read()); break;
            case setVolDt: m_rgb_music.analyzer.setVolDt(it.read()); break;
            case setVolK: m_rgb_music.analyzer.setVolK(it.read()); break;
            case setVolMin: m_rgb_music.analyzer.setVolMin(it.read()); break;
            case setVolMax: m_rgb_music.analyzer.setVolMax(it.read()); break;
            case setAmpliDt: m_rgb_music.analyzer.setAmpliDt(it.read()); break;
            case setPulseMax: m_rgb_music.analyzer.setPulseMax(it.read()); break;
            case setPulseMin: m_rgb_music.analyzer.setPulseMin(it.read()); break;
            case setPulseTimeout: m_rgb_music.analyzer.setPulseTimeout((it.read() << 8) | it.read()); break;
            case setMinBright: m_rgb_music.setMinBright(it.read()); break;
            default: break;
        }
        return {};
    }

private:
    shs::RGBmusic& m_rgb_music;
};

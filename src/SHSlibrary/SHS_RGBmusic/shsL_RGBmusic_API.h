#pragma once

#include <memory>

#include <shsL_RGBmusic.h>

#include <shs_API.h>
#include <shs_ByteCollector.h>
#include <shs_ByteCollectorIterator.h>
#include <shs_DTPpacket.h>


namespace shs
{
    class RGBmusic_API;
}


class shs::RGBmusic_API
{
public:
    explicit RGBmusic_API(shs::RGBmusic& rgb_music, const shs::t::shs_ID_t id)
        : API_ID(id), m_rgb_music(rgb_music)
    {}

    API(API&& other) : API_ID(other.API_ID) { other.API_ID = {}; }

    ~API() = default;


    enum Commands : uint8_t
    {
        enable,
        disable,
        setEffect,
        getEffect,
        effect
    };


    [[nodiscard]] shs::DTPpacket handle(shs::ByteCollectorReadIterator<>& it) override
    {
        it.set_position(shs::DTPpacket::get_dataBeg(it));

        switch (it.read())
        {
            case enable: m_rgb_music.start(); break;
            case disable: m_rgb_music.stop(); break;
            [[likely]] case setEffect: m_rgb_music.setEffect(it.read()); break;

            case getEffect:
                {
                    shs::ByteCollector<> bc(2);
                    bc.push_back(Commands::effect);
                    bc.push_back(m_rgb_music.effect);

                    return std::move(shs::DTPpacket(API_ID, shs::DTPpacket::get_senderID(it), bc));
                }
                break;

            default: break;
        }
        return std::move(shs::DTPpacket(true));
    }

private:
    shs::RGBmusic& m_rgb_music;
};

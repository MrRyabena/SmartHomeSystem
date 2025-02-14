#pragma once

#include <memory>

#include "shsD_SmartSpot.h"

#include <shs_API.h>
#include <shs_ByteCollector.h>
#include <shs_ByteCollectorIterator.h>
#include <shs_DTPpacket.h>


namespace shs
{
    class SmartSpot_API;
}


class shs::SmartSpot_API : public shs::API
{
public:
    explicit SmartSpot_API(shs::SmartSpot& spot, const shs::t::shs_ID_t id) : API(id), m_spot(spot) {}

    enum Commands : uint8_t
    {
        stop,
        start,
        getFanPower, FanPower
        getTempInt, TempInt
    };

    [[nodiscard]] shs::DTPpacket handler(shs::ByteCollectorReadIterator<>& it) override
    {
        it.set_position(shs::DTPpacket::get_dataBeg(it));

        switch (it.read())
        {
            case stop: m_spot.stop(); break;
            case start: m_stop.start(); break;
            case getFanPower:
                {
                    shs::ByteCollector<> bc(2);

                    bc.push_back(FanPower, 1);
                    bc.push_back(m_spot.getFanPower(), 1);

                    return std::move(shs::DTPpacket(API_ID, shs::DTPpacket::get_senderID(it), bc));
                }
                break;

            case getTempInt:
                {
                    shs::ByteCollector<> bc(3);

                    bc.push_back(TempInt, 1);
                    bc.push_back(m_spot.getTempInt(), 2);

                    return std::move(shs::DTPpacket(API_ID, shs::DTPpacket::get_senderID(it), bc));
                }
                break;

            default: break;
        }

        return std::move(shs::DTPpacket(true));
    }

private:
    shs::SmartSpot& m_spot;
};

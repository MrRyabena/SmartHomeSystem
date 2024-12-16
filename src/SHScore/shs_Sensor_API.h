#pragma once

#include <memory>

#include "shs_API.h"
#include "shs_Sensor.h"
#include "shs_types.h"
#include "shs_DTPpacket.h"
#include "shs_ByteCollector.h"
#include "shs_ByteCollectorIterator.h"


namespace shs
{
    class Sensor_API;
}


class shs::Sensor_API : public shs::API
{
public:
    explicit Sensor_API(shs::Sensor& sensor, const shs::t::shs_ID_t id) : API(id), m_sensor(sensor) {}

    enum Commands : uint8_t
    {
        getType, Type,

        getValueI, ValueI,
        getValueF, ValueF,
        getValueD, ValueD,

        getAverageI, AverageI,
        getAverageF, AverageF,
        getAverageD, AverageD
    };

    [[nodiscard]] shs::DTPpacket handle(shs::ByteCollectorReadIterator<>& it) override
    {
        it.set_position(shs::DTPpacket::get_dataBeg(it));

        shs::ByteCollector<> bc(5);

        switch (it.read())
        {
            [[unlikely]]
            case getType:
                {
                    bc.push_back(Commands::Type, 1);
                    bc.push_back(m_sensor.type, 1);
                }
                break;

                [[likely]]
            case getValueI:
                {
                    bc.push_back(ValueI, 1);
                    bc.push_back(m_sensor.getValueI(), 2);
                }
                break;

                [[likely]]
            case getValueF:
                {
                    bc.push_back(ValueF, 1);
                    bc.push_back(m_sensor.getValueF());
                }
                break;

                [[unlikely]]
            case getValueD:
                {
                    bc.push_back(ValueD, 1);
                    bc.push_back(m_sensor.getValueD());

                }
                break;

                [[likely]]
            case getAverageI:
                {
                    bc.push_back(AverageI, 1);
                    bc.push_back(m_sensor.getAverageI(), 2);
                }
                break;

                [[likely]]
            case getAverageF:
                {
                    bc.push_back(AverageF, 1);
                    bc.push_back(m_sensor.getAverageF());
                }
                break;

                [[unlikely]]
            case getAverageD:
                {
                    bc.push_back(AverageD, 1);
                    bc.push_back(m_sensor.getAverageD(), 2);
                }
                break;

            default:
                return std::move(shs::DTPpacket(true));
                break;
        }

        return std::move(shs::DTPpacket(API_ID, shs::DTPpacket::get_senderID(it), std::move(bc)));

    }

private:
    shs::Sensor& m_sensor;
};

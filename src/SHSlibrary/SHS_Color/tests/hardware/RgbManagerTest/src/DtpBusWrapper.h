#pragma once

#include <shs_DTPbus.h>
#include <shs_DTPbusPolicy.h>


namespace shs::lib::Color::tests
{
    class DtpBusWrapper : public shs::DTPbus
    {
    public:
        explicit DtpBusWrapper(const shs::t::shs_busID_t busID, shs::API* handler = nullptr)
            : shs::DTPbus(busID, shs::DTPbusPolicy::STATIC_BUS, handler)
        {}

        bool isActive() const override { return true; }
        void setActive(const bool active) override {}

        void start() override {}
        void tick() override {}
        void stop() override {}

        ReceiveStatus checkBus() override { return ReceiveStatus::no_data; }

        uint8_t sendPacket(const shs::DTPpacket& packet) override
        {
            return sendRAW(const_cast<shs::ByteCollector<>&>(packet.bc));
        }

        uint8_t sendRAW(shs::ByteCollector<>& bc) override
        {
            if (m_context.handler)
            {
                auto it = bc.getReadIt();
                m_context.handler->handle(it);
                return bc.size();
            }
            return 0;
        }

        uint8_t sendRAW(const uint8_t* data, const uint8_t size) override
        {
            return 0;
        }

        uint8_t sendRAW(shs::ByteCollectorReadIterator<>& it) override
        {
            return 0;
        }

    };
}

#pragma once


#include <initializer_list>
#include <functional>

#include "shs_SortedBuf.h"
#include "shs_Process.h"
#include "shs_types.h"
#include "shs_API"
#include "shs_DTP.h"
#include "shs_DTPpacket.h"
#include "shs_ByteCollector.h"
#include "shs_ByteCollectorIterator.h"



namespace shs
{
    class EventTracker;
};


class shs::EventTracker : public shs::Process, public shs::API
{
public:

    Event(shs::DTP& dtp, const shs::t::shs_ID_t apiID, std::initializer_list<shs::t::shs_ID_t> listenerIDs = {}) noexcept
        : API(id), m_dtp(dtp), m_listenerIDs(listenerIDs)
    {}

    virtual ~Event() noexcept = default;


    void attachListeners(std::initializer_list<shs::t::shs_ID_t> listenerIDs) { for (const auto& id : listenerIDs) m_listeners.attach(id); }
    void detachListeners(std::initializer_list<shs::t::shs_ID_t> listenerIDs) { for (const auto& id : listenerIDs) m_listeners.detach(id); }


    // shs::API
    enum Commands : uint8_t { NOCOMMAND, ERROR, ATTACH_LISTENER, DETACH_LISTENER };

    shs::DTPpacket handle(shs::ByteCollectorReadIterator<>& it) override
    {
        it.set_position(shs::DTPpacket::get_dataBeg(it));

        switch (it.read())
        {
            case ATTACH_LISTENER:
                {
                    shs::t::shs_ID_t id{};

                    it.get(id);
                    attachListeners(id);
                }
                break;

            case DETACH_LISTENER:
                {
                    shs::t::shs_ID_t id{};

                    it.get(id);
                    detachListeners(id);
                }
                break;

            default: break;
        }

        return std::move(shs::DTPpacket(true));
    }


    // shs::Process
    void start() override {}

    void tick() override
    {
        if (m_checkEvent())
        {
            auto data = m_getEventData(m_observed);

            for (const auto& id : m_listenerIDs) m_dtp.sendPacket(shs::DTPpacket(API_ID, id, data));
        }
    }

    void stop() override {}


protected:
    [[nodiscard]] virtual bool m_checkEvent() = 0;
    [[nodiscard]] virtual shs::ByteCollector<> m_getEventData() = 0;

private:
    shs::DTP& m_dtp;
    shs::SortedBuf<shs::t::shs_ID_t> m_listenerIDs;
};

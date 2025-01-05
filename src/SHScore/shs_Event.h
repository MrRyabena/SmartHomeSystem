#pragma once


#include <initializer_list>

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
    template <class>
    class Event;
};


template <class TObserved>
class shs::Event : public shs::Process, public shs::API
{
public:

    using EventPtr = bool (TObserved::*)();
    using EventDataPtr = shs::ByteCollector<>(TObserved::*)();

    Event(TObserved& observed, shs::DTP& dtp, EventPtr event_ptr, EventDataPtr eventData_ptr, std::initializer_list<shs::t::shs_ID_t> listenerIDs)
        : m_observed(observed), m_dtp(dtp), m_event_ptr(event_ptr), m_eventData_ptr(eventData_ptr), m_listenerIDs(listenerIDs)
    {}

    ~Event() = default;


    void attachListeners(std::initializer_list<shs::t::shs_ID_t> listenerIDs) { for (const auto& id : listenerIDs) m_listeners.attach(id); }
    void detachListeners(std::initializer_list<shs::t::shs_ID_t> listenerIDs) { for (const auto& id : listenerIDs) m_listeners.detach(is); }

    // shs::API
    shs::DTPpacket handle(shs::ByteCollectorReadIterator<>& it) override;


    // shs::Process
    void start() override {}

    void tick() override
    {
        if (m_observed.*m_event_ptr())
            for (const auto& id : m_listenerIDs)
                m_dtp.sendPacket(shs::DTPpacket(API_ID, id, std::move(m_observed.*m_eventData_ptr())));
    }

    void stop() override {}


protected:
    TObserved& m_observed;
    shs::DTP& m_dtp;
    EventPtr m_event_ptr;
    EventDataPtr m_eventData_ptr;
    shs::SortedBuf<shs::t::shs_ID_t> m_listenerIDs;
};

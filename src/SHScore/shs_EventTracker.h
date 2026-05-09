#pragma once

/*
  Last update: v2.0.0
  Versions:
    v2.0.0 — created.
      - It is not debugged, has bugs.
      - Support and development is expected in the following versions.
    v2.3.0 — fixed bugs, updated docs.
*/


#include <initializer_list>
#include <functional>

#include "shs_SortedBuf.h"
#include "shs_Process.h"
#include "shs_types.h"
#include "shs_APIids.h"
#include "shs_API.h"
#include "shs_DTP.h"
#include "shs_DTPpacket.h"
#include "shs_ByteCollector.h"
#include "shs_ByteCollectorIterator.h"



namespace shs
{
    class EventTracker;
};


/**
 * @brief Base class for event-driven APIs that notify listeners when an event occurs.
 */
class shs::EventTracker : public shs::Process, public shs::API
{
public:
    /**
     * @brief Creates an event tracker with an initial listener list.
     */
    EventTracker(shs::DTP& dtp, shs::t::shs_ID_t apiID, std::initializer_list<shs::t::shs_ID_t> listenerIDs = {}) noexcept
        : API(apiID.setComponentID(shs::constants::APIids::EventTracker)), m_dtp(dtp), m_listenerIDs(listenerIDs)
    {}

    /**
     * @brief Destroys the event tracker.
     */
    virtual ~EventTracker() noexcept = default;


    /**
     * @brief Adds listeners that should receive future events.
     */
    void attachListeners(std::initializer_list<shs::t::shs_ID_t> listenerIDs) { for (const auto& id : listenerIDs) m_listenerIDs.attach(id); }

    /**
     * @brief Removes listeners from the notification list.
     */
    void detachListeners(std::initializer_list<shs::t::shs_ID_t> listenerIDs) { for (const auto& id : listenerIDs) m_listenerIDs.detach(id); }


    // shs::API
    enum Commands : uint8_t { NOCOMMAND, ERROR, ATTACH_LISTENER, DETACH_LISTENER };

    /**
     * @brief Handles listener management commands.
     */
    shs::DTPpacket handle(shs::ByteCollectorReadIterator<>& it) override
    {
        it.set_position(shs::DTPpacket::get_dataBeg(it));

        switch (it.read())
        {
            case ATTACH_LISTENER:
                {
                    shs::t::shs_ID_t id{};

                    it.get(id);
                    attachListeners({id});
                }
                break;

            case DETACH_LISTENER:
                {
                    shs::t::shs_ID_t id{};

                    it.get(id);
                    detachListeners({id});
                }
                break;

            default: break;
        }

        return shs::DTPpacket();
    }


    // shs::Process
    /**
     * @brief Starts event polling.
     */
    void start() override {}

    /**
     * @brief Checks the event and sends it to all listeners when triggered.
     */
    void tick() override
    {
        if (m_checkEvent())
        {
            auto data = m_getEventData();

            for (const auto& id : m_listenerIDs) m_dtp.sendPacket(shs::DTPpacket(API_ID, id, data));
        }
    }

    /**
     * @brief Stops event polling.
     */
    void stop() override {}


protected:
    /**
     * @brief Reports whether the tracked event has occurred.
     */
    [[nodiscard]] virtual bool m_checkEvent() = 0;

    /**
     * @brief Builds payload data for a triggered event.
     */
    [[nodiscard]] virtual shs::ByteCollector<> m_getEventData() = 0;

private:
    shs::DTP& m_dtp;
    shs::SortedBuf<shs::t::shs_ID_t> m_listenerIDs;
};

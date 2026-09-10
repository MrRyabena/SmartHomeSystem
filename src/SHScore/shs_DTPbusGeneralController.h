#pragma once

#include "shs_settings_private.h"

#ifndef SHS_SF_AVR

#include <memory>

#include "shs_DTPbus.h"
#include "shs_DTPbusStatus.h"
#include "shs_Process.h"
#include "shs_ProgramTimer.h"
#include "shs_types.h"

namespace shs
{
    class DTPbusGeneralController;
}



class shs::DTPbusGeneralController
{
public:
    static constexpr auto DEFAULT_REQUEST_TIMEOUT = 30'000;   // ms
    static constexpr auto DEFAULT_OFFLINE_TIMEOUT = 180'000;  // ms
    static constexpr auto DEFAULT_UNUSED_TIMEOUT = 600'000;   // ms, 10 minutes

    /**
     * @brief Creates a new DTP bus controller.
     * @param bus Weak pointer to the bus instance to control.
     * @param policy Policy to use for handling connection issues.
     * @param offline_timeout Timeout for considering a bus offline.
     * @param request_timeout Timeout for waiting for a response from the bus.
     * @param unused_timeout Timeout for considering a bus unused.
     */
    explicit DTPbusGeneralController(shs::t::shs_time_t request_timeout = DEFAULT_REQUEST_TIMEOUT,
        shs::t::shs_time_t offline_timeout = DEFAULT_OFFLINE_TIMEOUT,
        shs::t::shs_time_t unused_timeout = DEFAULT_UNUSED_TIMEOUT
    );

    void setRequestTimeout(shs::t::shs_time_t timeout) noexcept { m_request_timer.setTimeout(timeout); }
    void setOfflineTimeout(shs::t::shs_time_t timeout) noexcept { m_offline_timeout = timeout; }
    void setUnusedTimeout(shs::t::shs_time_t timeout) noexcept { m_unused_timeout = timeout; }

    shs::t::shs_time_t getRequestTimeout() const noexcept { return m_request_timer.getTimeout(); }
    shs::t::shs_time_t getOfflineTimeout() const noexcept { return m_offline_timeout; }
    shs::t::shs_time_t getUnusedTimeout() const noexcept { return m_unused_timeout; }

    void controlBus(std::shared_ptr<shs::DTPbus> bus);

    /**
     * @brief Checks the status of a DTP bus and applies the appropriate policy.
     * @param bus Shared pointer to the bus instance to check.
     * @param policy Policy to use for handling connection issues.
     * @param offline_timeout Timeout for considering a bus offline.
     * @param request_timeout Timeout for waiting for a response from the bus.
     * @param unused_timeout Timeout for considering a bus unused.
     */
    static void s_controlBus(std::shared_ptr<shs::DTPbus> bus,
        shs::t::shs_time_t offline_timeout = DEFAULT_OFFLINE_TIMEOUT,
        shs::t::shs_time_t request_timeout = DEFAULT_REQUEST_TIMEOUT,
        shs::t::shs_time_t unused_timeout = DEFAULT_UNUSED_TIMEOUT,
        shs::DTPbusPolicy policy = shs::DTPbusPolicy::UNKNOWN_POLICY
    );

protected:
    shs::ProgramTimer m_request_timer;
    shs::t::shs_time_t m_offline_timeout;
    shs::t::shs_time_t m_unused_timeout;

    static shs::DTPbusPolicy m_getPolicy(std::shared_ptr<shs::DTPbus> bus, shs::DTPbusPolicy policy) noexcept;
};


#endif // #ifndef SHS_SF_AVR

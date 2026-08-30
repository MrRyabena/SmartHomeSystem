#pragma once

#include <memory>

#include "shs_DTPbus.h"
#include "shs_DTPbusStatus.h"
#include "shs_Process.h"
#include "shs_ProgramTimer.h"
#include "shs_types.h"

namespace shs
{
    class DTPbusController;
}



class shs::DTPbusController : public shs::Process
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
    explicit DTPbusController(std::weak_ptr<shs::DTPbus> bus,
        shs::t::shs_time_t request_timeout = DEFAULT_REQUEST_TIMEOUT,
        shs::t::shs_time_t offline_timeout = DEFAULT_OFFLINE_TIMEOUT,
        shs::t::shs_time_t unused_timeout = DEFAULT_UNUSED_TIMEOUT,
        shs::DTPbusPolicy policy = shs::DTPbusPolicy::UNKNOWN_POLICY
    );

    bool isActive() const noexcept { return !m_bus.expired(); }

    void setPolicy(shs::DTPbusPolicy policy) noexcept { m_policy = policy; }
    void setRequestTimeout(shs::t::shs_time_t timeout) noexcept { m_request_timer.setTimeout(timeout); }
    void setOfflineTimeout(shs::t::shs_time_t timeout) noexcept { m_offline_timeout = timeout; }
    void setUnusedTimeout(shs::t::shs_time_t timeout) noexcept { m_unused_timeout = timeout; }

    shs::DTPbusPolicy getPolicy() const noexcept { return m_getPolicy(m_bus.lock(), m_policy); }
    shs::t::shs_time_t getRequestTimeout() const noexcept { return m_request_timer.getTimeout(); }
    shs::t::shs_time_t getOfflineTimeout() const noexcept { return m_offline_timeout; }
    shs::t::shs_time_t getUnusedTimeout() const noexcept { return m_unused_timeout; }

    void start() override;
    void tick() override;
    void stop() override;

    /**
     * @brief Checks the status of a DTP bus and applies the appropriate policy.
     * @param bus Shared pointer to the bus instance to check.
     * @param policy Policy to use for handling connection issues.
     * @param offline_timeout Timeout for considering a bus offline.
     * @param request_timeout Timeout for waiting for a response from the bus.
     * @param unused_timeout Timeout for considering a bus unused.
     */
    static void controlBus(std::shared_ptr<shs::DTPbus> bus,
        shs::t::shs_time_t offline_timeout = DEFAULT_OFFLINE_TIMEOUT,
        shs::t::shs_time_t request_timeout = DEFAULT_REQUEST_TIMEOUT,
        shs::t::shs_time_t unused_timeout = DEFAULT_UNUSED_TIMEOUT,
        shs::DTPbusPolicy policy = shs::DTPbusPolicy::UNKNOWN_POLICY
    );

protected:
    std::weak_ptr<shs::DTPbus> m_bus;
    shs::ProgramTimer m_request_timer;
    shs::t::shs_time_t m_offline_timeout;
    shs::t::shs_time_t m_unused_timeout;
    shs::DTPbusPolicy m_policy;

    static shs::DTPbusPolicy m_getPolicy(std::shared_ptr<shs::DTPbus> bus, shs::DTPbusPolicy policy) noexcept;
};

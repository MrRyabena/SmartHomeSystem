#pragma once

#include <stdint.h>

#include <shs_Process.h>
#include <shs_ProgramTimer.h>
#include <shs_types.h>

#include "shs_lib_Color_VFilter.h"

namespace shs::lib::Color
{
    class BrightSmoothFilter;
}


class shs::lib::Color::BrightSmoothFilter : public VFilter
{
public:
    BrightSmoothFilter(const shs::t::shs_time_t step_timeout, const uint8_t target_brightness = 0, const uint8_t step = 1);

    /**
     * @brief Apply the filter to the given value.
     * @param value The value to apply the filter to.
     * @return true if the value was changed, false otherwise.
     */
    bool apply(uint8_t& value) override;

    void enable(const shs::t::shs_time_t step_timeout) { m_enabled = true; m_step_timer.reset(); }
    void disable() { m_enabled = false; }
    [[nodiscard]] bool isEnabled() const { return m_enabled; }

    void setStepTimeout(const shs::t::shs_time_t step_timeout) noexcept { m_step_timer.setTimeout(step_timeout); }
    void setTarget(const uint8_t target_brightness) noexcept { m_target_brightness = target_brightness; }
    void setTarget(const uint8_t target_brightness, const shs::t::shs_time_t step_timeout) { m_target_brightness = target_brightness; m_step_timer.setTimeout(step_timeout); }
    void setStep(const uint8_t step) noexcept { m_step = step; }
    [[nodiscard]] uint8_t getStep() const noexcept { return m_step; }

    /**
     * @return the time needed for changing value from 0 to the 255.
     */
    [[nodiscard]] shs::t::shs_time_t calculatePeriod() const noexcept { return calculatePeriod(0, 255); }

    /**
     * @brief Get the period of changing value to the internal target.
     * @param current_brightness The current brightness.
     * @return The period of changing value to the target.
     */
    [[nodiscard]] shs::t::shs_time_t calculatePeriod(const uint8_t current_brightness) const noexcept { return calculatePeriod(current_brightness, m_target_brightness); }

    /**
     * @brief Get the period of changing value from the current brightness to the target brightness.
     * @param current_brightness The current brightness.
     * @param target_brightness The target brightness.
     * @return The period of changing value from the current brightness to the target brightness.
     */
    [[nodiscard]] shs::t::shs_time_t calculatePeriod(const uint8_t current_brightness, const uint8_t target_brightness) const noexcept { return calculatePeriod(current_brightness, target_brightness, m_step_timer.getTimeout()); }

    /**
     * @brief Get the step timeout.
     * @return The step timeout.
     */
    [[nodiscard]] shs::t::shs_time_t getStepTimeout() const noexcept { return m_step_timer.getTimeout(); }

    /**
     * @brief Get the target brightness.
     * @return The target brightness.
     */
    [[nodiscard]] uint8_t getTarget() const noexcept { return m_target_brightness; }

    /**
     * @brief Get the period of changing value from the current brightness to the target brightness.
     * @param current_brightness The current brightness.
     * @param target_brightness The target brightness.
     * @param step_timeout The timeout for each step.
     * @param step_size The size of each step.
     * @return The period of changing value from the current brightness to the target brightness.
     */
    [[nodiscard]] static shs::t::shs_time_t calculatePeriod(const uint8_t current_brightness,
        const uint8_t target_brightness, const shs::t::shs_time_t step_timeout, const uint8_t step_size = 1) noexcept;

    /**
     * @brief Get the step timeout for a given period.
     * @param current_brightness The current brightness.
     * @param target_brightness The target brightness.
     * @param period The period.
     * @param step_size The size of each step.
     * @return The step timeout.
     */
    [[nodiscard]] static shs::t::shs_time_t calculateStepTimeout(const uint8_t current_brightness,
        const uint8_t target_brightness, const shs::t::shs_time_t period, const uint8_t step_size = 1) noexcept;

private:
    shs::ProgramTimer m_step_timer;
    uint8_t m_target_brightness;
    uint8_t m_step;
    bool m_enabled;
};

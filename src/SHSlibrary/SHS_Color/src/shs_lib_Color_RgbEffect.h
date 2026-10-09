#pragma once

#include <optional>
#include <utility>

#include <shs_ProgramTimer.h>
#include <shs_types.h>
#include <shs_Process.h>

#include "shs_lib_Color_RGB888.h"

namespace shs::lib::Color
{
    class RgbEffect;
}


class shs::lib::Color::RgbEffect
{
public:
    explicit RgbEffect(const shs::t::shs_time_t dt)
        : m_timer(dt)
    {}

    virtual ~RgbEffect() = default;

    using result_t = std::pair<std::optional<RGB888>, std::optional<uint8_t>>;

    /**
     * @brief Updates the effect and returns the new color and brightness.
     * @return A pair containing the new RGB888 color and the new brightness value (0-255).
     *         If the color or brightness has not changed, the corresponding value in the pair will be std::nullopt.
     * @note This method should be called frequently in a loop to update the effect over time.
     *       The effect will automatically manage its timing based on the specified dt.
     */
    [[nodiscard]] virtual result_t update() = 0;

    virtual void setPeriod(const shs::t::shs_time_t period) noexcept = 0;
    virtual shs::t::shs_time_t getPeriod() const noexcept = 0;

protected:
    shs::ProgramTimer m_timer;
};

#pragma once

#include <memory>
#include <vector>

#include <shs_Process.h>

#include "shs_lib_Color_RGBV8888.h"
#include "shs_lib_Color_RgbDriverInterface.h"


namespace shs
{
    namespace lib
    {
        namespace Color
        {
            class RgbFilter;
            class RgbEffect;

            class RgbManager;
        }
    }
}


class shs::lib::Color::RgbManager : public shs::Process
{
public:
    RgbManager(std::unique_ptr<RgbDriverInterface> driver);

    void start() override;
    void tick() override;
    void stop() override;

    

    void pushEffect(std::unique_ptr<RgbEffect> effect) { m_effects.push_back(std::move(effect)); }
    void popEffect() { if (!m_effects.empty()) m_effects.pop_back(); }
    void clearEffects() { m_effects.clear(); }

protected:
    std::vector<std::unique_ptr<RgbEffect>> m_effects;

    std::unique_ptr<RgbDriverInterface> m_driver;
    RGBV8888 m_color;
};

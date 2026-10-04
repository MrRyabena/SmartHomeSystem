#pragma once

#include <memory>
#include <vector>

#include <shs_Process.h>

#include "shs_lib_Color_RGBV8888.h"
#include "shs_lib_Color_RgbController.h"
#include "shs_lib_Color_RgbEffect.h"


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


class shs::lib::Color::RgbManager : public shs::Process, public shs::lib::Color::RgbController
{
public:

    using effect_id_t = uint16_t;

    RgbManager(std::shared_ptr<RgbController> controller);

    void start() override { m_active = true; }
    void tick() override;
    void stop() override { m_active = false; }

    void setup() override {}

    void setColor(const RGB888 color) override;
    RGB888 getColor() const override;

    void setBrightness(const uint8_t brightness) override;
    uint8_t getBrightness() const override;


    [[nodiscard]] effect_id_t pushEffect(std::unique_ptr<RgbEffect> effect) { m_effects.push_back(std::move(effect)); return m_effects.size() - 1; }
    effect_id_t popEffect() { if (!m_effects.empty()) m_effects.pop_back();  return m_effects.size(); }
    void removeEffect(const effect_id_t id) { if (id < m_effects.size()) m_effects.erase(m_effects.begin() + id); }
    void clearEffects() { m_effects.clear(); }

protected:
    std::vector<std::unique_ptr<RgbEffect>> m_effects;

    std::shared_ptr<RgbController> m_controller;
    RGBV8888 m_color;

    bool m_active;
};

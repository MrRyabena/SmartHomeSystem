#pragma once

#include <memory>
#include <vector>

#include <shs_Process.h>

#include "shs_lib_Color_RGBV8888.h"
#include "shs_lib_Color_RgbController.h"
#include "shs_lib_Color_RgbEffect.h"
#include "shs_lib_Color_BrightSmoothFilter.h"


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
    RgbManager(std::shared_ptr<RgbController> controller);

    void start() override { m_active = true; }
    void tick() override;
    void stop() override { m_active = false; }

    void setup() override {}

protected:
    std::vector<std::unique_ptr<RgbEffect>> m_effects;
    BrightSmoothFilter m_brightness_filter;

    std::shared_ptr<RgbController> m_controller;
    bool m_active;
};

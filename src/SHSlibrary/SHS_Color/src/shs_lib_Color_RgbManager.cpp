#include "shs_lib_Color_RgbManager.h"


shs::lib::Color::RgbManager::RgbManager(std::shared_ptr<RgbController> controller)
    : m_controller(controller), m_color(0, 0, 0, 255)
{}


void shs::lib::Color::RgbManager::tick()
{
    if (!m_active) return;

    for (auto& effect : m_effects)
    {
        auto value = effect->getColor();
        if (value)
        {
            m_color = *value;
            m_controller->setColor(m_color);
        }
    }
}

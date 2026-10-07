#include "shs_lib_Color_RgbManager.h"


shs::lib::Color::RgbManager::RgbManager(std::shared_ptr<RgbController> controller)
    : m_controller(controller), m_color(0, 0, 0, 255)
{}


void shs::lib::Color::RgbManager::tick()
{
    if (!m_active) return;

    if (m_brightness_filter.isEnabled())
    {
        auto brightness = m_controller->getBrightness();
        if (m_brightness_filter.apply(brightness)) m_controller->setBrightness(brightness);
    }

    for (auto& effect : m_effects)
    {
        auto value = effect->getColor();
        if (value)
        {
            m_controller->setColor(*value);
        }
    }
}

void shs::lib::Color::RgbManager::setColor(const RGB888 color)
{
    m_controller->setColor(color);
}

shs::lib::Color::RGB888 shs::lib::Color::RgbManager::getColor() const
{
    return m_controller->getColor();
}

void shs::lib::Color::RgbManager::setBrightness(const uint8_t brightness)
{
    if (m_brightness_filter.isEnabled()) m_brightness_filter.setTarget(brightness);
    else m_controller->setBrightness(brightness);
}

uint8_t shs::lib::Color::RgbManager::getBrightness() const
{
    return m_controller->getBrightness();
}


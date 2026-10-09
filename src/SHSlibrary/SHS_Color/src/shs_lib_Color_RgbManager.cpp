#include "shs_lib_Color_RgbManager.h"


shs::lib::Color::RgbManager::RgbManager(std::shared_ptr<RgbController> controller)
    : m_controller(controller), m_active(false)
{}

void shs::lib::Color::RgbManager::setup()
{
    m_controller->setup();
}


void shs::lib::Color::RgbManager::tick()
{
    if (!m_active) return;
    if (m_layers.empty()) return;

    RGBV8888 color(m_controller->getColor(), m_controller->getBrightness());
    m_layers.back()->apply(color);
    m_controller->setValue(color);
}

void shs::lib::Color::RgbManager::setColor(const RGB888 color)
{
    if (m_layers.empty())
    {
        m_controller->setColor(color);
    }
    else
    {
        m_layers.back()->setColor(color);
    }
}

shs::lib::Color::RGB888 shs::lib::Color::RgbManager::getColor() const
{
    return m_controller->getColor();
}

void shs::lib::Color::RgbManager::setBrightness(const uint8_t brightness)
{
    if (m_layers.empty())
    {
        m_controller->setBrightness(brightness);
    }
    else
    {
        m_layers.back()->setBrightness(brightness);
    }
}

uint8_t shs::lib::Color::RgbManager::getBrightness() const
{
    return m_controller->getBrightness();
}


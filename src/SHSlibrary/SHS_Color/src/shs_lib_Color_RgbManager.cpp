#include "shs_lib_Color_RgbManager.h"

#include "shs_lib_Color_RgbManagerLayer.h"

shs::lib::Color::RgbManager::RgbManager(std::shared_ptr<RgbController> controller)
    : m_controller(controller), m_active(true)
{}

void shs::lib::Color::RgbManager::setup()
{
    if (!m_controller) return;
    m_controller->setup();
}


void shs::lib::Color::RgbManager::tick()
{
    if (!m_active || !m_controller) return;
    if (m_layers.empty()) return;

    auto color = m_controller->getValue();
    if (m_layers.back()->apply(color))
    {
        m_controller->setValue(color);
    }
}

void shs::lib::Color::RgbManager::setColor(const RGB888 color)
{
    if (m_layers.empty())
    {
        if (!m_controller) return;
        m_controller->setColor(color);
    }
    else
    {
        m_layers.back()->setColor(color);
    }
}

shs::lib::Color::RGB888 shs::lib::Color::RgbManager::getColor() const
{
    if (!m_controller) return RGB888(0, 0, 0);

    return m_controller->getColor();
}

void shs::lib::Color::RgbManager::setBrightness(const uint8_t brightness)
{
    if (m_layers.empty())
    {
        if (!m_controller) return;
        m_controller->setBrightness(brightness);
    }
    else
    {
        m_layers.back()->setBrightness(brightness);
    }
}

uint8_t shs::lib::Color::RgbManager::getBrightness() const
{
    if (!m_controller) return 0;

    return m_controller->getBrightness();
}

auto shs::lib::Color::RgbManager::getTopLayer(bool create) -> std::shared_ptr<RgbManagerLayerInterface>
{
    if (!m_layers.empty())
    {
        return m_layers.back();
    }
    else if (create)
    {
        auto layer = std::make_shared<RgbManagerLayer>();
        layer->setup();
        m_layers.push_back(layer);
        return layer;
    }
    return nullptr;
}


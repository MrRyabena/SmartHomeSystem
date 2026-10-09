#pragma once

#include <memory>
#include <vector>

#include <shs_Process.h>

#include "shs_lib_Color_RGBV8888.h"
#include "shs_lib_Color_RgbController.h"
#include "shs_lib_Color_RgbManagerLayer.h"
#include "shs_lib_Color_BrightSmoothFilter.h"


namespace shs::lib::Color
{
    class RgbManager;
}


class shs::lib::Color::RgbManager : public shs::Process, public shs::lib::Color::RgbController
{
public:
    using layer_id_t = uint16_t;

    RgbManager(std::shared_ptr<RgbController> controller);

    void setup() override;

    void setColor(const RGB888 color) override;
    RGB888 getColor() const override;
    void setBrightness(const uint8_t brightness) override;
    uint8_t getBrightness() const override;

    void start() override { m_active = true; setup(); }
    void tick() override;
    void stop() override { m_active = false; }

    [[nodiscard]] layer_id_t addLayer(std::unique_ptr<RgbManagerLayer> layer) { m_layers.push_back(std::move(layer)); return m_layers.size() - 1; }
    void removeLayer(const layer_id_t id) { if (id < m_layers.size()) m_layers.erase(m_layers.begin() + id); }
    layer_id_t popLayer() { if (!m_layers.empty()) m_layers.pop_back();  return m_layers.size(); }

protected:
    std::vector<std::unique_ptr<RgbManagerLayer>> m_layers;

    std::shared_ptr<RgbController> m_controller;
    bool m_active;
};

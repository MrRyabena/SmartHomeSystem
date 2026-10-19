#pragma once

#include <shs_API.h>
#include <shs_DTP.h>
#include <shs_types.h>

#include "shs_lib_Color_RgbController.h"

namespace shs::lib::Color
{
    class RgbControllerVirtual;
}


class shs::lib::Color::RgbControllerVirtual : public shs::lib::Color::RgbController, public shs::API
{
public:
    RgbControllerVirtual(shs::DTP& dtp, shs::t::shs_ID_t id, shs::t::shs_ID_t remote_id);
    ~RgbControllerVirtual() override = default;

    void setColor(const RGB888 color) override;
    void setBrightness(const uint8_t brightness) noexcept override;

    [[nodiscard]] static shs::DTPpacket setColor(const RGB888 color, const shs::t::shs_ID_t id, const shs::t::shs_ID_t remote_id);
    [[nodiscard]] static shs::DTPpacket setBrightness(const uint8_t brightness, const shs::t::shs_ID_t api_id, const shs::t::shs_ID_t remote_id);

    shs::DTPpacket handle(shs::ByteCollectorReadIterator<>& it) override;

protected:
    shs::DTP& m_dtp;
    shs::t::shs_ID_t m_remote_id;
    shs::lib::Color::RGBV8888 m_color;
};

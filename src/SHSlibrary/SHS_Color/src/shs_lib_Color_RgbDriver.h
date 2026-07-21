#pragma once


#include <shs_settings_private.h>

#if defined(SHS_SF_AVR) || defined(SHS_SF_ESP)

#include <stdint.h>

#include <shs_types.h>
#include <shs_LoadPWM.h>

#include "shs_lib_Color_RGBV8888.h"


namespace shs
{
    namespace lib
    {
        namespace Color
        {
            struct RGBV8888;
            struct RGB888;
            class RgbDriver;
        }
    }
}


class shs::lib::Color::RgbDriver : public shs::lib::Color::RgbDriverInterface
{
public:
    enum class LedType : uint8_t
    {
        COMMON_ANODE,
        COMMON_CATHODE
    };

    explicit RgbDriver(const shs::t::shs_pin_t red_pin, const shs::t::shs_pin_t green_pin, const shs::t::shs_pin_t blue_pin,
        const LedType led_type = LedType::COMMON_CATHODE) noexcept;

    void start() override;

    void setColor(const RGBV8888& color) override noexcept;
    shs::lib::Color::RGB888 getColor() const noexcept;

    void setBrightness(const uint8_t brightness) noexcept { m_brightness = brightness; }
    uint8_t getBrightness() const noexcept { return m_brightness; }

private:
    shs::LoadPWM m_red;
    shs::LoadPWM m_green;
    shs::LoadPWM m_blue;
    const LedType m_led_type;
    const uint8_t m_brightness;
};

#endif    // #if defined(SHS_SF_AVR) || defined(SHS_SF_ESP)

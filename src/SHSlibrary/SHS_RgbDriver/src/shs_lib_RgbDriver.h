#pragma once


#include <shs_settings_private.h>

#if defined(SHS_SF_AVR) || defined(SHS_SF_ESP)

#include <stdint.h>

#include <shs_types.h>
#include <shs_LoadPWM.h>

#include <shs_lib_Color_RGBV8888.h>
#include <shs_lib_Color_RgbController.h>


namespace shs::lib::Color
{
    class RgbDriver;
}



/**
 * @brief A class for controlling RGB LEDs, strips or other RGB devices.
 * This class provides a concrete implementation for controlling RGB devices.
 */
class shs::lib::Color::RgbDriver : public shs::lib::Color::RgbController
{
public:
    enum class LedType : uint8_t
    {
        COMMON_ANODE,
        COMMON_CATHODE
    };

    explicit RgbDriver(const shs::t::shs_pin_t red_pin, const shs::t::shs_pin_t green_pin, const shs::t::shs_pin_t blue_pin,
        const LedType led_type = LedType::COMMON_CATHODE) noexcept;

    void setup() override;

    void setColor(const RGB888 color) override;
    shs::lib::Color::RGB888 getColor() const override;

    void setBrightness(const uint8_t brightness) override;
    uint8_t getBrightness() const  override { return m_brightness; }

    RGBV8888 getValue() const override;

private:
    shs::LoadPWM m_red;
    shs::LoadPWM m_green;
    shs::LoadPWM m_blue;
    const LedType m_led_type;
    uint8_t m_brightness;
};

#endif    // #if defined(SHS_SF_AVR) || defined(SHS_SF_ESP)

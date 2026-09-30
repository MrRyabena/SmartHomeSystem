#pragma once

#include <memory>
#include <vector>
#include <functional>

#include "shs_lib_Color_RGB888.h"
#include "shs_lib_Color_RGBV8888.h"

namespace shs
{
    namespace lib
    {
        namespace Color
        {
            class RgbFilter;
            class RgbController;
        }
    }
}


/**
 * @brief Abstract base class for controlling RGB leds, strips or other RGB devices.
 * This class provides an interface for setting and getting the color and brightness of RGB devices.
 * It is designed to be inherited by specific implementations of driver classes that control actual
 * hardware or virtual representations.
 */
class shs::lib::Color::RgbController
{
public:
    virtual ~RgbController() = default;

    virtual void setup() = 0;

    virtual void setColor(const RGB888 color) = 0;
    virtual RGB888 getColor() const = 0;

    virtual void setBrightness(const uint8_t brightness) = 0;
    virtual uint8_t getBrightness() const = 0;

};

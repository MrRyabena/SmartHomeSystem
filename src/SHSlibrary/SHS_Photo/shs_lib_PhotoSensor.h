#pragma once


#include <shs_types.h>

#include "shs_lib_SensorTypes.h"
#include "shs_settings_private.h"


namespace shs
{
    class SensorAnalog;    // declared in shs_SensorAnalog.h 
    class PhotoSensor;
}


class shs::PhotoSensor : public shs::SensorAnalog
{
public:
    enum class Metrics : uint8_t { RAW, PERCENT, NORMALIZE_255 };
    enum class Status : uint8_t { OK, INPUT_ERROR };

    explicit PhotoSensor(const shs::t::shs_pin_t pin, const uint8_t samples = SENSOR_AVERAGE_SAMPLES);

    void setBounds(uint16_t floor_bound, uint16_t ceil_bound);

    [[nodiscard]] int32_t              getValueI(const uint8_t metric = 0) override { return static_cast<int32_t>(getValueFx()); }
    [[nodiscard]] shs::t::shs_fixed_t  getValueFx(const uint8_t metric = 0) override;
    [[nodiscard]] shs::t::shs_float_t  getValueF(const uint8_t metric = 0) override { return static_cast<shs::t::shs_float_t>(getValueFx(metric)); }
    [[nodiscard]] shs::t::shs_double_t getValueD(const uint8_t metric = 0) override { return static_cast<shs::t::shs_double_t>(getValueFx(metric)); }


protected:
    uint16_t m_floor_bound{};
    uint16_t m_ceil_bound{};
};

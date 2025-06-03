#pragma once


/*
  Last update: v2.1.0
  Versions:
    v2.0.0 — created.
    v2.1.0 — fixed bugs, tested.
*/


#include <cmath>

#include <shs_SensorAnalog.h>
#include <shs_utils.h>


namespace shs
{
    class Thermistor;
}


/*
  A class for getting values from thermistors.
  The class is based on shs::SensorAnalog.
  The class is used to get the temperature from a thermistor connected to an analog pin.
*/
class shs::Thermistor : public shs::SensorAnalog
{
public:
    static constexpr auto ABSOLUTE_ZERO = -273.15f;

    explicit Thermistor(const shs::t::shs_pin_t pin, const uint32_t res_R, const uint16_t th_B, const uint8_t th_Temp = 25, const uint32_t th_R = 10000, const uint8_t ADC_resolution = 10, const uint8_t samples = SENSOR_AVERAGE_SAMPLES)
        : SensorAnalog(pin, samples), m_RES_R(res_R), m_TH_R(th_R), m_TH_B(th_B), m_TH_TEMP(th_Temp), m_ADC_RESOLUTION(ADC_resolution)
    {}

    enum class Status { OK, INPUT_OVERSHOOTING };

    void update() override;
    void updateFast() override;

    uint8_t getStatus() override;

    static shs::t::shs_float_t computeTemperature(const shs::t::shs_float_t signal, const uint32_t res_R, const uint16_t th_B, const uint8_t th_Temp = 25, const uint32_t th_R = 10000, const uint8_t ADCres = 10);


private:
    const uint32_t m_RES_R;
    const uint32_t m_TH_R;
    const uint16_t m_TH_B;
    const uint8_t m_TH_TEMP;
    const uint8_t m_ADC_RESOLUTION;
};

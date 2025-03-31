#pragma once


#include <shs_Sensor.h>
#include <MHZ19_uart.h>  // https://github.com/piot-jp-Team/mhz19_uart/tree/master


namespace shs
{
    class MHZ19;
}


class shs::MHZ19 : public shs::Sensor
{
public:
    enum class Metrics : uint8_t { PPM, TEMPERATURE };
    enum class Status : uint8_t { OK, NO_RESPONSE, UNDEFINED, HIGH_ACCURACY, INCREASED_ACCURACY, MEDIUM_ACCURACY, REDUCED_ACCURACY, LOW_ACCURACY };

    explicit MHZ19(const uint8_t rx, const uint8_t tx) : m_mhz19(rx, tx) {}

    ~MHZ19() = default;

    void setup() override { m_mhz19.setAutoCalibration(false); }

    void update()     override {}
    void updateFast() override {}

    [[nodiscard]] bool isUpdated() override { return true; }
    [[nodiscard]] uint8_t getStatus() override;

    [[nodiscard]] int32_t              getValueI(const uint8_t metric = static_cast<uint8_t>(Metrics::PPM))  override { return (metric ? m_mhz19.getTemperature() : m_mhz19.getPPM()); }
    [[nodiscard]] shs::t::shs_fixed_t  getValueFx(const uint8_t metric = static_cast<uint8_t>(Metrics::PPM)) override { return (metric ? m_mhz19.getTemperature() : m_mhz19.getPPM()); }
    [[nodiscard]] shs::t::shs_float_t  getValueF(const uint8_t metric = static_cast<uint8_t>(Metrics::PPM))  override { return (metric ? m_mhz19.getTemperature() : m_mhz19.getPPM()); }
    [[nodiscard]] shs::t::shs_double_t getValueD(const uint8_t metric = static_cast<uint8_t>(Metrics::PPM))  override { return (metric ? m_mhz19.getTemperature() : m_mhz19.getPPM()); }

protected:
    MHZ19_uart m_mhz19;
};

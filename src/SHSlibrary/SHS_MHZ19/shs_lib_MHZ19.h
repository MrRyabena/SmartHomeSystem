#pragma once


#include <shs_Sensor.h>
#include <MHZ19_uart.h>


namespace shs
{
    class MHZ19;
}


class shs::MHZ19 : public shs::Sensor
{
public:
    enum Metrics : uint8_t { PPM, TEMPERATURE };
    enum Status : uint8_t { OK, CONNECTION_LOST }

    MHZ19() {}
    explicit MHZ19(const uint8_t rx, const uint8_t tx) : m_mhz19(rx, tx) {}

    ~MHZ19() = default;


    void setup() override { m_mhz19.setAutoCalibration(false); }

    void update()     override {}
    void updateFast() override {}

    [[nodiscard]] virtual bool isUpdated() { return true; }

    [[nodiscard]] virtual int32_t              getValueI(const uint8_t metric = PPM) { return (metric ? m_mhz19.getPPM() : m_mhz19.getTemperature()); }
    [[nodiscard]] virtual shs::t::shs_fixed_t  getValueFx(const uint8_t metric = PPM) { return (metric ? m_mhz19.getPPM() : m_mhz19.getTemperature()); }
    [[nodiscard]] virtual shs::t::shs_float_t  getValueF(const uint8_t metric = PPM) { return (metric ? m_mhz19.getPPM() : m_mhz19.getTemperature()); }
    [[nodiscard]] virtual shs::t::shs_double_t getValueD(const uint8_t metric = PPM) { return (metric ? m_mhz19.getPPM() : m_mhz19.getTemperature()); }

protected:
    MHZ19_uart m_mhz19;
};

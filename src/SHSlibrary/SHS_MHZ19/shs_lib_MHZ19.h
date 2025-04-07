#pragma once

#include <stdint.h>


#include <MHZ19_uart.h>  // https://github.com/piot-jp-Team/mhz19_uart/tree/master

#include <shs_Sensor.h>
#include <shs_TimedData.h>
#include <shs_utils.h>


namespace shs
{
    class MHZ19;
}


class shs::MHZ19 : public shs::Sensor
{
public:
    enum class Metrics : uint8_t { PPM, TEMPERATURE };
    enum class Status : uint8_t { OK, NO_RESPONSE, UNDEFINED, HIGH_ACCURACY, INCREASED_ACCURACY, MEDIUM_ACCURACY, REDUCED_ACCURACY, LOW_ACCURACY, WARMING, CACHE_ERROR };

    explicit MHZ19(const uint8_t rx, const uint8_t tx, const uint32_t cache_expiration_time = 5000) : m_mhz19(rx, tx), m_data(cache_expiration_time) {}

    ~MHZ19() = default;

    void setup() override { m_mhz19.setAutoCalibration(false); }

    void update()     override;
    void updateFast() override { update(); }
    void updateForced(bool fast = false) override;

    [[nodiscard]] bool isUpdated() override { return !m_data.isExpired(); }
    [[nodiscard]] uint8_t getStatus() override;

    void clearCache() override { m_data.freeExpired(); }
    void setCacheExpiration(const uint32_t expiration_time) override { m_data.setExpiration(expiration_time); }
    uint32_t getCacheExpiration() const override { return m_data.getExpiration(); }


    [[nodiscard]] int32_t              getValueI(const uint8_t metric = shs::etoi(Metrics::PPM))  override { return metric ? m_data->co2 : m_data->temperature; }
    [[nodiscard]] shs::t::shs_fixed_t  getValueFx(const uint8_t metric = shs::etoi(Metrics::PPM)) override { return getValueI(metric); }
    [[nodiscard]] shs::t::shs_float_t  getValueF(const uint8_t metric = shs::etoi(Metrics::PPM))  override { return getValueI(metric); }
    [[nodiscard]] shs::t::shs_double_t getValueD(const uint8_t metric = shs::etoi(Metrics::PPM))  override { return getValueI(metric); }

protected:
    struct Data
    {
        uint32_t co2{};
        int32_t temperature{};
    };


    MHZ19_uart m_mhz19;

    shs::TimedData<Data> m_data;
    Status m_status;
};

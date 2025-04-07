#pragma once


#include <shs_Sensor.h>
#include <shs_TimedData.h>
#include <shs_lib_SensorTypes.h>

#include <shs_types.h>
#include <shs_utils.h>

#include <stdint.h>


#include <GyverBME280.h>


namespace shs
{
    class BME280;
}


class shs::BME280 : public shs::Sensor
{
public:
    GyverBME280 bme;

    enum class Metrics : uint8_t { PRESSURE_BAR, PRESSURE_MmHg, HUMIDITY, TEMPERATURE };
    enum class Status : uint8_t { OK, NO_CONNECTION, CACHE_ERROR, FAILED_READ };

    explicit BME280(const uint32_t cache_expiration_time = 2000)
        :
        shs::Sensor(static_cast<shs::Sensor::Type>(shs::lib::SensorTypes::BME280)),
        m_data(cache_expiration_time)
    {}

    ~BME280() override = default;

    void setup() override { m_status = bme.begin() ? Status::OK : Status::NO_CONNECTION; }

    void update() override;
    void updateFast() override { update(); }
    void updateForced(bool fast = false) override;

    [[nodiscard]] bool isUpdated() override { return !m_data.isExpired(); }
    [[nodiscard]] uint8_t getStatus() override { return shs::etoi(m_status); }

    void clearCache() override { m_data.freeExpired(); }
    void setCacheExpiration(const uint32_t expiration_time) override { m_data.setExpiration(expiration_time); }
    uint32_t getCacheExpiration() const override { return m_data.getExpiration(); }

    [[nodiscard]] int32_t              getValueI(const uint8_t metric = 0) override { return static_cast<int32_t>(getValueF(metric)); }
    [[nodiscard]] shs::t::shs_fixed_t  getValueFx(const uint8_t metric = 0) override { return shs::t::shs_fixed_t(getValueF(metric)); }
    [[nodiscard]] shs::t::shs_float_t  getValueF(const uint8_t metric = 0) override;
    [[nodiscard]] shs::t::shs_double_t getValueD(const uint8_t metric = 0) override { return static_cast<shs::t::shs_double_t>(getValueF(metric)); }

protected:
    struct Data
    {
        shs::t::shs_float_t pressure{};
        shs::t::shs_float_t temperature{};
        shs::t::shs_float_t humidity{};
    };

    shs::TimedData<Data> m_data;

    Status m_status{};
};

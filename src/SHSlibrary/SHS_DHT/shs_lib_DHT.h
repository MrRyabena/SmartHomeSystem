#pragma once

#include <DHT.h>  // https://github.com/adafruit/DHT-sensor-library

#include <shs_Sensor.h>
#include <shs_TimedData.h>

#include <shs_lib_SensorTypes.h>
#include <shs_types.h>
#include <shs_utils.h>


using adafruit_DHT = DHT;

namespace shs
{
    class DHT;
}


class shs::DHT : public shs::Sensor
{
public:
    enum class DHTtype : uint8_t { T_DHT11 = DHT11, T_DHT12 = DHT12, T_DHT21 = DHT21, T_DHT22 = DHT22, T_AM2301 = AM2301 };
    enum class Metrics : uint8_t { TEMPERATURE, HUMIDITY };
    enum class Status : uint8_t { OK, FAILED_READ, CACHE_ERROR, NO_DATA };


    explicit DHT(const uint8_t pin, const DHTtype dht_type, const uint32_t cache_expiration_time = 10000)
        :
        Sensor(static_cast<shs::Sensor::Type>(shs::lib::SensorTypes::DHT)),
        m_dht(pin, static_cast<uint8_t>(dht_type)), m_data(cache_expiration_time)
    {}

    void setup() override { m_dht.begin(); }

    void update() override;
    void updateFast() override { update(); }
    void updateForced([[maybe_unused]] bool fast = false) override;

    [[nodiscard]] bool isUpdated() override { return !m_data.isExpired(); }
    [[nodiscard]] uint8_t getStatus() override { return shs::etoi(m_status); }

    void clearCache() override { m_data.freeExpired(); }
    void setCacheExpiration(const uint32_t expiration_time) override { m_data.setExpiration(expiration_time); }
    uint32_t getCacheExpiration() const override { return m_data.getExpiration(); }

    [[nodiscard]] int32_t              getValueI(const uint8_t metric = 0)  override { return getValueF(metric); }
    [[nodiscard]] shs::t::shs_fixed_t  getValueFx(const uint8_t metric = 0) override { return static_cast<shs::t::shs_fixed_t>(getValueF(metric)); }
    [[nodiscard]] shs::t::shs_float_t  getValueF(const uint8_t metric = 0)  override;
    [[nodiscard]] shs::t::shs_double_t getValueD(const uint8_t metric = 0)  override { return getValueF(metric); }

protected:
    adafruit_DHT m_dht;

    struct Data
    {
        shs::t::shs_float_t temperature{};
        shs::t::shs_float_t humidity{};
    };

    shs::TimedData<Data> m_data;

    Status m_status{};
};


constexpr auto operator+(shs::DHT::DHTtype value) noexcept { return static_cast<uint8_t>(value); }
constexpr auto operator+(shs::DHT::Metrics value) noexcept { return static_cast<uint8_t>(value); }
constexpr auto operator+(shs::DHT::Status value) noexcept { return static_cast<uint8_t>(value); }

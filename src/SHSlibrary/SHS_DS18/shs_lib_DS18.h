#pragma once


#include <DS18.h>                         // https://github.com/GyverLibs/DS18

#include <shs_Sensor.h>
#include <shs_lib_SensorTypes.h>
#include <shs_TimedData.h>
#include <shs_types.h>


namespace shs
{
    class DS18;
}


class shs::DS18 : public shs::Sensor
{
public:
    GyverDS18Single gds;

    enum class Status { OK, FAILED_READ, CACHE_ERROR };
    enum class Metrics { TEMPERATURE, HUMIDITY }

    explicit DS18(const uint8_t pin, const bool parasite = true) : Sensor(shs::Sensor::Type::DIGITAL), gds(pin, parasite) {}
    ~DS18() override = default;


    void setup() override { gds.request(); }

    void update();
    void updateFast() override { update(); }
    void updateForced(bool fast = false) override;

    [[nodiscard]] virtual bool isUpdated() = 0;
    [[nodiscard]] virtual uint8_t getStatus() = 0;


    virtual void clearCache() = 0;
    virtual void setCacheExpiration(const uint32_t expiration_time) = 0;
    virtual uint32_t getCacheExpiration() const = 0;


    [[nodiscard]] virtual int32_t              getValueI(const uint8_t metric = 0) = 0;
    [[nodiscard]] virtual shs::t::shs_fixed_t  getValueFx(const uint8_t metric = 0) = 0;
    [[nodiscard]] virtual shs::t::shs_float_t  getValueF(const uint8_t metric = 0) = 0;
    [[nodiscard]] virtual shs::t::shs_double_t getValueD(const uint8_t metric = 0) = 0;

protected:
    shs::TimedData<shs::t::shs_float_t> m_data;
    Status m_status;

};


constexpr auto operator+(shs::GyverDS18_Sensor::Metrics value) noexcept { return static_cast<uint8_t>(value); }
constexpr auto operator+(shs::MHZ19::Status value) noexcept { return static_cast<uint8_t>(value); }


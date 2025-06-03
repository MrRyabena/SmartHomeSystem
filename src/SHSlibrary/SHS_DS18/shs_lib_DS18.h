#pragma once

/*
  Last update: v2.1.0
  Versions:
    v2.0.0 — development started.
    v2.1.0 — completed, but need testing.
*/

#include <GyverDS18.h>                 // https://github.com/GyverLibs/GyverDS18

#include <shs_Sensor.h>
#include <shs_lib_SensorTypes.h>
#include <shs_TimedData.h>
#include <shs_types.h>

#include <shs_lib_SensorTypes.h>
#include <shs_utils.h>


namespace shs
{
    class DS18;
}


class shs::DS18 : public shs::Sensor
{
public:
    GyverDS18Single gds;

    enum class Status { OK, FAILED_READ, CACHE_ERROR, UPDATING };
    enum class Metrics { TEMPERATURE };

    explicit DS18(shs::t::shs_pin_t pin, bool parasite = false);
    ~DS18() override = default;


    void setup() override { gds.requestTemp(); }

    void update();
    void updateFast() override { update(); }
    void updateForced(bool fast = false) override;

    [[nodiscard]] bool isUpdated() override;
    [[nodiscard]] uint8_t getStatus() { return shs::etoi(m_status); };


    void clearCache() override { m_data.freeExpired(); }
    void setCacheExpiration(const uint32_t expiration_time) override { m_data.setExpiration(expiration_time); }
    uint32_t getCacheExpiration() const override { return m_data.getExpiration(); }


    [[nodiscard]] int32_t              getValueI(const uint8_t metric = 0) override { return static_cast<int32_t>(getValueF()); }
    [[nodiscard]] shs::t::shs_fixed_t  getValueFx(const uint8_t metric = 0) override { return static_cast<shs::t::shs_fixed_t>(getValueF()); }
    [[nodiscard]] shs::t::shs_float_t  getValueF(const uint8_t metric = 0) override;
    [[nodiscard]] shs::t::shs_double_t getValueD(const uint8_t metric = 0) override { return static_cast<shs::t::shs_double_t>(getValueD()); }

protected:
    shs::TimedData<shs::t::shs_float_t> m_data;
    Status m_status;
};

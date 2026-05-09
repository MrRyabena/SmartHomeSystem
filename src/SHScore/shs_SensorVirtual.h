#pragma once

/*
  Last update: v2.2.0
  Versions:
    v0.2.0 — created.
    v1.0.0 — release.
    v2.0.0 — moved to a separate file, redesigned, debugged and tested.
    v2.2.0 — bug fixed: updated according to changes in the shs base class::Sensor.
*/

/*
  The "handler" class controls the load on the module itself.
  The "virtual" class implements the interface on the remote device.
*/


#include "shs_settings_private.h"

#ifndef SHS_SF_AVR

#ifdef SHS_SF_AVR
#include <shs_lib_AVR_STD_memory.h>
#else
#include <memory>
#endif 

#include "shs_Sensor.h"
#include "shs_Sensor_API.h"
#include "shs_types.h"
#include "shs_APIids.h"
#include "shs_API.h"
#include "shs_ByteCollector.h"
#include "shs_ByteCollectorIterator.h"
#include "shs_DTP.h"
#include "shs_DTPpacket.h"
#include "shs_TimedData.h"


namespace shs
{
    class SensorVirtual;
}


/**
 * @brief Virtual sensor implementation that receives values from a remote module over DTP.
 */
class shs::SensorVirtual : public shs::Sensor, public shs::API
{
public:
  /**
   * @brief Creates a virtual sensor that reads values from a remote module.
   */
    explicit SensorVirtual(shs::t::shs_ID_t thisID, shs::t::shs_ID_t virtualID, shs::DTP& dtp, shs::Sensor::Type stype = UNKNOWN, uint32_t expiration_time = 10'000);

  /**
   * @brief Releases the virtual sensor.
   */
    ~SensorVirtual() = default;

    // API
  /**
   * @brief Handles requests directed to the virtual sensor.
   */
    shs::DTPpacket handle(shs::ByteCollectorReadIterator<>& it) override;

    // Sensor
  /**
   * @brief Initializes the virtual sensor interface.
   */
    void setup() override {}
    
  /**
   * @brief Requests a fresh value from the remote sensor.
   */
    void update() override;

  /**
   * @brief Requests a faster update path from the remote sensor.
   */
    void updateFast() override;

  /**
   * @brief Forces a sensor update and optionally uses the fast path.
   */
    void updateForced([[maybe_unused]] bool fast = false) override;
    

  /**
   * @brief Reports whether the cached remote value is still valid.
   */
    [[nodiscard]] bool isUpdated() override { return !m_data.isExpired(); }

  /**
   * @brief Returns the current status code.
   */
    [[nodiscard]] uint8_t getStatus() override { return 0; }

  /**
   * @brief Clears expired cached data.
   */
    void clearCache() override { m_data.freeExpired(); }

  /**
   * @brief Updates the cache lifetime.
   */
    void setCacheExpiration(const uint32_t expiration_time) { m_data.setExpiration(expiration_time); }

  /**
   * @brief Returns the cache lifetime.
   */
    uint32_t getCacheExpiration() const override { return m_data.getExpiration(); }

  /**
   * @brief Returns the cached value as a signed integer.
   */
    [[nodiscard]] int32_t              getValueI([[maybe_unused]] const uint8_t metric = 0) override { return static_cast<int32_t>(*m_data); }

  /**
   * @brief Returns the cached value as a fixed-point number.
   */
    [[nodiscard]] shs::t::shs_fixed_t  getValueFx([[maybe_unused]] const uint8_t metric = 0) override { return *m_data; }

  /**
   * @brief Returns the cached value as a float.
   */
    [[nodiscard]] shs::t::shs_float_t  getValueF([[maybe_unused]] const uint8_t metric = 0) override { return static_cast<shs::t::shs_float_t>(*m_data); }

  /**
   * @brief Returns the cached value as a double.
   */
    [[nodiscard]] shs::t::shs_double_t getValueD([[maybe_unused]] const uint8_t metric = 0) override { return static_cast<shs::t::shs_double_t>(*m_data); }

protected:
  /**
   * @brief Identifier of the remote virtual sensor endpoint.
   */
    shs::t::shs_ID_t m_virtualID;

  /**
   * @brief DTP transport used to exchange sensor data.
   */
    shs::DTP& m_dtp;

  /**
   * @brief Cached remote sensor value with expiration.
   */
    shs::TimedData<shs::t::shs_fixed_t> m_data;
};

#endif  // SHS_SF_AVR

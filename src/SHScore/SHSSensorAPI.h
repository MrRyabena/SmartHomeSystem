#pragma once

/*
  Last update: v1.0.0
  Versions:
    v0.2.0 — created.
    v1.0.0 — release.
*/

/*
  The "handler" class controls the load on the module itself.
  The "virtual" class implements the interface on the remote device.
*/

#include "SHSSensor.h"
#include "SHSAPI.h"

#include "SHSModule.h"
#include "SHSByteCollector.h"

namespace shs
{
    namespace SensorAPIcmds
    {
        enum SensorAPIcmds : uint8_t;
    };
    class SensorAPIvirtual;
    class SensorAPIhandler;
};

enum shs::SensorAPIcmds::SensorAPIcmds : uint8_t
{
    getValueI,
    getValueF,
    getValueD,
    getAverageI,
    getAverageF,
    getAverageD,

    retValueI,
    retValueF,
    retValueD,
    retAverageI,
    retAverageF,
    retAverageD,

};

/*
  ----------------------------------------
  PRIVATE/PROTECTED
  ----------------------------------------
*/

class shs::SensorAPIvirtual : public shs::API, public shs::Sensor
{
public:
    SensorAPIvirtual(const shs::settings::shs_ID_t apiID = 0, const shs::settings::shs_ModuleID_t to = 0);

    void setup() override{};

    int16_t getValueI(const shs::settings::shs_ID_t ID = 0) override;
    shs::settings::shs_float_t getValueF(const shs::settings::shs_ID_t ID = 0) override;
    shs::settings::shs_double_t getValueD(const shs::settings::shs_ID_t ID = 0) override;

    int16_t getAverageI(const shs::settings::shs_ID_t ID = 0) override;
    shs::settings::shs_float_t getAverageF(const shs::settings::shs_ID_t ID = 0) override;
    shs::settings::shs_double_t getAverageD(const shs::settings::shs_ID_t ID = 0) override;

protected:
    void m_prepareCommand(const shs::settings::shs_ID_t ID, const shs::SensorAPIcmds::SensorAPIcmds command);
};

/*
  ----------------------------------------
  SensorAPIhandler
  ----------------------------------------
*/

class shs::SensorAPIhandler : public shs::API
{
public:
    explicit SensorAPIhandler(const shs::settings::shs_ID_t apiID = 0,
                              const shs::settings::shs_ModuleID_t to = 0, shs::Sensor *sensors = nullptr);

    uint8_t handler(shs::ByteCollector &data) override;

protected:
    void m_prepareAnswer(const shs::settings::shs_ID_t ID, const shs::SensorAPIcmds::SensorAPIcmds cmd, const int16_t value);
    void m_prepareAnswer(const shs::settings::shs_ID_t ID, const shs::SensorAPIcmds::SensorAPIcmds cmd, const shs::settings::shs_float_t value);
    void m_prepareAnswer(const shs::settings::shs_ID_t ID, const shs::SensorAPIcmds::SensorAPIcmds cmd, const shs::settings::shs_double_t &value);

    shs::Sensor *m_sensors;
};

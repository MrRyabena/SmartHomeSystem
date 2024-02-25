#pragma once

#include "SHSSensor.h"
#include <vector>

namespace shs
{
    class SensorsKeeper;
};

class shs::SensorsKeeper : public Sensor
{
public:
    explicit SensorsKeeper() {}
    void attach(shs::Sensor *object);
    void detach(shs::Sensor *object);

    void setup() override;

    uint8_t find(const shs::settings::shs_ID_t ID);

    int16_t getValueI(const shs::settings::shs_ID_t ID) override;
    shs::settings::shs_float_t getValueF(const shs::settings::shs_ID_t ID) override;
    shs::settings::shs_double_t getValueD(const shs::settings::shs_ID_t ID) override;

    int16_t getAverageI(const shs::settings::shs_ID_t ID) override;
    shs::settings::shs_float_t getAverageF(const shs::settings::shs_ID_t ID) override;
    shs::settings::shs_double_t getAverageD(const shs::settings::shs_ID_t ID) override;

protected:
    std::vector<shs::Sensor *> m_ptrs;
    uint8_t m_find(const shs::Sensor *object);
};

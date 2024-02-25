#pragma once

#include "SHSLoad.h"
#include "SHSProcess.h"
#include "SHSProcessesKeeper.h"
#include <stdint.h>
#include <Arduino.h>

namespace shs
{
    class LoadPWM;
};

class shs::LoadPWM : public shs::Load, protected shs::Process
{
public:
    explicit LoadPWM(shs::settings::shs_ID_t ID = 0, uint8_t pin = 0,
            shs::ProcessesKeeper *keeper = nullptr, shs::LoadType ltype = shs::LoadType::PWM);
    ~LoadPWM();

    void setKeeper(shs::ProcessesKeeper *keeper);

    void setup() override;

    void on(uint8_t value = 255, uint8_t smoothing = 0, const shs::settings::shs_ID_t ID = 0) override;
    void on(uint16_t value = UINT16_MAX, uint16_t smoothing = 0, const shs::settings::shs_ID_t ID = 0) override;

    void off(uint16_t smoothing = 0, const shs::settings::shs_ID_t ID = 0) override;

    void begin() override;
    void tick() override;
    void end() override;

protected:
    struct Smoothing
    {
        uint16_t targetValue{};
        uint16_t value{};
        uint16_t k_smoothing{};
        uint16_t tmr{};
    };

protected:
    uint8_t m_pin;
    ProcessesKeeper *m_keeper;
    Smoothing *m_stc;
};

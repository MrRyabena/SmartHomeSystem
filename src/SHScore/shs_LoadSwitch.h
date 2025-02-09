#pragma once

#include "shs_settings_private.h"
#include "shs_Load.h"


#ifdef SHS_SF_ARDUINO

#include <GyverIO.h>


namespace shs
{
    class LoadSwitch;
}


class shs::LoadSwitch : public shs::Load
{
public:
    explicit LoadSwitch(const uint8_t pin, const Load::Type type = Load::Type::SWITCH)
        : Load(type), m_pin(pin)
    {}

    ~LoadSwitch() override = default;

    void setup() override
    {
    #ifdef SHS_SF_ESP
        gio::init(m_pin, OUTPUT);
    #else
        gio::mode(m_pin, OUTPUT);
    #endif
    }

    void on(const uint16_t value = UINT16_MAX) override { gio::write(m_pin, value); m_value = static_cast<bool>(value); }
    void off() override { gio::low(m_pin); m_value = 0; }

protected:
    const uint8_t m_pin;
};

#endif  // #ifdef SHS_SF_ARDUINO

#include "SHSLoadSwitch.h"

shs::LoadSwitch::LoadSwitch(shs::settings::shs_ID_t ID, uint8_t pin, shs::LoadType ltype)
    : ::shs::Load(ID, ltype), m_pin(pin) {}

void shs::LoadSwitch::setup() { pinMode(m_pin, OUTPUT); }

void shs::LoadSwitch::on(const uint8_t value, const uint8_t smoother) { digitalWrite(m_pin, value); }
void shs::LoadSwitch::on(const uint16_t value, const uint16_t smoother) { digitalWrite(m_pin, value); }

void shs::LoadSwitch::off(const uint8_t smoothing) { digitalWrite(m_pin, 0); }

void shs::LoadSwitch::begin() { setup(); }
void shs::LoadSwitch::tick() {}
void shs::LoadSwitch::end() {}

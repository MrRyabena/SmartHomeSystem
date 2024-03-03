#pragma once

/*
  Last update: v1.0.0
  Versions:
    v0.2.0 — created.
    v1.0.0 — release.
*/

/*
  This is a container for managing and configuring loads.
*/

#include "SHSLoad.h"
#include <stdint.h>
#include <vector>

namespace shs
{
    class LoadKeeper;
};

class shs::LoadKeeper : public shs::Load
{
public:
    explicit LoadKeeper(){};

    void attach(shs::Load *object);
    void detach(shs::Load *object);

    uint8_t find(shs::settings::shs_ID_t ID);

    void setup() override;

    void on(const uint8_t value = 255, const uint8_t smoothing = 0, const shs::settings::shs_ID_t ID = 0) override;
    void on(const uint16_t value = UINT16_MAX, const uint16_t smoothing = 0, const shs::settings::shs_ID_t ID = 0) override;

    void off(const uint16_t smoothing = 0, const shs::settings::shs_ID_t ID = 0) override;

protected:
    std::vector<shs::Load *> m_ptrs;
    uint8_t m_find(const shs::Load *object);
};

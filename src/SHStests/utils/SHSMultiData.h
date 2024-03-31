#pragma once

/*
  The struct MultiData with basic data for testing.
*/

/*
  Last update: v1.1.0
  Versions:
    v1.1.0 — created.
*/

#include <stdint.h>

namespace shs
{
    namespace tests
    {
        struct MultiData;
    }
}

struct shs::tests::MultiData
{
    uint8_t u8v{};
    int8_t i8v{};
    uint16_t u16v{};
    int16_t i16v{};
    uint32_t u32v{};
    int32_t i32v{};
    uint64_t u64v{};
    int64_t i64v{};

    float fv{};
    double dv{};

    constexpr static uint8_t cstr_size = 12;
    uint8_t cstr[cstr_size]{};
};

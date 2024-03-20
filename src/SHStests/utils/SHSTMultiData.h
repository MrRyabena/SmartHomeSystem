#pragma once

#include <stdint.h>
#include <stdfloat>

namespace shs::tests
{
    struct MultiData;
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

    char cstr[12];
};

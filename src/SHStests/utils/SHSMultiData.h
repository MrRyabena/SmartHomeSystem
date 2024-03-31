#pragma once

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
    // constexpr MultiData(const uint8_t _u8v, const int8_t _i8v, const uint16_t _u16v, const int16_t _i16v,
    //           const uint32_t _u32v, const int32_t _i32v, const uint64_t _u64v, const int64_t _i64v,
    //           const uint8_t *str)
    //     : u8v(_u8v), i8v(_i8v), u16v(_u16v), i16v(_i16v), u32v(_u32v), i32v(_i32v), u64v(_u64v), i64v(i64v)
    // {
    //     for (uint8_t i = 0; i < cstr_size; i++) cstr[i] = str[i];
    // }
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

#pragma once

/*
  This is simple struct with testing data.
*/

/*
  Last update: v1.1.0
  Versions:
    v1.1.0 — created.
*/

#include <stdint.h>
#include <cstddef>

namespace shs
{
    namespace tests
    {
        struct Data
        {
            constexpr static size_t size = 64;
            constexpr static uint8_t crc8arr1 = 150;
            constexpr static uint8_t crc8arr2 = 215;
            constexpr static uint16_t crc16arr1 = 56648;
            constexpr static uint16_t crc16arr2 = 42294;
            constexpr static uint32_t crc32arr1 = 2698385654;
            constexpr static uint32_t crc32arr2 = 333926124;

            const uint8_t arr1[size]{
                181,
                75,
                142,
                25,
                27,
                57,
                191,
                207,
                156,
                98,
                161,
                54,
                1,
                108,
                225,
                169,
                46,
                9,
                218,
                182,
                105,
                165,
                125,
                183,
                123,
                134,
                217,
                42,
                234,
                157,
                197,
                183,
                205,
                61,
                147,
                72,
                247,
                34,
                70,
                238,
                160,
                205,
                161,
                93,
                17,
                237,
                67,
                54,
                202,
                17,
                144,
                233,
                50,
                220,
                173,
                15,
                63,
                173,
                133,
                179,
                87,
                227,
                166,
                57,
            };
            const uint8_t arr2[size]{
                206,
                72,
                148,
                222,
                7,
                100,
                113,
                241,
                62,
                149,
                24,
                180,
                245,
                126,
                123,
                133,
                124,
                2,
                17,
                132,
                48,
                34,
                247,
                10,
                78,
                151,
                141,
                11,
                141,
                234,
                117,
                245,
                178,
                242,
                3,
                127,
                147,
                8,
                3,
                71,
                201,
                210,
                184,
                165,
                85,
                93,
                61,
                57,
                6,
                177,
                52,
                229,
                158,
                39,
                213,
                100,
                164,
                63,
                227,
                168,
                115,
                161,
                110,
                71,
            };
        } constexpr data;
    }
}

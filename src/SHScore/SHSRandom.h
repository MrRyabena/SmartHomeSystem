#pragma once

/*
  Random number generator.
    - supports various ranges
    - has seed auto-tuning.
*/

/*
  Last update: v1.1.0
  Versions:
    v1.1.0 — created.
*/

#include <stdint.h>
#include "SHSsettings_private.h"

#if __has_include(<Arduino.h>)
#include <Random16.h>
#else
#include <random>
#endif

namespace shs
{
    template <typename random_t>
    class Random;
}

template <typename random_t>
class shs::Random
{
public:
    random_t seed{};

public:
    constexpr explicit Random(const random_t min = 0, const random_t max = 0xffff, const random_t setSeed = 42);

    void setSeed(const random_t seed);
    void setRange(const random_t min, const random_t max);
    random_t autoSeed();

    random_t get();

protected:
#ifdef ARDUINO
    Random16 m_rnd;
#else
    std::mt19937 m_rnd_engine;
    std::uniform_real_distribution<> m_rnd_distribution;
#endif
    random_t m_max{};
    random_t m_min{};
};

template <typename random_t>
constexpr shs::Random<random_t>::Random(random_t min, random_t max, random_t setSeed)
    : m_min(min), m_max(max), seed(setSeed)
#ifdef ARDUINO

#else
      ,
      m_rnd_engine(setSeed),
      m_rnd_distribution(static_cast<double>(min), static_cast<double>(max))
#endif
{
}

template <typename random_t>
void shs::Random<random_t>::setSeed(random_t setSeed)
{
    seed = setSeed;
#ifdef ARDUINO
    m_rnd.setSeed(seed);
#else
    m_rnd_engine.seed(seed);
#endif
}

template <typename random_t>
inline random_t shs::Random<random_t>::autoSeed()
{
#ifdef ARDUINO
    seed = millis();
    m_rnd.setSeed(seed);
#else
    std::random_device device;
    seed = device();
    m_rnd_engine.seed(seed);
#endif
    return seed;
}

template <typename random_t>
inline void shs::Random<random_t>::setRange(const random_t min, const random_t max)
{
    m_min = min;
    m_max = max;
#ifdef ARDUINO

#else
    m_rnd_distribution = std::uniform_real_distribution<>(min, max);
#endif
}

template <typename random_t>
random_t shs::Random<random_t>::get()
{
#ifdef ARDUINO
    uint16_t value = m_rnd.get();
    random_t dis = (uint32_t)value * (m_max - m_min) / 0xffff;
    dis += m_min;
    return dis;

#else
    return static_cast<random_t>(m_rnd_distribution(m_rnd_engine));
#endif
}

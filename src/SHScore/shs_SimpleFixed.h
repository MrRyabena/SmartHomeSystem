#pragma once

/*
  Last update: v2.1.0
  Versions:
    v2.0.0 — created.
    v2.1.0 — added copy constructors and assignment operators.
*/

#include <stdint.h>
#include <math.h>

#include "shs_settings_private.h"
#ifdef SHS_SF_AVR
namespace std
{
    static inline double c_pow(const double x, const double y) { return pow(x, y); }
    inline double pow(const double x, const double y) { return c_pow(x, y); }
}

#endif

#include "shs_types.h"

namespace shs
{
    class SimpleFixed;
}


/**
 * @brief Lightweight fixed-point number helper used for convenience.
 */
class shs::SimpleFixed
{
public:
    /**
     * @brief Default decimal resolution used by the type.
     */
    static constexpr auto DEFAULT_POWER_OF_TEN = 4;

    /**
     * @brief Creates a fixed-point value from a floating-point input.
     */
    explicit SimpleFixed(const double value = 0, const uint8_t power_of_ten = DEFAULT_POWER_OF_TEN) noexcept
        : m_value(((static_cast<int64_t>(value* std::pow(10, power_of_ten)) << 4) & 0xfffffffffffffff0) | (power_of_ten & 0x0f))
    {}

    /**
     * @brief Destroys the fixed-point value.
     */
    ~SimpleFixed() = default;

    /**
     * @brief Copies a fixed-point value.
     */
    SimpleFixed(const SimpleFixed& other) noexcept = default;

    /**
     * @brief Moves a fixed-point value.
     */
    SimpleFixed(SimpleFixed&& other) noexcept = default;

    /**
     * @brief Copies a fixed-point value.
     */
    SimpleFixed& operator=(const SimpleFixed& other) noexcept = default;

    /**
     * @brief Moves a fixed-point value.
     */
    SimpleFixed& operator=(SimpleFixed&& other) noexcept = default;

    /**
     * @brief Assigns from an integer value.
     */
    SimpleFixed& operator=(const int64_t value) { set(value); return *this; }
    /**
     * @brief Assigns from an integer value.
     */
    SimpleFixed& operator=(const int32_t value) { set(static_cast<int64_t>(value)); return *this; }
    /**
     * @brief Assigns from an integer value.
     */
    SimpleFixed& operator=(const int16_t value) { set(static_cast<int64_t>(value)); return *this; }
    /**
     * @brief Assigns from an integer value.
     */
    SimpleFixed& operator=(const int8_t value) { set(static_cast<int64_t>(value)); return *this; }
    /**
     * @brief Assigns from an integer value.
     */
    SimpleFixed& operator=(const uint64_t value) { set(static_cast<int64_t>(value)); return *this; }
    /**
     * @brief Assigns from an integer value.
     */
    SimpleFixed& operator=(const uint32_t value) { set(static_cast<int64_t>(value)); return *this; }
    /**
     * @brief Assigns from an integer value.
     */
    SimpleFixed& operator=(const uint16_t value) { set(static_cast<int64_t>(value)); return *this; }
    /**
     * @brief Assigns from an integer value.
     */
    SimpleFixed& operator=(const uint8_t value) { set(static_cast<int64_t>(value)); return *this; }

    /**
     * @brief Assigns from a float value.
     */
    SimpleFixed& operator=(const float value) { set(value); return *this; }

    /**
     * @brief Assigns from a double value.
     */
    SimpleFixed& operator=(const double value) { set(value); return *this; }


    /**
     * @brief Sets the raw integer component with an optional decimal resolution.
     */
    void set(const int64_t value, const uint8_t power_of_ten = 0) { m_value = (value << 4) | ((power_of_ten ? power_of_ten : getResolution()) & 0x0f); }
    /**
     * @brief Sets the value from a float with an optional decimal resolution.
     */
    void set(const float   value, const uint8_t power_of_ten = 0) { m_value = ((static_cast<int64_t>(value * std::pow(10, power_of_ten ? power_of_ten : getResolution())) << 4) & 0xfffffffffffffff0) | ((power_of_ten ? power_of_ten : getResolution()) & 0x0f); }
    /**
     * @brief Sets the value from a double with an optional decimal resolution.
     */
    void set(const double  value, const uint8_t power_of_ten = 0) { m_value = ((static_cast<int64_t>(value * std::pow(10, power_of_ten ? power_of_ten : getResolution())) << 4) & 0xfffffffffffffff0) | ((power_of_ten ? power_of_ten : getResolution()) & 0x0f); }


    /**
     * @brief Returns the packed raw representation.
     */
    int64_t getRAW() const { return m_value; }

    /**
     * @brief Returns the integer component without the encoded resolution.
     */
    int64_t getRAWvalue() const { return m_value >> 4; }

    /**
     * @brief Returns the decimal resolution encoded in the value.
     */
    uint8_t getResolution() const { return m_value & 0x0f; }

    /**
     * @brief Re-encodes the value with a different resolution.
     */
    void setResolution(const uint8_t power_of_ten) { set(toDouble(), power_of_ten); }


    /**
     * @brief Converts the value to float.
     */
    float toFloat()   const { return static_cast<float>(getRAWvalue()) / std::pow(10, getResolution()); }

    /**
     * @brief Converts the value to double.
     */
    double toDouble() const { return static_cast<double>(getRAWvalue()) / std::pow(10, getResolution()); }

    /**
     * @brief Converts the value to integer.
     */
    int64_t toInt() const { return (getRAWvalue()) / std::pow(10, getResolution()); }


    /**
     * @brief Converts to float.
     */
    operator float()    const { return toFloat(); }

    /**
     * @brief Converts to double.
     */
    operator double()   const { return toDouble(); }

    /**
     * @brief Converts to signed 64-bit integer.
     */
    operator int64_t()  const { return static_cast<int64_t>(toInt()); }

    /**
     * @brief Converts to signed 32-bit integer.
     */
    operator int32_t()  const { return static_cast<int32_t>(toInt()); }

    /**
     * @brief Converts to signed 16-bit integer.
     */
    operator int16_t()  const { return static_cast<int16_t>(toInt()); }

    /**
     * @brief Converts to signed 8-bit integer.
     */
    operator int8_t()   const { return static_cast<int8_t>(toInt()); }

    /**
     * @brief Converts to unsigned 64-bit integer.
     */
    operator uint64_t() const { return static_cast<uint64_t>(toInt()); }

    /**
     * @brief Converts to unsigned 32-bit integer.
     */
    operator uint32_t()  const { return static_cast<uint32_t>(toInt()); }

    /**
     * @brief Converts to unsigned 16-bit integer.
     */
    operator uint16_t() const { return static_cast<uint16_t>(toInt()); }

    /**
     * @brief Converts to unsigned 8-bit integer.
     */
    operator uint8_t()  const { return static_cast<uint8_t>(toInt()); }

private:
    /**
     * @brief Encoded fixed-point value.
     */
    int64_t m_value;
};

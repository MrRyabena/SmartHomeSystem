#pragma once

#include <stdint.h>
#include <shs_math.h>
#include <shs_algorithm.h>

#include "shs_lib_Color_RGB888.h"
#include "shs_lib_Color_RGBV8888.h"
#include "shs_lib_Color_HSB888.h"
#include "shs_lib_Color_HSBV8888.h"
#include "shs_lib_Color_Kelvin.h"
#include "shs_lib_Color_Wheel256.h"
#include "shs_lib_Color_Wheel1530.h"


namespace shs
{
    namespace lib
    {
        namespace Color
        {
            namespace cast_policy
            {
                struct Default {};
                struct Fast {};
            }
            namespace cast_impl
            {
                using namespace shs::lib::Color;

                static constexpr inline uint8_t max3(uint8_t a, uint8_t b, uint8_t c)
                {
                    return (a > b) ? ((a > c) ? a : c) : ((b > c) ? b : c);
                }
                static constexpr inline uint8_t min3(uint8_t a, uint8_t b, uint8_t c)
                {
                    return (a < b) ? ((a < c) ? a : c) : ((b < c) ? b : c);
                }

                template<class To, class From, typename Policy>
                struct ColorCastImpl
                {

                };

                template<>
                struct ColorCastImpl<RGB888, RGBV8888, cast_policy::Default>
                {
                    static RGB888 cast(const RGBV8888& color)
                    {
                        return RGB888(color.red, color.green, color.blue);
                    }
                };

                template<>
                struct ColorCastImpl<RGBV8888, RGB888, cast_policy::Default>
                {
                    static RGBV8888 cast(const RGB888& color)
                    {
                        return RGBV8888(color.red, color.green, color.blue, 0xff);
                    }
                };

                template<>
                struct ColorCastImpl<HSB888, HSBV8888, cast_policy::Default>
                {
                    static HSB888 cast(const HSBV8888& color)
                    {
                        return HSB888(color.hue, color.saturation, color.brightness);
                    }
                };


                template<>
                struct ColorCastImpl<RGB888, HSB888, cast_policy::Default>
                {
                    static RGB888 cast(const HSB888& color)
                    {
                        float R, G, B;
                        float H = color.hue / 255.0;
                        float S = color.saturation / 255.0;
                        float V = color.brightness / 255.0;

                        int i = int(H * 6);
                        float f = H * 6 - i;
                        float p = V * (1 - S);
                        float q = V * (1 - f * S);
                        float t = V * (1 - (1 - f) * S);

                        switch (i % 6)
                        {
                            case 0: R = V, G = t, B = p; break;
                            case 1: R = q, G = V, B = p; break;
                            case 2: R = p, G = V, B = t; break;
                            case 3: R = p, G = q, B = V; break;
                            case 4: R = t, G = p, B = V; break;
                            case 5: R = V, G = p, B = q; break;
                        }

                        uint8_t r = R * 255.0;
                        uint8_t g = G * 255.0;
                        uint8_t b = B * 255.0;


                        return RGB888(r, g, b);
                    }
                };

                template<>
                struct ColorCastImpl<RGBV8888, HSBV8888, cast_policy::Default>
                {
                    static RGBV8888 cast(const HSBV8888& color)
                    {
                        return RGBV8888(ColorCastImpl<RGB888, HSB888, cast_policy::Default>::cast(color));
                    }
                };

                template<>
                struct ColorCastImpl<RGB888, HSB888, cast_policy::Fast>
                {
                    static RGB888 cast(const HSB888& color)
                    {

                        uint8_t r, g, b;
                        uint8_t value = ((24 * color.hue / 17) / 60) % 6;
                        uint8_t vmin = (long)color.brightness - color.brightness * color.saturation / 255;
                        uint8_t a = (long)color.brightness * color.saturation / 255 * (color.hue * 24 / 17 % 60) / 60;
                        uint8_t vinc = vmin + a;
                        uint8_t vdec = color.brightness - a;

                        switch (value)
                        {
                            case 0: r = color.brightness; g = vinc; b = vmin; break;
                            case 1: r = vdec; g = color.brightness; b = vmin; break;
                            case 2: r = vmin; g = color.brightness; b = vinc; break;
                            case 3: r = vmin; g = vdec; b = color.brightness; break;
                            case 4: r = vinc; g = vmin; b = color.brightness; break;
                            case 5: r = color.brightness; g = vmin; b = vdec; break;
                        }

                        return RGB888(r, g, b);
                    }
                };


                template<>
                struct ColorCastImpl<RGBV8888, HSBV8888, cast_policy::Fast>
                {
                    static RGBV8888 cast(const HSBV8888& color)
                    {
                        return RGBV8888(ColorCastImpl<RGB888, HSB888, cast_policy::Fast>::cast(color));
                    }
                };

                template<>
                struct ColorCastImpl<HSB888, RGB888, cast_policy::Default>
                {
                    static HSB888 cast(const RGB888& color)
                    {
                        uint8_t mx = max3(color.red, color.green, color.blue);
                        uint8_t mn = min3(color.red, color.green, color.blue);
                        uint8_t delta = mx - mn;

                        HSB888 hsb;
                        hsb.brightness = mx;

                        if (delta == 0)
                        {
                            hsb.hue = 0;
                            hsb.saturation = 0;
                            return hsb;
                        }

                        hsb.saturation = (uint16_t(delta) * 255) / mx;

                        int16_t h;

                        if (mx == color.red)
                        {
                            h = 43 * (int16_t(color.green) - int16_t(color.blue)) / delta;
                        }
                        else if (mx == color.green)
                        {
                            h = 85 + 43 * (int16_t(color.blue) - int16_t(color.red)) / delta;
                        }
                        else
                        {
                            h = 171 + 43 * (int16_t(color.red) - int16_t(color.green)) / delta;
                        }

                        if (h < 0)
                        {
                            h += 256;
                        }
                        else if (h > 255)
                        {
                            h -= 256;
                        }

                        hsb.hue = h;
                        return hsb;
                    }
                };

                template<>
                struct ColorCastImpl<HSBV8888, RGBV8888, cast_policy::Default>
                {
                    static HSBV8888 cast(const RGBV8888& color)
                    {
                        return HSBV8888(ColorCastImpl<HSB888, RGB888, cast_policy::Default>::cast(color));
                    }
                };

                template<>
                struct ColorCastImpl<RGB888, Kelvin, cast_policy::Default>
                {
                    static RGB888 cast(const Kelvin& color)
                    {
                        float tmpKelvin = color.kelvin / 100.0f;
                        float tmp;
                        uint8_t r, g, b;

                        if (tmpKelvin <= 66)
                        {
                            r = 255;
                        }
                        else
                        {
                            tmp = shs::math::pow(tmpKelvin - 60, -0.1332047592) * 329.698727446;
                            r = shs::clamp(tmp, 0.0f, 255.0f);
                        }

                        if (tmpKelvin <= 66)
                        {
                            tmp = 99.4708025861 * log(tmpKelvin) - 161.1195681661;
                        }
                        else
                        {
                            tmp = shs::math::pow(tmpKelvin - 60, -0.0755148492) * 288.1221695283;
                        }
                        g = shs::clamp(tmp, 0.0f, 255.0f);

                        if (tmpKelvin >= 66)
                        {
                            b = 255;
                        }
                        else if (tmpKelvin <= 19)
                        {
                            b = 0;
                        }
                        else
                        {
                            tmp = 138.5177312231 * shs::math::log(tmpKelvin - 10) - 305.0447927307;
                            b = shs::clamp(tmp, 0.0f, 255.0f);
                        }

                        return RGB888(r, g, b);
                    }
                };

                template<>
                struct ColorCastImpl<RGBV8888, Kelvin, cast_policy::Default>
                {
                    static RGBV8888 cast(const Kelvin& color)
                    {
                        return RGBV8888(ColorCastImpl<RGB888, Kelvin, cast_policy::Default>::cast(color));
                    }
                };

                template<>
                struct ColorCastImpl<RGB888, Kelvin, cast_policy::Fast>
                {
                    static RGB888 cast(const Kelvin& color)
                    {
                        float K = color.kelvin;
                        K = shs::clamp(K, 1000.0f, 10000.0f);
                        if (K < 6700)
                        {
                            return RGB888(
                                255,
                                -0.00000408 * K * K + 0.058 * K + 46.3,
                                K < 1600 ? 0 : -0.00000644 * K * K + 0.103 * K - 148.75);
                        }
                        else
                        {
                            return RGB888(
                                0.00000218 * K * K - 0.051f * K + 497.63,
                                0.0000013 * K * K - 0.031 * K + 402.43,
                                255);
                        }
                    }
                };

                template<>
                struct ColorCastImpl<RGBV8888, Kelvin, cast_policy::Fast>
                {
                    static RGBV8888 cast(const Kelvin& color)
                    {
                        return RGBV8888(ColorCastImpl<RGB888, Kelvin, cast_policy::Fast>::cast(color));
                    }
                };

                template<>
                struct ColorCastImpl<Wheel256, RGB888, cast_policy::Default>
                {
                    static RGB888 cast(const Wheel256& color)
                    {
                        uint8_t shift;

                        switch (color.wheel)
                        {
                            case 0 ... 85:
                                shift = color.wheel * 3;
                                return RGB888(255 - shift, shift, 0);
                                break;

                            case 86 ... 170:
                                shift = (color.wheel - 85) * 3;
                                return RGB888(0, 255 - shift, shift);
                                break;

                            case 171 ... 255:
                                shift = (color.wheel - 170) * 3;
                                return RGB888(shift, 0, 255 - shift);
                                break;
                        }

                    }
                };

                template<>
                struct ColorCastImpl<RGBV8888, Wheel256, cast_policy::Default>
                {
                    static RGBV8888 cast(const Wheel256& color)
                    {
                        return RGBV8888(ColorCastImpl<RGB888, Wheel256, cast_policy::Default>::cast(color));
                    }
                };

                template<>
                struct ColorCastImpl<Wheel1530, RGB888, cast_policy::Default>
                {
                    static RGB888 cast(const Wheel1530& color)
                    {
                        uint16_t col = color.wheel;
                        col = (col * 1530ul) >> 16;
                        switch (col)
                        {
                            case 0 ... 255: return RGB888(255, col, 0); break;
                            case 256 ... 510: return RGB888(510 - col, 255, 0); break;
                            case 511 ... 765: return RGB888(0, 255, col - 510); break;
                            case 766 ... 1020: return RGB888(0, 1020 - col, 255); break;
                            case 1021 ... 1275: return RGB888(col - 1020, 0, 255); break;
                            case 1276 ... 1530: return RGB888(255, 0, 1530 - col); break;
                        }
                    }
                };

                template<>
                struct ColorCastImpl<RGBV8888, Wheel1530, cast_policy::Default>
                {
                    static RGBV8888 cast(const Wheel1530& color)
                    {
                        return RGBV8888(ColorCastImpl<RGB888, Wheel1530, cast_policy::Default>::cast(color));
                    }
                };

                template<>
                struct ColorCastImpl<HSB888, Wheel256, cast_policy::Default>
                {
                    static HSB888 cast(const Wheel256& color)
                    {
                        return HSB888(color.wheel, 255, 255);
                    }
                };

                template<>
                struct ColorCastImpl<HSB888, Wheel1530, cast_policy::Default>
                {
                    static HSB888 cast(const Wheel1530& color)
                    {
                        return HSB888(color.wheel / 6, 255, 255);
                    }
                };

                template<>
                struct ColorCastImpl<HSBV8888, Wheel1530, cast_policy::Default>
                {
                    static HSBV8888 cast(const Wheel1530& color)
                    {
                        return HSBV8888(color.wheel / 6, 255, 255);
                    }
                };

                template<>
                struct ColorCastImpl<Wheel1530, Wheel256, cast_policy::Default>
                {
                    static Wheel1530 cast(const Wheel256& color)
                    {
                        return Wheel1530(color.wheel * 6);
                    }
                };

                template<>
                struct ColorCastImpl<Wheel256, Wheel1530, cast_policy::Default>
                {
                    static Wheel256 cast(const Wheel1530& color)
                    {
                        return Wheel256(color.wheel / 6);
                    }
                };

            } // namespace cast_impl

            /**
             * @brief Casts a color from one type to another.
             * @tparam T The target color type.
             * @tparam U The source color type.
             * @param color The source color to cast.
             * @return The casted color of type T.
             */
            template<class To, class From, typename Policy = cast_policy::Default>
            To color_cast(const From& color)
            {
                return cast_impl::ColorCastImpl<To, From, Policy>::cast(color);
            }
        }
    }
}

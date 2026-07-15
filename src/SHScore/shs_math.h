#pragma once

#include "shs_settings_private.h"

#if defined(SHS_SF_UNUSE_STL)
#include <math.h>
#else
#include <cmath>
#endif

namespace shs
{
    namespace math
    {
    #if defined(SHS_SF_UNUSE_STL)
        using ::abs;
        using ::acos;
        using ::acosh;
        using ::asin;
        using ::asinh;
        using ::atan;
        using ::atan2;
        using ::atanh;
        using ::cbrt;
        using ::ceil;
        using ::copysign;
        using ::cos;
        using ::cosh;
        using ::erf;
        using ::erfc;
        using ::exp;
        using ::exp2;
        using ::expm1;
        using ::fabs;
        using ::fdim;
        using ::floor;
        using ::fma;
        using ::fmax;
        using ::fmin;
        using ::fmod;
        using ::frexp;
        using ::hypot;
        using ::ilogb;
        using ::ldexp;
        using ::lgamma;
        using ::llrint;
        using ::llround;
        using ::log;
        using ::log1p;
        using ::log10;
        using ::log2;
        using ::logb;
        using ::lrint;
        using ::lround;
        using ::modf;
        using ::nearbyint;
        using ::nextafter;
        using ::nexttoward;
        using ::pow;
        using ::remainder;
        using ::remquo;
        using ::rint;
        using ::round;
        using ::scalbln;
        using ::scalbn;
        using ::sin;
        using ::sinh;
        using ::sqrt;
        using ::tan;
        using ::tanh;
        using ::tgamma;
        using ::trunc;
    #else
        using std::abs;
        using std::acos;
        using std::acosh;
        using std::asin;
        using std::asinh;
        using std::atan;
        using std::atan2;
        using std::atanh;
        using std::cbrt;
        using std::ceil;
        using std::copysign;
        using std::cos;
        using std::cosh;
        using std::erf;
        using std::erfc;
        using std::exp;
        using std::exp2;
        using std::expm1;
        using std::fabs;
        using std::fdim;
        using std::floor;
        using std::fma;
        using std::fmax;
        using std::fmin;
        using std::fmod;
        using std::frexp;
        using std::hypot;
        using std::ilogb;
        using std::ldexp;
        using std::lgamma;
        using std::llrint;
        using std::llround;
        using std::log;
        using std::log1p;
        using std::log10;
        using std::log2;
        using std::logb;
        using std::lrint;
        using std::lround;
        using std::modf;
        using std::nearbyint;
        using std::nextafter;
        using std::nexttoward;
        using std::pow;
        using std::remainder;
        using std::remquo;
        using std::rint;
        using std::round;
        using std::scalbln;
        using std::scalbn;
        using std::sin;
        using std::sinh;
        using std::sqrt;
        using std::tan;
        using std::tanh;
        using std::tgamma;
        using std::trunc;

        using std::fpclassify;
        using std::isfinite;
        using std::isinf;
        using std::isnan;
        using std::isnormal;
        using std::isgreater;
        using std::isgreaterequal;
        using std::isless;
        using std::islessequal;
        using std::islessgreater;
        using std::isunordered;

    #if defined(__cpp_lib_interpolate) || (__cplusplus >= 202002L)
        using std::lerp;
    #endif

    #endif

    }
}

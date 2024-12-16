#pragma once


/*
    The idea and code are taken from Alex Gyver's project:
    https://github.com/AlexGyver/ColorMusicRGB
*/


#include <VolAnalyzer.h>  // https://github.com/GyverLibs/VolAnalyzer
#include <GRGB.h>         // https://github.com/GyverLibs/GRGB

#include <shs_Process.h>


namespace shs
{
    class RGBmusic;
}


class shs::RGBmusic : public shs::Process
{
public:
    enum Effects : uint8_t { OFF, SHIFT_151, SHIFT_129, PULSE_WHEEL, FIRE }
    effect;

    VolAnalyzer analyzer;
    GRGB& grgb;

    RGBmusic(GRGB& set_grgb, const int8_t port = -1) : grgb(set_grgb), analyzer(port) {}

    void setEffect(const Effects eff) { effect = eff; }

    void start() override { grgb.setFade(false); }

    void tick() override
    {
        switch (effect)
        {
            case OFF: break;
            case SHIFT_151:
                if (analyzer.getPulse()) color += 151;
                led.setWheel8(color, analyzer.getVol());
                break;
            case SHIFT_129:
                if (analyzer.getPulse()) color += 129;
                led.setWheel8(color, analyzer.getVol());
                break;
            case PULSE_WHEEL:
                led.setWheel8(color++, analyzer.getVol());
                break;
            case FIRE:
                led.setHSVfast((analyzer.getVol() - 10) / 6, 255, analyzer.getVol());
                break;
            default: break;
        }
    }

    void stop() override { mode = OFF; grgb.setRGB(0, 0, 0); }

};

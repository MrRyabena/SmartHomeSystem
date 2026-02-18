#pragma once


/*
    The idea and code are taken from Alex Gyver's project:
    https://github.com/AlexGyver/ColorMusicRGB
*/

#include <Arduino.h>

#include <VolAnalyzer.h>  // https://github.com/GyverLibs/VolAnalyzer
#include <GRGB.h>         // https://github.com/GyverLibs/GRGB

#include <shs_Process.h>
#include <shs_debug.h>


namespace shs
{
    class RGBmusic;
}

class shs::RGBmusic : public shs::Process
{
public:
    enum Effects : uint8_t { OFF, SHIFT_151, SHIFT_129, PULSE_WHEEL, FIRE };

    VolAnalyzer analyzer;
    GRGB& grgb;

    RGBmusic(GRGB& set_grgb, const int8_t port = -1, uint8_t min_bright = 0)
        : grgb(set_grgb), analyzer(port), m_min_bright(min_bright)
    {}

    void setEffect(const Effects eff) { doutln("set music effect"); m_effect = eff; if (m_effect == OFF) stop(); }
    Effects getEffect() const { return m_effect; }

    void setMinBright(const uint8_t br) { m_min_bright = br; }
    uint8_t getMinBright() const { return m_min_bright; }

    void start() override { grgb.fadeMode(false); }

    void tick() override
    {
        if (m_effect == OFF) return;
        if (!analyzer.tick()) return;

        // Serial.print(analyzer.pulse() * 20); // скачок громкости
        // Serial.print(',');
        // Serial.print(analyzer.getVol());    // громкость 0-100
        // Serial.print(',');
        // Serial.print(analyzer.getRaw());    // сырая величина
        // Serial.print(',');
        // Serial.println(analyzer.getMax());  // амплитудная огибающая

        switch (m_effect)
        {
            case SHIFT_151:
                if (analyzer.pulse()) m_color += 151;
                grgb.setWheel8(m_color, m_min_bright + analyzer.getVol() >= 255 ? 255 : m_min_bright + analyzer.getVol());
                break;
            case SHIFT_129:
                if (analyzer.getPulse()) m_color += 129;
                grgb.setWheel8(m_color, m_min_bright + analyzer.getVol() >= 255 ? 255 : m_min_bright + analyzer.getVol());
                break;
            case PULSE_WHEEL:
                grgb.setWheel8(m_color++, m_min_bright + analyzer.getVol() >= 255 ? 255 : m_min_bright + analyzer.getVol());
                break;
            case FIRE:
                grgb.setHSVfast((analyzer.getVol() - 10) / 6, 255, m_min_bright + analyzer.getVol() >= 255 ? 255 : m_min_bright + analyzer.getVol());
                break;
            default: break;
        }
    }

    void stop() override { m_effect = OFF; grgb.setRGB(0, 0, 0); }

protected:
    uint8_t m_color{};
    uint8_t m_min_bright{};
    Effects m_effect{};

};

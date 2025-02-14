#pragma once


#include <VolAnalyzer.h>  // https://github.com/GyverLibs/VolAnalyzer
#include <GRGB.h>         // https://github.com/GyverLibs/GRGB
#include <GyverDS18.h>  // https://github.com/GyverLibs/GyverDS18

#include <shsL_GRGB_API.h>
#include <shsL_RGBmusic.h>

#include <shs_Sensor.h>
#include <shs_Process.h>


namespace shs
{
    class SmartSpot;
}


class shs::SmartSpot : public shs::Process
{
public:
    static constexpr uint8_t MIN_TEMP = 30;
    static constexpr uint8_t MAX_TEMP = 45;
    static constexpr uint8_t MIN_POWER = 100;
    static constexpr uint8_t MAX_POWER = 255;


    GRGB chip;
    shs::RGBmusic rgb_music;
    //shs::Sensor& temp_sensor;
    GyverDS18Single temp_sensor;


    explicit SmartSpot
    (
        //shs::Sensor& set_temp_sensor, 
        const uint8_t temp_sensor_pin, const uint8_t fan_pin, const uint8_t music_pin = -1,
        const uint8_t dir = COMMON_CATHODE, const uint8_t pinR = 0, const uint8_t pinG = 0, const uint8_t pinB = 0, const uint8_t shift = 0,
        )
        : chip(dir, pinR, pinG, pinB, shift), temp_sensor(temp_sensor_pin), rgb_music(chip, music_pin)
    {}

    uint8_t getFanPower() const { return m_fanPower; }
    int16_t getTempInt() const { return m_temp; }

    void temperatureControl()  // temporarily, it will be replaced later by shs::Load
    {
        if (millis() - m_tmr >= 4000)
        {
            if (temp_sensor.ready() && temp_sensor.readTemp())
            {
                m_temp = temp_sensor.getTempInt();
                m_fanPower = map(int(temp), MIN_TEMP, MAX_TEMP, MIN_POWER, MAX_POWER);
            }
            else m_fanPower = 128;

            if (!temp_sensor.isWaiting()) temp_sensor.request();

            analogWrite(fen_p, fanPower);

            m_tmr = millis();
        }
    }

    // shs::Process
    void start() override { temp_sensor.setup(); rgb_music.start(); temperatureControl(); }
    void tick() override { chip.tick(); rgb_music.tick(); }
    void stop() override {}


private:
    // temporarily, it will be replaced later by shs::Load
    const uint32_t tmr{};
    const uint8_t m_fan_pin;
    uint8_t m_fanPower;
    int16_t m_temp{};
};

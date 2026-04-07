#pragma once

#include <functional>

#include <shs_types.h>

class CRGB;

namespace shs
{
    class ProgramTimer;

    namespace argb
    {
        class Effect;

        class RingLoad;
    }
}


class shs::argb::RingLoad : public shs::argb::Effect
{
public:
    explicit RingLoad(CRGB* leds, uint16_t num_leds, std::function<void()> on_change_callback);

    void start() override;
    void tick() override;
    void stop() override;

    void setColor(const CRGB& color) { m_color = color; }       

protected:
    CRGB m_color;
    shs::t::shs_time_t m_period;
    shs::t::shs_time_t m_time;
    shs::ProgramTimer m_rotation_timer;

    float m_a;
    float m_w;
    

    uint16_t m_start_led;
    uint16_t m_end_led;
    uint16_t m_frame_size;

    void m_calculate_a();
    void m_fillRing(uint16_t start_pos, uint16_t end_pos, CRGB color);
    shs::t::shs_time_t m_getTime() const;

};

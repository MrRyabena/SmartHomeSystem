#pragma once

#include <FastBot.h>

namespace shs
{
    inline void updateRun();
    inline void _update_newMes(FB_msg &message);
    FastBot _update_bot(UPBOT_TOKEN);
    inline uint8_t _update_ID{};
};

void shs::updateRun()
{
    shs::_update_bot.attach(shs::_update_newMes);
    for (;;)
    {
        shs::_update_bot.tick();
        yield();
    }
}

void shs::_update_newMes(FB_msg &message)
{
    if (message.OTA && message.text.toInt() == shs::_update_ID)
    {
        if (message.fileName.indexOf("mklittlefs") > 0 || message.fileName.indexOf("spiffs") > 0)
        {
            shs::_update_bot.updateFS(); // update spiffs
        }
        else
        {
            shs::_update_bot.update(); // update sketch
        }
    }
}

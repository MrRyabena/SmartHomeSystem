#pragma once

#include <FastBot.h>

namespace shs
{
    void updateRun();
    FastBot *_update_bot{};
    void _update_newMes(FB_msg &message);
};

void shs::updateRun()
{
    _update_bot = new FastBot(UPBOT_TOKEN);
    shs::_update_bot->attach(shs::_update_newMes);
    uint32_t tmr = millis();
    for (;;)
    {
        shs::_update_bot->tick();
        yield();
        if (millis() - tmr >= 60000)
            break;
    }
    _update_bot->sendmessage("")
}

void shs::_update_newMes(FB_msg &message)
{
    if (message.OTA && message.text.toInt() == shs::_update_ID)
    {
        if (message.fileName.indexOf("mklittlefs") > 0 || message.fileName.indexOf("spiffs") > 0)
        {
            shs::_update_bot->updateFS(); // update spiffs
        }
        else
        {
            shs::_update_bot->update(); // update sketch
        }
    } 
    _update_bot->sendmessage("Error! Invalid ID", message.chatID);
}

#include "SHSupdate.h"

shs::Update::Update()
{
}

shs::Update::~Update()
{
}

void shs::Update::start(const uint32_t timeout, const bool resturt)
{
    FastBot *upbot = new FastBot(UPBOT_TOKEN);
    upbot.attach(_newMes);
    uint32_t tmr = millis();
    for (;;)
    {
        upbot.tick();
        yield();
        if (millis() - tmr >= timeout)
            break;
    }
    // upbot.sendMessage();
    delete upbot;

    if (resturt)
        ESP.resturt();
}

void shs::Update::setHandler(void (*handler)(FB_msg &message))
{
    _handler = handler;
}

void shs::Update::_newMes(FB_msg &message)
{
    if (_handler)
        _handler(message);

    if (message.OTA && message.text.toInt() == shs::_update_ID)
    {
        if (message.fileName.indexOf("mklittlefs") > 0 || message.fileName.indexOf("spiffs") > 0)
        {
            upbot->updateFS(); // update spiffs
        }
        else
        {
            upbot->update(); // update sketch
        }
    }
    upbot->sendmessage("Error! Invalid ID", message.chatID);
}

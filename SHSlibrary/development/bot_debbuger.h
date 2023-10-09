#pragma once
//#include "devsettings.h"

#include <FastBot.h>

class BotDebbuger {
public:

    BotDebbuger() {
        
    }

    template <typename T>
    void send(T& data) {
        String str;
        uint8_t* ptr = (uint8_t*)&data;

        for (uint8_t i = 0; i < sizeof(T); i++) str += static_cast<char>(*ptr++);
        _bot.sendMessage(str, _CHAT_ID);
    }

    void tick() {
        _bot.tick();
    }

    void newMsg(FB_msg& msg);


    
private:

    const char* _BOT_TOKEN = "6140197158:AAEK_E40LiN3GOoFZ31ACaDy5ouHofuTcV8";
    const char* _CHAT_ID = "438901860";
    FastBot _bot{_BOT_TOKEN};
};

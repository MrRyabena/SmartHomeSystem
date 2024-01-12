#pragma once
#include "SHSsettings.h"
#include <FastBot.h>

namespace shs
{
    class Update;
};

class shs::Update
{
public:
    Update();
    ~Update();

    void start(const uint32_t timeout = 120000, const bool resturt = true);
    void setHandler(void (*handler)(FB_msg &message));

private:
    void _newMes(FB_msg &message);
    void (*_handler)(FB_msg &message, FastBot &upbot) = nullptr;
};


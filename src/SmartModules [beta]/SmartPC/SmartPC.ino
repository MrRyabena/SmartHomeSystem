#include <shs_ControlWiFi.h>
#include <SHSsettings.h>
#include "presets.h"

bool PCstatus();
void PCswitch();
void controlStatus();

void setup()
{
    pinMode(POWER_SWITCH_pin, OUTPUT);
    digitalWrite(POWER_SWITCH_pin, 0);

    pinMode(POWER_LED_pin, INPUT);

    shs::ControlWiFi::configureWiFi();
    shs::ControlWiFi::connectWiFiWait();
}

void loop()
{
    telegramBot();
    controlStatus();
}

bool PCstatus() { return !digitalRead(POWER_LED_pin); }

void PCswitch()
{
    digitalWrite(POWER_SWITCH_pin, 1);
    delay(200);
    digitalWrite(POWER_SWITCH_pin, 0);
}

void controlStatus()
{
    static bool status = PCstatus();

    if (status != PCstatus())
    {
        status = !status;
        String str = "PC status changed: ";
        str += status;
        str += '!';

        botSendNotification(str);
    }
}

/**
 * @file blink.cpp
 * @brief Example of a simple blinking LED.
 *
 * shs::LoadSwitch or shs::LoadSwitchReversed is used to control the LED, depending on the platform.
 * The LED is toggled on and off every second using shs::ProgramTimer.
 *
 * @note See the shs_Load.h for the Load API and shs_ProgramTimer.h for the timer API.
 */

#include <shs_settings_private.h>
#include <shs_ProgramTimer.h>

#ifndef SHS_SF_ESP
#include <shs_LoadSwitchReversed.h>
using LoadType = shs::LoadSwitchReversed;
#else
#include <shs_LoadSwitch.h>
using LoadType = shs::LoadSwitch;
#endif

LoadType blink(LED_BUILTIN);
shs::ProgramTimer timer(1000);

void setup()
{
    blink.setup();
}

void loop()
{
    if (timer.check())
    {
        blink.on(!static_cast<bool>(blink.getValue()));
    }
}

/**
 * @file ControlWiFi.ino
 * @brief Example of WiFi connection control using the shs::ControlWiFi class.
 * @note Make sure that you add WiFi SSID and password to the shs_settings.h or
 * compile definitions in CMake or PlatformIO. See this gyide for more details:
 * https://github.com/MrRyabena/SmartHomeSystem/blob/main/SHSdocumentation/Usage/build_manual.md
 */

#include <shs_ControlWiFi.h>
#include <shs_debug.h>


void setup()
{
    dinit();

    /*
    If you don't want to set the WiFi SSID and password during the compile definitions,
    you can call the connectWiFi() function with the SSID and password as parameters:
        shs::ControlWiFi::connectWiFi("YourSSID", "YourPassword");
    or
        shs::ControlWiFi::connectWiFiWait(timeout, "YourSSID", "YourPassword");
        where timeout is the maximum time to wait for the connection in milliseconds.
    But it's recommended to set them in the compile definitions for security reasons.

    If you need to use non-blocking WiFi connection, you can use the connectWiFi() function without 
    waiting for the connection to complete.
    */

    if (shs::ControlWiFi::connectWiFiWait()) doutln("WiFi successfully conneted.");
    else                                     doutln("WiFi connection error!");

    dout("Local IP: "); doutln(shs::ControlWiFi::getLocalIP().toString());
}


void loop()
{

}

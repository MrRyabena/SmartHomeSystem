#include <shs_ControlWiFi.h>
#include <shs_debug.h>


void setup()
{
    dinit();

    if (shs::ControlWiFi::connectWiFiWait()) doutln("WiFi successfully conneted.");
    else                                     doutln("WiFi connection error!");
    shs::ControlWiFi::localIP();
}


void loop()
{

}

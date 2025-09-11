#include <shs_ControlWiFi.h>
#define DEBUG
#define SHS_SF_DEBUG
#include <shs_debug.h>

void setup()
{
    dinit();
    shs::ControlWiFi::connectWiFiMulti();

    delay(2000);
    if (WiFi.status() == WL_CONNECTED) { 
        dsep();
        doutln("WiFi connected!"); 
        doutln(WiFi.SSID());
        doutln(WiFi.localIP());
        dsep();
        }
    else { doutln("Connection faild!"); }

}

void loop() {}

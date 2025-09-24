
#define SHS_SF_DEBUG
#include <shs_debug.h>

#include <shs_ControlWiFi.h>
#include <shs_DTPdiscover.h>
#include <shs_ProgramTimer.h>
#include <shs_types.h>


shs::DTPdiscover discover(shs::t::shs_ID_t(0));
shs::ProgramTimer timer(5000);

void setup()
{
    dinit();

    shs::ControlWiFi::connectWiFiMulti();
    dout("WiFi connected: "); 
    doutln(shs::ControlWiFi::WiFiConnected());

    discover.start();


}

void loop()
{
    discover.discoverAll();
    delay(500);
    

    while (!timer.check()) 
    {
        discover.tick();
        delay(50);
    }

    discover.printAllDiscovered();
}

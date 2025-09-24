
#define SHS_SF_DEBUG
#include <shs_debug.h>

#include <shs_ControlWiFi.h>
#include <shs_DTPdiscover.h>
#include <shs_ProgramTimer.h>
#include <shs_types.h>



shs::DTPdiscover discover(shs::t::shs_ID_t(0));
void setup()
{
    dinit();

    shs::ControlWiFi::connectWiFiMulti();
    dout("WiFi connected: "); doutln(shs::ControlWiFi::WiFiConnected());

    
}

void loop()
{

}

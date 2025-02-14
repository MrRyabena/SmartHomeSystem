#include "settings.h"

#include <memory>

#include <shs_DTP.h>
#include <shs_ControlWiFi.h>
#include <shs_TcpSocket.h>

#include <shsD_SmartSpot.h>

#include <shsD_SmartSpot_API.h>
#include <shsL_GRGB_API.h>
#include <shs_Sensor_API.h>
#include <shs_ID.h>


shs::DTP dtp(MODULE_ID);

shs::SmartSpot sspot(TEMP_SENS_PIN, FANp, MUSICp, COMMON_CATHODE, Rp, Gp, Bp);


void setup()
{
    shs::ControlWiFi::connectWiFiWait();
    sspot.start();

    dtp.attachAPI(std::make_unique<shs::SmartSpot_API>(sspot, shs::ID(MODULE_ID, 1, 1)));
    dtp.attachAPI(std::make_unique<shs::GRGB_API>(sspot.chip, shs::ID(MODULE_ID, 1, 2)));

    dtp.attachBus(std::make_unique<shs::TcpSocket>(SERVER_IP, PORT));
}


void loop()
{
    sspot.tick();
    dtp.tick();
}

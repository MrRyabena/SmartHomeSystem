#include <gs_config.h>

#include <memory>
#include <shs_debug.h>

#include <shs_Network.hpp>
#include <shs_DTP.hpp>

#include <shs_Sensor.hpp>

shs::SensorAnalog temp_sensor(A0);


shs::DTP dtp(shs::config::Module_1::MODULE_ID);
shs::TcpServer server(shs::settings::DEFAULT_TCP_PORT, dtp);
shs::DTPdiscover discover(shs::config::Module_1::MODULE_ID);


void setup()
{
    dinit();
    shs::ControlWiFi::connectWiFiWait();

    dtp.attachAPI(std::make_unique<shs::Sensor_API>(temp_sensor, shs::t::shs_ID_t(shs::config::Module_1::MODULE_ID, shs::config::Module_1::DevicesIDs::THERM_SENSOR), dtp));

    dtp.start();
    server.start();
    discover.start();
}


void loop()
{
    dtp.tick();
    server.tick();
    discover.tick();
}

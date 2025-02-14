#include <shs_ControlWiFi.h>
#include <shs_DTP.h>
#include <shs_SensorAnalog.h>
#include <shs_Sensor_API.h>
#include <shs_ID.h>
#include <shs_IP.h>
#include <shs_types.h>
#include <shs_TcpServer.h>



constexpr shs::t::shs_ID_t THIS_ID(14, 0, 0);

shs::DTP dtp(THIS_ID);
shs::TcpServer server(5000, dtp);

shs::SensorAnalog sensor(A0);

void setup() {
  Serial.begin(115200);

  shs::ControlWiFi::setHostname("Load_Test");
  shs::ControlWiFi::connectWiFiWait();

  server.start();
  sensor.setup();
  dtp.attachAPI(std::make_unique<shs::Sensor_API>(sensor, shs::t::shs_ID_t(THIS_ID.getModuleID(), 1), dtp));
}

void loop() {
  dtp.tick();
  server.tick();
}

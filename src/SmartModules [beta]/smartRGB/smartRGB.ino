#include "settings.h"


#include <shs_ControlWiFi.h>

#include <FastBot.h>
FastBot bot(BOT_TOCKEN);

#include <GRGB.h>
GRGB strip(COMMON_CATHODE, Rp, Gp, Bp);

#include <shs_DTP.h>
#include <shsL_GRGB_API.h>
#include <shs_ByteCollector.h>
#include <shs_ByteCollectorIterator.h>
#include <ESP8266WiFi.h>
#include <shs_TcpClient.h>

shs::TcpClient client(S_IP, PORT, THIS_ID);
shs::GRGB_API grgb_api(strip, THIS_ID);
shs::DTP dtp(client, grgb_api, THIS_ID);

void setup() {
  shs::ControlWiFi::connectWiFiWait();

  botSetup();

  analogWriteResolution(8);

  //analogWriteFreq(10000);

  //pinMode(D4, OUTPUT);
}


void loop() {
  bot.tick();
  RGB();
  strip.tick();

  if (client.connected()) dtp.tick();
  else if (client.connect(SERVER_IP, PORT)) client.write(&THIS_ID - 1, 2);
}

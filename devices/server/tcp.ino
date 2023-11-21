#define MAX_WIFICLIENTS 4

WiFiServer server(80);
WiFiClient clients[MAX_WIFICLIENTS];

void setupTCP() {
  server.begin();
  server.setNoDelay(true);
}

void handleTCP() {

  uint8_t i{};
  static uint8_t lens[MAX_WIFICLIENTS]{};

  if (server.hasClient()) {
    for (i = 0; i < MAX_WIFICLIENTS; i++) {
      if (!clients[i] || !clients[i].connected()) {
        if (clients[i])
          clients[i].stop();
        clients[i] = server.available();
        continue;
      }
    }
    WiFiClient client = server.available();
    client.stop();
  }

  for (i = 0; i < MAX_WIFICLIENTS; i++) {
    if (clients[i] && clients[i].connected()) {
      if (clients[i].available()) {
        if (lens[i]) {
          if (clients[i].available() < lens[i]) continue;
          shs::ByteCollector col(lens[i]);
          col.buf[0] = lens[i];
          clients[i].read(&col.buf[1], col.buf[0] - 1);
          lens[i] = 0;
        }        
      }
    }
  }
}



void sendTCP(shs::ByteCollector* col, uint8_t id) {
  String str = F("192.168.1.");
  str += id;
  for (i  = 0; i < MAX_WIFICLIENTS; i++) {
    if (clients[i].remoteIP().equal(str)) {
      dtp.packDTP(col, id);
      clients[i].write(col.buf, col.buf[0]);
    }
  }
}
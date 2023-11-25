

shs::DTP dtp(0);

void setupTCP() {
  server.begin();
  server.setNoDelay(true);
}

void handleTCP() {

  //static uint8_t clients[MAX_WIFICLIENTS]{};
  uint8_t i{};

  if (server.hasClient()) {
    for (i = 0; i < MAX_WIFICLIENTS; i++) {
      if (!clients[i] || (clients[i] && clients[i].connected())) {
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



uint8_t sendTCP(shs::ByteCollector* col, uint8_t id) {
  for (uint8_t i = 0; i < MAX_WIFICLIENTS; i++) {
    if (clients[i].remoteIP()[3] == id) {
      dtp.packDTP(col, id);
      clients[i].write(col->buf, col->buf[0]);
      return 0;
    }
  }
  return 1;
}

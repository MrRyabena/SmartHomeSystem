#define MAX_WIFICLIENTS 4

WiFiServer server(80);
WiFiClient clients[MAX_WIFICLIENTS];

void setupTCP() {
  server.begin();
  server.setNoDelay(true);
}

void handleTCP() {

  uint8_t i{};

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
        while (clients[i].available()) {
          // parsing client
          clients[i].read();
        }
      }
    }
  }
}
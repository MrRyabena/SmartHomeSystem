
#define DEBUG
#include <settings.h>
#include <SHSlibrary.h>

WiFiServer server(80);


void setup() {
#ifdef DEBUG
  Serial.begin(115200);
#endif
  connectWiFi();
  server.begin();
}


void loop() {
  handleClient();
}


void handleClient() {
  WiFiClient client = server.available();
  if (client) {
    while (client) {
      while (client.available() > 0) {
        char c = client.read();
        Serial.print(c);
      }
      // delay(10);
      // answer
      client.println("I am glad to see you too!");
    }
  }
  client.stop();
}
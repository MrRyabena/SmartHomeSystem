void handleBus() {
  bus.tick();


  if (bus.gotData()) {
    uint8_t buf[BUSbufsize];
    bus.readData(buf);




    switch (buf[0]) {
      case started:
        {
          uint8_t buf[BUSbufsize]{};
          buf[0] = static_cast<uint8_t>(started);
          bus.sendData(LIGHTER_ID, buf);
          bot.send("started!");
        }
        break;
      case outAnalogAverage:
        {
          float val{};
          unpackBytes(&(buf[1]), val);
          bot.send(val);
        }
        break;
    }
    String str = "[0]";
    str += buf[0];
    str += "\n";

    str += "[1]";
    str += buf[1];
    str += "\n";
    str += "[2]";
    str += buf[2];
    str += "\n";
    str += "[3]";
    str += buf[3];
    str += "\n";
    str += "[4]";
    str += buf[4];
    str += "\n";
    str += "[5]";
    str += buf[5];
    str += "\n";
    bot.send(str);
  }
  static uint32_t tmr{};
  if (millis() - tmr >= 5000) {
    uint8_t buf[BUSbufsize]{};
    buf[0] = static_cast<uint8_t>(getAnalogAverageVal);
    bus.sendData(LIGHTER_ID, buf);

    tmr = millis();
  }
}
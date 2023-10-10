void handleBus() {
  bus.tick();


  if (bus.gotData()) {
    uint8_t buf[BUSbufsize]{};
    bus.readData(buf);


    switch (buf[0]) {
      case started: settings.flag = true; break;
      case setMode: settings.mode = buf[1]; break;
      case analogSetPin:
        analogWrite(buf[1], buf[2]);
        switch (buf[1]) {
          case BRARpin: settings.braRval = buf[2]; break;
          case BRALpin: settings.braLval = buf[2]; break;
          case BULBpin: settings.bulbval = buf[2]; break;
        }
        break;
      case digitalSetPin: digitalWrite(buf[1], buf[2]); break;
      case getAnalogAverageVal:
        {
          ByteCollector col(BUSbufsize);
          float f = 1.2;
          col.add(f);
          // col.addVal(outAnalogAverage);
          // col.addVal(getAnalogAverage(A0));
          uint8_t buf[BUSbufsize];
          float a = 25.6;
          buf[0] = outAnalogAverage;
          packBytes(&(buf[1]), a);
          bus.sendData(TABLE_ID, buf);
        }
        break;
    }
  }

  static uint32_t tmr{};
  if (!settings.flag && millis() - tmr >= 1000) {
    uint8_t buf[BUSbufsize]{};
    buf[0] = static_cast<uint8_t>(started);
    bus.sendData(TABLE_ID, buf);
    tmr = millis();
  }
}

void handleBus() {

  using lapi = LighterAPI::API;
  bus.tick();


  if (bus.gotData()) {
    uint8_t buf[BUSbufsize]{};
    bus.readData(buf);


    /*
+  started,
+  request,
  answer,
  
+  setMode,

+  analogSetPin,
+  digitalSetPin,
  
+  getAnalogVal,
+  getAnalogAverageVal,
  getDigitalVal,
  setK,

  setSettings,
  getSettigns,

  getValue,
  outAnalogAverage,
  */

    switch (buf[0]) {
      case lapi::started: settings.flag = true; break;
      case lapi::request:
        {
          uint8_t answ = static_cast<uint8_t>(lapi::answer);
          bus.sendData(TABLE_ID, answ);
        }
        break;

      case lapi::setMode: settings.mode = buf[1]; break;

      case lapi::analogSetPin:
        {
          for (uint8_t i = 0; i < buf[1] << 1; i += 2) {

            analogWrite(buf[2 + i], buf[3 + i]);
            switch (buf[2 + i]) {
              case BRARpin: settings.braRval = buf[3 + i]; break;
              case BRALpin: settings.braLval = buf[3 + i]; break;
              case BULBpin: settings.bulbval = buf[3 + i]; break;
            }
          }
        }
        break;

      case lapi::digitalSetPin:
        {
          for (uint8_t i = 0; i < buf[1] << 1; i += 2)
            digitalWrite(buf[2 + i], buf[3 + i]);
        }
        break;


      case lapi::getAnalogVal:
        {
          ByteCollector col(1 + 1 + buf[1] * (1 + 2));
          col.addVal(lapi::outAnalogVal);
          col.add(buf[1]);

          for (uint8_t i = 0; i < buf[1]; i++) {
            col.add(buf[2 + i]);
            col.addVal<uint16_t>(analogRead(buf[2 + i]), 2);
          }
          dtp.sendBuf(TABLE_ID, col.buf, col.size());
        }
        break;
      case lapi::getAnalogAverageVal:
        {
          ByteCollector col(1 + 1 + buf[1] * (1 + sizeof(float)));
          col.addVal(lapi::outAnalogAverage);
          col.add(buf[1]);

          for (uint8_t i = 0; i < buf[1]; i++) {
            col.add(buf[2 + i]);
            col.addVal<float>(getAnalogAverage(buf[2 + i]));
          }
          dtp.sendBuf(TABLE_ID, col.buf, col.size());
        }
        break;

      case lapi::getRPM:
        {
          ByteCollector col(1 + 2);
          col.addVal(lapi::outRPM);
          col.addVal(tach.getRPM(), 2);

          dtp.sendBuf(TABLE_ID, col.buf, col.size());
        }
        break;

      case lapi::getSettings:
        {
          ByteCollector col(1 + sizeof(LighterAPI::Settings));
          col.addVal(lapi::outSettings);
          col.add(settings);

          dtp.sendBuf(TABLE_ID, col.buf, col.size());
        }
        break;

      case lapi::setSettings:
        {
          unpackBytes(&buf[1], settings);
        }
        break;
    }
  }

  static uint32_t tmr{};
  if (!settings.flag && millis() - tmr >= 1000) {
    ByteCollector col(1);
    col.add(lapi::started);
    dtp.sendBuf(TABLE_ID, col.buf, col.size());
    tmr = millis();
  }
}

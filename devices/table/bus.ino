#define lapi LighterAPI::API



void handleBus() {

  bus.tick();


  if (bus.gotData()) {
    uint8_t buf[BUSbufsize];
    bus.readData(buf);




    switch (buf[0]) {
      case lapi::started:
        {
          ByteCollector col(1);
          col.add(lapi::started);
          dtp.sendBuf(LIGHTER_ID, col.buf, col.size());
        }
        break;
      case lapi::outAnalogAverage:
        {
          float t;
          unpackBytes(&buf[2], t);
          String str = "Temp: ";
          str += t;
          bot.sendMessage(str, CHAT_ID);
        }
        break;
      case lapi::outSettings:
        {
          LighterAPI::Settings sts;
          unpackBytes(&buf[1], sts);
          String str = "PWM: ";
          str += sts.pwm;
          bot.sendMessage(str, CHAT_ID);
        }
        break;
      case lapi::outRPM:
        {
          uint16_t val{};
          unpackBytes(&buf[1], val);
          String str = "RPM: ";
          str += val;
          bot.sendMessage(str, CHAT_ID);
        }
        break;

    }
  }
}


void setBraR(uint8_t value) {
  ByteCollector col(4);

  col.add(lapi::analogSetPin, 1);
  col.add<uint8_t>(1, 1);
  col.add(BRARpin, 1);
  col.add(value, 1);

  dtp.sendBuf(LIGHTER_ID, col.buf, col.size());
}

void setBraL(uint8_t value) {
  ByteCollector col(4);

  col.add(lapi::analogSetPin, 1);
  col.add<uint8_t>(1, 1);
  col.add(BRALpin, 1);
  col.add(value, 1);

  dtp.sendBuf(LIGHTER_ID, col.buf, col.size());
}

void setBra(uint8_t value) {
  ByteCollector col(6);
  col.add(lapi::analogSetPin, 1);
  col.add<uint8_t>(2, 1);
  col.add(BRALpin, 1);
  col.add(value, 1);
  col.add(BRARpin, 1);
  col.add(value, 1);
}

void getT() {
  ByteCollector col(3);

  col.add(lapi::getAnalogAverageVal, 1);
  col.add<uint8_t>(1, 1);
  col.add(0, 1);
  dtp.sendBuf(LIGHTER_ID, col.buf, col.size());
}


void getPWM() {
  ByteCollector col(1);

  col.add(lapi::getSettings, 1);
  dtp.sendBuf(LIGHTER_ID, col.buf, col.size());
}


void getRPM() {
  ByteCollector col(1);

  col.add(lapi::getRPM, 1);
  dtp.sendBuf(LIGHTER_ID, col.buf, col.size());
}

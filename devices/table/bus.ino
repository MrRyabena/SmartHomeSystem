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
        }
        break;
    }
  }
}


void setBraR(uint8_t value) {
  ByteCollector col(4);

  col.addVal(lapi::analogSetPin, 1);
  col.addVal<uint8_t>(1, 1);
  col.addVal(BRARpin, 1);
  col.add(value, 1);

  dtp.sendBuf(LIGHTER_ID, col.buf, col.size());
}

void setBraL(uint8_t value) {
  ByteCollector col(4);

  col.addVal(lapi::analogSetPin, 1);
  col.addVal<uint8_t>(1, 1);
  col.addVal(BRALpin, 1);
  col.add(value, 1);

  dtp.sendBuf(LIGHTER_ID, col.buf, col.size());
}

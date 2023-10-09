void handleBus(uint8_t* buf) {
  bus.tick();


  if (bus.gotData()) {
    uint8_t buf[BUSbufsize]{};


    switch (buf[0]) {
      case setMode: settings.mode = buf[1]; break;

      case analogSetPin: analogWrite(buf[1], buf[2]); break;
      case digitalSetPin: digitalWrite(buf[1], buf[2]); break;
      case getAnalogVal:
        {
          ByteCollector col(10);
          col.addVal(outAnalogAverage);
          col.addVal(getAnalogAverage(A0));
        }
        break;
    }
  }
}

uint8_t APIhandler::handler(shs::ByteCollector &bc)
{
  shs::DTPpacker parser;
  shs::DTPdata data;

  parser.parseDTP(&bc, data);

  Serial.print("Message form: ");
  Serial.println(data.from);
  Serial.print("Message apiID: ");
  Serial.println(data.apiID);
  Serial.print("Message to: ");
  Serial.println(data.to);
  Serial.println();

  switch (data.from) {
    case shs::settings::SmartThermID:
    {
      uint8_t value = server.sendRAW(bc.buf, bc.buf[0], shs::settings::appID);
      Serial.println(value);
    }
      break;
    case shs::settings::appID:
      {
        switch (data.apiID) {
          case shs::settings::SmartThermID:
            server.sendRAW(bc.buf, bc.buf[0], shs::settings::SmartThermID);
            break;
        }
      }
  }

  return 0;
}
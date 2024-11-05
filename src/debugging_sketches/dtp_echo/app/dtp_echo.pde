import processing.net.*;

Server server;
Client client;

long tmr;
void tickServer()
{
  Client cl = server.available();


  if (client == null && cl != null)
  {
    print("new client!  ");
    println(cl.ip());
    client = cl;
  }
  if (client != null && client.active())
  {
    if (client.available() > 0) {
      byte inp[] = client.readBytes();
      println(inp);
    }


    if (millis() - tmr >= 10000)
    {
      byte [] buf = new byte[16];
      buf[0] = 16;
      buf[1] = 1;   
      buf[2] = 0;
      buf[3] = 0;
      buf[4] = 0;
      buf[5] = 10;
      buf[6] = 0;
      buf[7] = 0;
      buf[8] = 0;
      buf[9] = 12;
      buf[10] = 'H';
      buf[11] = 'e';
      buf[12] = 'l';
      buf[13] = 'l';
      buf[14] = 'o';
      buf[15] |= 0xff;

      client.write(buf);
      println("sended");

      tmr = millis();
    }
  }
}


void setup()
{
  server = new Server(this, 5000);
  println(server.ip());
}

void draw()
{
  tickServer();
}

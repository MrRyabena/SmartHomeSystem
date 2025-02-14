import hypermedia.net.*;

import processing.net.*;

Server server;
Client client;

//UDP udp;

long tmr1;
void sendAll()
{
   if (millis() - tmr1 > 5000) {
    for (int i = 2; i < 255; i++) {
      String ipAddress = String.format("192.168.1.%d", i); // Формируем IP-адрес
      Client cl = new Client(this, ipAddress, 5000); // Создаем новый клиент

      if (cl.active()) { // Проверяем, подключен ли клиент
        sendInit(cl); // Отправляем инициализацию
        cl.stop(); // Закрываем соединение
      } else {
        println("Failed to connect to: " + ipAddress); // Выводим сообщение об ошибке
      }
    }
    println("Sended!");
    tmr1 = millis(); // Обновляем таймер
  }
}

long tmr;
void tickServer()
{
  // Client cl = server.available();
  if (client == null) {
    client = new Client(this, "192.168.1.182", 5000);
    if (client.active())
    {
      sendInit(client);
    }
  }
  //if (client == null && cl != null)
  //{
  //  print("new client!  ");
  //  println(cl.ip());
  //  client = cl;
  //}
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
      buf[15] |= 0;

      client.write(buf);
      println("sended");

      tmr = millis();
    }
  }
}


void sendInit(Client client)
{

  byte [] buf = new byte[10];
  buf[0] = 10;
  buf[1] = 4;
  buf[2] = 0;
  buf[3] = 6;
  buf[4] = 4;
  buf[5] = 10;
  buf[6] = 0;
  buf[7] = 5;
  buf[8] = 0;
  buf[9] = 12;

  client.write(buf);
  println("sended initial answer");
  //  byte [] buf = new byte[10];
  buf[0] = 10;
  buf[1] = 3;
  buf[2] = 0;
  buf[3] = 6;
  buf[4] = 4;
  buf[5] = 10;
  buf[6] = 0;
  buf[7] = 5;
  buf[8] = 0;
  buf[9] = 12;

  client.write(buf);
  println("sended initial message");
}

void receive( byte[] data, String ip, int port ) {  // <-- extended handler
  
  
  // get the "real" message =
  // forget the ";\n" at the end <-- !!! only for a communication with Pd !!!
  println(data);

  String message = new String( data );
  
  // print the result
  println( "receive: \""+message+"\" from "+ip+" on port "+port );
}

void setup()
{
  //udp = new UDP(this, 6000);
  //udp.listen( true );
  client = new Client(this, "192.168.1.174", 5000);
  
  if (client.active()) sendInit(client);
  
  //server = new Server(this, 5000);
  //  //println(server.ip());
  //    // udp = new UDP(this, 8888);
  //     print("create");
  //     udp.broadcast(true);
  //     println( "init as multicast socket ... "+udp.isMulticast() );
  //     println( "joins a multicast group  ... "+udp.isJoined() );
}

void draw()
{
 // sendAll();
  //tickServer();
}

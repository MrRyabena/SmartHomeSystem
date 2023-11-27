#include "mainwindow.h"

#include <QApplication>
#include <QDateTime>
#include <QThread>

#include <stdint.h>

#include "tcpclient.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    TCPclient tcp;

    tcp.begin(108, "192.168.1.4", 50000);
    tcp.connect("192.168.1.4", 50000);
    time_t time = 0;
    for(;;) {
        tcp.checkData();
        if (QDateTime::currentDateTime().toTime_t() - time >= 5) {
        shs::ByteCollector col(1);
        col.add("Hi, server!");
        tcp.sendPacket(&col, 104);
        time = QDateTime::currentDateTime().toTime_t();
        qDebug() << "send";
        }
    }




    w.show();
    return a.exec();
}

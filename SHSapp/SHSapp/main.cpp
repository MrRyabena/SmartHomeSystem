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

    tcp.begin(108, "192.168.1.4", 80);
    tcp.connect("192.168.1.4", 80);
    for(;;) {
        tcp.checkData();
    }




    w.show();
    return a.exec();
}

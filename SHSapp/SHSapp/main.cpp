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
    QThread *thread = new QThread();

    //tcp.begin();
    tcp.moveToThread(thread);


    w.show();
    return a.exec();
}

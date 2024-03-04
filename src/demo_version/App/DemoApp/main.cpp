#include "mainwindow.h"
#include <QApplication>
#include <QDateTime>
#include <QThread>

#include <stdint.h>

#include "TCPstream.h"
#include <QApplication>

#include "../../../SHScore/SHSByteCollector.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    qDTP dtp(&w, w.socket);
    dtp.setup();
    w.d = &dtp.dtp;

    w.show();


    return a.exec();
}

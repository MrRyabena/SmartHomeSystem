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

    qDTP dtp(&w);
    dtp.setup();
    dtp.start();


    w.show();




    return a.exec();
}
